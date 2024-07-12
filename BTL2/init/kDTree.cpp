#include "kDTree.hpp"

/* TODO: You can implement methods, functions that support your data structures here.
 * */
void kDTree::destroyTree(kDTreeNode *node)
{
    if (node == nullptr)
        return;

    // Giải phóng node con bên trái
    destroyTree(node->left);

    // Giải phóng node con bên phải
    destroyTree(node->right);

    // Giải phóng node hiện tại
    delete node;
}

kDTreeNode* kDTree::copyTree(kDTreeNode* node)
{
    if (node == nullptr)
        return nullptr;

    // Sao chép node hiện tại
    kDTreeNode* newNode = new kDTreeNode(node->data);

    // Sao chép cây con bên trái và bên phải
    newNode->left = copyTree(node->left);
    newNode->right = copyTree(node->right);

    return newNode;
}

    void kDTree::clear()
    {
        // Gọi hàm đệ quy để giải phóng tất cả các node trong cây
        destroyTree(root);
        root = nullptr; // Đặt root thành nullptr sau khi cây đã được giải phóng
    }

void kDTree::printNode(const kDTreeNode *node, std::ostream& os) const
{
    os << "(";
    for (size_t i = 0; i < node->data.size(); ++i)
    {
        os << node->data[i];
        if (i != node->data.size() - 1)
            os << ", ";
    }
    os << ")";
}

void kDTree::inorderHelper(kDTreeNode *node, std::string& output) const
{
    if (node == nullptr)
        return;
    // Duyệt cây con bên trái
    inorderHelper(node->left, output);

    std::stringstream ss;
    printNode(node, ss);
    output += ss.str() + " ";
    // Duyệt cây con bên phải
    inorderHelper(node->right, output);
}

void kDTree::inorderTraversal() const
{
    std::string output;
    inorderHelper(root, output);
    // Loại bỏ khoảng trắng dư ở cuối
    output = output.substr(0, output.size() - 1);
    std::cout << output;
}

void kDTree::preorderHelper(kDTreeNode *node, std::ostream& os) const
{
    if (node == nullptr)
        return;
    // In giá trị của node
    printNode(node, os);
    os << " ";
    // Duyệt cây con bên trái
    preorderHelper(node->left, os);
    // Duyệt cây con bên phải
    preorderHelper(node->right, os);
}

void kDTree::preorderTraversal() const
{
    std::ostringstream os;
    preorderHelper(root, os);
    std::string output = os.str();
    // Loại bỏ khoảng trắng dư ở cuối
    output = output.substr(0, output.size() - 1);
    std::cout << output;
}

void kDTree::postorderHelper(kDTreeNode *node, std::ostream& os) const
{
    if (node == nullptr)
        return;
    // Duyệt cây con bên trái
    postorderHelper(node->left, os);
    // Duyệt cây con bên phải
    postorderHelper(node->right, os);
    // In giá trị của node
    printNode(node, os);
    os << " ";
}

void kDTree::postorderTraversal() const
{
    std::ostringstream os;
    postorderHelper(root, os);
    std::string output = os.str();
    // Loại bỏ khoảng trắng dư ở cuối
    output = output.substr(0, output.size() - 1);
    std::cout << output;
}

int kDTree::nodeCountHelper(kDTreeNode *node) const
{
    if (node == nullptr)
        return 0;
    else
    {
        // Tính số node của mỗi cây con
        int leftCount = nodeCountHelper(node->left);
        int rightCount = nodeCountHelper(node->right);

        // Trả về tổng số node của hai cây con, cộng thêm 1 (để tính nút hiện tại)
        return leftCount + rightCount + 1;
    }
}

int kDTree::nodeCount() const
{
    return nodeCountHelper(root);
}

int kDTree::leafCountHelper(kDTreeNode *node) const
{
    if (node == nullptr)
        return 0;
    else if (node->left == nullptr && node->right == nullptr)
        return 1;
    else
    {
        // Tính số node lá của mỗi cây con
        int leftCount = leafCountHelper(node->left);
        int rightCount = leafCountHelper(node->right);

        // Trả về tổng số node lá của hai cây con
        return leftCount + rightCount;
    }
}

int kDTree::leafCount() const
{
    return leafCountHelper(root);
}

void kDTree::insert(const vector<int>& point) {
    // Nếu số chiều của điểm không đúng với số chiều của các điểm trong cây, không thêm vào cây
    if (point.size() != k) {
        std::cerr << "Invalid dimension for insertion." << std::endl;
        return;
    }

    // Gọi hàm đệ quy để chèn điểm vào cây
    root = insertHelper(root, point, 0);
}

