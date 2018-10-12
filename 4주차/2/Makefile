ALL = main

all : $(ALL)

main : Main.cpp
	g++-7 -Wall -lm -g -static -DEVAL -o Main -O2 Main.cpp -std=c++11

clean :
	rm -rf $(ALL) main.o Main
