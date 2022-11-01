//
// Created by whg on 2022/10/29.
//

#include "universe.hpp"

PyObject* Universe::PyTrue = nullptr;
PyObject* Universe::PyFalse = nullptr;

PyObject* Universe::PyNone = nullptr;

void Universe::genesis() {
    PyTrue = new PyString("True");
    PyFalse = new PyString("False");

    PyNone = new PyString("None");
}

void Universe::destroy() {

}