kDTreeNode* kDTree::insertHelper(kDTreeNode* node, const vector<int>& point, int depth) {
    // Nếu node hiện tại là nullptr, đây là vị trí chèn mới
    if (node == nullptr) {
        return new kDTreeNode(point); // Tạo một nút mới với điểm là point
    }

    // Xác định mặt phẳng chia hiện tại (theo chiều của mặt phẳng chia)
    int dim = depth % k;

    // So sánh giá trị của mặt phẳng chia của node với giá trị tương ứng của điểm cần chèn
    if (point[dim] < node->data[dim]) {
        // Điều chỉnh sang cây con bên trái
        node->left = insertHelper(node->left, point, depth + 1);
    } else {
        // Điều chỉnh sang cây con bên phải
        node->right = insertHelper(node->right, point, depth + 1);
    }

    return node;
}

// Hàm tìm nút có giá trị nhỏ nhất theo chiều alpha trong cây con
kDTreeNode* kDTree::find_min_alpha(kDTreeNode* root, int depth, int k, int alpha, int& newalpha) {
    if (root == nullptr)
        return nullptr;

    if (depth % k == alpha) {
        if (root->left == nullptr) {
            newalpha = depth;
            return root;
        }
        return find_min_alpha(root->left, depth + 1, k, alpha, newalpha);
    } else {
        kDTreeNode* nleft = find_min_alpha(root->left, depth + 1, k, alpha, newalpha);
        kDTreeNode* nright = find_min_alpha(root->right, depth + 1, k, alpha, newalpha);

        kDTreeNode* min_node = root;
        newalpha = depth;

        if (nleft != nullptr && nleft->data[alpha] < min_node->data[alpha]) {
            min_node = nleft;
            newalpha = depth + 1;
        }

        if (nright != nullptr && nright->data[alpha] < min_node->data[alpha]) {
            min_node = nright;
            newalpha = depth + 1;
        }

        return min_node;
    }
}

// Hàm xóa nút từ cây kD-Tree
void kDTree::remove(const vector<int>& point) {
    root = removeNode(root, point, 0);
}

// Hàm đệ quy để xóa nút từ cây
kDTreeNode* kDTree::removeNode(kDTreeNode* root, const vector<int>& point, int depth) {
    if (root == nullptr)
        return nullptr;

    int dim = depth % k;

    // Nếu nút hiện tại là nút cần xóa
    if (root->data == point) {
        // Nếu nút có cây con bên phải
        if (root->right != nullptr) {
            int newalpha = 0;
            kDTreeNode* replacement_node = find_min_alpha(root->right, depth + 1, k, dim, newalpha);

            // Copy dữ liệu của nút thay thế vào nút hiện tại
            root->data = replacement_node->data;

            // Đệ quy xóa nút thay thế từ cây con bên phải
            root->right = removeNode(root->right, replacement_node->data, depth + 1);
        }
        // Nếu nút không có cây con bên phải nhưng có cây con bên trái
        else if (root->left != nullptr) {
            int newalpha = 0;
            kDTreeNode* replacement_node = find_min_alpha(root->left, depth + 1, k, dim, newalpha);

            // Copy dữ liệu của nút thay thế vào nút hiện tại
            root->data = replacement_node->data;

            // Cập nhật liên kết của nút hiện tại
            root->right = root->left;
            root->left = nullptr;

            // Đệ quy xóa nút thay thế từ cây con bên trái
            root->right = removeNode(root->right, replacement_node->data, depth + 1);
        }
        // Nếu nút hiện tại là nút lá
        else {
            delete root; // Giải phóng bộ nhớ của nút lá
            return nullptr; // Trả về nullptr để cập nhật liên kết của nút cha
        }
        return root;
    }

    // Nếu nút cần xóa nằm ở cây con trái hoặc phải
    if (point[dim] < root->data[dim])
        root->left = removeNode(root->left, point, depth + 1);
    else
        root->right = removeNode(root->right, point, depth + 1);

    return root;
}



