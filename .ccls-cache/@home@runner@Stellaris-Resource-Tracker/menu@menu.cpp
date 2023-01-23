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