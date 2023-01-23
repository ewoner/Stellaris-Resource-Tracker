#ifndef MODIFIER_HPP
#define MODIFIER_HPP

#include <string>
#include <vector>

namespace srt {

class Modifier;

typedef  std::vector<Modifier> ModifierContainer;

class Modifier {
public:
    std::string getName();
    void setName( std::string );
    double getModifier();
    void setModifier( double );


private:
    std::string name{"None"};
    double modifier = 0.0;

};
}//namespace
#endif