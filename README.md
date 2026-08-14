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