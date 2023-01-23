#ifndef SHORLIST_HPP
#define SHORLIST_HPP

#include <string>

namespace ewoner {
namespace utilities {

template <typename T>
class ShortList {
public:
    void push(T);
    T pop();
    uint size();

private:
    uint sizeCount = 0;
    class Node {
        Node * next = nullptr;
        T value;
    };
    Node * head = nullptr;
    

};
}
}
#endif