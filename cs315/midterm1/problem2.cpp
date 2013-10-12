#include <iostream>

int f(int n) {
    int count;
    for (int j = 7; j < 3 * n; j += 3) {
        count = 0;
        for (int k = j + 1; k < 4 * n; k += 2) {
            count++;
        }
        std::cout << count << " ";
    }
}

int main(void) {
    f(141);
}
