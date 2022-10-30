//
// Created by whg on 2022/10/3.
//

#include <string.h>
#include "pyString.hpp"
#include "runtime/universe.hpp"

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

PyObject *PyString::equal(PyObject *other) {
    PyString* otherStr = (PyString*)other;
    if(_length != otherStr->_length){
        return Universe::PyFalse;
    }
    for(int i=0;i<_length;i++){
        if(_value[i] != otherStr->_value[i]){
            return Universe::PyFalse;
        }
    }
    return Universe::PyTrue;

}