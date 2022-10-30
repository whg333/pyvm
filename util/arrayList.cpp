//
// Created by whg on 2022/10/3.
//

#include "arrayList.hpp"
#include "runtime/interpreter.hpp"
#include <stdio.h>

template <typename T>
ArrayList<T>::ArrayList(int length) {
    _length = length;
    _size = 0;
    _array = new T[length];
}

template<typename T>
void ArrayList<T>::add(T t) {
    if(_size >= _length){
        expand();
    }

    _array[_size++] = t;
}

template<typename T>
void ArrayList<T>::insert(int index, T t) {
    // check index in size
    add(NULL);

    for(int i=_size;i>index;i--){
        _array[i] = _array[i-1];
    }

    _array[index] = t;
}

template<typename T>
void ArrayList<T>::expand() {
    T* new_array = new T[_length << 1];
    for(int i=0;i<_length;i++){
        new_array[i] = _array[i];
    }
    delete[] _array;
    _array = new_array;

    _length <<= 1;
    printf("expand array length to %d, size is %d\n", _length, _size);
}

template<typename T>
T ArrayList<T>::get(int index) {
    return _array[index];
}

template<typename T>
void ArrayList<T>::set(int index, T t) {
    // check index in size
    _array[index] = t;
}

template<typename T>
int ArrayList<T>::size() {
    return _size;
}

template<typename T>
int ArrayList<T>::length() {
    return _length;
}

template<typename T>
void ArrayList<T>::push(T t) {
    add(t);
}

template<typename T>
T ArrayList<T>::pop() {
    return _array[--_size];
}

class PyObject;
template class ArrayList<PyObject*>;

class PyString;
template class ArrayList<PyString*>;

class Block;
template class ArrayList<Block*>;