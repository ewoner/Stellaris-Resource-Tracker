#include "job.hpp"
namespace srt {

Job::Job( std::string name, std::string category, std::string stratum, uint number ) 
    : name{ name },  category { category }, stratum { stratum }, number { number }, filled { 0 }
{ }

std::string Job::getName() {
    return this->name;
}
std::string Job::getCategory(){
    return this->category;
}
std::string Job::getStratum(){
    return this->stratum;
}
uint Job::getNumber(){
    return this->number;
}
uint Job::getFilled(){
    return this->filled;
}

void Job::setCategory( std::string category ){
    this->category = category;
}
void Job::setStratum( std::string stratum ) {
    this->stratum = stratum;
}
void Job::setNumber( uint number ){
    this->number = number;
}
void Job::setFilled( uint filled ) {
    this->filled = filled;
}

void Job::fill() {
    if ( this->filled < this->number ){
        this->filled ++;
    }
}
void Job::vacate(){
    if ( this->filled != 0 ) {
        this->filled --;
    }
}

const ResourceContainer  & Job::getProduction(){
    return this->production;
}

const ModifierContainer  & Job::getModifiers() {
    return this->modifiers;
}
const ResourceContainer  & Job::getUpkeep() {
    return this->upkeep;
}


void Job::addProduction( Resource ) {}
void Job::delProduction( Resource ) {}
Resource Job::getProduction( Resource ) {}
Resource Job::getProduction( std::string ){}

void Job::addModifiers( Modifier ){}
void Job::delModifiers( Modifier ){}
Resource Job::getModifiers( Modifier ){}
Resource Job::getModifiers( std::string ){}

void Job::addUpkeep( Resource ){}
void Job::delUpkeep( Resource ){}
Resource Job::getUpkeep( Resource ){}
Resource Job::getUpkeep( std::string ){}

}//namespace