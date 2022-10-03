//
// Created by whg on 2022/10/3.
//

#ifndef PYVM_BUFFERED_INPUT_STREAM_HPP
#define PYVM_BUFFERED_INPUT_STREAM_HPP

#include <stdio.h>

#define BUFFER_LEN 256

class BufferedInputStream {
private:
    FILE* fp;
    char szBuffer[BUFFER_LEN];
    unsigned short index;

public:
    BufferedInputStream(char const* filename){
        fp = fopen(filename, "rb");
        init();
    }

    ~BufferedInputStream(){
        close();
    }

    char read(){
        if(index < BUFFER_LEN){
            return szBuffer[index++];
        }else{
            init();
            return szBuffer[index++];
        }
    }

    void init(){
        fread(szBuffer, BUFFER_LEN * sizeof(char), 1, fp);
        index = 0;
    }

    int read_int(){
        int b1 = read() & 0xff;
        int b2 = read() & 0xff;
        int b3 = read() & 0xff;
        int b4 = read() & 0xff;
        return b4 << 24 | b3 << 16 | b2 << 8 | b1;
    }

    void unread(){
        index--;
    }

    void close(){
        if(fp != NULL){
            fclose(fp);
            fp = NULL;
        }
    }
};

#endif //PYVM_BUFFERED_INPUT_STREAM_HPP
