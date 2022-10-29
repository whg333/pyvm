//
// Created by whg on 2022/10/3.
//

#include <stdio.h>
#include "pyInteger.hpp"
#include "../runtime/universe.hpp"

#define COMPARE(x) x ? Universe::PyTrue : Universe::PyFalse

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

PyObject *PyInteger::less(PyObject *other) {
    PyInteger* otherInt = ((PyInteger*)other);
    return COMPARE(_value < otherInt->_value);
}

PyObject *PyInteger::le(PyObject *other) {
    PyInteger* otherInt = ((PyInteger*)other);
    return COMPARE(_value <= otherInt->_value);
}

PyObject *PyInteger::equal(PyObject *other) {
    PyInteger* otherInt = ((PyInteger*)other);
    return COMPARE(_value == otherInt->_value);
}

PyObject *PyInteger::not_equal(PyObject *other) {
    PyInteger* otherInt = ((PyInteger*)other);
    return COMPARE(_value != otherInt->_value);
}

PyObject *PyInteger::greater(PyObject *other) {
    PyInteger* otherInt = ((PyInteger*)other);
    return COMPARE(_value > otherInt->_value);
}

PyObject *PyInteger::ge(PyObject *other) {
    PyInteger* otherInt = ((PyInteger*)other);
    return COMPARE(_value >= otherInt->_value);
}
