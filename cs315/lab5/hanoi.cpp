#include <iostream>

void hanoi(int n, int from, int mid, int to) {
    if (n==1) {
        std::cout << "move disk " << n << " from " << from << " to " << to << std::endl;
    }
    else {
        hanoi(n-1, from, to, mid);
        std::cout << "move disk " << n << " from " << from << " to " << to << std::endl;
        hanoi(n-1, mid, from, to);
    }
}

int main(void) {
    hanoi(8, 1, 2, 3);
}
