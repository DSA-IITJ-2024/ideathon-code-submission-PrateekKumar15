#include<iostream>
#include<string>
#include<bits/stdc++.h>
#include<vector>
#include<algorithm>

using namespace std;

// Structure to store student information
struct Student {
    int rollNo;
    string name;
    string hostel;
    string courseType;

    // Constructor
    Student(int rollNo, const string& name, const string& hostel, const string& courseType)
        : rollNo(rollNo), name(name), hostel(hostel), courseType(courseType) {}
};

// Node structure for AVL tree
struct Node {
    int key;
    Student* data;
    Node* left;
    Node* right;
    int height;

    // Constructor
    Node(int key, Student* data)
        : key(key), data(data), left(nullptr), right(nullptr), height(1) {}
};

// Class for AVL tree
class AVLTree {
private:
    Node* root;

    // Helper function to get height of a node
    int getHeight(Node* node) {
        if (node == nullptr)
            return 0;
        return node->height;
    }

    // Helper function to get balance factor of a node
    int getBalanceFactor(Node* node) {
        if (node == nullptr)
            return 0;
        return getHeight(node->left) - getHeight(node->right);
    }

    // Helper function to rotate right around a node
    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        // Perform rotation
        x->right = y;
        y->left = T2;

        // Update heights
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

        return x;
    }

    // Helper function to rotate left around a node
    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        // Perform rotation
        y->left = x;
        x->right = T2;

        // Update heights
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

        return y;
    }

    // Helper function to insert a node recursively
    Node* insertUtil(Node* node, int key, Student* data) {
        // Perform standard BST insertion
        if (node == nullptr)
            return new Node(key, data);

        if (key < node->key)
            node->left = insertUtil(node->left, key, data);
        else if (key > node->key)
            node->right = insertUtil(node->right, key, data);
        else // Duplicate keys not allowed
            return node;

        // Update height of this ancestor node
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));

        // Get the balance factor to check if node became unbalanced
        int balance = getBalanceFactor(node);

        // Left Left Case
        if (balance > 1 && key < node->left->key)
            return rotateRight(node);

        // Right Right Case
        if (balance < -1 && key > node->right->key)
            return rotateLeft(node);

        // Left Right Case
        if (balance > 1 && key > node->left->key) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        // Right Left Case
        if (balance < -1 && key < node->right->key) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        // Return the (unchanged) node pointer
        return node;
    }

    // Helper function to find the node with minimum key value in a subtree
    Node* findMin(Node* node) {
        while (node->left != nullptr)
            node = node->left;
        return node;
    }

    // Helper function to delete a node recursively
    Node* deleteUtil(Node* root, int key) {
        if (root == nullptr)
            return root;

        if (key < root->key)
            root->left = deleteUtil(root->left, key);
        else if (key > root->key)
            root->right = deleteUtil(root->right, key);
        else {
            if (root->left == nullptr || root->right == nullptr) {
                Node* temp = root->left ? root->left : root->right;
                if (temp == nullptr) {
                    temp = root;
                    root = nullptr;
                } else {
                    *root = *temp;
                }
                delete temp;
            } else {
                Node* temp = findMin(root->right);
                root->key = temp->key;
                root->data = temp->data;
                root->right = deleteUtil(root->right, temp->key);
            }
        }

        if (root == nullptr)
            return root;

        // Update height of the current node
        root->height = 1 + max(getHeight(root->left), getHeight(root->right));

        // Get the balance factor to check if the node became unbalanced
        int balance = getBalanceFactor(root);

        // Balancing the tree if needed

        // Left Left Case
        if (balance > 1 && getBalanceFactor(root->left) >= 0)
            return rotateRight(root);

        // Left Right Case
        if (balance > 1 && getBalanceFactor(root->left) < 0) {
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }

        // Right Right Case
        if (balance < -1 && getBalanceFactor(root->right) <= 0)
            return rotateLeft(root);

        // Right Left Case
        if (balance < -1 && getBalanceFactor(root->right) > 0) {
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }

        return root;
    }

    // Helper function to search for a node recursively
    Node* searchUtil(Node* root, int key) {
        if (root == nullptr || root->key == key)
            return root;

        if (key < root->key)
            return searchUtil(root->left, key);
        else
            return searchUtil(root->right, key);
    }

