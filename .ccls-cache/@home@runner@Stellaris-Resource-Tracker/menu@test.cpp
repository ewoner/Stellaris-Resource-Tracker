#include <iostream>
#include <any>
#include <string>
#include <variant>
#include <vector>
#include <type_traits>
#include <optional>
#include <sstream>
#include <limits>
#include <cctype>


// Removes leading and trailing white-space chars from string s
// s - string to use (not changed)
// returns updated string

inline std::string trim(const std::string& s)
{
	constexpr char whitespace[] = " \t\n\r";
	const size_t first = s.find_first_not_of(whitespace);

	return (first != std::string::npos) ? s.substr(first, (s.find_last_not_of(whitespace) - first + 1)) : std::string {};
}


// Converts a text number to specified type. All of the text must be a valid number of the specified type. eg 63q is invalid
// Defaults to type int
// st - string to convert
// returns either value of converted number or no value if text number cannot be converted

template<typename T = int>
bool startsWithDigit(const std::string& s)
{
    if (s.empty())
        return false;
        
    if (std::isdigit(s.front()))
        return true;
        
    return (((std::is_signed<T>::value && (s.front() == '-')) || (s.front() == '+'))
                && ((s.size() > 1) && std::isdigit(s[1])));
}

template<typename T = int>
std::optional<T> stonum(const std::string& st)
{
	const auto s = trim(st);
	//bool ok = s.empty() ? false : (std::isdigit(s.front()) || (((std::is_signed<T>::value && (s.front() == '-')) || (s.front() == '+')) && ((s.size() > 1) && std::isdigit(s[1]))));
	bool ok = startsWithDigit<T>(s);

	auto v = T {};

	if (ok) {
		std::istringstream ss(s);

		ss >> v;
		ok = (ss.peek() == EOF);
	}

	return ok ? v : std::optional<T> {};
}


// Obtain a line of text from specified stream. Removes any existing data from input buffer
// is - input stream
// def - optional default text if no text entered
// returns either valid input line or no value if problem obtaining input

std::optional<std::string> getline(std::istream& is, const std::string& def = "")
{
	for (auto no = is.rdbuf()->in_avail(); no && is && std::isspace(is.peek()); is.ignore(), --no);

	std::string ln;

	return std::getline(is, ln) ? (ln.empty() && !def.empty() ? def : ln) : (is.clear(), std::optional<std::string> {});
}


// Obtain a line of text from console. First displays prompt text. If default text provided display within [..] after prompt
// prm - optional prompt text to display first
// def - optional default text if no text entered
// returns entered text as type string. No error conditions. Only returns when valid data entered

auto getline(const std::string& prm = "", const std::string& def = "")
{
	std::optional<std::string> o;

	do {
		std::cout << prm;
		if (!def.empty())
			std::cout << " [" << def << "]";

		std::cout << " :";
		o = getline(std::cin, def);
	} while (!o.has_value() && (std::cout << "Invalid input" << std::endl));

	return *o;
}


// Extract next item of data from specified stream. Data must terminate with a white-space char
// Defaults to type string. Note extraction for string stops at white-space char
// is - stream from which to extract data
// returns either valid extracted data or no value if problem extracting data

template<typename T = std::string>
std::optional<T> getdata(std::istream& is)
{
	auto i = T {};
	const bool b = (is >> i) && std::isspace(is.peek());

	for (is.clear(); is && !std::isspace(is.peek()); is.ignore());
	return b ? i : std::optional<T> {};
}


// Obtains a number from specified stream in specified type
// Default of number type is int
// is - stream from which to obtain number
// wholeline - true if only one number per line (default), false if can have multiple numbers per line.
// returns either valid number of required type or no value if problem extracting data

template<typename T = int>
auto getnum(std::istream& is, bool wholeline = true)
{
	if (wholeline) {
		const auto o = getline(is);
		return o.has_value() ? stonum<T>(*o) : std::optional<T> {};
	}

	return getdata<T>(is);
}


// Obtains a number from the console. First displays prompt text
// If specified, number must be within the specified min..max range and range displayed as (...) after prm
// prm - optional prompt text to display first
// nmin - optional minimum valid value
// nmax - optional maximum valid value
// wholeline - true if only one number per line (default), false if can have multiple numbers per line
// returns valid number of required type. No error conditions. Only returns when valid number entered

template <typename T = int>
auto getnum(const std::string& prm = "", T nmin = std::numeric_limits<T>::lowest(), T nmax = std::numeric_limits<T>::max(), bool wholeline = true)
{
	const auto showdefs = [nmin, nmax]() {
		std::cout << " (";

		if (nmin != std::numeric_limits<T>::lowest() || std::is_unsigned<T>::value)
			std::cout << nmin;

		std::cout << " - ";

		if (nmax != std::numeric_limits<T>::max())
			std::cout << nmax;

		std::cout << ")";
	};

	std::optional<T> o;

	do {
		std::cout << prm;

		if ((nmin != std::numeric_limits<T>::lowest()) || (nmax != std::numeric_limits<T>::max()))
			showdefs();

		std::cout << " :";
		o = getnum<T>(std::cin, wholeline);
	} while ((!o.has_value() || (((*o < nmin) || (*o > nmax)))) && (std::cout << "Invalid input" << std::endl));

	return *o;
}


// Obtains a char from the specified stream
// is - stream from which to obtain number
// def - default char to return if no character obtained
// wholeline - true if only one char per line (default), false if can have multiple chars per line
// returns either valid character or no value if problem extracting data

std::optional<char> getchr(std::istream& is, char def = 0, bool wholeline = true)
{
	if (wholeline)
		if (auto o = getline(is); o.has_value())
			return (o->empty() && def ? def : ((o->size() == 1) ? o->front() : std::optional<char> {}));
		else
			return {};

	return getdata<char>(is);
}


