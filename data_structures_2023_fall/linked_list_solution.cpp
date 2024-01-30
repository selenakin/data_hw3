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
#include <time.h>

using namespace std; 


//Node class is actually a Employee class that is represented by a "node".

class Node
{
    private:
        int id;
        int department;
        int salary;
        Node *next;
    public:
        Node();
        ~Node();
        void set_salary(int);    
        void set_department(int);
        void set_id(int);
        int get_id();
        int get_salary();
        int get_department();
        void set_next(Node *);
        Node *get_next();
};

Node::Node()
{
    id = 0;
    department = 0;
    salary = 0;
    next = NULL;
}

Node::~Node()
{
 
}

void Node::set_salary(int salary)
{
    this->salary = salary;
}

int Node::get_salary()
{
    return salary;
}

void Node::set_department(int department)
{
    this->department = department;
}

int Node::get_department()
{
    return department;
}

void Node::set_id(int id)
{
    this->id = id;
}

int Node::get_id()
{
    return id;
}

void Node::set_next(Node *next)
{
    this->next = next;
}

Node *Node::get_next()
{
    return next;
}

class LinkedList
{
    private:
        Node *tail;
        Node *head;
    public:
        
        LinkedList();
        ~LinkedList();
        Node* find_previous(int);
        Node* get_head();
        Node* get_tail();
        void add_node(Node *);
        void delete_node(int);
        void update_node(int, int, int);
        void print_list();
        bool is_empty();
        int get_tail_id();

};

LinkedList::LinkedList()
{
    head = NULL;
    tail = NULL;
}

LinkedList::~LinkedList()
{
    
}

Node* LinkedList::find_previous(int id)
{
    Node *current = head;
    Node *previous = NULL;
    while (current != NULL)
    {
        if (current->get_id() == id)
        {
            return previous;
        }
        previous = current;
        current = current->get_next();
    }
    return NULL;
}

Node* LinkedList::get_head()
{
    return head;
}

void LinkedList::add_node(Node *new_node)
{
    if (head == NULL)
    {
        head = new_node;
        tail = new_node;
    }
    else
    {
        tail->set_next(new_node);
        tail = new_node;
    }
}

void LinkedList::delete_node(int id)
{
    Node *previous = find_previous(id);
    if (previous == NULL)
    {
        head = head->get_next();
    }
    else
    {
        Node *current = previous->get_next();
        previous->set_next(current->get_next());
        delete current;
    }
}

void LinkedList::update_node(int id, int salary, int department)
{
    Node *previous = find_previous(id);
    if (previous == NULL)
    {
        head->set_salary(salary);
        head->set_department(department);
    }
    else
    {
        Node *current = previous->get_next();
        current->set_salary(salary);
        current->set_department(department);
    }
}

void LinkedList::print_list()
{
    Node *current = head;
    while (current != NULL)
    {
        cout << current->get_id() << " " << current->get_salary() << " " << current->get_department() << endl;
        current = current->get_next();
    }
}

int LinkedList::get_tail_id()
{
    int id = tail->get_id();
    return id;
}

