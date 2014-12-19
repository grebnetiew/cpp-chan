#include "chan.ih"

template<typename T>
T &&operator~(chan<T> &ch) {
    T result;
    return pair(this->d_impl->try_receive(result), result);
}