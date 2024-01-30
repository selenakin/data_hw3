/* @Author
    StudentName: Nurselen Akın
    StudentID: 150200087
    Date: 29.10.2023
*/

//FYI: Results of the time measurements are at the end of the file.


#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>


using namespace std;

class Employee{
    private:
        int id;
        int salary;
        int department;
    public:
        Employee(int i, int s, int d);
        ~Employee();
        int get_id();
        int get_salary();
        int get_department();
        void set_id(int i);
        void set_salary(int s);
        void set_department(int d);
        void print();
};

Employee::Employee(int i, int s, int d){
    id = i;
    salary = s;
    department = d;

}

Employee::~Employee(){
}

void Employee::set_salary(int salary){
    this->salary = salary;
}

int Employee::get_salary(){
    return salary;
}

void Employee::set_department(int department){
    this->department = department;
}

int Employee::get_department(){
    return department;
}

void Employee::set_id(int id){
    this->id = id;
}

int Employee::get_id(){
    return id;
}

void Employee::print(){
    cout << id << ";" << salary << ";" << department << endl;
}

class Node{
        Employee *employee;
        Node *left;
        Node *right;
        Node *parent;
    public:
        Node();
        ~Node();
        Node(Employee *employee);
        void set_employee(Employee *employee);
        Employee *get_employee();
        void set_left(Node *left);
        void set_right(Node *right);
        void set_parent(Node *parent);
        Node *get_left();
        Node *get_right();
        Node *get_parent();

};

Node::Node(){
    employee = NULL;
    left = NULL;
    right = NULL;
    parent = NULL;
}

Node::~Node(){
    delete employee;
}   

Node::Node(Employee *employee){
    this->employee = employee;
    left = NULL;
    right = NULL;
}

void Node::set_employee(Employee *employee){
    this->employee = employee;
}

Employee *Node::get_employee(){
    return employee;
}

void Node::set_left(Node *left){
    this->left = left;
}

void Node::set_right(Node *right){
    this->right = right;
}

Node *Node::get_left(){
    return left;
}

Node *Node::get_right(){
    return right;
}

Node *Node::get_parent(){
    return parent;
}

void Node::set_parent(Node *parent){
    this->parent = parent;
}

class BinaryTree{

    private:
        Node* root;
        Node* getMaximumNode(Node* node);
        int getHeightRecursive(Node* node);
    public:
        BinaryTree();
        ~BinaryTree();
        void insert(Employee* employee);
        void remove(int id);
        Employee* search(int id);
        int getHeight();
        void printToFile(string filename);
        void printToConsole();
        int getMaximumId();
};

BinaryTree::BinaryTree(){
    this-> root = NULL;
}

BinaryTree::~BinaryTree(){
    Node* current = root;

    while (current != nullptr) {
        if (current->get_left() == nullptr) {
            delete current;
            current = current->get_right();
        } else {
            Node* predecessor = current->get_left();
            while (predecessor->get_right() != nullptr && predecessor->get_right() != current) {
                predecessor = predecessor->get_right();
            }

            if (predecessor->get_right() == nullptr) {
                predecessor->set_right(current);
                current = current->get_left();
            } else {
                predecessor->set_right(nullptr);
                delete current;
                current = current->get_right();
            }
        }
    }
}



void BinaryTree::insert(Employee* employee) {
    Node* new_node = new Node(employee);

    if (this->root == nullptr) {
        this->root = new_node;
        return;
    }

    Node* current = this->root;
    Node* parent = nullptr;

    while (current != nullptr) {
        parent = current;
        if (employee->get_id() <= current->get_employee()->get_id()) {
            current = current->get_left();
        } else {
            current = current->get_right();
        }
    }

    new_node->set_parent(parent);
    if (employee->get_id() <= parent->get_employee()->get_id()) {
        parent->set_left(new_node);
    } else {
        parent->set_right(new_node);
    }
}

Employee* BinaryTree::search(int id) {
    Node* current = root;
    while (current != nullptr) {
        if (id == current->get_employee()->get_id()) {
            return current->get_employee();
        } else if (id < current->get_employee()->get_id()) {
            current = current->get_left();
        } else {
            current = current->get_right();
        }
    }
    return nullptr; 
}

