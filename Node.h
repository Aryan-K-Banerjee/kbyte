class Node {

private:
    bool signal;

public:
    Node();
    Node(bool initialValue);

    void setSignal(bool value);
    bool getSignal() const;
};