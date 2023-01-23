#include <iostream>
#include <string>

#include "./Menu/test.cpp"
#import "resources/resources.hpp"

using namespace srt;

void test_resource();

int main1( void ) {
   
}
void test_resource() {
    std::string testString {"Metal"};
    double amount = 1.5, base = 4.1, added = 2.4, subtracted = 1.5;
    std::cout << std::boolalpha;
    std::cout << "Constructors....\n";
    Resource test{"Metal"};
    std::cout << "Resource(\"Metal\") -- " << ( test.getName() == testString and test.getAmount() == 0.0 and test.getBase() == 0.0 ) << std::endl;
    testString = "Silver";
    test = Resource{ testString, amount };
    std::cout << "Resource(\"Silver,1.5\") -- " << ( test.getName() == testString and test.getAmount() == amount and test.getBase() == amount ) << std::endl;
    testString = "Gold";
    test = Resource{ testString, amount, base };
    std::cout << "Resource(\"Gold,1.5,4.1\") -- " << ( test.getName() == testString and test.getAmount() == amount and test.getBase() == base ) << std::endl;
    std::cout << "\nAdjusting amount and base....\n";
    test.add(added);
    std::cout << "Resource.add( 2.4 ) -- " << ( test.getAmount() == amount + added ) << std::endl;
    test = Resource{ testString, amount, base };
    test.subtract( subtracted );
    std::cout << "Resource.subtract( 1.5 ) -- " << ( test.getAmount() == amount - subtracted ) << std::endl;
    test = Resource{ testString, amount, base };
    test.newAmount( added + subtracted );
    std::cout << "Resource.newAmount( 3.9 ) -- " << ( test.getAmount() == added + subtracted ) << std::endl;
    test = Resource{ testString, amount };
    test.setBase( amount + subtracted );
    std::cout << "Resource.setBase( 3.0 ) -- " << ( test.getBase() == amount + subtracted ) << std::endl;
}