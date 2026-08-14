#include "Node.h"
#include <cassert>

// Test that a Node can be initialized low.
void testLowNode(){
    Node node(false);

    assert(node.getSignal() == false);
}

// Test that a Node can be initialized high.
void testHighNode(){
    Node node(true);

    assert(node.getSignal() == true);
}

// Test that the signal can be changed.
void testSetSignal(){
    Node node(false);

    node.setSignal(true);
    assert(node.getSignal() == true);

    node.setSignal(false);
    assert(node.getSignal() == false);
}

int main(){

    testLowNode();
    testHighNode();
    testSetSignal();

    return 0;
}