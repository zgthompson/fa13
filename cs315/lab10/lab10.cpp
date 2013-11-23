#include "ArrayAnimator.h"
#include "CallbackArray.h"
#include "EasyBMP.h"
#include <iostream>
#include <algorithm>

int ARRAY_SIZE = 5;
int FRAME_WIDTH = 1024;
int FRAME_HEIGHT = 768;

int main(void) {
    ArrayAnimator<int> animator(FRAME_WIDTH, FRAME_HEIGHT, ARRAY_SIZE);
    CallbackArray<int> array(ARRAY_SIZE, &animator);

    for (int i = 0; i < array.size(); ++i) {
        array[i] = i+1;
    }

    animator.loadFirstFrame(array);
    animator.callbackOn();

    std::random_shuffle( array.begin(), array.end() );

    for (int i = 0; i < array.size(); ++i) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
}
