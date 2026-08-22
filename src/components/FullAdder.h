#ifndef FULLADDER_H
#define FULLADDER_H

#include "circuits/Node.h"
#include "components/HalfAdder.h"
#include "gates/NOR2.h"
#include "gates/Inverter.h"

class FullAdder {
    private:
        Node* input_a;
        Node* input_b;
        Node* carry_in;

        Node* sum;
        Node* carry_out;

        Node partial_sum;
        Node carry_1;
        Node carry_2;
        Node carry_middle;

        HalfAdder half_adder_1;
        HalfAdder half_adder_2;

        NOR2 nor2;
        Inverter inverter;

        int counter;

    public:
        FullAdder(
            Node* input_a,
            Node* input_b,
            Node* carry_in,
            Node* sum,
            Node* carry_out
        );

        Node* getInputA() const;
        Node* getInputB() const;
        Node* getCarryIn() const;

        Node* getSum() const;
        Node* getCarryOut() const;

        void update();

        bool getSumVal() const;
        bool getCarryOutVal() const;
};

#endif