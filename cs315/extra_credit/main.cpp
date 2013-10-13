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

int main(void) {
    /*
    IntSLList *list1 = new IntSLList();
    list1 -> addToHead(12345678);
    list1 -> addToHead(12345678);
    list1 -> addToHead(12345678);
    
    (list1 -> kmult(list1)) -> printList();
    std::cout << std::endl;
    */


    IntSLList *list1, *list2, *list3;
    double wall0, wall1, cpu0, cpu1;

    list1 = new IntSLList();
    list1 -> addToHead(12345);

    wall0 = get_wall_time();
   cpu0 = get_cpu_time();

    list2 = IntSLList::exp(list1, 12345);
    std::cout << std::endl;

    wall1 = get_wall_time();
    cpu1 = get_cpu_time();

    std::cout << "Recursive implementation of 12345^12345:\n";
    std::cout << "Wall Time = " << wall1 - wall0 << std::endl;
    std::cout << "CPU Time  = " << cpu1  - cpu0  << std::endl;

    wall0 = get_wall_time();
    cpu0 = get_cpu_time();

    list3 = IntSLList::kexp(list1, 12345);
    std::cout << std::endl;

    wall1 = get_wall_time();
    cpu1 = get_cpu_time();
    std::cout << "Karatsuba mult implementation of 12345^12345:\n";
    std::cout << "Wall Time = " << wall1 - wall0 << std::endl;
    std::cout << "CPU Time  = " << cpu1  - cpu0  << std::endl;

    std::cout << "Lists are equal: " << IntSLList::equal(list2, list3) << std::endl;
}
