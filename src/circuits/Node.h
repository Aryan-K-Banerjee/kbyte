//src/circuits/Node.h
#ifndef NODE_H
#define NODE_H

class Node {
    private:
        bool signal;

    public:
        Node(bool signal);

        void setSignal(bool value);
        bool getSignal() const;
};

#endif