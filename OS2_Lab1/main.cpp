//
//  main.cpp
//  OS2_Lab1
//
//  Created by EzCoder on 23.12.14.
//  Copyright (c) 2014 EzCoder. All rights reserved.
//

#include <iostream>
using namespace std;

#define BLOCK_SIZE 1024
#define BLOCK_COUNT  10
#define cls system("clear")

struct
{
    bool bLock;
    int  ParentIndex;
    int  size;
}memory[BLOCK_COUNT];



void PrintMemStat()
{
    for (int i = 0; i < BLOCK_COUNT; i++) {
        if (memory[i].bLock == false) {
            cout<<i<<") Блок свободен"<<endl;
        }else
        {
            cout<<i<<") Блок занят (size:"<<memory[i].size<<"/"<<BLOCK_SIZE<<")"<<endl;
        }
    }
}

void Init()
{
    memset(&memory[0], 0, sizeof(memory[0])*BLOCK_COUNT);
    cls;
    PrintMemStat();
}

void Alloc_Memory(int size)
{
    
}

void Release_Memory(int index)
{
    
}

char* GetParam(char *str){
    char* offset = strstr(str, "-");
    if (offset != nullptr) {
        return offset+1;
    }
    return nullptr;
}

int main(int argc, const char * argv[]) {
    Init();
    char cBuffer[1024];
    
    while (true) {
        cin>>cBuffer;
        cls;
        PrintMemStat();
        if (!strcmp(cBuffer, "exit")) {
            break;
        }else if(strstr(cBuffer,"alloc"))
        {
            cout<<"Занять "<<GetParam(cBuffer)<<" памяти"<<endl;
            Alloc_Memory(atoi(GetParam(cBuffer)));
        }else if(strstr(cBuffer,"free"))
        {
            cout<<"Освободить "<<GetParam(cBuffer)<<"-й блок памяти"<<endl;
            Release_Memory(atoi(GetParam(cBuffer)));
        }
        PrintMemStat();
    }
    
    return 0;
}
