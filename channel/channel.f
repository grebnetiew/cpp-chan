template<typename T>
Channel<T>::Channel(size_t capacity):
    std::unique_ptr<std::deque<T>>(new std::deque<T>()),
    d_cap(capacity)
{}