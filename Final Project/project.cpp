#include<iostream>
#include<string>
#include<bits/stdc++.h>
#include<vector>
#include<algorithm>

using namespace std;

class Authentication
{
    string userName;
    string userPassword;
    int loginAttempt = 0;

public:
    bool login_status()
    {
        while (loginAttempt < 5)
        {
            cout << "Please enter your user name : ";
            cin >> userName;
            cout << "Please enter your password : ";
            cin >> userPassword;

            if (userName == "Yogesh" && userPassword == "b22ch044")
            {
                cout << "Welcome Yogesh!\n";
                cout << "You are now logged in!\n\n";
                return true;
            }
            else if (userName == "Prateek" && userPassword == "b22es024")
            {
                cout << "Welcome Prateek\n";
                cout << "You are now logged in!\n\n";
                return true;
            }
            else if (userName == "Shatakshi" && userPassword == "b22me060")
            {
                cout << "Welcome Shatakshi!\n";
                cout << "You are now logged in!\n\n";
                return true;
            }
            else if (userName == "IITJ" && userPassword == "IITJ"){
                cout << "Welcome\n";
                cout << "You are now logged in!\n\n";
                return true;
            }
            else
            {
                cout << "Invalid login attempt. Please try again.\n\n"
                     << '\n';
                loginAttempt++;
            }
        }
        cout << "Too many login attempts! The program will now terminate.";
        return false;
    }
};
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

// Node structure for BST
struct Node {
    int key;
    Student* data;
    Node* left;
    Node* right;

    // Constructor
    Node(int key, Student* data)
        : key(key), data(data), left(nullptr), right(nullptr) {}
};

// Class for binary search tree
class BST {
private:
    Node* root;

    // Helper function to recursively insert a node
    Node* insertUtil(Node* root, int key, Student* data) {
        if (root == nullptr)
            return new Node(key, data);
        
        if (key < root->key)
            root->left = insertUtil(root->left, key, data);
        else if (key > root->key)
            root->right = insertUtil(root->right, key, data);
        
        return root;
    }

    // Helper function to recursively search for a node
    Node* searchUtil(Node* root, int key) {
        if (root == nullptr || root->key == key)
            return root;
        
        if (key < root->key)
            return searchUtil(root->left, key);
        else
            return searchUtil(root->right, key);
    }

    // Helper function to find minimum node in a subtree
    Node* findMin(Node* node) {
        while (node->left != nullptr)
            node = node->left;
        return node;
    }

    // Helper function to recursively delete a node
    Node* deleteUtil(Node* root, int key) {
        if (root == nullptr)
            return root;
        
        if (key < root->key)
            root->left = deleteUtil(root->left, key);
        else if (key > root->key)
            root->right = deleteUtil(root->right, key);
        else {
            if (root->left == nullptr) {
                Node* temp = root->right;
                delete root;
                return temp;
            }
            else if (root->right == nullptr) {
                Node* temp = root->left;
                delete root;
                return temp;
            }
            Node* temp = findMin(root->right);
            root->key = temp->key;
            root->data = temp->data;
            root->right = deleteUtil(root->right, temp->key);
        }
        return root;
    }

public:
    // Constructor
    BST() : root(nullptr) {}

    // Function to insert a student into BST
    void insert(int key, Student* data) {
        root = insertUtil(root, key, data);
    }

    // Function to search for a student in BST
    Student* search(int key) {
        Node* result = searchUtil(root, key);
        return (result != nullptr) ? result->data : nullptr;
    }

    // Function to delete a student from BST
    void remove(int key) {
        root = deleteUtil(root, key);
    }
};

void deleteLineByRollNo(const string& filename, int rollNoToDelete) {
    ifstream inputFile(filename);
    ofstream outputFile("temp.txt");
    string line;
    bool found = false;

    // Copy all lines except the one with the matching roll number to a temporary file
    while (getline(inputFile, line)) {
        stringstream ss(line);
        string rollNoStr;
        getline(ss, rollNoStr, ',');
        int rollNo = stoi(rollNoStr);

        if (rollNo != rollNoToDelete) {
            outputFile << line << endl;
        } else {
            found = true;
        }
    }

    // Close files
    inputFile.close();
    outputFile.close();

    // Rename the temporary file to the original filename
    if (found) {
        remove(filename.c_str());
        rename("temp.txt", filename.c_str());
        cout << "Roll number " << rollNoToDelete << " deleted successfully from " << filename << endl;
    } else {
        remove("temp.txt");
        cout << "Roll number " << rollNoToDelete << " not found in " << filename << endl;
    }
}

void addDataToTxt(const string& filename, int rollNo, const string& name, const string& hostel, const string& course) {
    ofstream outputFile(filename, ios::app); // Open file in append mode
    if (outputFile.is_open()) {
        outputFile << rollNo << "," << name << "," << hostel << "," << course << endl;
        outputFile.close();
        cout << "Data added successfully to " << filename << endl;
    } else {
        cerr << "Unable to open file " << filename << " for writing!" << endl;
    }
}

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





    BST studentDB;

   for(auto it : row){
    Student* student = new Student(stoi(it[0]), it[1], it[2], it[3]);
    studentDB.insert(student->rollNo, student);
    
   }

    Authentication auth;
    bool isLoggedIn = false;

    char choice;
    int rollNoToSearch;


    while (1)
    {
        if (isLoggedIn == true or auth.login_status() == true)
        {
            isLoggedIn = true;
            cout << "\t\t== STUDENT DATABASE MANAGEMENT SYSTEM ==";
            cout << "\n\n                                          ";
            cout << "\n \t\t\t 0. Search Record";
            cout << "\n \t\t\t 1. Add    Records";
            cout << "\n \t\t\t 2. Delete Records";
            cout << "\n \t\t\t 3. Exit   Program";
            cout << "\n\n";
            cout << "\t\t\t Select Your Choice :=> ";

            cin >> choice;
            switch (choice)
            {
            case '0':
            {

                cout << "Enter Roll number to search: ";
                int r;
                cin >> r;

                Student* foundStudent = studentDB.search(r);
                if (foundStudent != nullptr) {
                    cout << "Student found: " << endl;
                    cout << "Name: " << foundStudent->name << endl;
                    cout << "ROll No.: " << foundStudent->rollNo << endl;
                    cout << "Hostel: " << foundStudent->hostel<< endl;
                    cout << "Course: " << foundStudent->courseType << endl;

                } else {
                    cout << "Student with this roll number not found." << endl;
                }
            }
            break;

            case '1':
            {
                int rollNo;
                string name, hostel, course;

                // Input roll number, name, hostel, and course from the user
                cout << "Enter Roll No.: ";
                cin >> rollNo;
                cin.ignore(); // Ignore newline character left in the input buffer
                cout << "Enter Name: ";
                getline(cin, name);
                cout << "Enter Hostel: ";
                getline(cin, hostel);
                cout << "Enter Course: ";
                getline(cin, course);

                addDataToTxt(file_path, rollNo, name, hostel, course);

                Student* student = new Student((rollNo), name, hostel, course);
                studentDB.insert(rollNo, student);

            }
            break;

            case '2':
            {
                    cout << "Enter Roll number to delete: ";
                    int r;
                    cin >> r;
                    deleteLineByRollNo(file_path, r);

                    studentDB.remove(r);

            }
            break;

            case '3':
            {
                exit(0);

            }
            break;
            }
        }
    }
    return 0;
}