void merge(vector<vector<int>>& points, int dim, int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;
   
    vector<vector<int>> L(n1), R(n2);

    
    for (i = 0; i < n1; i++)
        L[i] = points[left + i];
    for (j = 0; j < n2; j++)
        R[j] = points[mid + 1 + j];

    i = 0; // Chỉ số bắt đầu cho mảng con đầu tiên
    j = 0; // Chỉ số bắt đầu cho mảng con thứ hai
    k = left; // Chỉ số bắt đầu cho mảng con đã được merge
    while (i < n1 && j < n2) {
        if (L[i][dim] <= R[j][dim]) {
            points[k] = L[i];
            i++;
        } else {
            points[k] = R[j];
            j++;
        }
        k++;
    }

    
    while (i < n1) {
        points[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        points[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(vector<vector<int>>& points, int dim, int left, int right) {
    if (left < right) {
      
        int mid = left + (right - left) / 2;

       
        mergeSort(points, dim, left, mid);
        mergeSort(points, dim, mid + 1, right);

      
        merge(points, dim, left, mid, right);
    }
}

kDTreeNode* kDTree::buildTreeHelper(vector<vector<int>>& points, int depth, int start, int end) {
    if (start > end)
        return nullptr;

    
    int dim = depth % k;
    mergeSort(points, dim, start, end);
    
    int mid = start + (end - start) / 2;

   
    kDTreeNode* node = new kDTreeNode(points[mid]);

    node->left = buildTreeHelper(points, depth + 1, start, mid - 1);
    node->right = buildTreeHelper(points, depth + 1, mid + 1, end);

    return node;
}

void kDTree::buildTree(const vector<vector<int>>& pointList) {
    if (pointList.empty())
        return;

    vector<vector<int>> points = pointList;

    root = buildTreeHelper(points, 0, 0, points.size() - 1);
}

bool kDTree::search(const vector<int>& point) {
    return searchHelper(root, point, 0);
}

bool kDTree::searchHelper(kDTreeNode* node, const vector<int>& point, int depth) const {
    // Nếu node hiện tại là nullptr, tức là chúng ta đã đi qua lá của cây và không tìm thấy điểm
    if (node == nullptr) {
        return false;
    }

    // So sánh điểm của node hiện tại với điểm cần tìm kiếm
    if (node->data == point) {
        return true; // Nếu tìm thấy điểm
    }

    // Xác định mặt phẳng chia hiện tại (theo chiều của mặt phẳng chia)
    int dim = depth % k;

    // Nếu giá trị của mặt phẳng chia của node lớn hơn giá trị tương ứng của điểm cần tìm kiếm
    if (point[dim] < node->data[dim]) {
        return searchHelper(node->left, point, depth + 1); // Duyệt sang cây con bên trái
    } else {
        return searchHelper(node->right, point, depth + 1); // Duyệt sang cây con bên phải
    }
}

// Hàm tính khoảng cách Euclid giữa hai điểm
double kDTree::distanceEuclid(const vector<int>& p1, const vector<int>& p2) {
    double sum = 0.0;
    for (size_t i = 0; i < this->k; ++i) {
        sum += pow(p1[i] - p2[i], 2);
    }
    return sqrt(sum);
}

// Hàm tìm nút láng giềng gần nhất trong cây KD-tree
void kDTree::nearestNode(kDTreeNode* root, const vector<int>& target, kDTreeNode*& best, double& bestDist, int level) {
    if (root == nullptr)
        return;

    int k = target.size();
    int dimen = level % k; // Lấy chiều để so sánh
    bool goRight = (target[dimen] > root->data[dimen]);

    // Di chuyển xuống cây theo chiều đúng
    if (goRight) {
        nearestNode(root->right, target, best, bestDist, level + 1);
    } else {
        nearestNode(root->left, target, best, bestDist, level + 1);
    }

    // Tính khoảng cách từ nút hiện tại đến mục tiêu
    double currentDist = distanceEuclid(root->data, target);

    // Cập nhật nút láng giềng gần nhất nếu tìm thấy nút tốt hơn
    if (currentDist < bestDist) {
        best = root;
        bestDist = currentDist;
    }

    // Kiểm tra xem có cần đi sang nhánh còn lại không
    double splitDist = abs(target[dimen] - root->data[dimen]);
    if (splitDist < bestDist) {
        if (goRight) {
            nearestNode(root->left, target, best, bestDist, level + 1);
        } else {
            nearestNode(root->right, target, best, bestDist, level + 1);
        }
    }
}

// Phương thức tìm láng giềng gần nhất của điểm target
void kDTree::nearestNeighbour(const vector<int>& target, kDTreeNode*& best) {
    double bestDist = 1e9;
    nearestNode(this->root, target, best, bestDist, 0);
}


void kDTree::kNearestNeighbour(const vector<int>& target, int k, vector<kDTreeNode*>& bestList) {
    // Tạo một vector để lưu trữ k điểm gần nhất
    vector<NodeDist> bestNodes;

    // Gọi hàm đệ quy để tìm k láng giềng gần nhất
    kNearestNode(this->root, target, bestNodes, k, 0);

    // Chuyển các điểm từ vector bestNodes sang danh sách kết quả
    for (const auto& nodeDist : bestNodes) {
        bestList.push_back(nodeDist.node);
    }
}

void kDTree::kNearestNode(kDTreeNode* root, const vector<int>& target, vector<NodeDist>& bestNodes, int k, int level) {
    if (root == nullptr)
        return;

    int dimen = level % this->k; // Lấy chiều để so sánh
    bool goRight = (target[dimen] > root->data[dimen]);

    // Di chuyển xuống cây theo chiều đúng
    if (goRight) {
        kNearestNode(root->right, target, bestNodes, k, level + 1);
    } else {
        kNearestNode(root->left, target, bestNodes, k, level + 1);
    }

    // Tính khoảng cách từ nút hiện tại đến mục tiêu
    double currentDist = distanceEuclid(root->data, target);

    // Tìm vị trí chèn phù hợp trong vector
    int i = 0;
    while (i < bestNodes.size() && bestNodes[i].dist < currentDist) {
        ++i;
    }

    // Thêm nút hiện tại vào vị trí chèn trong vector
    if (i < k) {
        bestNodes.insert(bestNodes.begin() + i, NodeDist(root, currentDist));

        // Nếu có nhiều hơn k điểm trong vector, loại bỏ điểm xa nhất
        if (bestNodes.size() > k) {
            bestNodes.pop_back();
        }
    }

    // Kiểm tra xem có cần đi sang nhánh còn lại không
    double splitDist = abs(target[dimen] - root->data[dimen]);
    if (bestNodes.size() < k || splitDist < bestNodes.back().dist) {
        if (goRight) {
            kNearestNode(root->left, target, bestNodes, k, level + 1);
        } else {
            kNearestNode(root->right, target, bestNodes, k, level + 1);
        }
    }
}
//                                                                      KNN
//######################################################################   #########################################################################

 void kNN::fit(Dataset& X_train, Dataset& y_train) {
        this->X_train = X_train;
        this->y_train = y_train;

        // Build the kD-Tree using the training data
        vector<vector<int>> treeNode;
        auto it_y = y_train.data.begin();

        for (const list<int>& li : X_train.data) {
            vector<int> node(li.begin(), li.end());
            if (it_y != y_train.data.end()) {
                node.push_back(it_y->front());
                ++it_y;
            }
            treeNode.push_back(node);
        }
        kDTree kDTree(784);
        kDTree.buildTree(treeNode);
        this->tree = kDTree;
        
    }
    Dataset kNN::predict(const Dataset& X_test) {
    Dataset y_pred; // Dataset to store predicted labels
    for (const list<int>& image : X_test.data) {
        // Convert image (row) to a vector of int
        vector<int> query_point(image.begin(), image.end());
        // Find k nearest neighbors in the kDTree
        vector<kDTreeNode*> nearest_neighbors;
        this->tree.kNearestNeighbour(query_point, k, nearest_neighbors);
        /*for (auto node : nearest_neighbors)
        {
            cout << *node << " ";
        }*/
        const int max_label_value = 10; 
        vector<int> label_counts(max_label_value + 1, 0);

        for (kDTreeNode* neighbor : nearest_neighbors) {
            int label = neighbor->data.back(); 
            //cout<<label; //in label 
            label_counts[label]++;
        }

        int predicted_label = -1;
        int max_count = 0;
        for (int label_value = 0; label_value <= max_label_value; ++label_value) {
            if (label_counts[label_value] > max_count) {
                max_count = label_counts[label_value];
                predicted_label = label_value;
            }
        }
        list<int> pred_row = {predicted_label};
        y_pred.data.push_back(pred_row);
        y_pred.columnName = this->y_train.columnName;
    }
    return y_pred;
}
double kNN::score(Dataset& y_test, Dataset& y_pred) {
    // Kiểm tra xem y_test và y_pred có cùng kích thước không
    if (y_test.data.size() != y_pred.data.size()) {
        return 0.0;
    }

    // Tính số lượng dự đoán chính xác
    int correct = 0;
    auto it_test = y_test.data.begin();
    auto it_pred = y_pred.data.begin();

    while (it_test != y_test.data.end() && it_pred != y_pred.data.end()) {
        if (it_test->front() == it_pred->front()) {
            ++correct;
        }
        ++it_test;
        ++it_pred;
    }

    // Trả về tỷ lệ dự đoán chính xác
    return static_cast<double>(correct) / y_test.data.size();
}









