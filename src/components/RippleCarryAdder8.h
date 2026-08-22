#ifndef RIPPLECARRYADDER8_H
#define RIPPLECARRYADDER8_H

#include <array>

#include "circuits/Node.h"
#include "components/FullAdder.h"

class RippleCarryAdder8 {
    private:
        std::array<Node*, 8> input_a;
        std::array<Node*, 8> input_b;
        std::array<Node*, 8> sum;

        Node* carry_in;
        Node* carry_out;

        Node carry_0;
        Node carry_1;
        Node carry_2;
        Node carry_3;
        Node carry_4;
        Node carry_5;
        Node carry_6;

        FullAdder bit_0;
        FullAdder bit_1;
        FullAdder bit_2;
        FullAdder bit_3;
        FullAdder bit_4;
        FullAdder bit_5;
        FullAdder bit_6;
        FullAdder bit_7;

        std::array<FullAdder*, 8> full_adders;

        int counter;

    public:
        RippleCarryAdder8(
            std::array<Node*, 8> input_a,
            std::array<Node*, 8> input_b,
            Node* carry_in,
            std::array<Node*, 8> sum,
            Node* carry_out
        );

        void update();

        bool getSumVal(int bit) const;
        bool getCarryOutVal() const;
};

#endif