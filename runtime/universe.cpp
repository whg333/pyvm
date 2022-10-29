//
// Created by whg on 2022/10/29.
//

#include "universe.hpp"

PyInteger* Universe::PyTrue = nullptr;
PyInteger* Universe::PyFalse = nullptr;

PyObject* Universe::PyNone = nullptr;

void Universe::genesis() {
    PyTrue = new PyInteger(1);
    PyFalse = new PyInteger(0);

    PyNone = new PyObject();
}

void Universe::destroy() {

}