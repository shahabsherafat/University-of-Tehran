all: CarWashManager clean

CarWashManager: main.o Carwash.o Stage.o Worker.o Car.o orders_implementation.o split_and_compares.o
	g++ -std=c++20 main.o Carwash.o Stage.o Worker.o Car.o orders_implementation.o split_and_compares.o -o CarWashManager.out
main.o: main.cpp
	g++ -std=c++20 -c main.cpp
Carwash.o: Carwash.cpp
	g++ -std=c++20 -c Carwash.cpp
Stage.o: Stage.cpp
	g++ -std=c++20 -c Stage.cpp
Worker.o: Worker.cpp
	g++ -std=c++20 -c Worker.cpp
Car.o: Car.cpp
	g++ -std=c++20 -c Car.cpp
orders_implementation.o: orders_implementation.cpp
	g++ -std=c++20 -c orders_implementation.cpp
split_and_compares.o: split_and_compares.cpp
	g++ -std=c++20 -c split_and_compares.cpp
	
clean:
	rm -f *.o
