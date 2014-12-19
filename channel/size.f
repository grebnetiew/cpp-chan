template<typename T>
size_t Channel<T>::size() const {
    return std::unique_ptr<std::deque<T>>::get()->size();
}