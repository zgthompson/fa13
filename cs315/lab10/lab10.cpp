#include "ArrayAnimator.h"
#include "CallbackArray.h"
#include "EasyBMP.h"
#include <iostream>
#include <algorithm>

int ARRAY_SIZE = 30;
int FRAME_WIDTH = 300;
int FRAME_HEIGHT = 300;

int main(void) {
    ArrayAnimator<int> animator(FRAME_WIDTH, FRAME_HEIGHT, ARRAY_SIZE);
    CallbackArray<int> array(ARRAY_SIZE, &animator);

    for (int i = 0; i < array.size(); ++i) {
        array[i] = i+1;
    }

    std::random_shuffle( array.begin(), array.end() );

    animator.loadFirstFrame(array);

    animator.addPadding();

    animator.callbackOn();

    std::make_heap( array.begin(), array.end() );
    
    for (int i = 0; i < ARRAY_SIZE; i++) {
        std::pop_heap( array.begin(), array.end() - i);
    }

    animator.addPadding();

    animator.printComparisions();
}
