#include "modifier.hpp"
namespace srt { 

inline std::string Modifier::getName() {
    return this->name;
}

inline void Modifier::setName( std::string name ) {
        this->name = name;
    }
inline double Modifier::getModifier() {
    return this->modifier;
}
inline void Modifier::setModifier( double modifier ) {
    this->modifier = modifier;
}

}//namespace