#include <thread>
#include <iostream>
#include <chrono>
#include "chan/chan.h"
using namespace std;

void builder(chan<string> in, chan<string> out) {
    while(true) {
        string product;
        in >> product;
        product += "two-story ";
        out << product;
    }
}
void painter(chan<string> in, chan<string> out) {
    while(true) {
        string product;
        in >> product;
        product += "blue ";
        out << product;
    }
}
void finisher(chan<string> in, chan<string> out) {
    while(true) {
        string product;
        in >> product;
        product += "house.\n";
        out << product;
    }
}

int main() {
    // make channels and workers
    chan<string> ch1, ch2, ch3;
    chan<string> ch4(10); // some capacity
    thread(builder,  ch1, ch2).detach();
    thread(painter,  ch2, ch3).detach();
    thread(finisher, ch3, ch4).detach();

    // make orders
    for (size_t i = 0; i != 10; ++i) {
        ch1 << "A ";
    }

    // get results
    for (size_t i = 0; i != 10; ++i) {
        string result;
        ch4 >> result;
        cout << result;
    }
}