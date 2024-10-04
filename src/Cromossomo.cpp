#include "Cromossomo.hpp"

Cromossomo::Cromossomo(size_t quantidadeDeGenes) {
	std::random_device randomNumber;
	std::mt19937 seed(randomNumber());
	std::uniform_int_distribution<int> gap(0, 1);
	
	this->quantidadeDeGenes = quantidadeDeGenes;
	for (size_t i = 0; i < quantidadeDeGenes; ++i)
		this->genes += std::to_string(gap(seed)); 	
}

Cromossomo::~Cromossomo() {}

Cromossomo::Cromossomo(std::string primeiraMetade, std::string segundaMetade) {
	this->quantidadeDeGenes = primeiraMetade.size() + segundaMetade.size();
	this->genes = primeiraMetade + segundaMetade;
}

Cromossomo::Cromossomo(std::string genes) {
	this->quantidadeDeGenes = genes.size();
	this->genes = genes;
}

std::ostream& operator<<(std::ostream& os, Cromossomo* cromossomo) {
	os << cromossomo->genes;
	return os;
}
