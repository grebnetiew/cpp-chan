template<typename T>
chan<T>::chan(size_t capacity): d_impl(new Channel<T>(capacity)) {}