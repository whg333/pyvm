//
// Created by whg on 2022/10/3.
//

#include <stdio.h>
#include "pyInteger.hpp"

PyInteger::PyInteger(int i) {
    _value = i;
}

PyObject* PyInteger::add(PyObject* other) {
    PyInteger* otherInt = ((PyInteger*)other);
    return new PyInteger(_value + otherInt->_value);
}

void PyInteger::print() {
    printf("%d", _value);
}