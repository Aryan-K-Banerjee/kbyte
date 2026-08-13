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

