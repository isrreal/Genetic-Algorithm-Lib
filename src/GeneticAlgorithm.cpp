#include "GeneticAlgorithm.hpp"

//
// retorna um novo chromosome com a quantidade de genes especificada
//

Chromosome GeneticAlgorithm::generateChromosome(size_t genes_size) {
    Chromosome chromosome {Chromosome(genes_size)};
    fitness(chromosome);

	return chromosome;
}

//
// A função cria uma população com chromosomes com uma quantidade específica de genes
//

void GeneticAlgorithm::createPopulation(size_t population_size, size_t genes_size) {
	for (size_t i {0}; i < population_size; ++i) {
		population.push_back(generateChromosome(genes_size));
    }
}

// 
// A função separa os genes do chromosome em subgrupos de cadeias com o tamanho especificado
// retorna um vetor de strings contendo os valuees dos subgrupos  
//

std::vector<std::string> GeneticAlgorithm::readValues(const Chromosome& chromosome, size_t string_size) {
	std::string value {};
	std::vector<std::string> sub_group;
    
    sub_group.reserve(string_size);
    
	for (size_t i {1}; i < genes_size + 1; ++i) {
		value += chromosome.genes[i - 1];
		if (i % string_size == 0) {
			sub_groups.push_back(value);
			value = "";
		}
	}
    
	return sub_groups;
}

//
// A função converte os valuees binarys dos genes em decimais
// retorna um vetor contendo os valuees em decimal dos binarys de entrada
//

std::vector<std::string> GeneticAlgorithm::binaryToDecimal(const std::vector<std::string>& binary) {
	std::vector<std::string> decimals;
    decimals.reserve(genes_size); 
    
	for (const auto& it: binary) { 
		decimals.push_back(binaryToDecimal(it));
    }

	return decimals;
}

//
// retorna a conversão em decimal do binário de entrada  
//

std::string GeneticAlgorithm::binaryToDecimal(std::string binary) {
	std::string decimals {}; 
	int value {};
	for (size_t i {0}, j {binary.size() - 1}; i < binary.size(); ++i, --j) { 
		value += (binary.data()[i] == '1' ? 1 : 0) * std::pow(2, j);
    }

	return std::to_string(value);
}

// a função recebe um chromosome e atribui sua nota de aptidão
// retorna um par contendo o chromosome e sua nota de aptidão

void GeneticAlgorithm::fitness(Chromosome& chromosome) {
	size_t ones_amount {0};
	for (auto it: chromosome.genes) {
		if (it == '1') {
			++ones_amount;
        }
    }

    chromosome.fitness = ones_amount;
}

// a função recebe dois chromosomes e seleciona, dentro os dois, o que possui melhor genética
// retorna o chromosome com mais aptidão dentre os comparados

Chromosome& GeneticAlgorithm::chooseBestSolution(Chromosome& chromosome1, Chromosome& chromosome2) {
    return (chromosome1.fitness < chromosome2.fitness ? chromosome1: chromosome2);
}

Chromosome& GeneticAlgorithm::chooseWorstSolution(Chromosome& chromosome1, Chromosome& chromosome2) {
    return (chromosome1.fitness > chromosome2.fitness ? chromosome1: chromosome2);
}

Chromosome& GeneticAlgorithm::tournamentSelection(const std::vector<Chromosome>& population) {
    constexpr float parameter { 0.75f }; 
    std::random_device randomNumber;
    std::mt19937 seed(randomNumber()); 
    std::uniform_int_distribution<size_t> gap(0, population_size - 1);
    std::uniform_real_distribution<float> prob(0.0, 1.0);   

    const Chromosome& c1 { population[gap(seed)] };
    const Chromosome& c2 { population[gap(seed)] };

    float probability { prob(seed) };

    if (probability < parameter) {
        return chooseBestSolution(const_cast<Chromosome&>(c1), const_cast<Chromosome&>(c2));
    } 
    else {
        return chooseWorstSolution(const_cast<Chromosome&>(c1), const_cast<Chromosome&>(c2));
    }
}

//
// a função realiza o cross over completo de dois chromosomes, e cria um chromosome filho, contendo genes dos chromosomes fathers 
// retorna um chromosome filho, contendo o material genético dos chromosomes father e mãe
//

