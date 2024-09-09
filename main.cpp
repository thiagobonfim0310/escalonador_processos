#include <iostream>
#include <fstream>  
#include <string>   
#include <vector>
#include <sstream>
#include <string.h>
#include <algorithm>

//    tempo de retorno: quantidade necessaria de tempo para  executar o processo
//    tempo de espera qauntidade de tempo que o processo ficou na fila
//    tempo de resposta : tempo para execultar pela primeira vez
struct Processos
{
    int id;
    int tempArrival;
    int tempDuration;
    int temRetorno;
    int tempEspera;
    int tempResposta;

    bool operator==(const Processos& other) const {
        return id == other.id ;
    }
};

std::vector<Processos> processos;

void readFile(){
    int pid =1;
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
        p.id = pid;
        pid++;
        processos.push_back(p);
    }

    inputFile.close();  // Fecha o arquivo

      
}

bool comparar(const Processos& a, const Processos& b) {
    return a.tempArrival < b.tempArrival;
}

void FCFS(){

std::cout << "-------------------FCFS-------------------" << std::endl;
std:: vector<Processos> queue(processos.size());
std:: vector<Processos> queueSequence;
std::copy(processos.begin(), processos.end(), queue.begin());
    
    std::sort(queue.begin(), queue.end(), comparar);

    int tempoCorrente = 0;
       int somaRetorno = 0;
    int somaEspera = 0;
    int somaResposta = 0;

    // Calculando tempos de retorno, espera e resposta
    for (auto& processo : queue) {
        if (tempoCorrente < processo.tempArrival) {
            tempoCorrente = processo.tempArrival;
        }
        
        processo.tempResposta = tempoCorrente - processo.tempArrival;
        processo.tempEspera = processo.tempResposta;
        processo.temRetorno = processo.tempEspera + processo.tempDuration;
        
        tempoCorrente += processo.tempDuration; // Atualizando o tempo corrente

        somaRetorno += processo.temRetorno;
        somaEspera += processo.tempEspera;
        somaResposta += processo.tempResposta;
    }


    // Exibindo os processos ordenados e seus tempos calculados
    std::cout << "\nProcessos ordenados por FCFS com tempos de retorno, espera e resposta:\n";
    for (const auto& processo : queue) {
        std::cout << "Processo " << processo.id 
                  << " - Tempo de chegada: " << processo.tempArrival
                  << ", Tempo de duracao: " << processo.tempDuration
                  << ", Tempo de retorno: " << processo.temRetorno
                  << ", Tempo de espera: " << processo.tempEspera
                  << ", Tempo de resposta: " << processo.tempResposta << '\n';
    }

  double mediaRetorno = static_cast<double>(somaRetorno) / queue.size();
    double mediaEspera = static_cast<double>(somaEspera) / queue.size();
    double mediaResposta = static_cast<double>(somaResposta) / queue.size();

  std::cout << "\nMédias:\n";
    std::cout << "Média do tempo de retorno: " << mediaRetorno << '\n';
    std::cout << "Média do tempo de espera: " << mediaEspera << '\n';
    std::cout << "Média do tempo de resposta: " << mediaResposta << '\n';



// int tempQueue= 0;

//     while (queue.size()){
//         tempQueue++;
//         Processos firstArrival = queue[0];
//         for (const auto& p : queue) {
//             if(p.tempArrival<firstArrival.tempArrival){
//                 firstArrival=p;
//             }
//         }
//         queueSequence.push_back(firstArrival);
//         auto it = std::remove(queue.begin(), queue.end(), firstArrival);
//         queue.erase(it, queue.end());

//     }

//      std::cout << "Temp " << tempQueue << std::endl;
//       std::cout << "Size" << queueSequence.size() << std::endl;
//       for (const auto& p : queueSequence) {
//         std::cout << "Processos "<< p.id << " Tempo de Chegada: " << p.tempArrival
//                   << ", Duração: " << p.tempDuration << std::endl;
//     }
    
}
void SJFS(){

}
void RR_2(){

}
int main() {
    readFile();
    FCFS();

  
   
    return 0;
}