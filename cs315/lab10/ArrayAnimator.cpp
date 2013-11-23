#include "ArrayAnimator.h"
#include <string>
#include <boost/lexical_cast.hpp>

template<class T>
ArrayAnimator<T>::ArrayAnimator(int imgWidth, int imgHeight, int vectorSize) {
    callback = false;
    width = imgWidth;
    height = imgHeight;
    size = vectorSize;
    frames = 0;
    v_offset = (imgHeight - (7 * vectorSize)) / 2;
    h_step = (imgWidth * .8) / vectorSize;
}

template<class T>
void ArrayAnimator<T>::addFrame() {
    frames++;
    std::string filename = "frame" + boost::lexical_cast<std::string>(++frames) + ".bmp";
    frame.WriteToFile(filename.c_str());
}

template<class T>
void ArrayAnimator<T>::updateRow(BMP& frame, int row, int value) {
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

template<class T>
void ArrayAnimator<T>::calcHeight(int row, int& min, int& max) {
    min = v_offset + (row * 7) + 2;
    max = min + 3;
}

template<class T>
void ArrayAnimator<T>::calcWidth(int value, int& min, int& max) {
    min = (width - (value * h_step)) / 2;
    max = min + (value * h_step);
}

template<class T>
void ArrayAnimator<T>::onUpdate(int index, const T& value) {
    if (callback) {
        updateRow(index, int(value));
        addFrame();
    }
}

template<class T>
void ArrayAnimator<T>::loadFirstFrame(CallbackArray<T> array) {
    frame.SetBitDepth(1);
    frame.SetSize(width, height);

    for (int i = 0; i < array.size(); ++i) {
        updateRow(i, int(array[i]));
    }

    addFrame();
}
