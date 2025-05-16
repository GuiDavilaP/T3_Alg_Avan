#include "../inc/fattest_path.h"
#include "../inc/max_heap.h"
#include <algorithm>
#include <iostream>

using namespace std;

std::vector<Edge*> FattestPathStrategy::findPath(FlowGraph& graph, int source, int sink) {
    auto startTime = std::chrono::high_resolution_clock::now();
    auto path = findFattestPath(graph, source, sink);
    auto endTime = std::chrono::high_resolution_clock::now();
    
    return path;
}

std::vector<Edge*> FattestPathStrategy::reconstructPath(const std::vector<Edge*>& parent, int source, int sink) {
    std::vector<Edge*> path;
    if (parent[sink] == nullptr) return path;  // Nenhum caminho encontrado
    
    for (int at = sink; at != source;) {
        Edge* edge = parent[at];
        path.push_back(edge);
        at = edge->reverse->to;
    }
    
    std::reverse(path.begin(), path.end());
    return path;
}

std::vector<Edge*> findFattestPath(FlowGraph& graph, int source, int sink) {
    int n = graph.getNumVertices();
    std::vector<int> bottleneck(n, 0);
    std::vector<Edge*> parent(n, nullptr);
    std::vector<bool> visited(n, false);
    
    // Inicializa a capacidade da origem
    bottleneck[source] = INF;
    
    // Usa um max-heap com melhor k encontrado no trabalho anteriro para selecionar o vértice com maior gargalo
    MaxHeap heap(9, n);
    heap.insert(source, bottleneck[source]);
    
    while (!heap.isEmpty()) {
        auto [current_bottleneck, u] = heap.deleteMax();
        
        // Já encontrou um caminho melhor
        if (current_bottleneck < bottleneck[u]) {
            continue;
        }
        
        // Se chegamos ao destino, reconstruímos o caminho
        if (u == sink) {
            std::vector<Edge*> path;
            for (int at = sink; at != source;) {
                Edge* edge = parent[at];
                path.push_back(edge);
                at = edge->reverse->to;
            }
            std::reverse(path.begin(), path.end());
            return path;
        }
        
        // Explora todas as arestas adjacentes
        for (Edge* edge : graph.getAdjList()[u]) {
            int v = edge->to;
            int residual = edge->residual();
            
            if (residual <= 0) continue;
            
            // O gargalo do caminho é o mínimo entre o gargalo atual e a capacidade residual da aresta
            int new_bottleneck = std::min(bottleneck[u], residual);
            
            // Se encontramos um caminho com gargalo maior
            if (new_bottleneck > bottleneck[v]) {
                bottleneck[v] = new_bottleneck;
                parent[v] = edge;
                heap.insertOrUpdate(v, new_bottleneck);
            }
        }
    }
    
    return std::vector<Edge*>();  // Retorna caminho vazio se não encontrar
}