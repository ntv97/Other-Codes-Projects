finalproj: finalproject.o main.o
	g++ finalproject.o main.o -o finalproj

finalproject.o: model.h finalproject.cpp main.cpp
	g++ -c -Wall -Werror finalproject.cpp main.cpp

execs = finalproj 

clean:
	rm -f $(execs) *.o
