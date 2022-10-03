//
// Created by whg on 2022/10/3.
//

#include "pyString.hpp"
#include <string.h>

PyString::PyString(const char* c) {
    _length = strlen(c);
    _value = new char[_length];
    strcpy(_value, c);
}

PyString::PyString(const char* c, const int length) {
    _length = length;
    _value = new char[_length];
    for(int i=0;i<_length;i++){
        _value[i] = c[i];
    }
}