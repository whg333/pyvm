//
// Created by whg on 2022/10/3.
//

#include <assert.h>

#include <iostream>
using std::cout;
using std::endl;

#include "binaryFileParser.hpp"
#include "object/pyInteger.hpp"

BinaryFileParser::BinaryFileParser(BufferedInputStream *stream):
    file_stream(stream) {
}

CodeObject* BinaryFileParser::parse() {
    int magic_number = file_stream->read_int();
    printf("magic number is 0x%x\n", magic_number);

    int modify_date = file_stream->read_int();
    printf("modify date is 0x%x\n", modify_date);

    char object_type = file_stream->read();
    if(object_type == 'c'){
        CodeObject* result = get_code_object();
        printf("parse OK!\n");
        return result;
    }
    return NULL;
}

CodeObject *BinaryFileParser::get_code_object() {
    int arg_count = file_stream->read_int();
    cout << arg_count << endl;
    int n_locals = file_stream->read_int();
    int stack_size = file_stream->read_int();
    int flag = file_stream->read_int();
    cout << flag << endl;

    PyString* bytecodes = get_byte_codes();
    ArrayList<PyObject*>* consts = get_consts();
    ArrayList<PyObject*>* names = get_names();
    ArrayList<PyObject*>* var_names = get_var_names();
    ArrayList<PyObject*>* free_vars = get_free_vars();
    ArrayList<PyObject*>* cell_vars = get_cell_vars();
    PyString* file_name = get_file_name();
    PyString* module_name = get_name();
    int begin_line_no = file_stream->read_int();
    PyString* notable = get_no_table();

    return new CodeObject(arg_count, n_locals, stack_size, flag, bytecodes,
            names, consts, var_names,
            free_vars, cell_vars,
            module_name, file_name, begin_line_no, notable);
}

PyString *BinaryFileParser::get_byte_codes() {
    assert(file_stream->read() == 's');
    return get_string();
}

ArrayList<PyObject *> *BinaryFileParser::get_consts() {
    if (file_stream->read() == '(') {
        return get_tuple();
    }

    file_stream->unread();
    return NULL;
}

ArrayList<PyObject *> *BinaryFileParser::get_names() {
    if (file_stream->read() == '(') {
        return get_tuple();
    }

    file_stream->unread();
    return NULL;
}

ArrayList<PyObject *> *BinaryFileParser::get_var_names() {
    if (file_stream->read() == '(') {
        return get_tuple();
    }

    file_stream->unread();
    return NULL;
}

ArrayList<PyObject *> *BinaryFileParser::get_free_vars() {
    if (file_stream->read() == '(') {
        return get_tuple();
    }

    file_stream->unread();
    return NULL;
}

ArrayList<PyObject *> *BinaryFileParser::get_cell_vars() {
    if (file_stream->read() == '(') {
        return get_tuple();
    }

    file_stream->unread();
    return NULL;
}

PyString *BinaryFileParser::get_file_name() {
    return get_name();
}

PyString *BinaryFileParser::get_name() {
    char ch = file_stream->read();

    if (ch == 's') {
        return get_string();
    } else if (ch == 't') {
        PyString* str = get_string();
        _string_table.add(str);
        return str;
    } else if (ch == 'R') {
        return _string_table.get(file_stream->read_int());
    }

    return NULL;
}

PyString *BinaryFileParser::get_no_table() {
    char ch = file_stream->read();

    if (ch != 's' && ch != 't') {
        file_stream->unread();
        return NULL;
    }

    return get_string();
}

PyString *BinaryFileParser::get_string() {
    int length = file_stream->read_int();
    char* value = new char[length];
    for(int i=0;i<length;i++){
        value[i] = file_stream->read();
    }
    PyString* str = new PyString(value, length);
    delete[] value;
    return str;
}

ArrayList<PyObject *> *BinaryFileParser::get_tuple() {
    int length = file_stream->read_int();
    PyString* str;

    ArrayList<PyObject*>* list = new ArrayList<PyObject*>(length);
    for(int i=0;i<length;i++){
        char obj_type = file_stream->read();
        switch (obj_type) {
            case 'c':
                cout << "got a code object!" << endl;
                list->add(get_code_object());
                break;
            case 'i':
                list->add(new PyInteger(file_stream->read_int()));
                break;
            case 'N':
                list->add(NULL);
                break;
            case 't':
                str = get_string();
                list->add(str);
                _string_table.add(str);
                break;
            case 's':
                list->add(get_string());
                break;
            case 'R':
                int index = file_stream->read_int();
                list->add(_string_table.get(index));
                break;
        }
    }
    return list;
}
