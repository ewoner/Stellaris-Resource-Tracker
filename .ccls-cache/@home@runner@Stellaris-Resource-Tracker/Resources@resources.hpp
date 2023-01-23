#ifndef RESOURCES_HPP
#define RESOURCES_HPP

#include <string>

namespace srt {

class Resource {
public:
    Resource() = delete;
    Resource( std::string );
    Resource( std::string, double amount );

    std::string getName();
    double addAmount( double );
    double subtractAmount ( double );
    double newAmount( double );
    double getAmount();
private:
    void setName( std::string );
    std::string name;
    double amount = 0.0;

};
class ResourceStat : public Resource {
public:
    double getModified();
    double addModifier( double) ;
    double removeModifier( double );
    double addToBase( double );
private:
    double modified = this->getAmount();

};
class ResourceNode : public Resource {
public:
    ResourceNode() = delete;
    ResourceNode( std::string );
    ResourceNode( std::string, double );

    ResourceNode* getNext();
    ResourceNode* setNext( Resource );
    ResourceNode* delNext( );
private:
    ResourceNode * next;

};

} //namespace

#endif