public:
    // Constructor
    AVLTree() : root(nullptr) {}

    // Function to insert a student into AVL tree
    void insert(int key, Student* data) {
        root = insertUtil(root, key, data);
    }

    // Function to search for a student in AVL tree
    Student* search(int key) {
        Node* result = searchUtil(root, key);
        return (result != nullptr) ? result->data : nullptr;
    }

    // Function to delete a student from AVL tree
    void remove(int key) {
        root = deleteUtil(root, key);
    }
};

int main() {
    //reading starts
    string file_path = "students.txt";
    //file reading starts
    ifstream file;
    file.open(file_path);
    string line;
    
    vector<vector<string>> row;
    while (getline(file, line)) {
        vector<string> str;
        line = line + ',';
        string word = "";
        for(int i  = 0;i<line.size();i++){
            if(line[i] == '['){
                string s = "";
                while(line[i] != ']'){
                  s = s + line[i];
                  i++;
                }
                s = s + line[i];
                str.push_back(s);
                continue;
            }
            if(line[i] == ','){
                str.push_back(word);
                word = "";
            }
            else{
              word = word + line[i];
            }
        }
        row.push_back(str);
    }

  
    file.close();

    
   vector<string> st;
   bool flagChecker = true;
   //processing the file here
   for(int i  = 0;i<row.size();i++){
        for(int j = 2;j<row[0].size();j++){
            
            if(row[i][j][0] == '['){
               string s = row[i][j];
               s.erase(s.begin());
               s.erase(s.end() - 1);
               s = s + ',';
               string word = "";
               for(int k = 0;k<s.size();k++){
                  if(s[k] == ','){
                    if(find(st.begin(),st.end(),word) == st.end()){
                     st.push_back(word);
                     word = "";
                    }
                  }
                  else{
                    word = word + s[k];
                  }
               }
            }
            else{
                if(find(st.begin(),st.end(),row[i][j]) == st.end()){
                     st.push_back(row[i][j]);
                    }
                
            }
        }
    }

    for(auto it = st.begin();it != st.end();it++){
        if(*it == "\n" || *it == "" || *it == " ")
         st.erase(it);
    }





    AVLTree studentDB;

   for(auto it : row){
    Student* student = new Student(stoi(it[0]), it[1], it[2], it[3]);
    studentDB.insert(student->rollNo, student);
    
   }


















    // Creating an AVL tree for student database
    






    // Inserting sample student data
    // Student* student1 = new Student(101, "Alice", "Hostel A", "Engineering");
    // Student* student2 = new Student(102, "Bob", "Hostel B", "Science");
    // Student* student3 = new Student(103, "Charlie", "Hostel C", "Arts");

    // studentDB.insert(student1->rollNo, student1);
    // studentDB.insert(student2->rollNo, student2);
    // studentDB.insert(student3->rollNo, student3);

    // Searching for a student
    int rollNoToSearch = 44;
    Student* foundStudent = studentDB.search(rollNoToSearch);
    if (foundStudent != nullptr) {
        cout << "Student found: " << foundStudent->name << endl;
    } else {
        cout << "Student with roll number " << rollNoToSearch << " not found." << endl;
    }

    // Deleting a student
    int rollNoToDelete = 102;
    studentDB.remove(rollNoToDelete);

    // Searching again after deletion
    foundStudent = studentDB.search(rollNoToDelete);
    if (foundStudent != nullptr) {
        cout << "Student found: " << foundStudent->name << endl;
    } else {
        cout << "Student with roll number " << rollNoToDelete << " not found." << endl;
    }

    return 0;
}
