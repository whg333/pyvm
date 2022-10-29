//
// Created by whg on 2022/10/3.
//

#ifndef PYVM_PY_INTEGER_HPP
#define PYVM_PY_INTEGER_HPP

#include "pyObject.hpp"

class PyInteger:public PyObject {
private:
    int _value;
public:
    PyInteger(int i);
    int value(){
        return _value;
    }
    PyObject * add(PyObject *other) override;
    void print() override;

    PyObject * less(PyObject *other) override;
    PyObject * le(PyObject *other) override;
    PyObject * equal(PyObject *other) override;
    PyObject * not_equal(PyObject *other) override;
    PyObject * greater(PyObject *other) override;
    PyObject * ge(PyObject *other) override;
};


#endif //PYVM_PY_INTEGER_HPP
