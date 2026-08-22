#ifndef MUX2_H
#define MUX2_H

#include "circuits/Node.h"
#include "gates/Inverter.h"
#include "gates/NAND2.h"
#include "gates/NOR2.h"

class MUX2 {
    private:
        Node* input_a;
        Node* input_b;
        Node* select;
        Node* output;

        Node not_select;

        Node nand_a;
        Node and_a;

        Node nand_b;
        Node and_b;

        Node nor_output;

        Inverter select_inverter;

        NAND2 nand2_a;
        Inverter inverter_a;

        NAND2 nand2_b;
        Inverter inverter_b;

        NOR2 nor2;
        Inverter output_inverter;

        int counter;

    public:
        MUX2(Node* input_a, Node* input_b, Node* select, Node* output);

        Node* getInputA() const;
        Node* getInputB() const;
        Node* getSelect() const;
        Node* getOutput() const;

        void update();

        bool getOutputVal() const;
};

#endif