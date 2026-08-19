#ifndef NAND2_H
#define NAND2_H

#include "circuits/Node.h"
#include "circuits/Transistor.h"
#include "circuits/Circuit.h"

class NAND2 {
    private:
        Node vdd;
        Node ground;
        Node middle;

        Node* input_a;
        Node* input_b;
        Node* output;

        Transistor pmos_a;
        Transistor pmos_b;
        Transistor nmos_a;
        Transistor nmos_b;

        Circuit circuit;
    
    public:
        NAND2(Node* input_a, Node* input_b, Node* output);

        Node* getInputA() const;
        Node* getInputB() const;
        Node* getOutput() const;

        void update();
        bool getOutputVal() const;
};

#endif