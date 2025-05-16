#ifndef FATTEST_PATH_H
#define FATTEST_PATH_H

#include "max_flow.h"
#include "max_heap.h"
#include <vector>
#include <chrono>

// Estratégia para encontrar o caminho com maior gargalo (Fattest Path)
class FattestPathStrategy : public PathStrategy {
public:
    FattestPathStrategy() {}
    
    std::vector<Edge*> findPath(FlowGraph& graph, int source, int sink) override;

private:
    std::vector<Edge*> reconstructPath(const std::vector<Edge*>& parent, int source, int sink);
};

// Função auxiliar para encontrar o caminho com maior gargalo usando Dijkstra modificado
std::vector<Edge*> findFattestPath(FlowGraph& graph, int source, int sink);

#endif // FATTEST_PATH_H