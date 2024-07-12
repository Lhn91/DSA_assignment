#include "kNN.hpp"
//ok
/* TODO: You can implement methods, functions that support your data structures here.
 * */
std::ostream& operator<<(std::ostream& os, const Pair& p) {
     os << "(" << p.distance << ", " << p.label << ")";
     return os;
 }
 void kNN::fit(const Dataset& X_train, const Dataset& y_train) {
     /*List<int>* label = this->getdata().getLabel();

     abList<int>::node* temp = label->head;
     while(temp) {
         List<int>* newRow = new List<int>();
         newRow->push_back(temp->val);
         y_train.getData()->push_back(newRow);
         temp = temp->next;
     }

     abList<List<int>*>::node* temp2 = this->getdata().getData()->head;
     while(temp2) {
         List<int>* originalRow = temp2->val;
         List<int>* newRow = new List<int>();
         abList<int>::node* tempCol = originalRow->head->next;
         while(tempCol) {
             newRow->push_back(tempCol->val);
             tempCol = tempCol->next;
         }
         temp2 = temp2->next;
         X_train.getData()->push_back(newRow);
     }*/
     this->X_train = X_train; // Copy training data to the private member
     this->y_train = y_train;

 }

 double euclidean_distance(List<int>* a, List<int>* b) {
     double sum = 0;
     for (int i = 0; i < a->length(); i++) {
         sum += pow(a->get(i) - b->get(i), 2);
     }
     return sqrt(sum);
 }

 /*Dataset kNN::predict(const Dataset& X_test) {
     Dataset y_pred;
     for (int i = 0; i < X_test.getData()->length(); i++) {
         // Create a list to store the nearest neighbors
         List<Pair>* nearest = new List<Pair>();
         for (int j = 0; j < X_train.getData()->length(); j++) {
             double distance = euclidean_distance(X_test.getData()->get(i), X_train.getData()->get(j));
             Pair pair = {distance, y_train.getData()->get(j)->get(0)};
             // Add the pair to the list
             nearest->push_back(pair);
         }
         // Sort the list based on the distance
         for (int m = 0; m < nearest->length(); m++) {
             for (int n = m + 1; n < nearest->length(); n++) {
                 if (nearest->get(m).distance > nearest->get(n).distance) {
                     Pair temp = nearest->get(m);
                     nearest->get(m) = nearest->get(n);
                     nearest->get(n) = temp;
                 }
             }
         }
         // Get the most common label in the k nearest neighbors
         int labels[10] = {0}; // Assuming labels are from 0 to 9
         for (int l = 0; l < k; l++) {
             labels[nearest->get(l).label]++;
         }
         int most_common_label = -1;
         int max_count = 0;
         for (int l = 0; l < 10; l++) {
             if (labels[l] > max_count) {
                 max_count = labels[l];
                 most_common_label = l;
             }
         }
         // Predict the label
         List<int>* pred = new List<int>();
         pred->push_back(most_common_label);
         y_pred.getData()->push_back(pred);
     }
     return y_pred;
 }*/
 Dataset kNN::predict(const Dataset& X_test) {
     Dataset y_pred;
     y_pred.getIndex()->push_back(-1);
     for (int i = 0; i < X_test.getData()->length(); i++) {
         List<int>* pred_row = new List<int>();
         List<Pair>* nearest = new List<Pair>();
         for (int j = 0; j < X_train.getData()->length(); j++) {
             double distance = euclidean_distance(X_test.getData()->get(i), X_train.getData()->get(j));
             Pair pair = { distance, y_train.getData()->get(j)->get(0) };
             nearest->push_back(pair);
         }

         for (int m = 0; m < nearest->length(); m++) {
             for (int n = m + 1; n < nearest->length(); n++) {
                 if (nearest->get(m).distance > nearest->get(n).distance) {
                     Pair temp = nearest->get(m);
                     nearest->get(m) = nearest->get(n);
                     nearest->get(n) = temp;
                 }
             }
         }

         int labels[10] = { 0 };
         for (int l = 0; l < k; l++) {
             labels[nearest->get(l).label]++;
         }
         int most_common_label = -1;
         int max_count = 0;
         for (int l = 0; l < 10; l++) {
             if (labels[l] > max_count) {
                 max_count = labels[l];
                 most_common_label = l;
             }
         }

         pred_row->push_back(most_common_label);

         y_pred.getData()->push_back(pred_row);
     }
     return y_pred;
 }


 double kNN::score(const Dataset& y_test, const Dataset& y_pred) {
     double correct_predictions = 0;
     for (int i = 0; i < y_test.getData()->length(); i++) {
         if (y_test.getData()->get(i)->get(0) == y_pred.getData()->get(i)->get(0)) {
             correct_predictions++;
         }
     }
     return correct_predictions / y_test.getData()->length();
 }
 void train_test_split(Dataset& X, Dataset& y, double test_size,
     Dataset& X_train, Dataset& X_test, Dataset& y_train, Dataset& y_test) {
     int text = X.getData()->count * (1.0 - test_size);
     int train = X.getData()->count - train;
     X_test = X.extract(text, -1, 0, -1);
     X_train = X.extract(0, text - 1, 0, -1);
     y_test = y.extract(text, -1, 0, -1);
     y_test.getIndex()->push_back(-1);
     y_train = y.extract(0, text - 1, 0, -1);
 }
 ///KNN========================================================================================================
 Dataset Dataset::extract(int startRow, int endRow, int startCol, int endCol) const {
     //Dataset load;
     //load.loadFromCSV("D:\\HK232\\run\\mnist.csv");
     Dataset extractedData;
     startRow = max(0, startRow);
     endRow = (endRow == -1) ? this->data->count - 1 : min(this->data->count - 1, endRow);
     startCol = max(0, startCol);
     endCol = (endCol == -1) ? this->data->head->val->count - 1 : min(this->data->head->val->count - 1, endCol);


     abList<List<int>*>::node* temp = this->data->head;
     for (int i = 0; i < startRow; ++i) {
         temp = temp->next;
     }

     for (int i = startRow; i <= endRow; ++i) {
         List<int>* originalRow = temp->val;
         List<int>* newRow = new List<int>();

         abList<int>::node* tempCol = originalRow->head;
         for (int i = 0; i < startCol; i++) {
             tempCol = tempCol->next;
         }
         for (int j = startCol; j <= endCol; ++j) {
             newRow->push_back(tempCol->val);
             tempCol = tempCol->next;
         }

         extractedData.data->push_back(newRow);
         temp = temp->next;
     }

     return extractedData;
 }

 List<List<int>*>* Dataset::getData() const {
     return this->data;
 }


 string numtoaddres(int n) {
     if (n == -1) return "label";
     return to_string((n - 1) / 28 + 1) + "x" + to_string((n - 1) % 28 + 1);
 }

 int addresstonum(string address) {
     int x, y;
     stringstream ss(address);
     char separator;
     ss >> x >> separator >> y;
     return (x - 1) * 28 + y;
 }

 bool Dataset::loadFromCSV(const char* fileName) {
     // Open the CSV file
     ifstream ifs(fileName);
     if (!ifs.is_open()) {
         // Handle error
         return false;
     }

     string firstLine;
     getline(ifs, firstLine);
     stringstream ss(firstLine);
     string item;


     while (getline(ss, item, ',')) {
         if (item == "label") {
             index->push_back(-1);
         }
         else {
             index->push_back(addresstonum(item));
         }
     }

     string line;
     while (getline(ifs, line)) {
         List<int>* newList = new List<int>();
         stringstream ss(line);
         string item;
         while (getline(ss, item, ',')) {
             newList->push_back(stoi(item));

         }
         this->data->push_back(newList);
         this->label->push_back(newList->head->val);
         this->size++;
     }
     return true;
 }



 void Dataset::printData() {
     abList<List<int>*>::node* temp = this->data->head;

     while (temp != NULL) {

         List<int>* list = temp->val;
         abList<int>::node* temp2 = list->head;
         while (temp2 != NULL) {
             cout << temp2->val << " ";
             temp2 = temp2->next;
         }
         cout << endl;
         temp = temp->next;
     }
 }



 void Dataset::printHead(int nRows, int nCols) {
     ///in dong dau

     abList<int>::node* temp2 = this->index->head;
     int fr = 0;
     while (temp2 && fr < nCols && fr < data->head->val->count) {
         if (temp2->val == -1) {
             cout << "label";
         }
         else {
             cout << " " << numtoaddres(temp2->val);
         }
         temp2 = temp2->next;
         fr++;
     }
     cout << endl;

     abList<List<int>*>::node* temp = this->data->head;
     List<int>* list = temp->val;

     /// in data
     int i = 0;
     while (i < nRows && i < data->count) {
         List<int>* list = temp->val;
         abList<int>::node* temp2 = list->head;
         for (int j = 0; j < nCols && j < data->head->val->count; j++) {
             cout << temp2->val << ((j == nCols - 1) ? "" : " ");
             temp2 = temp2->next;
         }
         ++i;
         (i >= 0 && i < data->count - 1 && i < nRows) ? cout << endl : cout << "";
         temp = temp->next;
     }
 }

 void Dataset::printTail(int nRows = 5, int nCols = 5) {
     abList<int>::node* temp = this->index->head;
     int i = index->count;
     while (temp) {
         if (i <= nCols) cout << numtoaddres(temp->val) << (temp->next ? " " : "");
         temp = temp->next;
         i--;
     }
     cout << endl;

     ////////////////////////////
     for (int j = nRows; j > 0; j--) {
         List<int>* temp = this->data->get(data->count - j > 0 ? data->count - j : 0);
         for (int k = nCols; k > 0; k--) {
             cout << temp->get(28 * 28 + 1 - k) << (k == 1 ? "" : " ");//28*28-k
         }
         (j == 1) ? cout << "" : cout << endl;
     }
 }


 void Dataset::getShape(int& nRows, int& nCols) const {
     nRows = data->count;
     nCols = this->data->head->val->count;
 }

 void Dataset::columns()const {
     abList<List<int>*>::node* temp = this->data->head;
     List<int>* list = temp->val;
     abList<int>::node* temp2 = list->head;
     while (temp2) {
         if (temp2->val == -1) {
             cout << "label";
         }
         else cout << " " << numtoaddres(temp2->val);
         temp2 = temp2->next;

     }
 }

 ///**************CHECK ten cot co trong qui dinh khong (dung cho drop columns)
 bool check_columName(string chuoi) {
     int x, y;
     stringstream ss(chuoi);
     char separator;
     ss >> x >> separator >> y;

     if (separator != 'x' || x < 1 || x > 28 || y < 1 || y > 28) {
         return false;
     }

     return true;
 }

 /// cur Hang
 int Dataset::getRowCount() const {
     return this->data->count;
 }

 /// cur Cot
 int Dataset::getColumnCount()const {
     if (this->data->head != nullptr) {
         return this->index->count;
     }
     return 0;
 }

 bool Dataset::drop(int axis, int index, std::string columns) {
     int curCols = getColumnCount() - 1;
     int curRows = getRowCount() - 1;

     if (axis != 0 && axis != 1) {
         return false;
     }
     if (axis == 0) {
         if (index >= getRowCount() || index < 0) {
             return false;
         }
         else {
             this->data->remove(index);
             this->data->count -= 1;
             return true;
         }
     }

     bool flag = false;
     if (axis == 1) {
         int num = addresstonum(columns);

         if (check_columName(columns)) {
             int index = 0;
             abList<int>::node* temp = this->index->head;
             while (temp) {
                 if (temp->val == num) {
                     flag = true;
                     break;
                 }
                 temp = temp->next;

                 ++index;
             }

             if (index < getColumnCount()) {
                 abList<List<int>*>::node* temp = this->data->head;
                 this->index->remove(index);
                 this->index->count--;
                 while (temp) {
                     temp->val->remove(index);
                     temp = temp->next;
                 }
             }
             else {
                 flag = false;
             }
         }
     } return flag;
 }