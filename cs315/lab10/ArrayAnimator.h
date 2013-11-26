#ifndef ARRAY_ANIMATOR_H
#define ARRAY_ANIMATOR_H

#include "EasyBMP.h"
#include "CallbackArray.h"
#include <string>
#include <iomanip>
#include <sstream>

template<class T>
class ArrayAnimator : public ArrayCallback<T> {
    public:
        ArrayAnimator(int imgWidth, int imgHeight, int vectorSize);
        void addFrame();
        void loadFirstFrame(CallbackArray<T>& array);
        void callbackOn() { callback = true; }
        void callbackOff() { callback = false; }
        void onUpdate(int index, const T& value);
        void addPadding();

    private:
        BMP frame;
        int width, height, size, frames, v_offset, h_step;
        bool callback;
        void updateRow(int value, int row);
        void calcWidth(int value, int& min, int& max);
        void calcHeight(int row, int& min, int& max);
};

template<class T>
ArrayAnimator<T>::ArrayAnimator(int imgWidth, int imgHeight, int vectorSize) {
    callback = false;
    width = imgWidth;
    height = imgHeight;
    size = vectorSize;
    frames = 0;
    v_offset = (imgHeight - (7 * vectorSize)) / 2;
    h_step = imgWidth  / vectorSize;
}

template<class T>
void ArrayAnimator<T>::addFrame() {
    std::ostringstream ss;
    ss << std::setw(3) << std::setfill('0') << ++frames;
    std::string filename = "frames/frame" + ss.str() + ".bmp";
    frame.WriteToFile(filename.c_str());
}

template<class T>
void ArrayAnimator<T>::addPadding() {
    for (int i = 0; i < 12; ++i) {
        addFrame();
    }
}

template<class T>
void ArrayAnimator<T>::updateRow(int row, int value) {
    int minWidth, maxWidth, minHeight, maxHeight;
    calcWidth(value, minWidth, maxWidth);
    calcHeight(row, minHeight, maxHeight);

    for (int x = 0; x < width; ++x) {
        for (int y = minHeight; y < maxHeight; ++y) {
            frame(x,y)->Red = 255;
            frame(x,y)->Green = 255;
            frame(x,y)->Blue = 255;
        }
    }

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
void ArrayAnimator<T>::loadFirstFrame(CallbackArray<T>& array) {
    frame.SetBitDepth(1);
    frame.SetSize(width, height);

    for (int i = 0; i < array.size(); ++i) {
        updateRow(i, int(array[i]));
    }

    addFrame();
}
#endif
