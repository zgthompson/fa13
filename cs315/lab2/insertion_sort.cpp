#include <vector>
#include <iostream>
#include <cstdlib>


const int ARRAY_SIZE = 10;
const int NUM_OF_TIMES = 1000;

void insertion_sort(std::vector<int> A) {
    for (int j = 1; j < A.size(); ++j) {
        int k;
        int temp = A[j];
        for (k = j - 1; k >= 0 && A[k] > temp; k--)
            A[k+1] = A[k];
        A[k+1] = temp;
    }
}

int insertion_sort_comparisons(std::vector<int> A) {
    int count = 0;
    for (int j = 1; j < A.size(); ++j) {
        int k;
        int temp = A[j];
        for (k = j - 1; k >= 0 && A[k] > temp; k--) {
            count++;
            A[k+1] = A[k];
        }
        count++;
        A[k+1] = temp;
    }

    return count;
}

void swap(std::vector<int> A, int p, int q) {
    int temp = A[p];
    A[p] = A[q];
    A[q] = temp;
}

void selection_sort(std::vector<int> A) {
    for (int j = 0; j < A.size()-1; j++) {
        int min = j;
        for (int k = j+1; k < A.size(); k++) 
            if (A[k] < A[min])
                min = k;
        swap(A, j, min);
    }
}

int selection_sort_min_changes(std::vector<int> A) {
    int count = 0;
    for (int j = 0; j < A.size()-1; j++) {
        int min = j;
        for (int k = j+1; k < A.size(); k++) 
            if (A[k] < A[min]) {
                count++;
                min = k;
            }
        swap(A, j, min);
    }
    return count;
}



int main(int argc, char** argv) {
    std::vector<int> vec;
    int total = 0;
    double average;
    srand(int(time(0)));
    int i, j, k;

    for (i = 10; i < 101; i += 10) {
        for (j = 0; j < NUM_OF_TIMES; ++j) {
            for (k = 0; k < i; ++k) {
                vec.push_back(rand());
            }
            total += insertion_sort_comparisons(vec);
            vec.clear();
        }
        average = (double) total / NUM_OF_TIMES;
        std::cout << "Average insertion sort comparisons for array size " << i << " = " << average << '\n';
        total = 0;
    }

    for (i = 100; i < 1001; i += 100) {
        for (j = 0; j < NUM_OF_TIMES; ++j) {
            for (k = 0; k < i; ++k) {
                vec.push_back(rand());
            }
            total += selection_sort_min_changes(vec);
            vec.clear();
        }
        average = (double) total / NUM_OF_TIMES;
        std::cout << "Average selection sort min changes for array size " << i << " = " << average << '\n';
        total = 0;
    }
}