Chromosome GeneticAlgorithm::crossOver(const Chromosome& chromosome1, const Chromosome& chromosome2) {
    Chromosome father {chromosome1};
    Chromosome mother {chromosome2}; 

    if (father.genes.size() % 2 != 0) {
        father.genes = std::string("0") + father.genes;
    }
    
    if (mother.genes.size() % 2 != 0) {
        mother.genes = std::string("0") + mother.genes;
    }   
    
    if (father.genes.size() > mother.genes.size()) {
        size_t extra_digits = father.genes.size() - mother.genes.size();
        mother.genes = std::string(extra_digits, '0') + mother.genes;	
    }

    if (mother.genes.size() > father.genes.size()) {
        size_t extra_digits = mother.genes.size() - father.genes.size();
        father.genes = std::string(extra_digits, '0') + father.genes;	
    }
		
    std::string firstHalf = father.genes.substr(0, father.genes.size() / 2);
    std::string secondHalf = mother.genes.substr(mother.genes.size() / 2);

    return Chromosome(firstHalf, secondHalf);
}


    //
    // essa função simula a mutação de genética do chromosome, alterando seus genes baseados na taxa de mutação
    // retorna um novo chromosome sujeito a mutação genética
    //

    void GeneticAlgorithm::mutation(Chromosome& chromosome) {
        std::random_device randomNumber;
        std::mt19937 seed(randomNumber()); 
        std::uniform_real_distribution<float> gap(0.0, 1.0);

        double raffle {0.0};
        for (size_t i {0}; i < genes_size; ++i) {
            raffle = gap(seed);
            if (raffle <= mutation_rate) {
                chromosome.genes[i] = (chromosome.genes[i] == '0' ? '1' : '0'); 
            }
        }
    }

    //
    // A função simula a identificação de um chromosome geneticamente superior aos demais da população, baseado na taxa de elitism
    // retorna uma nova população contendo os genes do chromosome geneticamente superior 
    //
     
    std::vector<Chromosome>& GeneticAlgorithm::elitism(float elitism_rate) {
       
        std::random_device randomNumber;
        std::mt19937 seed(randomNumber()); 
        std::uniform_int_distribution<size_t> gap(0, population_size - 1);

        Chromosome bestSolution = [&]() {
            
		    Chromosome bestSolution { population[gap(seed)] };
		    Chromosome solution;
		    for (const auto& chromosome: population) {
		    	solution = chromosome;		
		    	if (chromosome.fitness > bestSolution.fitness) {
		    		bestSolution = chromosome;
		    	}
		    }

		    return bestSolution;
	    }();
        
        size_t iterations { static_cast<size_t>(std::ceil(population_size * elitism_rate)) };
        
        population.clear();
        population.reserve(iterations);

        for (size_t i {0}; i < iterations; ++i) {
            population.emplace_back(bestSolution);
        } 

        return population;
    }

    // A função simula a reprodução de uma nova população geneticamente superior, sujeitas a mutações e elitism, usando a população inicial
    // retorna uma nova população geneticamente superior
    //

    std::vector<Chromosome>& GeneticAlgorithm::createNewPopulation() {
        std::vector<Chromosome> temp { population };
        elitism(elitism_rate);

        temp.reserve(population_size);
        
        std::random_device randomNumber;
        std::mt19937 seed(randomNumber());
        std::uniform_int_distribution<size_t> gap(0, population_size - 1);

        Chromosome selected1;
        Chromosome selected2;
        Chromosome offspring;

        while (population.size() < population_size) {
            selected1 = temp[gap(seed)];
            selected2 = temp[gap(seed)];

            offspring = crossOver(selected1, selected2);

            mutation(offspring);

            population.emplace_back(offspring);
        }
        
        population.swap(temp); 

        return population;
    }

    // 
    // A função aplica o algoritmo genético, simulando mutações e elitism, utilizando uma quantidade específica de gerações
    // retorna o melhor indivíduo dentre as gerações
    //

    Chromosome GeneticAlgorithm::run(size_t generations) {
        createPopulation(population_size, genes_size);
        Chromosome bestChromosome;

        for (size_t i {0}; i < generations; ++i) {
            bestChromosome = tournamentSelection(population);
            population.swap(createNewPopulation());	
	    }

	    return bestChromosome;
    }


