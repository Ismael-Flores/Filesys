myprog : sdisk.o filesys.o shell.o table.o main.o 
	c++ -o myprog sdisk.o filesys.o shell.o table.o main.o
sdisk.o : sdisk.cpp
	c++ -c sdisk.cpp
filesys.o : filesys.cpp
	c++ -c filesys.cpp
shell.o : shell.cpp
	c++ -c shell.cpp
table.o : table.cpp
	c++ -c table.cpp
main.o : main.cpp
	c++ -c main.cpp
clean:
	rm *.o