// Obtains a char from the console. First displays prompt text
// prm - optional prompt text to display first
// valid - optional string containing valid values for the char. Displayed within (...)
// def - optional default char to use if none entered. Displayed within [...]
// wholeline - true if only one char per line (default), false if can have multiple chars per line
// returns valid char. No error conditions. Only returns when valid char entered

auto getchr(const std::string& prm = "", const std::string& valid = "", char def = 0, bool wholeline = true)
{
	const auto showopt = [&valid, def]() {
		std::cout << " (";

		for (size_t i = 0, s = valid.size(); i < s; ++i)
			std::cout << (i ? "/" : "") << valid[i];

		if (std::cout << ")"; def)
			std::cout << " [" << def << "]";
	};

	std::optional<char> o;

	do {
		if (std::cout << prm; !valid.empty())
			showopt();

		std::cout << " :";
		o = getchr(std::cin, def, wholeline);
	} while ((!o.has_value() || ((!valid.empty()) && (valid.find(*o) == std::string::npos))) && (std::cout << "Invalid input" << std::endl));

	return *o;
}


class Menu {
private:
	using f_type = void(*)(std::any& param);

	struct MenItm
	{
		std::string name;
		std::variant<f_type, Menu*> func;
	};

	using vmi = std::vector<MenItm>;

public:
	Menu() {}
	Menu(const std::string& t, const vmi& vm) : stitle(t), mitems(vm) {}

	auto title() const noexcept
	{
		return stitle;
	}

	void title(const std::string& t)
	{
		stitle = t;
	}

	void menu(std::any& param)
	{
		menu(*this, param);
	}

	bool erase(size_t indx)
	{
		if (indx < mitems.size()) {
			mitems.erase(mitems.begin() + indx);
			return true;
		}

		return false;
	}

	bool append(const MenItm& mi)
	{
		mitems.emplace_back(mi);
		return true;
	}

	bool insert(size_t indx, const MenItm& mi)
	{
		if (indx < mitems.size()) {
			mitems.insert(mitems.begin() + indx, mi);
			return true;
		}

		return false;
	}

private:
	class RunVisitor
	{
	public:
		RunVisitor(std::any& par) : param(par) {}

		void operator()(f_type func) { func(param); }
		void operator()(Menu* menu) { Menu::menu(*menu, param); }

	private:
		std::any& param;
	};

	static void menu(const Menu& m, std::any& param)
	{
		const static auto show = [](const Menu& mu) {
			std::ostringstream oss;
			const auto nom = mu.mitems.size();

			oss << '\n' << mu.title() << "\n\n";

			for (size_t i = 0U; i < nom; ++i)
				oss << i + 1 << ")  " << mu.mitems[i].name << '\n';

			oss << "0)  Exit menu\n\nEnter menu option number";
			return getnum<size_t>(oss.str(), 0, nom);
		};


		for (size_t opt = 0U; (opt = show(m)) > 0; )
			/*
			if (const auto& mi = m.mitems[opt - 1]; std::holds_alternative<Menu::f_type>(mi.func))
				std::get<Menu::f_type>(mi.func)(param);
			else
				menu(*std::get<Menu*>(mi.func), param);
			*/

			std::visit(RunVisitor(param), m.mitems[opt - 1].func);
	}

	std::string stitle;
	vmi mitems;
};


using namespace std;
using Params = vector<variant<size_t, int, double, char, string>>;

void f1(any& param)
{
	auto& v = any_cast<Params&>(param);

	v.push_back(getnum<size_t>("Enter a pos integer"));
}

void f2(any& param)
{
	auto& v = any_cast<Params&>(param);

	v.push_back(getnum<double>("Enter a real"));
}

void f6(any& param)
{
	auto& v = any_cast<Params&>(param);

	v.push_back(getnum<double>("Enter a real between", 5.5, 50.5));
}

void f3(any& param)
{
	auto& v = any_cast<Params&>(param);

	v.push_back(getchr("Enter a char"));
}

void f7(any& param)
{
	auto& v = any_cast<Params&>(param);

	v.push_back(getchr("Enter a vowel", "aeiou", 'a'));

}
void f4(any& param)
{
	auto& v = any_cast<Params&>(param);

	v.push_back(getline("Enter text"));
}

void f51(any& param)
{
	const static auto proc = [](const auto& val) {cout << val << endl; };

	auto& v = any_cast<Params&>(param);

	cout << "Entered data is\n";

	for (const auto& d : v)
		visit(proc, d);
}

void f5(any& param)
{
	auto& v = any_cast<Params&>(param);

	cout << "Entered data is\n";

	for (const auto& d : v)
		if (auto pvi = get_if<int>(&d))
			cout << *pvi << endl;
		else
			if (auto pvd = get_if<double>(&d))
				cout << *pvd << endl;
			else
				if (auto pvc = get_if<char>(&d))
					cout << *pvc << endl;
				else
					if (auto pvs = get_if<string>(&d))
						cout << *pvs << endl;
					else
						if (auto pvu = get_if<size_t>(&d))
							cout << *pvu << endl;
						else
							cout << "Unknown type" << endl;
}

int main()
{
	Menu m3 {"Text data"s, {{"Char"s, f3}, {"Vowel", f7}, {"Text"s, f4}}};
	Menu m2 {"Numeric data"s, {{"Integer"s, f1}, {"Real"s, f2}, {"Real Range", f6}}};
	Menu m1 {"Data maintenance"s, {{"Numeric", &m2}, {"Text"s, &m3}, {"Display"s, /*f5*/ f51}}};

	any param = Params {};

	m1.menu(param);
}
