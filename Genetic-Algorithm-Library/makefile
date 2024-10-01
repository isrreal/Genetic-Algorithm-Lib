CPPFLAGS=-std=c++17 -Wall -Wextra
IPATH=-Iinc/
SRC=src/
OBJ=obj/

all: app

app: main.gch AlgoritmoGenetico.gch Cromossomo.gch 
	g++ $(OBJ)main.gch $(OBJ)AlgoritmoGenetico.gch $(OBJ)Cromossomo.gch -o app

main.gch: $(SRC)main.cpp
	$(CHAIN)-gcc $(CPPFLAGS) $(IPATH) -c $(SRC)main.cpp -o $(OBJ)main.gch
                                        
AlgoritmoGenetico.gch: $(SRC)AlgoritmoGenetico.cpp                         
	g++ $(CPPFLAGS) $(IPATH) -c $(SRC)AlgoritmoGenetico.cpp -o $(OBJ)AlgoritmoGenetico.gch

Cromossomo.gch: $(SRC)Cromossomo.cpp 
	g++ $(CPPFLAGS) $(IPATH) -c $(SRC)Cromossomo.cpp -o $(OBJ)Cromossomo.gch
	

clean:
	rm -rf $(OBJ)*.gch

