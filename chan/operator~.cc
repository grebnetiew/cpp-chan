#include "chan.ih"

template<typename T>
pair<bool, T> chan<T>::operator~() {
    T result;
    return pair<bool, T>(this->d_impl->try_receive(result), result);
}