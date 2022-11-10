//
// Created by whg on 2022/11/5.
//

#include "pyList.hpp"
#include "pyInteger.hpp"

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

PyList::PyList() {
    _list = new ArrayList<PyObject*>();
    setClass(ListClass::getInst());
}
PyList::PyList(ObjList list) {
    _list = list;
    setClass(ListClass::getInst());
}