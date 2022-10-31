//
// Created by whg on 2022/10/3.
//

#include <stdio.h>
#include "pyInteger.hpp"
#include "runtime/universe.hpp"

#define COMPARE(x) x ? Universe::PyTrue : Universe::PyFalse

IntegerClass* IntegerClass::instance = nullptr;
IntegerClass::IntegerClass() {

}
IntegerClass* IntegerClass::getInst() {
    //TODO 考虑并发使用双检查？
    if(instance == nullptr){
        instance = new IntegerClass();
    }
    return instance;
}

PyInteger::PyInteger(int i) {
    _value = i;
    setClass(IntegerClass::getInst());
}

void IntegerClass::print(PyObject *self) {
    PyInteger* selfInt = (PyInteger*)self;
    assert(selfInt && (selfInt->getClass() == (Klass*)this));
    printf("%d", selfInt->value());
}

PyObject* IntegerClass::add(PyObject *self, PyObject* other) {
    assert(self->getClass() == other->getClass());
    PyInteger* selfInt = (PyInteger*)self;
    PyInteger* otherInt = (PyInteger*)other;
    assert(selfInt && (selfInt->getClass() == (Klass*)this));
    assert(otherInt && (otherInt->getClass() == (Klass*)this));

    return new PyInteger(selfInt->value() + otherInt->value());
}

PyObject *IntegerClass::less(PyObject *self, PyObject *other) {
    assert(self->getClass() == other->getClass());
    PyInteger* selfInt = (PyInteger*)self;
    PyInteger* otherInt = (PyInteger*)other;
    assert(selfInt && (selfInt->getClass() == (Klass*)this));
    assert(otherInt && (otherInt->getClass() == (Klass*)this));

    return COMPARE(selfInt->value() < otherInt->value());
}

PyObject *IntegerClass::le(PyObject *self, PyObject *other) {
    assert(self->getClass() == other->getClass());
    PyInteger* selfInt = (PyInteger*)self;
    PyInteger* otherInt = (PyInteger*)other;
    assert(selfInt && (selfInt->getClass() == (Klass*)this));
    assert(otherInt && (otherInt->getClass() == (Klass*)this));

    return COMPARE(selfInt->value() <= otherInt->value());
}

PyObject *IntegerClass::equal(PyObject *self, PyObject *other) {
    if(self->getClass() != other->getClass()){
        return Universe::PyFalse;
    }
    PyInteger* selfInt = (PyInteger*)self;
    PyInteger* otherInt = (PyInteger*)other;
    assert(selfInt && (selfInt->getClass() == (Klass*)this));
    assert(otherInt && (otherInt->getClass() == (Klass*)this));
    return COMPARE(selfInt->value() == otherInt->value());
}

PyObject *IntegerClass::not_equal(PyObject *self, PyObject *other) {
    assert(self->getClass() == other->getClass());
    PyInteger* selfInt = (PyInteger*)self;
    PyInteger* otherInt = (PyInteger*)other;
    assert(selfInt && (selfInt->getClass() == (Klass*)this));
    assert(otherInt && (otherInt->getClass() == (Klass*)this));

    return COMPARE(selfInt->value() != otherInt->value());
}

PyObject *IntegerClass::greater(PyObject *self, PyObject *other) {
    assert(self->getClass() == other->getClass());
    PyInteger* selfInt = (PyInteger*)self;
    PyInteger* otherInt = (PyInteger*)other;
    assert(selfInt && (selfInt->getClass() == (Klass*)this));
    assert(otherInt && (otherInt->getClass() == (Klass*)this));

    return COMPARE(selfInt->value() > otherInt->value());
}

PyObject *IntegerClass::ge(PyObject *self, PyObject *other) {
    assert(self->getClass() == other->getClass());
    PyInteger* selfInt = (PyInteger*)self;
    PyInteger* otherInt = (PyInteger*)other;
    assert(selfInt && (selfInt->getClass() == (Klass*)this));
    assert(otherInt && (otherInt->getClass() == (Klass*)this));

    return COMPARE(selfInt->value() >= otherInt->value());
}
