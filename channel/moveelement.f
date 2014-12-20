template<typename T>
void Channel<T>::moveElement(T *result) {
    auto storage = std::unique_ptr<std::deque<T>>::get();
    if (result != nullptr) {
        *result = std::move(storage->front());      // Take the item
    }
    storage->pop_front();                           // has nothrow
}