#include <iostream>
#include <fstream>  
#include <string>   
#include <vector>
#include <sstream>
#include <string.h>
#include <algorithm>
#include <queue>

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
    int tempRestante;//para o RR

    bool operator==(const Processos& other) const {
        return id == other.id ;
    }
};

std::vector<Processos> processos;

void readFile(){
    int indiceFila =1;
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
        p.id = indiceFila;
        indiceFila++;
        processos.push_back(p);
    }

    inputFile.close();  // Fecha o arquivo

      
}

bool compararFCFS(const Processos& a, const Processos& b) {
    return a.tempArrival < b.tempArrival;
}

bool compararSJF(const Processos& a, const Processos& b) {
    if (a.tempArrival == b.tempArrival) {
        return a.tempDuration < b.tempDuration; // Se o tempo de chegada for igual, comparar pela duração
    }
    return a.tempArrival < b.tempArrival; // Caso contrário, comparar pelo tempo de chegada
}

void calcularTempos(std::vector<Processos>& processos) {
    int tempoCorrente = 0;
    int somaRetorno = 0;
    int somaEspera = 0;
    int somaResposta = 0;

    // Calculando tempos de retorno, espera e resposta
    for (auto& processo : processos) {
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

  double mediaRetorno = static_cast<double>(somaRetorno) / processos.size();
    double mediaEspera = static_cast<double>(somaEspera) / processos.size();
    double mediaResposta = static_cast<double>(somaResposta) / processos.size();

    std::cout << mediaRetorno << ' ';
    std::cout << mediaEspera << ' ';
    std::cout <<  mediaResposta << '\n';


}

void FCFS(){

std:: vector<Processos> queue(processos.size());
std::copy(processos.begin(), processos.end(), queue.begin());
    
    std::sort(queue.begin(), queue.end(), compararFCFS);

 calcularTempos(queue);
}

void SJFS(){
   
std:: vector<Processos> queue(processos.size());
std::copy(processos.begin(), processos.end(), queue.begin());
    
    std::sort(queue.begin(), queue.end(), compararSJF);

calcularTempos(queue);
    

}
void RR_2(){
    int quantum = 2;
   
    std:: vector<Processos> queue(processos.size());
    std::copy(processos.begin(), processos.end(), queue.begin());
    
     // Ordenar os processos por tempo de chegada
    std::sort(queue.begin(), queue.end(), [](const Processos& a, const Processos& b) {
        return a.tempArrival < b.tempArrival;
    });

    // Fila para armazenar os processos prontos para execução
    std::queue<int> filaProntos;
    int tempoCorrente = 0;
    int index = 0; // Índice para os processos na lista ordenada
    int somaRetorno = 0, somaEspera = 0, somaResposta = 0;
    bool primeiroExec = true;

    // Inicializar os tempos de retorno, espera e resposta
    for (int i = 0; i < queue.size(); ++i) {
        queue[i].tempRestante = queue[i].tempDuration; // Inicializa o tempo restante como o tempo de duração
    }

    while (!filaProntos.empty() || index < queue.size()) {
        // Adicionar processos que chegaram até o tempo corrente à fila
        while (index < queue.size() && queue[index].tempArrival <= tempoCorrente) {
            filaProntos.push(index);
            index++;
        }

        // Atualiza o tempo atual e reinica o loop
        if (filaProntos.empty()) {
            tempoCorrente = queue[index].tempArrival;
            continue;
        }

        // Pega o próximo processo da fila
        int indiceFila = filaProntos.front();
        filaProntos.pop();
        
        // Verifica se ainda não executou o processo
        if (queue[indiceFila].tempRestante == queue[indiceFila].tempDuration) {
            queue[indiceFila].tempResposta = tempoCorrente - queue[indiceFila].tempArrival;
        }

        // Executa o processo 
        int tempoExecucao = std::min(quantum, queue[indiceFila].tempRestante);
        queue[indiceFila].tempRestante -= tempoExecucao;
        tempoCorrente += tempoExecucao;

        // Se o processo terminou, calcular os tempos de retorno e espera
        if (queue[indiceFila].tempRestante == 0) {
            queue[indiceFila].temRetorno = tempoCorrente - queue[indiceFila].tempArrival;
            queue[indiceFila].tempEspera = queue[indiceFila].temRetorno - queue[indiceFila].tempDuration;

            // Acumula os tempos para o cálculo das médias
            somaRetorno += queue[indiceFila].temRetorno;
            somaEspera += queue[indiceFila].tempEspera;
            somaResposta += queue[indiceFila].tempResposta;

        } else {
            // Se o processo não terminou, coloca-o de volta na fila
            filaProntos.push(indiceFila);
        }

        // Adicionar novos queue que chegaram enquanto o processo atual estava executando
        while (index < queue.size() && queue[index].tempArrival <= tempoCorrente) {
            filaProntos.push(index);
            index++;
        }
    }

    // Calculando as médias
    double mediaRetorno = static_cast<double>(somaRetorno) / queue.size();
    double mediaEspera = static_cast<double>(somaEspera) / queue.size();
    double mediaResposta = static_cast<double>(somaResposta) / queue.size();

   
   
    std::cout <<  mediaRetorno << ' ';
    std::cout <<  mediaResposta << ' ';
    std::cout <<  mediaEspera << '\n';

}
int main() {
    readFile();
    std::cout << "FCFS: ";
    FCFS();
    std::cout << "SJF: ";
    SJFS();
    std::cout << "RR: ";
    RR_2();

    return 0;
}