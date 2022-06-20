#ifndef TABLE_H
#define TABLE_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include "sdisk.h"
#include "filesys.h"
#include "shell.h"

class Table:public Filesys
{
public:
	Table(string diskname,int blocksize,int numberofblocks, string flatfile, string indexfile);
	int Build_Table(string input_file);
	int Search(string value);
private:
	string flatfile;
	string indexfile;
	int numrec; //number of records
	//Filesys filesystem;
	int IndexSearch(string key);
};

#endif