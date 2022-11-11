//
// Created by whg on 2022/11/5.
//

#ifndef PYVM_PYLIST_HPP
#define PYVM_PYLIST_HPP

#include "pyObject.hpp"
#include "util/arrayList.hpp"

class ListClass: public Klass{
private:
    static ListClass* instance;
    ListClass();
public:
    static ListClass* getInst();
    void print(PyObject *self) override;
    PyObject * subscr(PyObject *self, PyObject *index) override;
    PyObject * contains(PyObject *self, PyObject *element) override;
};

class PyList: public PyObject{
private:
    ArrayList<PyObject*>* _list;
public:
    PyList();
    PyList(ObjList list);

    ArrayList<PyObject*>* list(){
        return _list;
    }
    int size(){
        return _list->size();
    }
    void append(PyObject* obj){
        _list->add(obj);
    }
    PyObject* pop(){
        return _list->pop();
    }
    PyObject* get(int index){
        return _list->get(index);
    }
    void set(int index, PyObject* obj){
        _list->set(index, obj);
    }
    PyObject* top(){
        return _list->get(size()-1);
    }
};


#endif //PYVM_PYLIST_HPP
