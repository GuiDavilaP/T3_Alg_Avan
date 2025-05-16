#include "../inc/max_flow.h"
#include "../inc/fattest_path.h"
#include <chrono>
#include <sstream>
#include <fstream>
#include <cmath>

using namespace std;

int fordFulkerson(FlowGraph& graph) {
    // Create FattestPath strategy
    std::unique_ptr<PathStrategy> strategy = std::make_unique<FattestPathStrategy>();
    
    int maxFlow = 0;
    int source = graph.getSource();
    int sink = graph.getSink();
    
    while (true) {
        // Find path using FattestPath strategy
        std::vector<Edge*> path = strategy->findPath(graph, source, sink);
        
        if (path.empty()) break;
        
        // Find minimum residual flow in the path
        int flow = INF;
        for (Edge* edge : path) {
            flow = std::min(flow, edge->residual());
        }
        
        // Augment flow along the path
        for (Edge* edge : path) {
            edge->flow += flow;
            edge->reverse->flow -= flow;
        }
        
        maxFlow += flow;
    }
    
    return maxFlow;
}