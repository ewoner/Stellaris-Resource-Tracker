#ifndef JOBCATEGORY_HPP
#define JOBCATEGORY_HPP

#include <string>
namespace srt {
class JobCategory;
class JobCategory {
public:
    JobCategory() = delete;
    JobCategory(std::string category ): category{category} {}

    std::string getName() { return category;}
    std::string getParentName() { std::string rv = "None"; if (this->parent) {rv= parent->getName();} return rv;}

private:
    std::string category;
    JobCategory * parent = nullptr;

};
}
#endif