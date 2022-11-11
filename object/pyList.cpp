//
// Created by whg on 2022/11/5.
//

#include "pyList.hpp"
#include "pyInteger.hpp"
#include "runtime/universe.hpp"

ListClass* ListClass::instance = nullptr;
ListClass *ListClass::getInst() {
    if(instance == nullptr){
        instance = new ListClass();
    }
    return instance;
}
ListClass::ListClass() {

}

void ListClass::print(PyObject *self) {
    PyList* selfList = (PyList*)self;
    assert(selfList && (selfList->getClass() == this));
    printf("[");
    int size = selfList->size();
    if(size >= 1){
        selfList->get(0)->print();
    }
    for(int i=1;i<size;i++){
        printf(", ");
        selfList->get(i)->print();
    }
    printf("]");
}

PyObject *ListClass::subscr(PyObject *self, PyObject *index) {
    PyList* selfList = (PyList*)self;
    PyInteger* indexInt = (PyInteger*)index;
    assert(selfList && (selfList->getClass() == this));
    assert(indexInt && (indexInt->getClass() == IntegerClass::getInst()));
    return selfList->get(indexInt->value());
}

PyObject *ListClass::contains(PyObject *self, PyObject *element) {
    PyList* selfList = (PyList*)self;
    assert(selfList && (selfList->getClass() == this));
    int size = selfList->size();
    for(int i=0;i<size;i++){
        if(selfList->get(i)->equal(element)){
            return Universe::PyTrue;
        }
    }
    return Universe::PyFalse;
}

PyList::PyList() {
    _list = new ArrayList<PyObject*>();
    setClass(ListClass::getInst());
}
PyList::PyList(ObjList list) {
    _list = list;
    setClass(ListClass::getInst());
}