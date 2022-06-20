myprog : sdisk.o filesys.o shell.o table.o main.o 
	g++ -o myprog sdisk.o filesys.o shell.o table.o main.o
sdisk.o : sdisk.cpp
	g++ -c sdisk.cpp
filesys.o : filesys.cpp
	g++ -c filesys.cpp
shell.o : shell.cpp
	g++ -c shell.cpp
table.o : table.cpp
	g++ -c table.cpp
main.o : main.cpp
	g++ -c main.cpp
clean:
	rm *.o