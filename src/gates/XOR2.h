#ifndef XOR2_H
#define XOR2_H

#include "circuits/Node.h"
#include "circuits/Transistor.h"
#include "circuits/Circuit.h"

class XOR2 {
    private:
        Node vdd;
        Node ground;

        Node not_a;
        Node xnor;

        Node* input_a;
        Node* input_b;
        Node* output;

        // Create NOT A
        Transistor inv_a_pmos;
        Transistor inv_a_nmos;

        // Select A or NOT A based on B
        Transistor pass_not_a;
        Transistor pass_a;

        // Invert XNOR into XOR
        Transistor out_pmos;
        Transistor out_nmos;

        Circuit circuit;

    public:
        XOR2(Node* input_a, Node* input_b, Node* output);

        Node* getInputA() const;
        Node* getInputB() const;
        Node* getOutput() const;

        void update();
        bool getOutputVal() const;
};

#endif