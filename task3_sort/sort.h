#include <iostream>

template<typename T>
void mergesort(T *array, int Len) {
    //make a new array, istead of splitting into two different
    T *tmp = new T[Len];
    T *from = array, *to = tmp;
    for (int step = 1; step < Len; step *= 2) {
        int start1, end1, start2, end2;
        int index = 0;
        for (int start = 0; start < Len; start += 2 * step) {
            start1 = start;
            end1 = start1 + step;
            end1 = (end1 < Len) ? end1 : Len;
            start2 = end1;
            end2 = start2 + step;
            end2 = (end2 < Len) ? end2 : Len;
            //take the least element from two parts
            while (start1 < end1 && start2 < end2) {
                to[index++] = (from[start1] < from[start2]) ? from[start1++] : from[start2++];
            }
            //if something is left in from_array that has nothing to compare with, we just rewrite it
            //in the end of to_array
            while (start1 < end1) {
                to[index++] = from[start1++]; }
            while (start2 < end2) {
                to[index++] = from[start2++]; }
        }
        std::swap(from, to);
    }
    //if sorted array not in initial array - swap array and tmp
    if (from != array) {
        int i = 0;
        while (i < Len) {
            array[i] = tmp[i];
            ++i;
        }
    }
    delete[] tmp;
}
