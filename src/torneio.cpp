#include <iostream>
#include <vector>
#include <iomanip>
#include "../inc/max_flow.h"

// Estrutura para armazenar os dados do torneio
struct TournamentData {
    int numTeams;
    std::vector<int> wins;
    std::vector<std::vector<int>> games;
};

// Lê os dados do torneio da entrada padrão
TournamentData readTournamentData() {
    TournamentData data;
    
    // Ler número de equipes
    std::cin >> data.numTeams;
    
    // Ler vetor de vitórias atuais
    data.wins.resize(data.numTeams);
    for (int i = 0; i < data.numTeams; i++) {
        std::cin >> data.wins[i];
    }
    
    // Ler matriz de jogos restantes
    data.games.resize(data.numTeams, std::vector<int>(data.numTeams, 0));
    for (int i = 0; i < data.numTeams-1; i++) {
        for (int j = i+1; j < data.numTeams; j++) {
            std::cin >> data.games[i][j];
            data.games[j][i] = data.games[i][j];
        }
    }
    
    return data;
}

// Imprime os dados do torneio
void printTournamentData(const TournamentData& data) {
    std::cout << "Número de equipes: " << data.numTeams << std::endl;
    
    std::cout << "Vitórias atuais: ";
    for (int w : data.wins) {
        std::cout << w << " ";
    }
    std::cout << std::endl;
    
    std::cout << "Jogos restantes:" << std::endl;
    for (int i = 0; i < data.numTeams; i++) {
        for (int j = 0; j < data.numTeams; j++) {
            std::cout << std::setw(3) << data.games[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

// Verifica as condições iniciais do torneio
bool checkInitialConditions(const TournamentData& data, std::vector<int>& maxAdditionalWins) {
    int r1 = 0;
    for (int j = 1; j < data.numTeams; j++) {
        r1 += data.games[0][j];
    }
    
    int maxWinsTeam1 = data.wins[0] + r1;
    maxAdditionalWins.resize(data.numTeams);
    
    for (int i = 1; i < data.numTeams; i++) {
        maxAdditionalWins[i] = maxWinsTeam1 - data.wins[i] - 1;
        if (maxAdditionalWins[i] < 0) {
            /*std::cout << "Impossível: equipe " << i 
                     << " já tem mais vitórias que o máximo possível da equipe 1" 
                     << std::endl;*/
            std::cout << "Não" << std::endl;
            return false;
        }
    }
    return true;
}

// Cria o grafo de fluxo para o problema do torneio
FlowGraph createTournamentGraph(const TournamentData& data, const std::vector<int>& maxAdditionalWins) {
    int numPairs = (data.numTeams-1)*(data.numTeams-2)/2;
    int totalVertices = 1 + numPairs + (data.numTeams-1) + 1;
    FlowGraph graph(totalVertices);
    
    int source = 0;
    int sink = totalVertices - 1;
    graph.setSourceSink(source, sink);
    
    int firstPairVertex = 1;
    int firstTeamVertex = firstPairVertex + numPairs;
    
    // Adiciona arestas da fonte para os pares de equipes
    int pairIndex = firstPairVertex;
    for (int i = 1; i < data.numTeams; i++) {
        for (int j = i+1; j < data.numTeams; j++) {
            if (data.games[i][j] > 0) {
                graph.addEdge(source, pairIndex, data.games[i][j]);
                
                int teamI = firstTeamVertex + (i-1);
                int teamJ = firstTeamVertex + (j-1);
                graph.addEdge(pairIndex, teamI, INF);
                graph.addEdge(pairIndex, teamJ, INF);
            }
            pairIndex++;
        }
    }
    
    // Adiciona arestas das equipes para o sumidouro
    for (int i = 1; i < data.numTeams; i++) {
        int teamVertex = firstTeamVertex + (i-1);
        graph.addEdge(teamVertex, sink, maxAdditionalWins[i]);
    }
    
    return graph;
}

int main() {
    // Lê os dados do torneio
    TournamentData data = readTournamentData();
    
    // Imprime os dados lidos
    //printTournamentData(data);
    
    // Verifica condições iniciais
    std::vector<int> maxAdditionalWins;
    if (!checkInitialConditions(data, maxAdditionalWins)) {
        return 1;
    }
    
    // Cria e processa o grafo de fluxo
    FlowGraph flowGraph = createTournamentGraph(data, maxAdditionalWins);
    
    if (flowGraph.getNumVertices() > 0) {
        //std::cout << "Grafo de fluxo criado com sucesso!" << std::endl;
        //std::cout << "Número de vértices: " << flowGraph.getNumVertices() << std::endl;
        //std::cout << "Número de arestas: " << flowGraph.getNumEdges() << std::endl;
        
        int maxFlow = fordFulkerson(flowGraph);
       // std::cout << "Fluxo máximo encontrado: " << maxFlow << std::endl;

        // Verifica se o time 1 pode vencer
        int totalGames = 0;
        for (int i = 1; i < data.numTeams; i++) {
            for (int j = i+1; j < data.numTeams; j++) {
                totalGames += data.games[i][j];
            }
        }

        if (maxFlow == totalGames) {
            std::cout << "Sim" << std::endl;
        } else {
            std::cout << "Não" << std::endl;
        }
    }
    
    return 0;
}