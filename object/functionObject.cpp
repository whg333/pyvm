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