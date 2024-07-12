#include "main.hpp"
#include "Dataset.hpp"
/* TODO: Please design your data structure carefully so that you can work with the given dataset
 *       in this assignment. The below structures are just some suggestions.
 */
struct kDTreeNode
{   vector<int> data;
    kDTreeNode *left;
    kDTreeNode *right;
    kDTreeNode(vector<int> data, kDTreeNode *left = nullptr, kDTreeNode *right = nullptr)
    {
        this->data = data;
        this->left = left;
        this->right = right;
    }

     friend std::ostream& operator<<(std::ostream& os, const kDTreeNode& node) {
    os << "(";
    for (int i = 0; i < node.data.size(); ++i) {
        os << node.data[i];
        if (i != node.data.size() - 1) {
            os << ", ";
        }
    }
    os << ")";
    return os;
}
};

class NodeDist {
public:
    kDTreeNode* node;
    double dist;

    NodeDist(kDTreeNode* node, double dist) : node(node), dist(dist) {}
};

class kDTree
{
private:
    int k;
    kDTreeNode *root;

public:
    kDTree(int k = 2){
        this->k = k;
        this->root = NULL;    
    };
    ~kDTree() {
    destroyTree(root);
}

    const kDTree &operator=(const kDTree &other){
         if (this == &other) {
        return *this; // Tránh gán tự gán
    }

    // Xóa dữ liệu hiện tại (nếu có)
    clear(); // Gọi hàm clear để giải phóng cây hiện tại

    // Sao chép giá trị của k
    k = other.k;

    // Sao chép cây từ other sang *this
    root = copyTree(other.root);

    return *this;
    };

    kDTree(const kDTree &other){
    // Sao chép giá trị của k từ other sang *this
    k = other.k;
    // Sao chép cây từ other sang *this bằng cách gọi hàm đệ quy copyTree
    root = copyTree(other.root);
    };

    void printNode(const kDTreeNode *node, std::ostream& os) const;

    void inorderHelper(kDTreeNode *node, std::string& output) const;
    void inorderTraversal() const;

    void preorderHelper(kDTreeNode *node, std::ostream& os) const;
    void preorderTraversal() const;
    
    void postorderHelper(kDTreeNode *node, std::ostream& os) const;
    void postorderTraversal() const;
    int height() const;
    
    int nodeCountHelper(kDTreeNode *node) const;
    int nodeCount() const;
    
    int leafCountHelper(kDTreeNode *node) const;
    int leafCount() const;
    
    void insert(const vector<int> &point);
    kDTreeNode* insertHelper(kDTreeNode* node, const vector<int>& point, int depth);

    void remove(const vector<int> &point);
    kDTreeNode* find_node_remove(kDTreeNode* root, int depth, int k, const vector<int> &point, int &alpha);
    kDTreeNode* find_min_alpha(kDTreeNode* root, int depth, int k, int alpha, int& newalpha);
    kDTreeNode* removeNode(kDTreeNode* root, const vector<int>& point, int depth);

    bool search(const vector<int> &point);
    bool searchHelper(kDTreeNode* node, const vector<int>& point, int depth) const;

    void buildTree(const vector<vector<int>> &pointList);
    kDTreeNode* buildTreeHelper(vector<vector<int>>& points, int depth, int start, int end);

   void nearestNode(kDTreeNode* root, const vector<int>& target, kDTreeNode*& best, double& bestDist, int level);
   void nearestNeighbour(const vector<int>& target, kDTreeNode*& best);
    //void nearestNeighbourHelper(kDTreeNode* node, const vector<int>& target, int depth, kDTreeNode*& best);
    //void nearestNeighbourHelper(kDTreeNode* node, const std::vector<int>& target, kDTreeNode*& best, double& bestDistance, int depth) ;
   void kNearestNode(kDTreeNode* root, const vector<int>& target, vector<NodeDist>& bestNodes, int k, int level);
   void kNearestNeighbour(const vector<int>& target, int k, vector<kDTreeNode*>& bestList);
    // void kNearestNeighbourHelper(kDTreeNode* node, const vector<int>& target, int depth, int k, vector<double>& closestDistances, vector<kDTreeNode*>& closestNodes);
    //void kNearestNeighbourHelper(kDTreeNode* node, const std::vector<int>& target, int k, int depth, std::list<NodeDistance>& nearestList) const;
    double distanceEuclid(const vector<int>& p1, const vector<int>& p2);
  
    kDTreeNode* copyTree(kDTreeNode* node);
    void destroyTree(kDTreeNode *node);
    void clear();

};

class kNN
{
private:
    int k;
    Dataset X_train;
    Dataset y_train;
    

public:
    kDTree tree; // Thêm thuộc tính tree
   kNN(int k = 5) {
        this->k = k;
    }
    void fit(Dataset &X_train, Dataset &y_train);
    Dataset predict(const Dataset &X_test);
    double score( Dataset &y_test,  Dataset &y_pred);
};

// Please add more or modify as needed
