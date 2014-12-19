#include "chan.ih"

size_t chan<T>::size() const {
    return d_impl->size();
}
