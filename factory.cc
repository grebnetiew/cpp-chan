#include <thread>
#include <iostream>
#include <chrono>
#include "chan/chan.h"
using namespace std;

void worker(chan<string> in, chan<string> out, string const &text) 
try {
    while(true) {
        string product;
        in >> product;
        product += text;
        out << product;
    }
} catch (Channel<string>::ClosedException &e) {
    out.close();
}

int main() {
    // make channels and workers
    chan<string> ch1, ch2, ch3;
    chan<string> ch4(10); // some capacity
    thread t1(worker, ch1, ch2, "two-story ");
    thread t2(worker, ch2, ch3, "blue ");
    thread t3(worker, ch3, ch4, "house.\n");

    // make orders
    for (size_t i = 0; i != 10; ++i) {
        ch1 << "A ";
    }

    // get results
    for (size_t i = 0; i != 10; ++i) {
        cout << "Houses ready: " << ch4.size() << '\n';

        string result;
        ch4 >> result;
        cout << result;
    }
    
    // clean up workers
    ch1.close();
    t1.join();
    t2.join();
    t3.join();
}