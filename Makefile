start: prog4

prog4: D_00_P4_main.o D_00_P4_func.o
	g++ D_00_P4_main.o D_00_P4_func.o -o prog4

main.o: D_00_P4_main.cpp	D_00_P4_func.h D_00_P4_class.h
	g++ -c D_00_P4_main.cpp

func.o: D_00_P4_func.cpp D_00_P4_func.h D_00_P4_class.h
	g++ -c D_00_P4_func.cpp

clean:
	rm prog4 *o

run: prog4
	./prog4