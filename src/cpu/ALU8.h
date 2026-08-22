#ifndef ALU8_H
#define ALU8_H

#include <array>

#include "circuits/Node.h"
#include "cpu/ALU1.h"

class ALU8 {

    private:
        std::array<Node*, 8> input_a;
        std::array<Node*, 8> input_b;
        std::array<Node*, 8> output;

        Node* carry_in;
        Node* carry_out;

        Node* op0;
        Node* op1;

        Node carry_0;
        Node carry_1;
        Node carry_2;
        Node carry_3;
        Node carry_4;
        Node carry_5;
        Node carry_6;

        ALU1 alu_0;
        ALU1 alu_1;
        ALU1 alu_2;
        ALU1 alu_3;
        ALU1 alu_4;
        ALU1 alu_5;
        ALU1 alu_6;
        ALU1 alu_7;

        std::array<ALU1*, 8> alus;

        int counter;

    public:
        ALU8(
            std::array<Node*, 8> input_a,
            std::array<Node*, 8> input_b,
            Node* carry_in,
            Node* op0,
            Node* op1,
            std::array<Node*, 8> output,
            Node* carry_out
        );

        void update();

        bool getOutputVal(int bit) const;
        bool getCarryOutVal() const;
};

#endif