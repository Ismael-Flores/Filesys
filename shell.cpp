#include "sdisk.h"
#include "filesys.h"
#include "shell.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

Shell::Shell(string diskname,int numberofblocks, int blocksize):Filesys(diskname,numberofblocks,blocksize)
{

}

int Shell::dir(){
    vector<string> flist=ls();
    for(int i=0;i<flist.size();i++)
    {
        cout<<flist[i]<<endl;
    }
    return 0;
}

int Shell::add(string file, string buffer)
{
    int error = newfile(file);
    if (error < 1)
    {
        cout << "Sorry" << endl;
	return 0;
    }
  
    vector<string> blocks = block(buffer, getblocksize());
    for(int i = 0; i < blocks.size(); i++)
    {
	addblock(file, blocks[i]);
    }
    return 1;
}

int Shell::del(string file)
{
    int block = getfirstblock(file);
    while(block > 0) 
    {
	delblock(file, block);
	block = getfirstblock(file);
    }
    rmfile(file);
    return 1;
}

int Shell::type(string file)
{
    int block = getfirstblock(file);
    string buffer;
    while(block > 0)
    {
	string t;
	int error = readblock(file, block, t);
	buffer += t;
	block = nextblock(file, block);
    }
    cout << buffer << endl;
    cout << buffer.length() << endl;
   
    return 1;
}

int Shell::copy(string file1, string file2)
{
    int block = getfirstblock(file1);
    int error = newfile(file2);
    string buffer;

    if(block==-1)
    {
        cout<<"NO such file"<<endl;
        return 0;
    }

    while(block > 0)
    {
        string t;
        error = readblock(file1, block, t);
	buffer += t;
        addblock(file2, buffer);
        block = nextblock(file1, block);
    }
    return 0;
}




