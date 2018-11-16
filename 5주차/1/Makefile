ALL = main run

all : $(ALL)
test : $(ALL)

main : Main.cpp
	g++-7 -Wall -lm -static -DEVAL -g -o Main -O2 Main.cpp -std=c++11

run : Main
	./Main < test.txt