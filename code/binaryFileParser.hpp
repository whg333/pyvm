//
// Created by whg on 2022/10/3.
//

#ifndef PYVM_BINARY_FILEPARSER_HPP
#define PYVM_BINARY_FILEPARSER_HPP

#include "util/bufferedInputStream.hpp"
#include "codeObject.hpp"

class BinaryFileParser {
private:
    BufferedInputStream* file_stream;
    int cur;
    ArrayList<PyString*> _string_table;

    CodeObject* get_code_object();
    PyString* get_byte_codes();

    ArrayList<PyObject*>* get_consts();
    ArrayList<PyObject*>* get_names();
    ArrayList<PyObject*>* get_var_names();
    ArrayList<PyObject*>* get_free_vars();
    ArrayList<PyObject*>* get_cell_vars();

    PyString* get_file_name();
    PyString* get_name();
    PyString* get_no_table();

    PyString* get_string();
    ArrayList<PyObject*>* get_tuple();
public:
    BinaryFileParser(BufferedInputStream* stream);
    CodeObject* parse();
};


#endif //PYVM_BINARY_FILEPARSER_HPP
