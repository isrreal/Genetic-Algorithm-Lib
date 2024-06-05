#ifndef CROMOSSOMO_HPP
#define CROMOSSOMO_HPP


#include <random>
#include <string>

struct Cromossomo {
	size_t quantidadeDeGenes;
	std::string genes;
	Cromossomo(size_t);
	Cromossomo(std::string, std::string);
	Cromossomo(std::string);
	~Cromossomo();
};

#endif
