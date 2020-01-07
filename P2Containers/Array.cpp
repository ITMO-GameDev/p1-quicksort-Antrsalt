#include "Array.h"
#include <iostream>

template <typename T>
Array<T>::Array() {
    array_ = new T[16];
    size_ = 0;
    capacity_ = 16;
}

template <typename T>
Array<T>::Array(int capacity) {
    array_ = new T[capacity];
    size_ = 0;
    capacity_ = capacity;
}

template <typename T>
Array<T>::~Array() {
    delete[] array_;
}

template <typename T>
void Array<T>::insert(const T& value) {
    if (size_ == capacity_) {
        extend();
    }
    array_[size_] = value;
    size_++;
}

template <typename T>
void Array<T>::insert(int index, const T& value) {
    if (index > size_) {
        throw std::out_of_range("Incorrect index for insertion");
    }
    if (size_ == capacity_) {
        extend();
    }
    std::copy(array_ + index, array_ + size_, array_ + index + 1);
    array_[index] = value;
    size_++;
}

template <typename T>
void Array<T>::remove(int index) {
    if (index > capacity_) {
        throw std::out_of_range("Incorrect index for removal");
    }
    if (size_ > 0) {
        std::copy(array_ + index + 1, array_ + size_, array_ + index);
        array_[size_ - 1] = 0;
        size_--;
    }
}

template<typename T>
int Array<T>::size() {
    return size_;
}

template<typename T>
int Array<T>::capacity() {
    return capacity_;
}

template <typename T>
T& Array<T>::operator[](int index) {

    if (index < 0 || index >= capacity_) {
        throw std::out_of_range("Incorrect index");
    }
    return array_[index];
}

template<typename T>
const T& Array<T>::operator[](int index) const {
    if (index < 0 || index >= capacity_) {
        throw std::out_of_range("Incorrect index");
    }
    return array_[index];
}


template<typename T>
void Array<T>::extend() {
    T* temp = nullptr;
    if (size_ == capacity_) {
        temp = new T[capacity_ * 2];
        std::move(array_, array_ + size_, temp);
    }
    delete array_;
    array_ = temp;
    capacity_ = capacity_ * 2;
}

template<typename T>
typename Array<T>::Iterator Array<T>::iterator() {
    return Array<T>::Iterator(*this);
}

template<typename T>
const typename Array<T>::Iterator Array<T>::iterator() const {
    return Array<T>::Iterator(*this);
}

template<typename T>
Array<T>::Iterator::Iterator(Array<T>& arr) : array_(arr) {
    index_ = 0;
}

template<typename T>
const T& Array<T>::Iterator::get() const {
    return array_[index_];
}

template<typename T>
void Array<T>::Iterator::set(const T& value) {
    array_[index_] = value;
}

template<typename T>
void Array<T>::Iterator::insert(const T& value) {
    if (array_.size_ < array_.capacity_)
        array_.insert(index_, value);
}

template<typename T>
void Array<T>::Iterator::remove() {
    array_.remove(index_);
}

template<typename T>
void Array<T>::Iterator::next() {
    if (hasNext())
        index_++;
}

template<typename T>
void Array<T>::Iterator::prev() {
    if (hasPrev())
        index_--;
}

template<typename T>
void Array<T>::Iterator::toIndex(int index) {
    if (index < array_.size_)
        this->index_ = index;
}

template<typename T>
bool Array<T>::Iterator::hasNext() const {
    return index_ < array_.size_ - 1;
}

template<typename T>
bool Array<T>::Iterator::hasPrev() const {
    return index_ > 0;
}
