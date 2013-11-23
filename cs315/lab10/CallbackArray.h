#ifndef CALLBACK_ARRAY_H
#define CALLBACK_ARRAY_H

#include <iostream>
#include <algorithm>

template<class T>
class WriteCheck;

template<class T>
class ArrayCallback {
    public:
        virtual ~ArrayCallback() {};
        virtual void onUpdate(int index, const T& value) = 0;
};

template<class T>
class CallbackArray {
    private:
        WriteCheck<T>* array;
        int arraySize;
    public:
        CallbackArray(int size, ArrayCallback<T>* callback) {
            arraySize = size;
            array = new WriteCheck<T>[arraySize];
            for (int i = 0; i < arraySize; ++i) {
                array[i] = WriteCheck<T>(callback, i);
            }
        }

        ~CallbackArray() {
            delete [] array;
        }

        WriteCheck<T>* begin() {
            return array;
        }

        WriteCheck<T>* end() {
            return array + arraySize;
        }

        int size() {
            return arraySize;
        }

        T const& operator[](int index) const {
            return array[index];
        }

        WriteCheck<T> operator[](int index) {
            return array[index];
        }
};

template<class T>
class WriteCheck {
    private:
        ArrayCallback<T>* callback;
        T* object;
        int index;

    public:
        WriteCheck() {
            callback = NULL;
            object = new T();
            index = -1;
        }

        WriteCheck(ArrayCallback<T>* cb, int i) {
            callback = cb;
            object = new T();
            index = i;
        }

        WriteCheck<T>& operator=(WriteCheck<T> const &rhs) {
            if (index == -1) {
                callback = rhs.callback;
                object = rhs.object;
                index = rhs.index;
            }
            else {
                object = rhs.object;
                callback -> onUpdate(index, *(rhs.object));
            }
        }

        WriteCheck<T>& operator=(T const &rhs) {
            *object = rhs;
            callback -> onUpdate(index, rhs);
        }

        operator T const&() {
            return *object;
        }
};

#endif
