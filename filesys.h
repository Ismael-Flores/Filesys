#ifndef FILESYS_H
#define FILESYS_H
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>
//#include <istringstream>
#include <cmath>
using namespace std;

class Filesys: public Sdisk
{
public:
Filesys(string diskname, int numberofblocks, int blocksize); // checks if filesys exists 
int fsclose(); // empty (done) 
int newfile(string file); //(done)
int rmfile(string file); 
int getfirstblock(string file); //returns first block # (done)
int addblock(string file, string block); // (done) 
int delblock(string file, int blocknumber);
int readblock(string file, int blocknumber, string& buffer); // (done)
int writeblock(string file, int blocknumber, string buffer); // (done)
int nextblock(string file, int blocknumber); // (done)
vector<string> ls();
vector<string> block(string buffer, int b);
private:
int rootsize;           // maximum number of entries in ROOT
int fatsize;            // number of blocks occupied by FAT
vector<string> filename;   // filenames in ROOT
vector<int> firstblock; // firstblocks in ROOT
vector<int> fat;// FAT
void buildfs(); // creates inital FAT, filename, firstblock (done)
int fssynch(); // (done)
void readfs();
bool checkblock(string file, int blocknumber); // (done)
};

#endif