bool LinkedList::is_empty()
{
    if (head == NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void delete_employee(LinkedList* employeeList, int id){
    if (employeeList->is_empty()){
        cout << "ERROR: There is no Employee";
        return;
    }

    bool found = false;
    Node* current = employeeList->get_head();
    while (current != NULL){
        if (current->get_id() == id){
            found = true;
            break;
        }
        current = current->get_next();
    }
    if (!found){
        cout << "ERROR: An invalid ID to delete";
        return;
    }
    employeeList->delete_node(id);
}

void add_employee(LinkedList* employeeList, int id, int salary, int department){
    Node* new_employee = new Node();
    new_employee->set_id(id);
    new_employee->set_salary(salary);
    new_employee->set_department(department);
    employeeList->add_node(new_employee);
}

void update_employee(LinkedList* employeeList, int id, int salary, int department){
    
    bool found = false;
    Node* current = employeeList->get_head();
    while (current != NULL){
        if (current->get_id() == id){
            found = true;
            break;
        }
        current = current->get_next();
    }
    if (!found){
        cout << "ERROR: An invalid ID to update";
        return;
    }

    employeeList->update_node(id, salary, department);
}

void newcsv(LinkedList* employeeList){
    ofstream out_file;
    out_file.open("linked_list_solution.csv");
    out_file << "Employee_ID;Salary;Department" << endl;
    Node* current = employeeList->get_head();
    while (current != NULL){
        out_file << current->get_id() << ";" << current->get_salary() << ";" << current->get_department() << endl;
        current = current->get_next();
    }
    out_file.close();
}

int main (int argc, char **argv){

    LinkedList* employeeList = new LinkedList();
    ifstream first_file(argv[1]);
    if (!first_file.is_open()){
        cout << "Error: file open failed." << endl;
        exit(1);
    }
    string first_line;
    int i = -1;
    while( getline(first_file, first_line)){
        if (i == -1){
            i++;
            continue;
        }
        Node* new_employee = new Node();
        int id = stoi(first_line.substr(0, first_line.find(";")));
        int salary = stoi(first_line.substr(first_line.find(";")+1, first_line.find_last_of(";")-first_line.find(";")-1));
        int department = stoi(first_line.substr(first_line.find_last_of(";")+1, first_line.length()-first_line.find_last_of(";")-1));
        new_employee->set_id(id);
        new_employee->set_salary(salary);
        new_employee->set_department(department);
        employeeList->add_node(new_employee);
    }
    first_file.close();
    // employeeList->print_list();

    ifstream file(argv[2]);
    if (!file.is_open()){
         cout << "Error: file open failed." <<  endl;
        exit(1);
    }
     string line;
    while ( getline(file, line)){

    size_t pos1 = line.find(";");
    size_t pos2 = line.find(";", pos1 + 1);
    string command = line.substr(0, pos1);
    int id, salary, department;

        if ( line.substr(0, line.find(";")) == "ADD"){
            // clock_t start = clock();
            id =  employeeList->is_empty() ? 1 : employeeList->get_tail_id() + 1;
            salary = stoi(line.substr(pos1 + 1, pos2 - pos1 - 1));
            department = stoi(line.substr(line.find_last_of(";") + 1, line.length() - line.find_last_of(";") - 1));
            add_employee(employeeList, id, salary, department);
            // clock_t end = clock();
            // double time = (end - start)*1000 / CLOCKS_PER_SEC; 
            // cout << "ADD linked list solution " << time << " miliseconds." << endl;
        }
        if ( line.substr(0, line.find(";")) == "UPDATE"){
            // clock_t start = clock();
            id = stoi(line.substr(pos1 + 1, pos2 - pos1 - 1));
            salary = stoi(line.substr(pos2 + 1));
            department = stoi(line.substr(line.find_last_of(";") + 1, line.length() - line.find_last_of(";") - 1));
            update_employee(employeeList, id, salary, department);
            // clock_t end = clock();
            // double time = (end - start)*1000 / CLOCKS_PER_SEC; 
            // cout<<"UPDATE linked list solution "<<time<<" miliseconds."<<endl;
        }
        if ( line.substr(0, line.find(";")) == "DELETE"){
            // clock_t start = clock();
            id = stoi(line.substr(pos1 + 1));
            delete_employee(employeeList, id);
            // clock_t end = clock();
            // double time = (end - start)*1000 / CLOCKS_PER_SEC;
            // cout<<"DELETE linked list solution "<<time<<" miliseconds."<<endl;
        }

    }
    
    file.close();

    newcsv(employeeList);

    return 0;

}

// I get varying result with calico500.txt files. I think it is because of the file size.
// ADD linked list solution 0 miliseconds.
// ADD linked list solution 0 miliseconds.
// UPDATE linked list solution 0 miliseconds.
// UPDATE linked list solution 0 miliseconds.
// ADD linked list solution 0 miliseconds.
// DELETE linked list solution 0 miliseconds.
// DELETE linked list solution 0 miliseconds.