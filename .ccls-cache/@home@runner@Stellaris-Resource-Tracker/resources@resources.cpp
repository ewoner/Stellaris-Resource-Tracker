#include "resources.hpp"
namespace srt {

Resource::Resource( std::string name ) 
    : Resource( name, 0.0, 0.0 ) 
{}
Resource::Resource( std::string name, double amount )
    : Resource(name, amount, amount)
{}
Resource::Resource( std::string name, double amount, double base )
    : name{name}, amount{ amount }, base {base}
{}

std::string Resource::getName() {
    return this->name;
}
double Resource::add( double addAmount ) {
    this->amount += addAmount;
    return amount;
}
double Resource::subtract ( double subAmount ){
    this->amount -= subAmount;
    return amount;
}
double Resource::newAmount( double newAmount ) {
    this->amount = newAmount;
    return this->amount;
}
double Resource::getAmount() {
    return this->amount;
}

void Resource::setName( std::string name ) {
    this->name = name;
}

double Resource::getBase() {
    return this->base;
}
void Resource::setBase( double base ) {
    this->base = base;
}

} //namespace