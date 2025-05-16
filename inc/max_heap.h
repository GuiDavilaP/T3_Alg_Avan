#ifndef MAX_HEAP_H
#define MAX_HEAP_H

#include <vector>
#include <utility>
#include <string>

// Classe para implementação de um max-heap k-ário
class MaxHeap {
private:
    int k;                                     // Aridade do heap
    std::vector<std::pair<int, int>> heap;     // Pares (valor, vértice)
    std::vector<int> position;                 // Posição de cada vértice no heap
    std::vector<bool> inHeap;                  // Indica se um vértice está no heap
    
    // Contador de estatísticas
    int totalSiftUp;
    int totalSiftDown;
    int totalInsert;
    int totalDeleteMax;
    int totalUpdate;
    std::vector<std::pair<std::string, double>> rValues;
    int totalEdges;

    // Operações internas do heap
    void swapNodes(int index1, int index2);
    int getParent(int childIndex);
    int getChild(int parentIndex, int childPos);
    int getMaxChild(int parentIndex);
    int siftDown(int nodeIndex);
    int siftUp(int nodeIndex);
    void logOperation(const std::string& operation, int sifts);

public:
    // Construtor
    MaxHeap(int k, int n);
    
    // Operações principais do heap
    void insert(int nodeIndex, int value);
    void update(int nodeIndex, int newValue);
    void insertOrUpdate(int nodeIndex, int value);
    std::pair<int, int> deleteMax();
    bool isEmpty() const;
    
    // Estatísticas
    void printStatistics() const;
};

#endif // MAX_HEAP_H