void BinaryTree::remove(int id) {
    Node* parent = nullptr;
    Node* current = root;
    
    while (current != nullptr && current->get_employee()->get_id() != id) {
        parent = current;
        if (id < current->get_employee()->get_id()) {
            current = current->get_left();
        } else {
            current = current->get_right();
        }
    }
    
    if (current == nullptr) return;
    
    // Node with one child or no child
    if (current->get_left() == nullptr || current->get_right() == nullptr) {
        Node* newChild = (current->get_left() == nullptr) ? current->get_right() : current->get_left();
        
        if (parent == nullptr) {
            root = newChild; 
        } else {
            if (current == parent->get_left()) {
                parent->set_left(newChild);
            } else {
                parent->set_right(newChild);
            }
        }
        delete current; 
    } else {
        // Node with two children
        Node* successorParent = current;
        Node* successor = current->get_right();
        
        while (successor->get_left() != nullptr) {
            successorParent = successor;
            successor = successor->get_left();
        }
        
        *current->get_employee() = *successor->get_employee();

        if (successorParent != current) {
            successorParent->set_left(successor->get_right());
        } else {
            successorParent->set_right(successor->get_right());
        }
        delete successor;
    }
}

Node* BinaryTree::getMaximumNode(Node* node) {
    Node* current = node;
    while (current && current->get_right() != nullptr) {
        current = current->get_right();
    }
    return current;
}

int BinaryTree::getMaximumId() {
    Node* max = getMaximumNode(this->root);
    if (max != nullptr) {
        return max->get_employee()->get_id();
    }
    return -1;
}

int BinaryTree::getHeight(){
    return getHeightRecursive(this->root);
}

int BinaryTree::getHeightRecursive(Node* node) {
    if (node == NULL) {
        return 0;
    } else {
        int leftHeight = getHeightRecursive(node->get_left());
        int rightHeight = getHeightRecursive(node->get_right());
        return max(leftHeight, rightHeight) + 1;
    }
}

void BinaryTree::printToConsole() {
    Node* current = root;

    while (current != nullptr) {
        if (current->get_left() == nullptr) {
            std::cout << current->get_employee()->get_id() << ";"
                      << current->get_employee()->get_salary() << ";"
                      << current->get_employee()->get_department() << std::endl;
            current = current->get_right();
        } else {
            Node* predecessor = current->get_left();
            while (predecessor->get_right() != nullptr && predecessor->get_right() != current) {
                predecessor = predecessor->get_right();
            }

            if (predecessor->get_right() == nullptr) {
                std::cout << current->get_employee()->get_id() << ";"
                          << current->get_employee()->get_salary() << ";"
                          << current->get_employee()->get_department() << std::endl;
                predecessor->set_right(current);
                current = current->get_left();
            } else {
                predecessor->set_right(nullptr);
                current = current->get_right();
            }
        }
    }
}

void BinaryTree::printToFile(string filename) {
    ofstream file(filename, ios::app);
    // file << "Employee_ID;Salary;Department" << endl;

    Node *current = root, *pre;
    while (current != nullptr) {
        if (current->get_left() == nullptr) {
            file << current->get_employee()->get_id() << ";"
                 << current->get_employee()->get_salary() << ";"
                 << current->get_employee()->get_department() << "\n";
            current = current->get_right();
        } else {
            // Find the inorder predecessor of current
            pre = current->get_left();
            while (pre->get_right() != nullptr && pre->get_right() != current) {
                pre = pre->get_right();
            }

            // Make current the right child of its inorder predecessor
            if (pre->get_right() == nullptr) {
                pre->set_right(current);
                current = current->get_left();
            } else {
                // Revert the changes made in the 'if' part to restore the original tree
                // i.e., fix the right child of predecessor
                pre->set_right(nullptr);
                file << current->get_employee()->get_id() << ";"
                     << current->get_employee()->get_salary() << ";"
                     << current->get_employee()->get_department() << "\n";
                current = current->get_right();
            }
        }
    }
    file.close();
}


class Forest{
    private:
        vector<BinaryTree*> trees;
        static const int RANGE = 5000;
    public:
        Forest(int size);
        ~Forest();
        void insert(Employee* employee);
        void remove(int id);
        Employee* search(int id);
        void printToFile(string filename);
        int getMaximumId();
};

Forest::Forest(int size){
    for(int i = 0; i < size; i++){
        BinaryTree* bt = new BinaryTree();
        trees.push_back(bt);
    }
}

Forest::~Forest(){
    for(unsigned int i = 0; i < trees.size(); i++){
        delete trees[i];
    }
}

void Forest::insert(Employee* employee) {
    unsigned int index = employee->get_id() / RANGE;
    while (index >= trees.size()) {
        trees.push_back(new BinaryTree());
    }
    trees[index]->insert(employee);
}

Employee* Forest::search(int id) {
    unsigned int index = id / RANGE;
    if (index < trees.size()) {
        return trees[index]->search(id);
    }
    return nullptr;
}

void Forest::remove(int id) {
    unsigned int index = id / RANGE;
    if (index < trees.size()) {
        trees[index]->remove(id);
    }
}

