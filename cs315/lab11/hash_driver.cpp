#include <iostream>
#include "OpenHash.h"
#include "ClosedHash.h"

int main(void) {
    OpenHash oh;
    ClosedHash ch;

    ch.insert("one");
    ch.insert("two");
    ch.insert("three");
    ch.remove("two");

    std::cout << "contains one: " << ch.contains("one") << std::endl;
    std::cout << "contains two: " << ch.contains("two") << std::endl;
    std::cout << "contains four: " << ch.contains("four") << std::endl;

}
