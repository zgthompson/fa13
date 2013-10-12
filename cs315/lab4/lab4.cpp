#include <iostream>
#include "intSLList.h"

int main(int argc, const char* argv[]) {
    int n, p, q;
    IntSLList *factorialList, *expList1, *expList2, *tempList;

    std::cout << "Problem 1: Enter an integer n, 1 <= n <= 9999:" << std::endl;
    std::cin >> n;
    std::cout << "Factorial of " << n << " is" << std::endl;

    tempList = new IntSLList();

    factorialList = tempList -> factorial(n);

    factorialList -> printList();
    std::cout << std::endl;

    std::cout << "Problem 2: Enter two integers p and q, 1 <= p, q <= 9999:"
        << std::endl;

    std::cin >> p >> q;

    std::cout << "2^p + 3^q is" << std::endl;

    expList1 = tempList -> exponent(2, p);
    expList2 = tempList -> exponent(3, q);

    delete tempList;
    tempList = expList1 -> add(expList2);

    tempList -> printList();
    std::cout << std::endl;
}
