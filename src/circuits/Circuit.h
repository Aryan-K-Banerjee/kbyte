//src/circuits/Circuit.h
#ifndef CIRCUIT_H
#define CIRCUIT_H

#include "Node.h"
#include "Transistor.h"

#include <unordered_set>

class Circuit {
    private:
        std::unordered_set<Node*> nodes;
        std::unordered_set<Node*> driven_nodes;
        std::unordered_set<Transistor*> transistors;
    
    public:
        Circuit(std::unordered_set<Node*> nodes, std::unordered_set<Node*> driven_nodes, std::unordered_set<Transistor*> transistors);

        void evaluate();
};

#endif