#ifndef CHROMOSOME_HPP 
#define CHROMOSOME_HPP

#include <iostream>
#include <random>
#include <string>

struct Chromosome {
	std::string genes;
    
    size_t fitness;

    Chromosome() = default;
    
	Chromosome(size_t);

	Chromosome(std::string, std::string);
	
    Chromosome(std::string);

    Chromosome(const Chromosome& chromosome);

    Chromosome& operator=(const Chromosome& chromosome) {
        if (this != &chromosome) {
            genes = chromosome.genes;
            fitness = chromosome.fitness;
        }

        return *this;
    }

    ~Chromosome() = default;
    
    friend std::ostream& operator<<(std::ostream& os, const Chromosome& chromosome);
};

#endif
