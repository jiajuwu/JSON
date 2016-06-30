/*************************************************************************
    > File Name: read.cpp
    > Author: Wu Jiaju
    > Mail: jiaju.wu@nokia.com 
    > Created Time: Mon 18 Apr 2016 04:54:33 PM CST
 ************************************************************************/

#include <iostream>
#include <fstream>
#include "lm.helloworld.pb.h" 
using namespace std;

void ListMsg(const lm::helloworld & msg) { 
    cout << msg.id() << endl; 
    cout << msg.str() << endl; 
} 

int main(int argc, char* argv[]) { 

    lm::helloworld msg1; 

    { 
        fstream input("./log", ios::in | ios::binary); 
        if (!msg1.ParseFromIstream(&input)) { 
            cerr << "Failed to parse address book." << endl; 
            return -1; 
        } 
    } 

    ListMsg(msg1); 
}

