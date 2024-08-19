#include <iostream>
#include <fstream>  // Biblioteca para operações com arquivos
#include <string>   // Biblioteca para manipulação de strings
#include <vector>
#include <sstream>

struct Processos
{
    int tempArrival;
    int tempDuration;
};

std::vector<Processos> processos;

void readFile(){
     std::ifstream inputFile("arquivo.txt");  // Abre o arquivo para leitura

    // Verifica se o arquivo foi aberto com sucesso
    if (!inputFile.is_open()) {
        std::cerr << "Não foi possível abrir o arquivo!" << std::endl;
        return;
    }

    std::string linha;

    // Lê o arquivo linha por linha
    while (std::getline(inputFile, linha)) {
        std::stringstream ss(linha);
        Processos p;

        ss >> p.tempArrival >> p.tempDuration;
        processos.push_back(p);
    }

    inputFile.close();  // Fecha o arquivo

       for (const auto& p : processos) {
        std::cout << "Tempo de Chegada: " << p.tempArrival
                  << ", Duração: " << p.tempDuration << std::endl;
    }
}

int main() {
    readFile();
  
   
    return 0;
}