#include "Chromosome.hpp"

Chromosome::Chromosome(size_t genesSize) {
	std::random_device randomNumber;
	std::mt19937 seed(randomNumber());
	std::uniform_int_distribution<short> gap(0, 1);
	
	for (size_t i {0}; i < genesSize; ++i) {
		this->genes += std::to_string(gap(seed)); 	
    }

    fitness = 0;
}

Chromosome::Chromosome(const Chromosome& chromosome): genes(chromosome.genes), fitness(chromosome.fitness) {} 

Chromosome::Chromosome(std::string firstHalf, std::string secondHalf): genes(firstHalf + secondHalf), fitness(0) {}

Chromosome::Chromosome(std::string genes): genes(genes), fitness(0) {} 

std::ostream& operator<<(std::ostream& os, const Chromosome& chromosome) {
	os << "[" << chromosome.genes << "]" << "fitness: " << chromosome.fitness;
	return os;
}
