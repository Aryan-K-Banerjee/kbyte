#include "components/FullAdder.h"
#include <cassert>

// Run enough ticks for the Full Adder to completely settle.
void settle(FullAdder& full_adder){
    for(int i = 0; i < 5; i++){
        full_adder.update();
    }
}

void testFullAdder000(){
    Node a(false);
    Node b(false);
    Node carry_in(false);

    Node sum(true);
    Node carry_out(true);

    FullAdder gate(&a, &b, &carry_in, &sum, &carry_out);

    settle(gate);

    assert(sum.getSignal() == false);
    assert(carry_out.getSignal() == false);
}

void testFullAdder001(){
    Node a(false);
    Node b(false);
    Node carry_in(true);

    Node sum(false);
    Node carry_out(true);

    FullAdder gate(&a, &b, &carry_in, &sum, &carry_out);

    settle(gate);

    assert(sum.getSignal() == true);
    assert(carry_out.getSignal() == false);
}

void testFullAdder010(){
    Node a(false);
    Node b(true);
    Node carry_in(false);

    Node sum(false);
    Node carry_out(true);

    FullAdder gate(&a, &b, &carry_in, &sum, &carry_out);

    settle(gate);

    assert(sum.getSignal() == true);
    assert(carry_out.getSignal() == false);
}

void testFullAdder011(){
    Node a(false);
    Node b(true);
    Node carry_in(true);

    Node sum(true);
    Node carry_out(false);

    FullAdder gate(&a, &b, &carry_in, &sum, &carry_out);

    settle(gate);

    assert(sum.getSignal() == false);
    assert(carry_out.getSignal() == true);
}

void testFullAdder100(){
    Node a(true);
    Node b(false);
    Node carry_in(false);

    Node sum(false);
    Node carry_out(true);

    FullAdder gate(&a, &b, &carry_in, &sum, &carry_out);

    settle(gate);

    assert(sum.getSignal() == true);
    assert(carry_out.getSignal() == false);
}

void testFullAdder101(){
    Node a(true);
    Node b(false);
    Node carry_in(true);

    Node sum(true);
    Node carry_out(false);

    FullAdder gate(&a, &b, &carry_in, &sum, &carry_out);

    settle(gate);

    assert(sum.getSignal() == false);
    assert(carry_out.getSignal() == true);
}

void testFullAdder110(){
    Node a(true);
    Node b(true);
    Node carry_in(false);

    Node sum(true);
    Node carry_out(false);

    FullAdder gate(&a, &b, &carry_in, &sum, &carry_out);

    settle(gate);

    assert(sum.getSignal() == false);
    assert(carry_out.getSignal() == true);
}

void testFullAdder111(){
    Node a(true);
    Node b(true);
    Node carry_in(true);

    Node sum(false);
    Node carry_out(false);

    FullAdder gate(&a, &b, &carry_in, &sum, &carry_out);

    settle(gate);

    assert(sum.getSignal() == true);
    assert(carry_out.getSignal() == true);
}

int main(){

    testFullAdder000();
    testFullAdder001();
    testFullAdder010();
    testFullAdder011();

    testFullAdder100();
    testFullAdder101();
    testFullAdder110();
    testFullAdder111();

    return 0;
}