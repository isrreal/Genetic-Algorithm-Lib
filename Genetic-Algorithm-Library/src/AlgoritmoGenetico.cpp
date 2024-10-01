#include "AlgoritmoGenetico.hpp"

//
// retorna um novo cromossomo com a quantidade de genes especificada
//

Cromossomo* AlgoritmoGenetico::criarCromossomo(size_t quantidadeDeGenes) {
	return new Cromossomo(quantidadeDeGenes);
}

//
// A função cria uma população com cromossomos com uma quantidade específica de genes
//

void AlgoritmoGenetico::criarPopulacao(size_t quantidadeDeCromossomos, size_t quantidadeDeGenes) {
	for (size_t i = 0; i < quantidadeDeCromossomos; ++i)
		this->populacao.push_back(this->criarCromossomo(quantidadeDeGenes));
}

// 
// A função separa os genes do cromossomo em subgrupos de cadeias com o tamanho especificado
// retorna um vetor de strings contendo os valores dos subgrupos  
//

std::vector<std::string> AlgoritmoGenetico::leituraDeValores(Cromossomo* cromossomo, size_t tamanhoDaCadeia) {
	std::string valor = "";
	std::vector<std::string> subgrupos;

	for (size_t i = 1; i < cromossomo->quantidadeDeGenes + 1; ++i) {
		valor += cromossomo->genes[i - 1];
		if (i % tamanhoDaCadeia == 0) {
			subgrupos.push_back(valor);
			valor = "";
		}
	}

	return subgrupos;
}

//
// A função converte os valores binarios dos genes em decimais
// retorna um vetor contendo os valores em decimal dos binarios de entrada
//

std::vector<std::string> AlgoritmoGenetico::binarioParaDecimal(std::vector<std::string> binarios) {
	std::vector<std::string> decimais;

	for (auto it: binarios) 
		decimais.push_back(binarioParaDecimal(it));

	return decimais;
}

//
// retorna a conversão em decimal do binário de entrada  
//

std::string AlgoritmoGenetico::binarioParaDecimal(std::string binario) {
	std::string decimais = "";
	int valor = 0;
	for (size_t i = 0, j = binario.size() - 1; i < binario.size(); ++i, --j) 
		valor += (binario.data()[i] == '1' ? 1 : 0) * std::pow(2, j);
	return std::to_string(valor);
}

// a função recebe um cromossomo e atribui sua nota de aptidão
// retorna um par contendo o cromossomo e sua nota de aptidão

std::pair<Cromossomo*, int> AlgoritmoGenetico::fitness(Cromossomo* cromossomo) {
	size_t quantidadeDeUns = 0;
	for (auto it: cromossomo->genes)
		if (it == '1')
			++quantidadeDeUns;
	return {cromossomo, quantidadeDeUns};
}

// a função recebe dois cromossomos e seleciona, dentro os dois, o que possui melhor genética
// retorna o cromossomo com mais aptidão dentre os comparados

Cromossomo* AlgoritmoGenetico::selecionarMelhorIndividuo(Cromossomo* cromossomo1, Cromossomo* cromossomo2) {
	return (this->fitness(cromossomo1).second > this->fitness(cromossomo2).second ? cromossomo1 : cromossomo2);
}

//
// a função realiza o cross over completo de dois cromossomos, e cria um cromossomo filho, contendo genes dos cromossomos pais 
// retorna um cromossomo filho, contendo o material genético dos cromossomos pai e mãe
//
Cromossomo* AlgoritmoGenetico::crossOver(Cromossomo* pai, Cromossomo* mae) {
	if (pai->quantidadeDeGenes % 2 != 0)
		pai->genes = "0" + pai->genes;
	if (mae->quantidadeDeGenes % 2 != 0)
		mae->genes = "0" + mae->genes;
	if (pai->quantidadeDeGenes > mae->quantidadeDeGenes) {
		int digitosExtras = (pai->quantidadeDeGenes - mae->quantidadeDeGenes);
		mae->genes = std::string("0", digitosExtras) + mae->genes;	
	}

	if (mae->quantidadeDeGenes > pai->quantidadeDeGenes) {
		int digitosExtras = (mae->quantidadeDeGenes - pai->quantidadeDeGenes);
		pai->genes = std::string("0", digitosExtras) + pai->genes;	
	}
		
	std::string parte1 = pai->genes.substr(0, pai->quantidadeDeGenes / 2);
	std::string parte2 = mae->genes.substr(mae->quantidadeDeGenes / 2, mae->quantidadeDeGenes);
	return new Cromossomo(parte1, parte2);
}

