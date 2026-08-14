#include "Node.h"
#include <cassert>

// Test that a default Node starts low.
void testDefaultNode(){
    Node node;

    assert(node.getSignal() == false);
}

// Test that a Node can be initialized high.
void testInitialValue(){
    Node node(true);

    assert(node.getSignal() == true);
}

// Test that the signal can be changed.
void testSetSignal(){
    Node node(false);

    node.setSignal(true);

    assert(node.getSignal() == true);
}

int main(){

    testDefaultNode();
    testInitialValue();
    testSetSignal();

    return 0;
}