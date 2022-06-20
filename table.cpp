#include "table.h"
#include "sdisk.h"
#include "filesys.h"
#include "shell.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

Table::Table(string diskname,int numberofblocks,int blocksize , string flatfile, string indexfile):Filesys(diskname,numberofblocks,blocksize)
{

	this->indexfile = indexfile;
	this->flatfile = flatfile;
	//numrec=0;
	newfile(flatfile);
	newfile(indexfile);
}

int Table::Build_Table(string input_file)
{
	ifstream infile;
	infile.open(input_file.c_str());
	vector<string> key;
	vector<int> b;
	string s;
	getline(infile, s);
	int number = 0;
	while(infile.good())
	{
		string k = s.substr(0,5);
		vector<string> blocks = block(s ,getblocksize());
		int bid = addblock(flatfile,blocks[0]);
		key.push_back(k);
		b.push_back(bid);
		getline(infile,s);

		if(infile.bad() and key.size()>0)
		{
			ostringstream indexstream;
			indexstream << key.size() << " ";
			for(int i=0;i < key.size(); i++)
			{
				indexstream  << key[i] << " " << b[i] << " ";
			}
			string buffer = indexstream.str();
			vector<string> blocks2 = block(buffer,getblocksize());
			int error = addblock(indexfile, blocks2[0]);
			key.clear();
			b.clear();
		}
	}
	return 0;
	
}
int Table::IndexSearch(string key)
{
	stringstream instream;
	int b = getfirstblock(indexfile);
	string bigbuffer;
	if(b <= 0)
	{
		return 0;
	}
	while( b != 0)
	{
		string buffer;
		int error = readblock(indexfile, b, buffer);
		bigbuffer += buffer;
		b = nextblock(indexfile, b);
	}
	//indexfile is a string in big buffer
	instream.str(bigbuffer);
	for(int i = 0; i < numrec ; i++)
	{
		string s;
		int block;
		instream >> key >> block;
		if(key==s)
		{
			return block;
		}
	}
	return -1;
	
}
int Table::Search(string value)
{
	int b = IndexSearch(value);
	if(b <= 0)
	{
		cout<<"No Record"<<endl;
		return -1;
	}
         else {
		string buffer;
		b = readblock(flatfile,b,buffer);
		cout << buffer << endl;
		return b;
	}
        //return 0; 
}