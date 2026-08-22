#include "components/MUX2.h"
#include <cassert>


// Fully propagate through the MUX.
void settle(MUX2& mux){
    for(int i = 0; i < 5; i++){
        mux.update();
    }
}


// Select A when select = 0.
void testSelectA00(){
    Node input_a(false);
    Node input_b(false);
    Node select(false);
    Node output(true);

    MUX2 mux(&input_a, &input_b, &select, &output);

    settle(mux);

    assert(mux.getOutputVal() == false);
}


void testSelectA10(){
    Node input_a(true);
    Node input_b(false);
    Node select(false);
    Node output(false);

    MUX2 mux(&input_a, &input_b, &select, &output);

    settle(mux);

    assert(mux.getOutputVal() == true);
}


// Select B when select = 1.
void testSelectB01(){
    Node input_a(false);
    Node input_b(true);
    Node select(true);
    Node output(false);

    MUX2 mux(&input_a, &input_b, &select, &output);

    settle(mux);

    assert(mux.getOutputVal() == true);
}


void testSelectB11(){
    Node input_a(true);
    Node input_b(false);
    Node select(true);
    Node output(true);

    MUX2 mux(&input_a, &input_b, &select, &output);

    settle(mux);

    assert(mux.getOutputVal() == false);
}


// Changing select should change which input reaches output.
void testSelectChange(){
    Node input_a(false);
    Node input_b(true);
    Node select(false);
    Node output(true);

    MUX2 mux(&input_a, &input_b, &select, &output);

    // Select A
    settle(mux);
    assert(mux.getOutputVal() == false);

    // Select B
    select.setSignal(true);

    settle(mux);
    assert(mux.getOutputVal() == true);

    // Select A again
    select.setSignal(false);

    settle(mux);
    assert(mux.getOutputVal() == false);
}


// Changing input values should propagate correctly.
void testInputChanges(){
    Node input_a(false);
    Node input_b(false);
    Node select(false);
    Node output(true);

    MUX2 mux(&input_a, &input_b, &select, &output);

    settle(mux);
    assert(mux.getOutputVal() == false);

    input_a.setSignal(true);

    settle(mux);
    assert(mux.getOutputVal() == true);

    select.setSignal(true);

    settle(mux);
    assert(mux.getOutputVal() == false);

    input_b.setSignal(true);

    settle(mux);
    assert(mux.getOutputVal() == true);
}


// Output should not reach its final value until tick 5.
void testPropagationDelay(){
    Node input_a(true);
    Node input_b(false);
    Node select(false);

    // Final result should be true.
    Node output(false);

    MUX2 mux(&input_a, &input_b, &select, &output);

    mux.update(); // Tick 1
    assert(output.getSignal() == false);

    mux.update(); // Tick 2
    assert(output.getSignal() == false);

    mux.update(); // Tick 3
    assert(output.getSignal() == false);

    mux.update(); // Tick 4
    assert(output.getSignal() == false);

    mux.update(); // Tick 5
    assert(output.getSignal() == true);
}


int main(){

    testSelectA00();
    testSelectA10();

    testSelectB01();
    testSelectB11();

    testSelectChange();
    testInputChanges();
    testPropagationDelay();

    return 0;
}