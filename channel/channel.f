template<typename T>
Channel<T>::Channel():
    unique_ptr<deque<T>>(new deque<T>()),
    d_cap(0)
{}

template<typename T>
Channel<T>::Channel(size_t capacity):
    unique_ptr<deque<T>>(new deque<T>()),
    d_cap(capacity)
{}
