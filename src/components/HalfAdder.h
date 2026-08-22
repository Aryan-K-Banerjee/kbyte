#ifndef HALFADDER_H
#define HALFADDER_H

#include "circuits/Node.h"
#include "gates/Inverter.h"
#include "gates/NAND2.h"
#include "gates/XOR2.h"

class HalfAdder {
    private:
        Node* input_a;
        Node* input_b;
        Node* sum;
        Node* carry;

        Node carry_middle;

        NAND2 nand2;
        Inverter inverter;
        XOR2 xor2;

        int counter;
    
    public:
        HalfAdder(Node* input_a, Node* input_b, Node* sum, Node* carry);

        Node* getInputA() const;
        Node* getInputB() const;
        Node* getSum() const;
        Node* getCarry() const;

        void update();
        bool getSumVal() const;
        bool getCarryVal() const;
};

#endif