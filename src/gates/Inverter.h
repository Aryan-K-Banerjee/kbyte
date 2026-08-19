#ifndef INVERTER_H
#define INVERTER_H

#include "circuits/Node.h"
#include "circuits/Transistor.h"
#include "circuits/Circuit.h"

class Inverter {
    private:
        Node vdd;
        Node ground;
        Node* input;
        Node* output;
        Transistor pmos;
        Transistor nmos;
        Circuit circuit;
    
    public:
        Inverter(Node* input, Node* output);

        Node* getInput() const;
        Node* getOutput() const;

        void update();
        bool getOutputVal() const;
};

#endif