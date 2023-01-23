#ifndef JOB_HPP
#define JOB_HPP

#include <string>

#include "jobcategory.hpp"
#include "modifier.hpp"
#include "../resources/resources.hpp"

namespace srt {

class Job {
public:
    Job() = delete;
    Job( std::string, std::string, std::string, uint number = 1 );

    std::string getName();
    std::string getCategory();
    std::string getStratum();
    uint getNumber();
    uint getFilled();

    void setCategory( std::string );
    void setStratum( std::string );
    void setNumber( uint );
    void setFilled( uint );

    void fill();
    void vacate();

    const ResourceContainer  & getProduction();
    const ModifierContainer & getModifiers();
    const ResourceContainer  & getUpkeep();

    
    void addProduction( Resource );
    void delProduction( Resource );
    Resource getProduction( Resource );
    Resource getProduction( std::string );

    void addModifiers( Modifier );
    void delModifiers( Modifier );
    Resource getModifiers( Modifier );
    Resource getModifiers( std::string );

    void addUpkeep( Resource );
    void delUpkeep( Resource );
    Resource getUpkeep( Resource );
    Resource getUpkeep( std::string );

private:
    std::string name;
    std::string category;
    std::string stratum;
    uint number;
    uint filled;
    ResourceContainer production;
    ModifierContainer modifiers;
    ResourceContainer upkeep;
    

};
}
#endif