void Forest::printToFile(string filename) {
    ofstream file(filename);
    file << "Employee_ID;Salary;Department" << endl;
    for (auto tree : trees) {
        if (tree != nullptr) {
            tree->printToFile(filename); // Assuming BinaryTree::printToFile appends to the file
        }
    }
    file.close();
}


int Forest::getMaximumId() {
    int max = -1;
    for (BinaryTree* tree : trees) {
        if (tree != nullptr) {
            int treeMax = tree->getMaximumId();
            if (treeMax > max) {
                max = treeMax;
            }
        }
    }
    return max;
}   

int main(int argc, char** argv){
    int i = -1;
    ifstream first_file;
    first_file.open(argv[1]);
    string first_line;

        
    // BinaryTree* bt = new BinaryTree();

    Forest* bt = new Forest(5000);

    while(getline(first_file, first_line)){

        if(i == -1){
            i++;
            continue;
        }
        int id, salary, department;
        id = stoi(first_line.substr(0, first_line.find(";")));
        salary = stoi(first_line.substr(first_line.find(";") + 1, first_line.find_last_of(";") - first_line.find(";") - 1));
        department = stoi(first_line.substr(first_line.find_last_of(";") + 1, first_line.length() - first_line.find_last_of(";") - 1));
        Employee *employee = new Employee(id, salary, department);  
            
        bt->insert(employee);
        i++;
        

    }
     
    first_file.close();


    ifstream file(argv[2]);
    string line;
    int line_number = 0;    
    // double add_time = 0;
    // double update_time = 0;
    // double delete_time = 0;
    // int add_count = 0; 
    // int update_count = 0;
    // int delete_count = 0;
    while (getline(file, line)) {
    line_number++;
    size_t pos1 = line.find(";");
    size_t pos2 = line.find(";", pos1 + 1);
    string command = line.substr(0, pos1);
        
        // if (line == "PRINT") {
        //     cout<< "P\n"; 
        //     bt->printToConsole();
        // } else if (line == "HEIGHT") {
        //      cout<< "H "<< bt->getHeight()<<"\n";
        // } 
            if (command == "ADD") {
            // add_count++;
            // clock_t add_start = clock();    
            int id = bt->getMaximumId() + 1;
            int salary = stoi(line.substr(pos1 + 1, pos2 - pos1 - 1));
            int department = stoi(line.substr(pos2 + 1));
            Employee* employee = new Employee(id, salary, department);
            bt->insert(employee);
            // clock_t add_end = clock();
            // add_time += (add_end - add_start)*1000 / CLOCKS_PER_SEC;
        } 
        else if (command == "UPDATE") {
            // update_count++;
            // clock_t update_start = clock();
            int id = stoi(line.substr(pos1 + 1, pos2 - pos1 - 1));
            int salary = stoi(line.substr(pos2 + 1));
            int department = stoi(line.substr(line.find_last_of(";") + 1, line.length() - line.find_last_of(";") - 1));
            Employee* employee = bt->search(id);
            if (employee != NULL) {
                employee->set_salary(salary);
                employee->set_department(department);
            }
            else{
                cout << "ERROR: An invalid ID to update" << "\n";
            }
            // clock_t update_end = clock();
            // update_time += (update_end - update_start)*1000 / CLOCKS_PER_SEC;
        }
         else if (command == "DELETE") {
            // delete_count++;
            // clock_t delete_start = clock();
            int id = stoi(line.substr(pos1 + 1));
            if(bt->search(id) == NULL){
                cout << "ERROR: An invalid ID to delete" << "\n";
            }
            bt->remove(id);
            // clock_t delete_end = clock();
            // delete_time += (delete_end - delete_start)*1000 / CLOCKS_PER_SEC;
        }
    
    }

    
    file.close();

    // cout << "Average time for ADD operation: " << add_time / add_count << " ms" << endl;
    // cout << "Average time for UPDATE operation: " << update_time / update_count << " ms" << endl;
    // cout << "Average time for DELETE operation: " << delete_time / delete_count << " ms" << endl;

    bt->printToFile("output.csv");  
    // bt->printToConsole();
    
    delete bt;
    return 0;
}

// Results of the time measurements for hybrid (ordered dataset):
// Average time for ADD operation: 0.845441 ms
// Average time for UPDATE operation: 0.0235399 ms
// Average time for DELETE operation: 0.0782055 ms

// Results of the time measurements for hybrid (shuffled dataset):
// Average time for ADD operation: 0.112108 ms
// Average time for UPDATE operation: 0.0056615 ms
// Average time for DELETE operation: 0.0054562 ms