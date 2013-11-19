#include "VectorAnimator.h"
#include "EasyBMP.h"
#include <iostream>
#include <vector>
#include <algorithm>

int VECTOR_SIZE = 100;
int FRAME_WIDTH = 1024;
int FRAME_HEIGHT = 768;

int main(void) {
    std::vector<int> v(VECTOR_SIZE);

    for (int i = 1; i <= v.size(); ++i) {
        v[i] = i;
    }

    std::random_shuffle( v.begin(), v.end() );

    VectorAnimator va(FRAME_WIDTH, FRAME_HEIGHT, v.size());
    for (int i = 0; i < 1000; i++) {
        std::cout << i << std::endl;
        va.addFrame(v);
    }
}
