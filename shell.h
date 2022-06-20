#ifndef SHELL_H
#define SHELL_H
#include "shell.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include "sdisk.h"
#include "filesys.h"

using namespace std; 

class Shell: public Filesys
{
public:
Shell(string filename,int numberofblocks, int blocksize);
int dir();// lists all files
int add(string file, string buffer);// add a new file using input from the keyboard
int del(string file);// deletes the file
int type(string file);//lists the contents of file
int copy(string file1, string file2);//copies file1 to file2
};

#endif