#include "chan.ih"

template<typename T>
T &&operator~(chan<T> &ch) {
    return ch.d_impl->receive();
}