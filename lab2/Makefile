all: app.exe
	
app.exe: main.o enigma.o rotor.o reflector.o
	g++ -o app.exe main.o enigma.o rotor.o reflector.o
	
main.o: main.cpp
	g++ -c main.cpp
	
enigma.o: enigma.cpp
	g++ -c enigma.cpp

rotor.o: rotor.cpp
	g++ -c rotor.cpp
	
reflector.o: reflector.cpp
	g++ -c reflector.cpp

clean:
	rm *.o*.exe
