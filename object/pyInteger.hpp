//
// Created by whg on 2022/10/3.
//

#ifndef PYVM_PY_INTEGER_HPP
#define PYVM_PY_INTEGER_HPP

#include "pyObject.hpp"

class IntegerClass:public Klass{
private:
    IntegerClass();
    static IntegerClass* instance;
public:
    static IntegerClass* getInst();

    void print(PyObject* self) override;
    PyObject * add(PyObject* self, PyObject *other) override;

    PyObject * less(PyObject* self, PyObject *other) override;
    PyObject * le(PyObject* self, PyObject *other) override;
    PyObject * equal(PyObject* self, PyObject *other) override;
    PyObject * not_equal(PyObject* self, PyObject *other) override;
    PyObject * greater(PyObject* self, PyObject *other) override;
    PyObject * ge(PyObject* self, PyObject *other) override;
};

class PyInteger:public PyObject {
private:
    int _value;
public:
    PyInteger(int i);
    int value(){
        return _value;
    }
};


#endif //PYVM_PY_INTEGER_HPP
