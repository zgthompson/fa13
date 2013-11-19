#include "VectorAnimator.h"

VectorAnimator::VectorAnimator(int imgWidth, int imgHeight, int vectorSize) {
    width = imgWidth;
    height = imgHeight;
    size = vectorSize;
    frames = 0;
    v_offset = (imgHeight - (7 * vectorSize)) / 2;
    h_step = (imgWidth * .8) / vectorSize;
}

void VectorAnimator::addFrame(std::vector<int> v) {
    BMP frame;
    frame.SetBitDepth(1);
    frame.SetSize(width, height);

    for (int i = 0; i < v.size(); ++i) {
        addRow(frame, i, v[i]);
    }

    frames++;
    frame.WriteToFile("frame.bmp");
}

void VectorAnimator::addRow(BMP& frame, int row, int value) {
    int minWidth, maxWidth, minHeight, maxHeight;
    calcWidth(value, minWidth, maxWidth);
    calcHeight(row, minHeight, maxHeight);

    for (int x = minWidth; x < maxWidth; ++x) {
        for (int y = minHeight; y < maxHeight; ++y) {
            frame(x,y)->Red = 0;
            frame(x,y)->Green = 0;
            frame(x,y)->Blue = 0;
        }
    }
}

void VectorAnimator::calcHeight(int row, int& min, int& max) {
    min = v_offset + (row * 7) + 2;
    max = min + 3;
}

void VectorAnimator::calcWidth(int value, int& min, int& max) {
    min = (width - (value * h_step)) / 2;
    max = min + (value * h_step);
}


