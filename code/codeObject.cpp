//
// Created by whg on 2022/10/3.
//

#include "codeObject.hpp"

CodeObject::CodeObject(int arg_count, int n_locals, int stack_size, int flag, PyString *bytecodes,
                       ArrayList<PyObject *> *names, ArrayList<PyObject *> *consts, ArrayList<PyObject *> *var_names,
                       ArrayList<PyObject *> *free_vars, ArrayList<PyObject *> *cell_vars,
                       PyString *co_name, PyString *file_name, int lineno, PyString *notable):
                       _arg_count(arg_count),
                       _n_locals(n_locals),
                       _stack_size(stack_size),
                       _flag(flag),
                       _bytecodes(bytecodes),
                       _names(names),
                       _consts(consts),
                       _var_names(var_names),
                       _free_vars(free_vars),
                       _cell_vars(cell_vars),
                       _co_name(co_name),
                       _file_name(file_name),
                       _lineno(lineno),
                       _notable(notable){

}