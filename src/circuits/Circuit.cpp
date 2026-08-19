//src/circuits/Circuit.cpp
#include "Circuit.h"

// Constructor
Circuit::Circuit(std::unordered_set<Node*> nodes, std::unordered_set<Node*> driven_nodes, std::unordered_set<Transistor*> transistors) :
    nodes(nodes),
    driven_nodes(driven_nodes),
    transistors(transistors) {
}

// Method to evaluate the circuit
void Circuit::evaluate() {
    /*
    Constraints:
        -Circuit is Valid
        -Circuit will not have conflicts
    */

    //Step 1: Keep track of evaluated nodes, which driven nodes already are, and a flag which is true if something changes
    std::unordered_set<Node*> evaluated = driven_nodes;
    int num_transistors = transistors.size();
    bool flag = true;

    //Step 2: Go through each transistor, and do this the number of times there is a transistor, as assuming the circuit is valid, even if each transistor output feeds into the next, it should be able to work in n times
    for(int i = 0; i < num_transistors; i++){
        if(!flag){
            break;            
        }
        flag = false;
        for(Transistor* transistor: transistors){
            Node* source = transistor->getSource();
            Node* gate = transistor->getGate();
            Node* drain = transistor->getDrain();
            //If both drain and source are evaluated, or the gate is not evaluated, skip
            if((evaluated.count(source) && evaluated.count(drain)) || !evaluated.count(gate)){
                continue;
            }
            else{
                //If at least one is evaluated, and the gate is evaluated, and the transistor is conducting set the other one
                if(transistor->isConducting()){
                    if(evaluated.count(source)){
                        drain->setSignal(source->getSignal());
                        evaluated.emplace(drain);
                        flag = true;
                    }
                    else if(evaluated.count(drain)){
                        source->setSignal(drain->getSignal());
                        evaluated.emplace(source);
                        flag = true;
                    }
                }
            }
        }
    }
    
}