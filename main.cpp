#include "table.h"
#include "sdisk.h"
#include "filesys.h"
#include "shell.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <string>

using namespace std;


int main()
{
 //
 //This main program inputs commands to the shell.
 //It inputs commands as : command op1 op2
 //You should modify it to work for your implementation.
 //
 Sdisk sdisk=Sdisk("sdisk.txt",256,128);
 Filesys fsys=Filesys("sdisk.txt",256,128);
 Shell shell=Shell("sdisk.txt",256,128);
 shell.add("file1", "data.txt"); 
 shell.add("file2", "This is the content");
 shell.add("file3", "Hello");
 //Table table=Table("sdisk.txt",256,128,"flatfile","indexfile");
 //table.Build_Table("data.txt");







 string s;
 string command="go";
 string op1,op2;

 while (command != "quit")
     {
       command.clear();
       op1.clear();
       op2.clear();
       cout << "$";
       getline(cin,s);
       int firstblank=s.find(' ');
       if (firstblank < s.length()) s[firstblank]='#';
       int secondblank=s.find(' ');
       command=s.substr(0,firstblank);
       if (firstblank < s.length())
         op1=s.substr(firstblank+1,secondblank-firstblank-1);
       if (secondblank < s.length())
         op2=s.substr(secondblank+1);
       if (command=="dir")
          {
       	// use the ls function	
         
	 shell.dir();
           }
       if (command=="add")
          {
           // The variable op1 is the new file 
         cout << "Add new file name: " << endl;
	 cin >> op1; 	
	 cout << "Enter file contents " << endl;
	 cin >> op2;
	 shell.add(op1,op2); 		
           }
       if (command=="del")
          {
           // The variable op1 is the file
	 cout << "Enter file name you want to delete: " << endl;
	 cin >> op1;
	 shell.del(op1);
           }
       if (command=="type")
          {
         // The variable op1 is the file
	 cout << "Enter the file you want to see contents of: " << endl;
	 cin >> op1;
	 cout << endl;
	 shell.type(op1); 
           }
       if (command=="copy")
          {
            // The variable op1 is the source file and the variable op2 is the destination file.    
	 cout << "Enter source file: " << endl;
	 cin >> op1;
	 cout << "Enter Destination file: " << endl;
	 cin >> op2; 
	 shell.copy(op1, op2);
           }
       if (command=="search")
          {
         
	cout << "Enter date: ";
	cin >> op1;
	cout << endl;
	cout << "Searching for "<< op1 << endl;
	//table.Search(op1);

           }
       
      }
 

    
      return 0;
}