#include <iostream>
#include "intSLList.h"
#include <sys/time.h>

double get_wall_time(){
    struct timeval time;
    if (gettimeofday(&time,NULL)){
        //  Handle error
        return 0;
    }
    return (double)time.tv_sec + (double)time.tv_usec * .000001;
}
double get_cpu_time(){
    return (double)clock() / CLOCKS_PER_SEC;
}

long exp1(long x, int n) {
    if (n == 0) return 1.0;
    else if (n % 2 == 0) return exp1(x * x, n/2);
    else return x * exp1(x, (n-1)/2) * exp1(x, (n-1)/2);
}

long exp2(long x, int n) {
    if (n == 0) return 1.0;
    else if (n % 2 == 0) return exp2(x * x, n/2);
    else return x * exp2(x * x, (n-1) / 2);
}

int C(int n, int m, int &ctr) {
    if (m > n) return 0;
    else if (m == n || m == 0) return 1;
    else {
        ctr += 2;
        return C(n-1, m, ctr) + C(n-1, m-1, ctr);
    }
}

float f(int n) {
    if (n == 1) return 1.0;
    else if (n % 2 == 0) return 1.0 / n + f(n-1);
    else return -1.0 / n + f(n-1);
}

int main(void) {
//    int ctr = 0;
//    std::cout << "C(10, 5) " << C(10,5, ctr) << std::endl;
//    ctr = 0;
//    std::cout << "C(9, 5) " << C(9,5, ctr) << std::endl;
//    ctr = 0;
//    std::cout << "C(9, 4) " << C(9,4, ctr) << std::endl;
//    ctr = 0;
//    std::cout << "C(8, 4) " << C(8,4, ctr) << std::endl;
//    ctr = 0;
//    std::cout << "C(8, 5) " << C(8,5, ctr) << std::endl;
//    ctr = 0;

    //std::cout << "f(5) = " << f(5) << std::endl;
    IntSLList *list1, *list2, *list3;
    double wall0, wall1, cpu0, cpu1;

    list1 = new IntSLList();
    list1 -> addToHead(12345);

    wall0 = get_wall_time();
   cpu0 = get_cpu_time();

    IntSLList::exp(list1, 12345) -> printList();
    std::cout << std::endl;

    wall1 = get_wall_time();
    cpu1 = get_cpu_time();

    std::cout << "Recursive implementation of 12345^12345:\n";
    std::cout << "Wall Time = " << wall1 - wall0 << std::endl;
    std::cout << "CPU Time  = " << cpu1  - cpu0  << std::endl;

    wall0 = get_wall_time();
    cpu0 = get_cpu_time();

    IntSLList::exponent(12345, 12345) -> printList();
    std::cout << std::endl;

    wall1 = get_wall_time();
    cpu1 = get_cpu_time();
    std::cout << "Iterative implementation of 12345^12345:\n";
    std::cout << "Wall Time = " << wall1 - wall0 << std::endl;
    std::cout << "CPU Time  = " << cpu1  - cpu0  << std::endl;
//
//    int ctr;
//    ctr = 0;
//    C(10, 5, ctr);
//    std::cout << "ctr = " << ctr << std::endl;
//    ctr = 0;
//    C(9, 5, ctr);
//    std::cout << "ctr = " << ctr << std::endl;
//    ctr = 0;
//    C(8, 5, ctr);
//    std::cout << "ctr = " << ctr << std::endl;
//    ctr = 0;
//    C(7, 5, ctr);
//    std::cout << "ctr = " << ctr << std::endl;
//    ctr = 0;
//    C(6, 5, ctr);
//    std::cout << "ctr = " << ctr << std::endl;
    //std::cout << "4^2 = " << exp1(4, 2) << std::endl;
    //std::cout << "4^2 = " << exp2(4, 2) << std::endl;
    //std::cout << "10^4 = " << exp1(10, 4) << std::endl;
    //std::cout << "10^4 = " << exp2(10, 4) << std::endl;
    //std::cout << "2^51 = " << exp1(2, 51) << std::endl;
    //std::cout << "2^51 = " << exp2(2, 51) << std::endl;

}
