#include "../inc/max_heap.h"
#include <iostream>
#include <algorithm>
#include <cassert>
#include <cmath>
#include <stdexcept>

using namespace std;

MaxHeap::MaxHeap(int k, int n)
    : k(k),
      position(n, -1),
      inHeap(n, false){ 
    this->heap.reserve(n);
}

// Insere ou atualiza um nodo no heap
void MaxHeap::insertOrUpdate(int nodeIndex, int value) {
    if (nodeIndex < 0 || nodeIndex >= static_cast<int>(position.size())) {
        throw runtime_error("Node index out of range in insertOrUpdate");
    }
    if (inHeap[nodeIndex]) {
        update(nodeIndex, value);
    } else {
        insert(nodeIndex, value);
    }
}

// Insere um nodo no heap
void MaxHeap::insert(int nodeIndex, int value) {
    assert(nodeIndex >= 0 && nodeIndex < static_cast<int>(position.size()));
    if (position[nodeIndex] != -1) return;

    heap.emplace_back(value, nodeIndex);
    position[nodeIndex] = heap.size() - 1;
    inHeap[nodeIndex] = true;
    
    siftUp(heap.size() - 1);
}


// Atualiza o valor de um nodo no heap
void MaxHeap::update(int nodeIndex, int newValue) {
    if (nodeIndex < 0 || nodeIndex >= static_cast<int>(position.size())) {
        throw runtime_error("Node index out of range in update");
    }
    if (position[nodeIndex] == -1) return; // Vértice não está no heap
    
    int heapIndex = position[nodeIndex];
    int oldValue = heap[heapIndex].first;
    heap[heapIndex].first = newValue;

    // If new value is larger, sift up
    if (newValue > oldValue) {
        siftUp(heapIndex);
    }
    // If new value is smaller, sift down
    else if (newValue < oldValue) {
        siftDown(heapIndex);
    }
}

// Modify deleteMax to use siftDown
pair<int, int> MaxHeap::deleteMax() {
    if (heap.empty()) throw runtime_error("Heap is empty");

    pair<int, int> maxNode = heap[0];
    swapNodes(0, heap.size() - 1);
    position[maxNode.second] = -1;  // Marca como removido
    inHeap[maxNode.second] = false; // Marca como não presente no heap
    heap.pop_back();

    if (!heap.empty()) {
        siftDown(0);
    }

    return maxNode;
}
bool MaxHeap::isEmpty() const {
    return heap.empty();
}

// Troca dois vértices no heap
void MaxHeap::swapNodes(int index1, int index2) {
    assert(index1 >= 0 && index1 < static_cast<int>(heap.size()));
    assert(index2 >= 0 && index2 < static_cast<int>(heap.size()));
    swap(heap[index1], heap[index2]);
    position[heap[index1].second] = index1;
    position[heap[index2].second] = index2;
}

// Retorna o índice do pai de um nodo
int MaxHeap::getParent(int childIndex) {
    return (childIndex - 1) / k;
}

// Retorna o índice de um filho específico de um nodo
int MaxHeap::getChild(int parentIndex, int childPos) {
    return k * parentIndex + (childPos + 1);
}

// Retorna o índice do maior filho de um nodo
int MaxHeap::getMaxChild(int parentIndex) {
    const int firstChild = k * parentIndex + 1;
    if (firstChild >= static_cast<int>(heap.size())) return -1;
    
    // Encontra o maior filho dentro do intervalo válido
    const int endChild = min(firstChild + k, static_cast<int>(heap.size()));
    
    int maxChildIndex = firstChild;
    for (int i = firstChild + 1; i < endChild; i++) {
        if (heap[i].first > heap[maxChildIndex].first) {
            maxChildIndex = i;
        }
    }
    return maxChildIndex;
}

// Realiza o sift-down no heap (para max-heap)
int MaxHeap::siftDown(int nodeIndex) {
    while (true) {
        int maxChildIndex = getMaxChild(nodeIndex);
        if (maxChildIndex == -1 || heap[maxChildIndex].first <= heap[nodeIndex].first) {
            break; // Propriedade do heap satisfeita
        }
        swapNodes(nodeIndex, maxChildIndex);
        nodeIndex = maxChildIndex;
    }
    return 0;
}

// Realiza o sift-up no heap (para max-heap)
int MaxHeap::siftUp(int nodeIndex) {
    while (nodeIndex > 0) {
        int parentIndex = getParent(nodeIndex);

        if (heap[nodeIndex].first > heap[parentIndex].first) {
            swapNodes(nodeIndex, parentIndex);
            nodeIndex = parentIndex;
        } else {
            break;
        }
    }
    return 0;
}