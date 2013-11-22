#ifndef VECTOR_ANIMATOR_H
#define VECTOR_ANIMATOR_H

#include <vector>
#include "EasyBMP.h"

class VectorAnimator {
    public:
        VectorAnimator(int imgWidth, int imgHeight, int vectorSize);
        void addFrame(std::vector<int> v);

    private:
        int width, height, size, frames, v_offset, h_step;
        void addRow(BMP& frame, int value, int row);
        void calcWidth(int value, int& min, int& max);
        void calcHeight(int row, int& min, int& max);
};

#endif
