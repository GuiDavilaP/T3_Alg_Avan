#ifndef MAX_FLOW_H
#define MAX_FLOW_H

#include <vector>
#include <string>
#include <memory>
#include <limits>
#include <iostream>

const int INF = std::numeric_limits<int>::max();

// Estrutura para representar uma aresta no grafo
struct Edge {
    int from;       // Adicionamos o vértice de origem para facilitar o rastreamento
    int to;
    int capacity;
    int flow;
    Edge* reverse;

    Edge(int from, int to, int capacity) 
        : from(from), to(to), capacity(capacity), flow(0), reverse(nullptr) {}
    
    // Capacidade residual da aresta
    int residual() const { return capacity - flow; }
    
    // Verifica se a aresta está crítica (para Edmonds-Karp)
    bool isCritical() const { return residual() == 0 && capacity > 0; }
};

// Classe para representar o grafo
class FlowGraph {
private:
    int numVertices;
    int numEdges;   // Adicionamos contador de arestas
    std::vector<std::vector<Edge*>> adjList;
    int source;
    int sink;
    int maxCapacity; // Adicionamos o valor da capacidade máxima

public:
    FlowGraph(int n) 
        : numVertices(n), numEdges(0), adjList(n), source(0), sink(n-1), maxCapacity(0) {}
    
    void setSourceSink(int s, int t) {
        source = s;
        sink = t;
    }
    
    int getMaxCapacity() const { return maxCapacity; }
    int getSource() const { return source; }
    int getSink() const { return sink; }
    int getNumVertices() const { return numVertices; }
    int getNumEdges() const { return numEdges; }
    
    void addEdge(int from, int to, int capacity) {
        Edge* e1 = new Edge(from, to, capacity);
        Edge* e2 = new Edge(to, from, 0);  // Aresta reversa com capacidade 0
        e1->reverse = e2;
        e2->reverse = e1;
        adjList[from].push_back(e1);
        adjList[to].push_back(e2);
        numEdges++;
        
        // Atualiza a capacidade máxima
        if (capacity > maxCapacity) {
            maxCapacity = capacity;
        }
    }
    
    std::vector<std::vector<Edge*>>& getAdjList() {
        return adjList;
    }
    
    ~FlowGraph() {
        for (auto& edges : adjList) {
            for (auto edge : edges) {
                delete edge;
            }
        }
    }
};

// Interface para as estratégias de busca de caminho
class PathStrategy {
public:
    virtual ~PathStrategy() {}
    virtual std::vector<Edge*> findPath(FlowGraph& graph, int source, int sink) = 0;
};

// Declaração da função principal do algoritmo Ford-Fulkerson
int fordFulkerson(FlowGraph& graph);

// Função para ler o grafo no formato DIMACS
FlowGraph readDimacsGraph(std::istream& input);

// Função para criar a estratégia com base no parâmetro de entrada
std::unique_ptr<PathStrategy> createStrategy(const std::string& strategyName);

#endif // MAX_FLOW_H