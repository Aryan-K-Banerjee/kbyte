#ifndef ALU1_H
#define ALU1_H

#include "circuits/Node.h"
#include "gates/NAND2.h"
#include "gates/NOR2.h"
#include "gates/XOR2.h"
#include "gates/Inverter.h"
#include "components/FullAdder.h"
#include "components/MUX2.h"

class ALU1 {
    private:
        Node* input_a;
        Node* input_b;
        Node* carry_in;

        Node* op0;
        Node* op1;

        Node* output;
        Node* carry_out;

        Node nand_middle;
        Node and_output;
        Node nor2_middle;
        Node or_output;
        Node xor_output;
        Node full_adder_sum;
        Node mux_a_output;
        Node mux_b_output;

        NAND2 nand;
        Inverter inverter_nand;

        NOR2 nor2;
        Inverter inverter_nor;

        XOR2 xor2;

        FullAdder full_adder;

        MUX2 mux_a;
        MUX2 mux_b;
        MUX2 mux_output;

        int counter;
    
    public:
        ALU1(Node* input_a, Node* input_b, Node* carry_in, Node* op0, Node* op1, Node* output, Node* carry_out);
        
        Node* getInputA() const;
        Node* getInputB() const;
        Node* getCarryIn() const;
        Node* getOp0() const;
        Node* getOp1() const;
        Node* getOutput() const;
        Node* getCarryOut() const;

        void update();

        bool getOutputVal() const;
        bool getCarryOutVal() const;
};

#endif