//
// essa função simula a mutação de genética do cromossomo, alterando seus genes baseados na taxa de mutação
// retorna um novo cromossomo sujeito a mutação genética
//

Cromossomo* AlgoritmoGenetico::mutacao(Cromossomo* cromossomo) {
	std::string cromossomoMutado = cromossomo->genes;
        std::random_device randomNumber;
        std::mt19937 seed(randomNumber()); 
        std::uniform_real_distribution<> gap(0.0, 1.0);
	double sorteio = 0.0;
        for (size_t i = 0; i < cromossomoMutado.size(); ++i) {
            sorteio = gap(seed);
            if (sorteio <= this->taxaDeMutacao)
                cromossomoMutado[i] = (cromossomoMutado[i] == '0' ? '1' : '0'); 
        }

        return new Cromossomo(cromossomoMutado);
}

//
// A função simula a identificação de um cromossomo geneticamente superior aos demais da população, baseado na taxa de elitismo
// retorna uma nova população contendo os genes do cromossomo geneticamente superior 
//
 
std::vector<Cromossomo*> AlgoritmoGenetico::elitismo() {
	std::vector<Cromossomo*> novaPopulacao;
	Cromossomo* melhorIndividuo = this->obterMelhorIndividuo();
	size_t numeroDeRepeticoes = this->populacao.size() * this->taxaDeElitismo;

	for (size_t i = 0; i < numeroDeRepeticoes; ++i)
		novaPopulacao.push_back(melhorIndividuo);

	return novaPopulacao;
}

//
// A função escolhe aleatoriamente os cromossomos da população inicial e testa a aptidão de cada um 
// retorna o cromossomo geneticamente superior 
//

Cromossomo* AlgoritmoGenetico::obterMelhorIndividuo() {
	std::random_device randomNumber;
	std::mt19937 seed(randomNumber());
	std::uniform_int_distribution<int> gap(0, this->populacao.size() - 1);
	std::pair<Cromossomo*, int> melhorIndividuo = this->fitness(this->populacao[gap(seed)]);
	std::pair<Cromossomo*, int> individuo;
	for (size_t i = 0; i < this->populacao.size(); ++i) {
		individuo = this->fitness(this->populacao[i]);
		if (individuo.second > melhorIndividuo.second)
			melhorIndividuo = individuo;
	}

	return melhorIndividuo.first;
}

//
// A função simula a reprodução de uma nova população geneticamente superior, sujeitas a mutações e elitismo, usando a população inicial
// retorna uma nova população geneticamente superior
//

std::vector<Cromossomo*> AlgoritmoGenetico::gerarNovaPopulacao() {
	std::vector<Cromossomo*> novaPopulacao = this->elitismo();
	std::random_device randomNumber;
	std::mt19937 seed(randomNumber());
	std::uniform_int_distribution<int> gap(0, this->populacao.size() - 1);
	Cromossomo* selecionado1 = nullptr;
	Cromossomo* selecionado2 = nullptr;
	
	Cromossomo* individuoMaisApto1 = nullptr;
	Cromossomo* individuoMaisApto2 = nullptr;
	
	Cromossomo* novoIndividuo = nullptr;
	Cromossomo* filho = nullptr;

	while (novaPopulacao.size() < this->populacao.size()) {
		selecionado1 = this->populacao[gap(seed)];
		selecionado2 = this->populacao[gap(seed)];

		individuoMaisApto1 = this->selecionarMelhorIndividuo(selecionado1, selecionado2);
			
		selecionado1 = this->populacao[gap(seed)];
		selecionado2 = this->populacao[gap(seed)];

		individuoMaisApto2 = this->selecionarMelhorIndividuo(selecionado1, selecionado2);
		novoIndividuo = this->crossOver(individuoMaisApto1, individuoMaisApto2);

		filho = this->mutacao(novoIndividuo);
		novaPopulacao.push_back(filho);
	}
	
	return novaPopulacao;
}

// 
// A função aplica o algoritmo genético, simulando mutações e elitismo, utilizando uma quantidade específica de gerações
// retorna o melhor indivíduo dentre as gerações
//

Cromossomo* AlgoritmoGenetico::rodarAG(size_t quantidadeDeGeracoes) {
	this->criarPopulacao(this->tamanhoDaPopulacao, this->quantidadeDeGenes);
	Cromossomo* melhorIndividuo = nullptr;

	for (size_t i = 0; i < quantidadeDeGeracoes; ++i) {
		melhorIndividuo = this->obterMelhorIndividuo();
		this->populacao = this->gerarNovaPopulacao();	
	}

	return melhorIndividuo;
}


