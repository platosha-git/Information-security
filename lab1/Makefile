all: install.exe app.exe program
install.exe: installer.o LinuxInfo.o
	g++ -o install.exe installer.o LinuxInfo.o
	
app.exe: main.o LinuxInfo.o
	g++ -o app.exe main.o LinuxInfo.o
	
program: hello.o
	g++ -o program hello.o

installer.o: installer.cpp
	g++ -c installer.cpp
	
main.o: main.cpp
	g++ -c main.cpp
	
LinuxInfo.o: LinuxInfo.cpp
	g++ -c LinuxInfo.cpp
	
hello.o: hello.cpp
	g++ -c hello.cpp

clean:
	rm *.o*.exe
