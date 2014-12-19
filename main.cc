#include <thread>
#include <iostream>
#include <chrono>
#include "chan.H"
using namespace std;

void work(chan<int> out) {
    for(size_t i = 0; i != 5; ++i) {
        out << i;
        this_thread::sleep_for(chrono::seconds(1));
    }
}

int main() {
    chan<int> ch;   // synchronous
    thread worker(work, ref(ch));

    while(true) {
        int output;
        ch >> output;
        cout << "Received a " << output << '\n';
    }
}