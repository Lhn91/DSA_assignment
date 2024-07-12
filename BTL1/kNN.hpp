#include "main.hpp"

/* TODO: Please design your data structure carefully so that you can work with the given dataset
 *       in this assignment. The below structures are just some suggestions.
 */

template<typename T>
class List {
private:
    Node* head;
    Node* tail;
 //////////////NODE///////////////
public:
    class* Node{
    private:
        int data;
        string firstline;
    public:
        Node(int val) : data(val) , next(nullptr);
        Node(string fl) : firstline(fl) , next(nullptr);
    }

    class* NodeLable : public Node{
    private:
        NodeLable* up;
        NodeLable* down;
        NodeLable* next;
    public:
        NodeLabel(std::string fl) : Node(fl), up(nullptr), down(nullptr), next(nullptr) {
        };
    };

    class* NodeVal{
private:
    NodeVal* next;
    NodeVal* pre;
public:
   NodeVal(int val) : Node(val), up(nullptr), down(nullptr), next(nullptr) {}
    };
//////////////NODE////////////
public:
    virtual ~List() = default;
    virtual void push_back(T value) = 0;
    virtual void push_front(T value) = 0;
    virtual void insert(int index, T value) = 0;
    virtual void remove(int index) = 0;
    virtual T& get(int index) const = 0;
    virtual int length() const = 0 ;
    virtual void clear() = 0;
    virtual void print() const = 0;
    virtual void reverse() = 0;
};

class Dataset {
private:
    List<List<int>*>* data;
    //You may need to define more
public:
    Dataset();
    ~Dataset();
    Dataset(const Dataset& other);
    Dataset& operator=(const Dataset& other);
    bool loadFromCSV(const char* fileName);
    void printHead(int nRows = 5, int nCols = 5) const;
    void printTail(int nRows = 5, int nCols = 5) const;
    void getShape(int& nRows, int& nCols) const;
    void columns() const;
    bool drop(int axis = 0, int index = 0, std::string columns = "");
    Dataset extract(int startRow = 0, int endRow = -1, int startCol = 0, int endCol = -1) const;
};

class kNN {
private:
    int k;
    //You may need to define more
public:
    kNN(int k = 5);
    void fit(const Dataset& X_train, const Dataset& y_train);
    Dataset predict(const Dataset& X_test);
    double score(const Dataset& y_test, const Dataset& y_pred);
};

void train_test_split(Dataset& X, Dataset& y, double test_size,
                        Dataset& X_train, Dataset& X_test, Dataset& y_train, Dataset& y_test);

// Please add more or modify as needed
