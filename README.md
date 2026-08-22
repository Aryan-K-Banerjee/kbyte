# KBYTE
I will be creating a computer from scratch in C++ to refresh my learning of computers in general

I will start at the transistor level and go all the way up to a CPU

- transistor
- logic gates

## Step 1: Transistor
From my electrical engineering classes, at the most basic a transistor has a drain, gate, and source. As I am coding I realize a good approach would actually be to create Nodes/wires as well as that allows multiple transistors to be connected to one Node if needed.

So a Node class with a boolean signal that represents the voltage as on or off. I think an abstraction that keeps things flowing. Other than that I will keep a getter and setter. 

```
class Node {
    bool signal
}
```

Now for the actual transistors, they can have a type which will determine behavior either NMOS or PMOS, and a Node pointer for the drain, source, and gate. Then getters and setters, along with a method to calculate the behavior of the transistor, and one to get the value.

```
class Transistor{
    Transistor_Type type;
    Node * drain;
    Node * source;
    Node * gate;

    void update();
    bool getOutputVal() const;
}
```

I wrote the update logic and it was pretty interesting as in a perfect world, our code is correct but it does simplify some of the real world electrical circuit considerations such as what happens when a transistor is off, my code would simply not change the value which might work for our computer but in the real world it is simply floating and capacitance could lead to it having some charge. A minor limitation of my design but I think it is fine for our project.

### Step 1.5: Testing and Build Config
I realized this sort of project is a good chance to learn real C++ build tools and testing methods so I have refactored into this format.

src/                        //The source headers and cpp
    Node.h
    Node.cpp
    ...
tests/                      //Test Files
    test_node.cpp
    test_transistor.cpp
    ...
build/                      //This is where the build files go
CMakeLists.txt          //This is the build file

So I have decided to learn how CMake works. I have used Makefiles before for normal C, I realize CMake is used widely in the industry as well so I have created my build config using CMake for this project. I have also incorporated CTest which is technically part of CMake so that creates my test suite.

## Step 2: Gates (Not, Nand, ...)
Now that we have transistors, we will make the base gates necessary for the computer and its smaller components. I will start with the Not / Inverter.

I will create the Not Gate using 4 nodes and 2 transisters, a PMOS and NMOS, which is how it is actually constructed. And in the cpp, the vdd, ground, pmos, and nmos are stored as members of the class not pointers as they exist only within the gate, while input and output are pointers as they connect the gate to external nodes.

```
class NotGate{
    Node vdd;
    Node ground;
    Node* input;
    Node* output;
    Transistor pmos;
    Transistor nmos;

    void update();
    bool getOutputVal() const;
}
```

So basically I am mapping the transistor level circuit to Nodes and Transistors within the constructor, and the update function basically updates the transistor.

I will use this method to create all the necessary gates.

### PROBLEM FOUND
While building the NAND gate, I found a limitation in my transistor model. My update() function copies the source value to the drain when a transistor is on, but a real transistor instead creates a conductive connection between the source and drain. This matters when multiple transistors are connected because a node containing 0 is not necessarily connected to ground, it could simply be floating.

For the solution, I realized we need to see the whole circuit, not just one part. So I will have a circuit class that evaluates circuits and instead of update(), the transistor will now simply determine whether it is conducting based on its type and gate. Then the circuit class can check and evaluate the node values.

```
class Transistor{
    Transistor_Type type;
    Node* drain;
    Node* source;
    Node* gate;

    bool isConducting() const;
}
```

For the circuit class, it will basically be like the physical topology by keeping track of the nodes, transistors, and which nodes are externally driven. When evaluating, it starts by marking the driven nodes as already known, then goes through each transistor and checks whether its gate has been evaluated and whether the transistor is conducting. If one side of a conducting transistor is known and the other is not, it copies the known value across the connection and marks the new node as evaluated. It keeps repeating this process while new nodes are being evaluated, which lets signals propagate through multiple connected transistors without depending on a specific update order.

```
class Circuit{
    std::unordered_set<Node*> nodes;
    std::unordered_set<Node*> driven_nodes;
    std::unordered_set<Transistor*> transistors;

    void evaluate();
}
```

At this point I think we are done with the base physical layer for now and can continue to make the gates necessary.

## Step 3: Components

At the component level I realized timing starts to matter. I don't want to simulate real nanoseconds or transistor-level electrical delay, so I simplified it by saying every logic gate takes 1 simulated tick. Components are then just circuits of gates and nodes, and their propagation delay comes from the logic depth. Gates on the same level can update in parallel, while gates that depend on earlier outputs update on later ticks. This gives each component a simple critical path based on the longest chain of gates.

I started with the Half Adder, then used two Half Adders to make a Full Adder, and finally chained 8 Full Adders into an 8-bit Ripple Carry Adder. The Half Adder calculates Sum and Carry, while the Full Adder adds a Carry In so they can be chained. For the Ripple Carry Adder, carry has to propagate from one Full Adder into the next. For now I use a conservative timing model where each Full Adder completely settles before the next begins, which keeps the logic simple and prevents stale carry values.

## Step 4: CPU Components

For the ALU I used a bit-sliced design. I first made an ALU1 which takes one bit from A and B and can perform ADD, AND, OR, or XOR. All four possible results are calculated and MUXes use the opcode bits to collapse them into the final result. I then chained 8 ALU1 slices together to make an ALU8, with carry propagating between the slices for addition and the same opcode being sent to every slice. At this point I have my first actual CPU component, and its behavior still traces all the way down through the gates, circuit evaluator, and transistors.