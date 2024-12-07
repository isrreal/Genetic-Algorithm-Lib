CPPFLAGS=-std=c++17 -Wall -Wextra -O3
IPATH=-Iinc/
SRC=src/
OBJ=obj/

all: make_obj_folder app

app: main.gch GeneticAlgorithm.gch Chromosome.gch 
	g++ $(OBJ)main.gch $(OBJ)GeneticAlgorithm.gch $(OBJ)Chromosome.gch -o app
make_folder:

main.gch: $(SRC)main.cpp
	$(CHAIN)-gcc $(CPPFLAGS) $(IPATH) -c $(SRC)main.cpp -o $(OBJ)main.gch
                                        
GeneticAlgorithm.gch: $(SRC)GeneticAlgorithm.cpp                         
	g++ $(CPPFLAGS) $(IPATH) -c $(SRC)GeneticAlgorithm.cpp -o $(OBJ)GeneticAlgorithm.gch

Chromosome.gch: $(SRC)Chromosome.cpp 
	g++ $(CPPFLAGS) $(IPATH) -c $(SRC)Chromosome.cpp -o $(OBJ)Chromosome.gch
	

make_obj_folder:
	mkdir -p $(OBJ) 
clean:
	rm -rf $(OBJ)*.gch

