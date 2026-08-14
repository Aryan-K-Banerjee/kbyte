#ifndef NOTGATE_H
#define NOTGATE_H

#include "Node.h"
#include "Transistor.h"

class NotGate {
    private:
        Node vdd;
        Node ground;
        Node* input;
        Node* output;
        Transistor pmos;
        Transistor nmos;
    
    public:
        NotGate(Node* input, Node* output);

        void setInput(Node* input);
        void setOutput(Node* output);

        Node* getInput() const;
        Node* getOutput() const;

        void update();
        bool getOutputVal() const;
};

#endif