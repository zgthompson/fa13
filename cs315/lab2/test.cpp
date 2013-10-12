#include <iostream>

int main(int argc, const char* argv[]) {
    int count = 0;
    for (int j = 1; j < 100; j++) {
        for (int k = j + 1; k < 100; ++k) {
            count++;
        }
    }

    std::cout << count;
}
