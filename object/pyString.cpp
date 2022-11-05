//
// Created by whg on 2022/10/3.
//

#include <string.h>
#include <stdio.h>
#include "pyString.hpp"
#include "runtime/universe.hpp"

StringClass* StringClass::instance = NULL;
StringClass *StringClass::getInst() {
    if(instance == NULL){
        instance = new StringClass();
    }
    return instance;
}

PyString::PyString(const char* c) {
    _length = strlen(c);
    _value = new char[_length];
    strcpy(_value, c);
    setClass(StringClass::getInst());
}

PyString::PyString(const char* c, const int length) {
    _length = length;
    _value = new char[_length];
    for(int i=0;i<_length;i++){
        _value[i] = c[i];
    }
    setClass(StringClass::getInst());
}

void StringClass::print(PyObject *self) {
    PyString* selfStr = (PyString*)self;
    assert(selfStr && (selfStr->getClass() == this));
    for(int i=0;i<selfStr->length();i++){
        printf("%c", selfStr->value()[i]);
    }
}

PyObject *StringClass::equal(PyObject *self, PyObject *other) {
    if(self->getClass() != other->getClass()){
        return Universe::PyFalse;
    }
    PyString* selfStr = (PyString*)self;
    PyString* otherStr = (PyString*)other;
    assert(selfStr && (selfStr->getClass() == (Klass*)this));
    assert(otherStr && (otherStr->getClass() == (Klass*)this));

    if(selfStr->length() != otherStr->length()){
        return Universe::PyFalse;
    }
    for(int i=0;i<selfStr->length();i++){
        if(selfStr->value()[i] != otherStr->value()[i]){
            return Universe::PyFalse;
        }
    }
    return Universe::PyTrue;
}