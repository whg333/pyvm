//
// Created by whg on 2022/11/5.
//

#include "pyList.hpp"

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

PyList::PyList() {
    _list = new ArrayList<PyObject*>();
    setClass(ListClass::getInst());
}
PyList::PyList(ObjList list) {
    _list = list;
    setClass(ListClass::getInst());
}