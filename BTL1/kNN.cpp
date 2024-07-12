#include "kNN.hpp"

//TODO: You can implement methods, functions that support your data structures here
Node* readfile(int filename) {
    ifstream ifs(filename);
    filename.open("mnist.csv");
    string line = "";
    auto data;
    NodeLable* HeadLable = new NodeLable(0);
    NodeLable* TailLable = new NodeLable(0);
    Node* head = new Node;
    Node* tail = new Node;

        if (getline(filename, line)) {
            stringstream inputString(line);
            if (getline(inputString, data, ',')) {
                 HeadLable = new NodeLable(data);
                 TailLable = HeadLable;
                 Node* head = HeadLable;
            }
            while (getline(inputString, data, ',')) {
                Node* head->next = new Node(data);
            }
        }

        while (getline(filename, line)) {
        stringstream inputString(line);
            if (getline(inputString, data, ',')) {
                NodeLable* HEAD = new NodeLable(data);
                Node* tail = HEAD;
            }
        while (getline(inputString, data, ',')) {
            Node*  = new Node(data);
        }

       
   
}
