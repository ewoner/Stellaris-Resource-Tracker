#ifndef JOB_HPP
#define JOB_HPP

#include <string>
namespace srt {

class Job {
public:
    Job() = delete;
    Job(std::string name ): name{name} {}

    std::string getName() { return name;}
    std::string getCategory() { std::string rv = "None"; if (this->category) {rv= category->getName();} return rv;}

private:
    std::string name;
    JobCategory * category = nullptr;

};
}
#endif