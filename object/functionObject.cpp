//
// Created by whg on 2022/11/1.
//

#include "functionObject.hpp"

FunctionClass* FunctionClass::instance = nullptr;
FunctionClass *FunctionClass::getInst() {
    if(instance == nullptr){
        instance = new FunctionClass();
    }
    return instance;
}
FunctionClass::FunctionClass() {

}

void FunctionClass::print(PyObject *self) {
    FunctionObject* selfFun = (FunctionObject*)self;
    assert(selfFun && (selfFun->getClass() == (Klass*)this));
    printf("<function : ");
    selfFun->name()->print();
    printf(">\n");
}

FunctionObject::FunctionObject(PyObject* codeObj) {
    CodeObject* code = (CodeObject*)codeObj;
    _code = code;
    _name = code->_co_name;
    _flags = code->_flag;
    setClass(FunctionClass::getInst());
}

void FunctionObject::setDefaults(ObjList defaults) {
    if(defaults == nullptr){
        _defaults = nullptr;
        return;
    }

    _defaults = new ArrayList<PyObject*>(defaults->length());
    for(int i=0;i<defaults->length();i++){
        _defaults->set(i, defaults->get(i));
    }
}