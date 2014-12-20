template<typename T>
std::pair<bool, T> chan<T>::operator~() {
    T result;
    return std::pair<bool, T>(this->d_impl->try_receive(&result), result);
}