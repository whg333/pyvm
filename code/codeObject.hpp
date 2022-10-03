//
// Created by whg on 2022/10/3.
//

#ifndef PYVM_CODE_OBJECT_HPP
#define PYVM_CODE_OBJECT_HPP

#include "object/pyObject.hpp"
#include "object/pyString.hpp"
#include "util/arrayList.hpp"

class CodeObject: public PyObject{
public:
    int _arg_count;
    int _n_locals;
    int _stack_size;
    int _flag;

    PyString* _bytecodes;
    ArrayList<PyObject*>* _names;
    ArrayList<PyObject*>* _consts;
    ArrayList<PyObject*>* _var_names;

    ArrayList<PyObject*>* _free_vars;
    ArrayList<PyObject*>* _cell_vars;

    PyString* _co_name;
    PyString* _file_name;

    int _lineno;
    PyString* _notable;

    CodeObject(int arg_count, int n_locals, int stack_size, int flag, PyString* bytecodes,
               ArrayList<PyObject*>* names, ArrayList<PyObject*>* consts, ArrayList<PyObject*>* var_names,
               ArrayList<PyObject*>* free_vars, ArrayList<PyObject*>* cell_vars,
               PyString* co_name, PyString* file_name, int lineno, PyString* notable);
};


#endif //PYVM_CODE_OBJECT_HPP
