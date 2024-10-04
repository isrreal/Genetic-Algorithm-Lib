#ifndef ALGORITMO_GENETICO_HPP
#define ALGORITMO_GENETICO_HPP

#include <iostream>
#include <random>
#include <vector>
#include <memory>
#include "Cromossomo.hpp"

class AlgoritmoGenetico {
	protected:
		size_t tamanhoDaPopulacao;
		size_t quantidadeDeGenes;
		float taxaDeMutacao;
		float taxaDeElitismo;
		std::vector<Cromossomo*> populacao;
		std::vector<std::string> subgrupos;
		
		Cromossomo* criarCromossomo(size_t);
              	virtual void criarPopulacao(size_t , size_t);
        	std::vector<std::string> binarioParaDecimal(std::vector<std::string>);
        	virtual std::pair<Cromossomo*, int> fitness(Cromossomo*);

              	Cromossomo* selecionarMelhorIndividuo(Cromossomo*, Cromossomo*);
              	virtual Cromossomo* crossOver(Cromossomo*, Cromossomo*);
        	Cromossomo* mutacao(Cromossomo*);
        	std::vector<Cromossomo*> elitismo();
              	Cromossomo* obterMelhorIndividuo();
        	std::vector<Cromossomo*> gerarNovaPopulacao();
	public:
		AlgoritmoGenetico(size_t tamanhoDaPopulacao, size_t quantidadeDeGenes,
			       	float taxaDeMutacao, float taxaDeElitismo):
        				tamanhoDaPopulacao(tamanhoDaPopulacao), quantidadeDeGenes(quantidadeDeGenes),
				       	taxaDeMutacao(taxaDeMutacao), taxaDeElitismo(taxaDeElitismo) {}
	
		Cromossomo* rodarAG(size_t);	
        	std::string binarioParaDecimal(std::string);
        	std::vector<std::string> leituraDeValores(Cromossomo*, size_t);
};	

#endif
