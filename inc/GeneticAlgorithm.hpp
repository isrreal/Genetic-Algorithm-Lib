#ifndef GENETIC_ALGORITHM_HPP
#define GENETIC_ALGORITHM_HPP

#include <iostream>
#include <random>
#include <vector>
#include <memory>
#include "Chromosome.hpp"

class GeneticAlgorithm {
	protected:
		size_t population_size;
		size_t genes_size;
		float mutation_rate;
		float elitism_rate;
		std::vector<Chromosome> population;
		std::vector<std::string> sub_groups;
	    Chromosome best_chromosome;
    
		virtual Chromosome generateChromosome(size_t);
        virtual void createPopulation(size_t , size_t);
        std::vector<std::string> binaryToDecimal(const std::vector<std::string>&);
        virtual void fitness(Chromosome&);

        Chromosome& chooseBestSolution(Chromosome&, Chromosome&);
        Chromosome& chooseWorstSolution(Chromosome&, Chromosome&);

        Chromosome& tournamentSelection(const std::vector<Chromosome>&);

       	virtual Chromosome crossOver(const Chromosome&, const Chromosome&);
        virtual void mutation(Chromosome&);
       	std::vector<Chromosome>& elitism(float mutation_rate);
        std::vector<Chromosome>& createNewPopulation();

	public:

		GeneticAlgorithm(size_t population_size, size_t genes_size,
			       	float mutation_rate, float elitism_rate):
        				population_size(population_size), genes_size(genes_size),
				       	mutation_rate(mutation_rate), elitism_rate(elitism_rate),
                        population(population_size), sub_groups(0) {}
	
		Chromosome run(size_t);	
        std::string binaryToDecimal(std::string);
        std::vector<std::string> readValues(const Chromosome&, size_t);
};	

#endif
