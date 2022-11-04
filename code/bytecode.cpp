//
// Created by whg on 2022/11/4.
//

#include "bytecode.hpp"

const unsigned char ByteCode::POP_TOP;
const unsigned char ByteCode::BINARY_ADD;

const unsigned char ByteCode::PRINT_ITEM;
const unsigned char ByteCode::PRINT_NEWLINE;

const unsigned char ByteCode::BREAK_LOOP;
const unsigned char ByteCode::RETURN_VALUE;
const unsigned char ByteCode::POP_BLOCK;

const unsigned char ByteCode::STORE_NAME;
const unsigned char ByteCode::STORE_GLOBAL;

const unsigned char ByteCode::LOAD_CONST;
const unsigned char ByteCode::LOAD_NAME;

const unsigned char ByteCode::LOAD_ATTR;
const unsigned char ByteCode::COMPARE_OP;

const unsigned char ByteCode::JUMP_FORWARD;
const unsigned char ByteCode::JUMP_ABSOLUTE;
const unsigned char ByteCode::POP_JUMP_IF_FALSE;
const unsigned char ByteCode::LOAD_GLOBAL;

const unsigned char ByteCode::SETUP_LOOP;
const unsigned char ByteCode::LOAD_FAST;
const unsigned char ByteCode::STORE_FAST;

const unsigned char ByteCode::CALL_FUNCTION;
const unsigned char ByteCode::MAKE_FUNCTION;

map<unsigned char, string> ByteCode::byteCodeMap;
void ByteCode::initMap() {
    pair<unsigned char, string> pairArray[] = {
            make_pair(ByteCode::POP_TOP, "POP_TOP"),
            make_pair(ByteCode::BINARY_ADD, "BINARY_ADD"),
            make_pair(ByteCode::PRINT_ITEM, "PRINT_ITEM"),
            make_pair(ByteCode::PRINT_NEWLINE, "PRINT_NEWLINE"),
            make_pair(ByteCode::BREAK_LOOP, "BREAK_LOOP"),
            make_pair(ByteCode::RETURN_VALUE, "RETURN_VALUE"),
            make_pair(ByteCode::POP_BLOCK, "POP_BLOCK"),
            make_pair(ByteCode::STORE_NAME, "STORE_NAME"),
            make_pair(ByteCode::STORE_GLOBAL, "STORE_GLOBAL"),
            make_pair(ByteCode::LOAD_CONST, "LOAD_CONST"),
            make_pair(ByteCode::LOAD_NAME, "LOAD_NAME"),
            make_pair(ByteCode::LOAD_ATTR, "LOAD_ATTR"),
            make_pair(ByteCode::COMPARE_OP, "COMPARE_OP"),
            make_pair(ByteCode::JUMP_FORWARD, "JUMP_FORWARD"),
            make_pair(ByteCode::JUMP_ABSOLUTE, "JUMP_ABSOLUTE"),
            make_pair(ByteCode::POP_JUMP_IF_FALSE, "POP_JUMP_IF_FALSE"),
            make_pair(ByteCode::LOAD_GLOBAL, "LOAD_GLOBAL"),
            make_pair(ByteCode::SETUP_LOOP, "SETUP_LOOP"),
            make_pair(ByteCode::LOAD_FAST, "LOAD_FAST"),
            make_pair(ByteCode::STORE_FAST, "STORE_FAST"),
            make_pair(ByteCode::CALL_FUNCTION, "CALL_FUNCTION"),
            make_pair(ByteCode::MAKE_FUNCTION, "MAKE_FUNCTION"),
    };
    map<unsigned char, string> tempMap(pairArray,pairArray+sizeof(pairArray) / sizeof(pairArray[0]));
    byteCodeMap = tempMap;
}