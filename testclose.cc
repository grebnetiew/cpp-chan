#include <iostream>
#include "chan/chan.h"
using namespace std;

int main() {
    chan<int> store(5);
    store << 1 << 2 << 3;
    store.close();

    for (size_t i = 0; i != 3; ++i) {
        int res;
        store >> res;
        cout << res << '\n';
    }

    try {
        store >> int();
    } catch(Channel<int>::ClosedException &e) {
        cout << "Okay okay, I'm going, jeez\n";
    }
}