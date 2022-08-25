#include <iostream>
#include <chrono>
#include "evenfunc.h"

#define ch std::chrono

bool isEven(unsigned long value) {
    return value % 2 == 0;
}

bool isEven2(unsigned long value) {
    return (value & 1) == 0;
}




int main() {
    auto start =ch::high_resolution_clock::now();
    for(auto i = 0; i < 100000000; ++i){
        isEven(i);
    }
    auto end = ch::high_resolution_clock::now();
    auto time1 =  ch::duration_cast<ch::microseconds>(end - start).count();
    start =ch::high_resolution_clock::now();
    for(auto i = 0; i < 100000000; ++i){
        isEven2(i);
    }
    end = ch::high_resolution_clock::now();
    auto time2= ch::duration_cast<ch::microseconds>(end - start).count();
    std::cout << time1 - time2;
}
