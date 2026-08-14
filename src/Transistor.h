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
        Transistor();
        Transistor(Transistor_Type type, Node* drain, Node* source, Node* gate);

        void setType(Transistor_Type type);
        void connectDrain(Node* node);
        void connectSource(Node* node);
        void connectGate(Node* node);

        Transistor_Type getType() const;
        Node* getDrain() const;
        Node* getSource() const;
        Node* getGate() const;

        void update();
        bool getOutput() const;
        
};

#endif