#include "chan.ih"

template<typename T>
chan<T>::chan(): d_impl(new Channel<T>()) {}

template<typename T>
chan<T>::chan(size_t capacity): d_impl(new Channel<T>(capacity)) {}