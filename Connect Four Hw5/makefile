all:connectfour
main.o:main.cpp 
	g++ -std=c++11 -c main.cpp
ConnectFourAbstract.o:ConnectFourAbstract.cpp
	g++ -std=c++11 -c ConnectFourAbstract.cpp
ConnectFourPlus.o:ConnectFourPlus.cpp
	g++ -std=c++11 -c ConnectFourPlus.cpp
ConnectFourDiagonal.o:ConnectFourDiagonal.cpp
	g++ -std=c++11 -c ConnectFourDiagonal.cpp
ConnectFourUndo.o:ConnectFourUndo.cpp
	g++ -std=c++11 -c ConnectFourUndo.cpp
Cell.o:Cell.cpp
	g++ -std=c++11 -c Cell.cpp
connectfour:main.o ConnectFourAbstract.o ConnectFourPlus.o ConnectFourDiagonal.o ConnectFourUndo.o Cell.o
	g++ -std=c++11 -o exe main.o ConnectFourAbstract.o ConnectFourPlus.o ConnectFourDiagonal.o ConnectFourUndo.o Cell.o
clean:
	rm *.o exe
