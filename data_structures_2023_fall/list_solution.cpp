/* @Author
    StudentName: Nurselen Akın
    StudentID: 150200087
    Date: 10.11.2023
*/

//FYI: Results of the time measurements are at the end of the file.

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <list>
#include <time.h>

 using namespace std;  

class Employee{
    private:
        int id;
        int department;
        int salary;
    public:
        Employee();
        ~Employee();
        void set_salary(int);    
        void set_department(int);
        void set_id(int);
        int get_id();
        int get_salary();
        int get_department();
};

Employee::Employee(){
    id = 0;
    department = 0;
    salary = 0;
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


void add_employee(list<Employee> &employees, int id, int salary, int department){
    Employee employee;
    employee.set_id(id);
    employee.set_salary(salary);
    employee.set_department(department);
    employees.push_back(employee);
}


void update_employee(list<Employee> &employees, int id, int salary, int department){
   
    bool found = false;
    for (list<Employee>::iterator it = employees.begin(); it != employees.end(); it++){
        if (it->get_id() == id){
            found = true;
            break;
        }
    }
    if (!found){
        cout << "ERROR: An invalid ID to update";
        return;
    }

    for (list<Employee>::iterator it = employees.begin(); it != employees.end(); it++){
        if (it->get_id() == id){
            it->set_salary(salary);
            it->set_department(department);
            break;
        }
    }
}

void delete_employee(list<Employee> &employees, int id){
    
    if (employees.empty()){
        cout << "ERROR: There is no Employee";
        return;
    }
   
    bool found = false;
    for (list<Employee>::iterator it = employees.begin(); it != employees.end(); it++){
        if (it->get_id() == id){
            found = true;
            break;
        }
    }
    if (!found){
        cout << "ERROR: An invalid ID to delete";
        return;
    }
    for (list<Employee>::iterator it = employees.begin(); it != employees.end(); it++){
        if (it->get_id() == id){
            employees.erase(it);
            break;
        }
    }
}

void newcsv(list<Employee> &employees){
    ofstream file;
    file.open("list_solution.csv");
    file << "Employee_ID;Salary;Department" << endl;
    for (list<Employee>::iterator it = employees.begin(); it != employees.end(); it++){
        file << it->get_id() << ";" << it->get_salary() << ";" << it->get_department() << endl;
    }
    file.close();
}

int main(int argc, char **argv){
    list<Employee> employees;
    Employee employee;

    ifstream first_file(argv[1]);
    string first_line;
     getline(first_file, first_line);
        while( getline(first_file, first_line)){
        int id;
        int salary;
        int department;
        sscanf(first_line.c_str(), "%d;%d;%d", &id, &salary, &department);
        employee.set_id(id);
        employee.set_salary(salary);
        employee.set_department(department);
        employees.push_back(employee);
    }
    first_file.close();


    // for (list<Employee>::iterator it = employees.begin(); it != employees.end(); it++){
    //     cout << it->get_id() << " " << it->get_salary() << " " << it->get_department() << endl;
    // }

   
    ifstream file(argv[2]);
    string line;
    while(getline(file, line)){

    size_t pos1 = line.find(";");
    size_t pos2 = line.find(";", pos1 + 1);
    string command = line.substr(0, pos1);
    int id, salary, department;

        if (line.substr(0, line.find(";")) == "ADD"){
            // clock_t start = clock();
            id = employees.empty() ? 1 : employees.back().get_id() + 1;
            salary = stoi(line.substr(pos1 + 1, pos2 - pos1 - 1));
            department = stoi(line.substr(line.find_last_of(";") + 1, line.length() - line.find_last_of(";") - 1));
            add_employee(employees, id, salary, department);
            // clock_t end = clock();
            // double time = (end - start)*1000 / CLOCKS_PER_SEC;
            // cout << "ADD list solution " << time << " miliseconds." << endl;
        }
        else if (line.substr(0, line.find(";")) == "UPDATE"){
            // clock_t start = clock();
            id = stoi(line.substr(pos1 + 1, pos2 - pos1 - 1));
            salary = stoi(line.substr(pos2 + 1));
            department = stoi(line.substr(line.find_last_of(";") + 1, line.length() - line.find_last_of(";") - 1));
            update_employee(employees, id, salary, department);
            // clock_t end = clock();
            // double time = (end - start)*1000 / CLOCKS_PER_SEC;
            // cout << "UPDATE list solution " << time << " miliseconds." << endl;
        }
        else if (line.substr(0, line.find(";")) == "DELETE"){
            // clock_t start = clock();    
            id = stoi(line.substr(pos1 + 1));            
            delete_employee(employees, id);
            // clock_t end = clock();
            // double time = (end - start)*1000 / CLOCKS_PER_SEC;
            // cout << "DELETE list solution " << time << " miliseconds." << endl;
        }
    }

     newcsv(employees);

    return 0;
}

// ADD list solution 0 miliseconds.
// ADD list solution 0 miliseconds.
// UPDATE list solution 0 miliseconds.
// UPDATE list solution 0 miliseconds.
// ADD list solution 0 miliseconds.
// DELETE list solution 0 miliseconds.
// DELETE list solution 0 miliseconds.