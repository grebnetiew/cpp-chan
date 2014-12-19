#include <thread>
#include <iostream>
#include <chrono>
#include "chan/chan.h"
using namespace std;

void work(chan<int> out) {
    for(size_t i = 0; i != 6; ++i) {
        out << i;
        this_thread::sleep_for(chrono::seconds(1));
    }
}

int main() {
    chan<int> ch;   // synchronous
    thread worker(work, ch);

    for(size_t i = 0; i != 5; ++i) {
        int output;
        ch >> output;
        cout << "Received a " << output << '\n';
    }

    pair<bool, int> conditionalInt{false, -1};
    while (!(conditionalInt = ~ch).first) {
        this_thread::yield();
    }
    cout << "Received finally a " << conditionalInt.second << '\n';

    worker.join();
}