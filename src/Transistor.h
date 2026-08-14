#ifndef TRANSISTOR_H
#define TRANSISTOR_H

#include "Node.h"

class Transistor{
        
    public:
        enum Transistor_Type{
            NMOS,
            PMOS
        };

    private:
        Transistor_Type type;
        Node * drain;
        Node * source;
        Node * gate;
    
    public:
        Transistor(Transistor_Type type, Node* source, Node* gate, Node* drain);

        void setType(Transistor_Type type);
        void connectSource(Node* node);
        void connectGate(Node* node);
        void connectDrain(Node* node);

        Transistor_Type getType() const;
        Node* getSource() const;
        Node* getGate() const;
        Node* getDrain() const;

        void update();
        bool getOutputVal() const;
        
};

#endif