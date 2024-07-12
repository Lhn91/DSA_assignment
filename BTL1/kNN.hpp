#include "main.hpp"

/* TODO: Please design your data structure carefully so that you can work with the given dataset
 *       in this assignment. The below structures are just some suggestions.
 */

template<typename T>
class abList {
public:
    class node {
    public:
        T val;
        node* next;
        node(T v = 0, node* n = 0) {
            val = v;
            next = n;
        }
    };

    node* head;
    node* tail;
    int count = 0;
public:
    virtual ~abList() = default;
    virtual void push_back(T value) = 0;
    virtual void push_front(T value) = 0;
    virtual void insert(int index, T value) = 0;
    virtual void remove(int index) = 0;
    virtual T& get(int index) const = 0;
    virtual int length() const = 0;
    virtual void clear() = 0;
    virtual void print() const = 0;
    virtual void reverse() = 0;
};

template<typename T>
class List : public abList<T> {
public:
    void push_back(T value) override {
        if (this->count == 0) {
            this->head = this->tail = new typename List<T>::node(value);
        }
        else {
            this->tail->next = new typename List<T>::node(value);
            this->tail = this->tail->next;
        }
        this->count++;
    }

    void push_front(T value)override {
        if (this->count == 0) {
            this->head = this->tail = new typename List<T>::node(value);
        }
        else {

            typename List<T>::node* temp = new typename List<T>::node(value, this->head);

            this->head = temp;
        }
        this->count++;
    }

    typename abList<T>::node gethead() {
        return this->head;
    }

    T& get(int index) const override {
        if (index < 0 || index >= this->count) {
            throw std::out_of_range("Index out of range");
        }
        typename abList<T>::node* temp = this->head;
        for (int i = 0; i < index; i++) {
            if (temp->next == nullptr) {
                throw std::out_of_range("Index out of range");
            }
            temp = temp->next;
        }

        return temp->val;
    }

  

    void remove(int index) override {
        if (index < 0 || index >= this->count) {
            return;
        }

        if (index == 0) {
            typename abList<T>::node* temp = this->head;
            this->head = this->head->next;
            delete temp;
            this->count--;
            return;
        }

        typename abList<T>::node* temp = this->head;
        for (int i = 0; i < index - 1; ++i) {
            temp = temp->next;
        }

        typename abList<T>::node* toDelete = temp->next;
        temp->next = toDelete->next;
        delete toDelete;
        this->count--;
    }

    //nnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn
    void insert(int index, T value) override {
        if (index < 0 || index > this->count) {
            return;
        }

        if (index == this->count) {
            push_back(value);
            return;
        }
        if (index == 0) {
            push_front(value);
            return;
        }

        typename abList<T>::node* temp = this->head;
        for (int i = 0; i < index - 1; ++i) {
            temp = temp->next;
        }

        temp->next = new typename List<T>::node(value, temp->next);
        this->count++;
    }
    int length() const override {
        return this->count;
    }

    void clear() override {
        while (this->head != nullptr) {
            typename abList<T>::node* temp = this->head;
            this->head = this->head->next;
            delete temp;
        }
        this->tail = nullptr;
        this->count = 0;
    }

    void print() const override {
        typename abList<T>::node* temp = this->head;
        while (temp != nullptr) {
            std::cout << temp->val << " ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }

    void reverse() override {
        typename abList<T>::node* prev = nullptr;
        typename abList<T>::node* current = this->head;
        typename abList<T>::node* next = nullptr;

        while (current != nullptr) {
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }

        this->head = prev;
    }

    //nnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn
};


class Dataset {
private:
    List<List<int>*>* data;
    List<int>* label;
    List<int>* index;
    int size = 0;

    //You may need to define more
public:
    Dataset() {
        data = new List<List<int>*>();
        index = new List<int>();
        label = new List<int>();
    }
    ~Dataset() {}
    Dataset(const Dataset& other) {
        this->data = other.data;
        this->label = other.label;
        this->index = other.index;
    }
    Dataset& operator=(const Dataset& other) {
        this->data = other.data;
        this->label = other.label;
        this->index = other.index;
        return *this;
    }
    bool loadFromCSV(const char* fileName);
    void printHead(int nRows, int nCols);
    void printData();
    void printTail(int nRows, int nCols);
    void getShape(int& nRows, int& nCols) const;
    void columns() const;
    bool drop(int axis, int index, std::string columns);
    Dataset extract(int startRow = 0, int endRow = -1, int startCol = 0, int endCol = -1) const;
    int getRowCount() const;
    int getColumnCount() const;
    List<int>* getLabel() {
        return this->label;
    }
    List<int>* getIndex() {
        return this->index;
    }

    List <List <int >* >* getData() const;
};



/* TODO: You can implement methods, functions that support your data structures here.
 * */
struct Pair {
    double distance;
    int label;
};


class kNN {
private:
    int k;
    //You may need to define more
    Dataset X_train;
    Dataset y_train;


public:
    kNN(int k = 5) {
        this->k = k;
    }
    void fit(const Dataset& X_train, const Dataset& y_train);
    Dataset predict(const Dataset& X_test);
    double score(const Dataset& y_test, const Dataset& y_pred);


};



void train_test_split(Dataset& X, Dataset& y, double test_size,
    Dataset& X_train, Dataset& X_test, Dataset& y_train, Dataset& y_test);
