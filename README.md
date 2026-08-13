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
    bool getOutput() const;
}
```

I wrote the update logic and it was pretty interesting as in a perfect world, our code is correct but it does simplify some of the real world electrical circuit considerations such as what happens when a transistor is off, my code would simply not change the value which might work for our computer but in the real world it is simply floating and capacitance could lead to it having some charge. A minor limitation of my design but I think it is fine for our project.