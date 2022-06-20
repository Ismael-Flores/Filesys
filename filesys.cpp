#include "sdisk.h"
#include "filesys.h"
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>
#include <cmath>

using namespace std; 

    Filesys::Filesys(string diskname, int numberofblocks, int blocksize):Sdisk(diskname,numberofblocks,blocksize)
{
        string buffer;

        rootsize = getblocksize()/12;
        fatsize = (getnumberofblocks()*5)/(getblocksize())+1;
        int code = getblock(0,buffer);
        if(code == 0){
                cout << "bad device";
                return;
        }
        code = getblock(1, buffer);

        if(buffer[0]=='#'){
                cout<<"No file system found " << endl;
                for(int i=0; i<=rootsize; i++){
                        filename.push_back("XXXXX");
                        firstblock.push_back(0);
                }
                fat.push_back(fatsize+2);
                fat.push_back(1);
                for(int i=0; i < fatsize ; i++){
                        fat.push_back(1);
                }
                for(int i = fatsize + 2; i < getnumberofblocks(); i++){
                        fat.push_back(i+1);
                }
                fat[fat.size()-1] = 0;
                fssynch();
                cout << "You have created file system" << endl;


        }
       else{
                istringstream istream;
                string buffer;
                getblock(1, buffer);

                istream.str(buffer);
                for(int i=0; i<rootsize; i++)
                {
                        string s;
                        int t;
                        istream >> s;
                        istream >> t;
                        filename.push_back(s);
                        firstblock.push_back(t);
                }

                string buffer2;
                istringstream istream2;
                for(int i=0; i<fatsize; i++)
                {
                        string b;
                        getblock(i + 2, b);
                        buffer2 += b;
                }

                istream2.str(buffer2);
                for(int i=0; i<getnumberofblocks(); i++)
                {
                        int t;
                        istream2 >> t;
                        fat.push_back(t);
                }

        }
}

vector<string> Filesys::block(string buffer, int b){
    vector<string> blocks;
    int numberofblocks=0;

    if (buffer.length() % b == 0)
    {
        numberofblocks = buffer.length()/b;
    }
    else
    {
        numberofblocks = buffer.length()/b +1;
    }

    string tempblock;
    for (int i=0; i<numberofblocks; i++)
    {
        tempblock=buffer.substr(b*i,b);
        blocks.push_back(tempblock);
    }

    int lastblock = blocks.size()-1;

    for (int i = blocks[lastblock].length(); i<b; i++)
    {
        blocks[lastblock] += "#";
    }

    return blocks;
}


int Filesys::fsclose(){
	fssynch();
	return 0;
}

int Filesys::fssynch(){
	ostringstream ostream;
    
    	for(int i = 0; i < rootsize; ++i)
	{
        	ostream << filename[i] << " " << firstblock[i] << " ";  
    	}	

    	string buffer = ostream.str();

	vector<string> blocks=block(buffer, getblocksize());
	putblock(1,blocks[0]);
    
    	ostringstream ostream2;
    	for(int i = 0; i < fat.size(); i++){
        	ostream2 << fat[i] << " ";
    	}
    	string buffer2 = ostream2.str();
    	vector<string> block2 = block(buffer2,getblocksize());
    
    	for(int i = 0; i < block2.size(); i++)
	{
        	putblock(2+i, block2[i]);
       	}
    	return 1; 
}


int Filesys::newfile(string file){
        for(int i=0; i<filename.size(); i++)
        {
            if(filename[i] == file)
	    {
                cout << "The file " << file << " already exists!" << endl;
                return 0;
            }
        }

        for(int i=0; i<filename.size(); i++)
	{
            if (filename[i] == "XXXXX"){
                cout << "Creating new file !" << file << endl;
                filename[i] = file;
		firstblock[i]=0;
		fssynch();
                return 1;
            }
        }
	cout << "No room in root" << " " << endl;
     	return 0;
}

int Filesys::rmfile(string file)
{
    for(int i = 0; i < filename.size(); i++) 
    {
         if(filename[i] == file && firstblock[i] == 0) 
         {
	     filename[i] = "XXXXX";
	     firstblock[i] = 0;
	 }
     }
     fssynch();
     return 1;
}

int Filesys::getfirstblock(string file)
{
   
    for(int i=0; i<filename.size(); i++)
    {
        if(filename[i]==file)
        {
            return firstblock[i];
        }
    }
    cout << "No such file" << " " << endl;
    return -1;
}


int Filesys::addblock(string file, string block)
{ // return allocated block  number 
	int first = getfirstblock(file);

	if(first == -1)
	{
		cout << "no such file";
		return 0;
	}
	int allocate = fat[0];
	fat[0] = fat[fat[0]];
	fat[allocate] = 0;
	if(first == 0)
	{
		for (int i = 0;i < filename.size(); i++)
		{
			if(filename[i]==file)
			{
				firstblock[i] = allocate;
			}
		}	
	}
	else
	{
		int b = first;
		while(fat[b] != 0)
		{
			b = fat[b];
		}
		fat[b] = allocate;
	}
	//fssynch();
	putblock(allocate, block);
	fssynch();
	return allocate;
}

bool Filesys::checkblock(string file, int blocknumber) // checks if blocknumber belongs to file
{
    //check if file exists
    int b = getfirstblock(file); // have first block in file also can be 0 if no files
    
    //if(b == -1)
   // {
     //   cout << "No such file";
      //  return false;
    //}

    if(b == blocknumber)
    {
        return true;
    } 

    while(fat[b] != 0) 
    {
        if(fat[b]==blocknumber)
        {
            return true;
        }
        b = fat[b]; 
    }
    return false;
}

int Filesys::delblock(string file, int blocknumber)
{
    if(!checkblock(file,blocknumber))
    {
	return 0;
    }
  
    if(blocknumber == getfirstblock(file)) 
    {
       	for(int i = 0; i < filename.size(); i++) 
	{
	    if(filename[i] == file) 
	    {
	        firstblock[i] = fat[blocknumber];
		break;
	    }
	}
    }
    else 
    {
	int b = getfirstblock(file);
	while(fat[b] != blocknumber) 
	{
	    b = fat[b];
	}
	fat[b] = fat[blocknumber];
    }
    fat[blocknumber] = fat[0];
    fat[0] = blocknumber;
    fssynch();
    //return 0;
}


int Filesys::readblock(string file, int blocknumber, string& buffer) 
{
    if(checkblock(file, blocknumber))
    {
        getblock(blocknumber, buffer);
        return 1;
    }
    else
    {
        cout << "No can do";
        return 0;
    }
}
int Filesys::writeblock(string file, int blocknumber, string buffer)
{
    if(checkblock(file, blocknumber))
    {
        putblock(blocknumber, buffer);
        return 1;
    }
    else
    {
        cout << "No can do";
        return 0;
    }
}

int Filesys::nextblock(string file, int blocknumber)
{
    int blockid = getfirstblock(file);
	while(blockid != blocknumber){
		blockid = fat[blockid];
	}
	return fat[blockid];	
}

vector<string> Filesys::ls(){
	vector<string> flist;
	for(int i=0;i<filename.size();i++){
		if(filename[i]!="XXXXX"){
			flist.push_back(filename[i]);
		}
	}
	return flist;
}
