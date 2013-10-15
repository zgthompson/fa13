#include <iostream>
#include <vector>

int count = 0;

void minsert_sort(std::vector<int>& a) {
    int n = a.size();
    for (int i = 1; i < n; i = i + 2) {
        int temp = a[i];
        count++;
        int j = i - 1;
        while (j > -1 && a[j] > temp) {
            a[j+1] = a[j];
            count++;
            j = j - 1;
        }
        a[j+1] = temp;
        count++;
    }

    for (int i = 2; i < n; i = i + 2) {
        int temp = a[i];
        count++;
        int j = i - 1;
        while (j > -1 && a[j] > temp) {
            a[j+1] = a[j];
            count++;
            j = j - 1;
        }
        a[j+1] = temp;
        count++;
    }
}

int main(void) {
    int vv[] = { 12, 9, 21, 10, 18, 7, 14, 3, 11 };
    //int vv[] = { 7, 9, 10, 12, 21, 18, 14, 3, 11 };
    std::vector<int> v(&vv[0], &vv[0]+9);

    minsert_sort(v);

    for(int i = 0; i < v.size(); i++)
            std::cout << v[i] << ' ';
    std::cout << std::endl;

    std::cout << count << std::endl;
}

