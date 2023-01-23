#ifndef RESOURCES_HPP
#define RESOURCES_HPP

#include <string>
#include <vector>

namespace srt {

class Resource;

typedef std::vector<Resource> ResourceContainer;

class Resource {
public:
    Resource() = delete;
    Resource( std::string );
    Resource( std::string, double );
    Resource( std::string, double, double );

    std::string getName();
    double add( double );
    double subtract ( double );
    double newAmount( double );
    double getAmount();
    double getBase();
    void setBase( double );
private:
    void setName( std::string );
    std::string name{ "None" };
    double base = 0.0;
    double amount = 0.0;

};

} //namespace

#endif