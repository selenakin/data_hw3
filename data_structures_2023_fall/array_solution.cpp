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

class Employee
{
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

Employee::Employee()
{
    id = 0;
    department = 0;
    salary = 0;
}

Employee::~Employee()
{
    // do nothing
}

void Employee::set_salary(int salary)
{
    this->salary = salary;
}

int Employee::get_salary()
{
    return salary;
}

void Employee::set_department(int department)
{
    this->department = department;
}

int Employee::get_department()
{
    return department;
}

void Employee::set_id(int id)
{
    this->id = id;
}

int Employee::get_id()
{
    return id;
}
    
void empty(Employee employees[])
{
    int i = -1;
    ifstream file;
    file.open("hw1.csv");
    // if (!file.is_open()){
    //      cout << "Error: file open failed." << endl;
    //     exit(1);
    // }
     string line;
    while (getline(file, line)){
        if (i == -1){
            i++;
            continue;
        }
        employees[i].set_id( stoi(line.substr(0, line.find(";"))));
        employees[i].set_salary( stoi(line.substr(line.find(";") + 1, line.find_last_of(";") - line.find(";") - 1)));
        employees[i].set_department( stoi(line.substr(line.find_last_of(";") + 1, line.length() - line.find_last_of(";") - 1)));
        i++;
    }
    file.close();
}

void add(Employee*& employees,int& num_employee, int salary, int department)
{
    int newID = 1;
    for (int i = 0; i < num_employee; i++) {
        if (employees[i].get_id() >= newID) {
            newID = employees[i].get_id() + 1;
        }
    }
    
    Employee* newEmployees = new Employee[num_employee+1];

    for (int i = 0; i < num_employee; i++) {
        newEmployees[i] = employees[i];
    }

    delete[] employees;

    employees = newEmployees;
    
    employees[num_employee].set_id(newID);
    employees[num_employee].set_salary(salary);
    employees[num_employee].set_department(department);

    num_employee++;

}

void update(Employee*& employees, int num_employee, int id, int salary, int department)
{
    
    bool found = false;
    for (int i = 0; i < num_employee; i++) {
        if (employees[i].get_id() == id) {
            found = true;
            break;
        }
    }
    if (!found) {
         cout <<"ERROR: An invalid ID to update";
    }

    for (int i = 0; i < num_employee; i++) {
        if (employees[i].get_id() == id) {
            employees[i].set_salary(salary);
            employees[i].set_department(department);
        }
    }
    
}

void deletee(Employee*& employees, int& num_employee, int id)
{
    
    if (num_employee == 0) {
         cout << "ERROR: There is no Employee";
        return;
    }
    bool found = false;
    for (int i = 0; i < num_employee; i++) {
        if (employees[i].get_id() == id) {
            found = true;
            break;
        }
    }
    if (!found) {
         cout << "ERROR: An invalid ID to delete";
    }

    int index = -1;
    for (int i = 0; i < num_employee; i++) {
        if (employees[i].get_id() == id) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        return;
    }

    Employee* newEmployees = new Employee[num_employee-1];

    for (int i = 0; i < index; i++) {
        newEmployees[i] = employees[i];
    }

    for (int i = index+1; i < num_employee; i++) {
        newEmployees[i-1] = employees[i];
    }

    delete[] employees;

    employees = newEmployees;

    num_employee--;
}

void newcsv(Employee* employees, int num_employee)
{
     ofstream outfile;
    outfile.open("array_solution.csv");
    outfile << "id;salary;department" <<  endl;
    for (int i = 0; i < num_employee; i++){
        outfile << employees[i].get_id() << ";" << employees[i].get_salary() << ";" << employees[i].get_department() <<  endl;
    }
    outfile.close();
}

int main(int argc, char** argv)
{
    int i = -1, n = 0;
     ifstream first_file;
     first_file.open(argv[1]);
    // if (!first_file.is_open()){
    //      cout << "Error: file open failed." <<  endl;
    //     exit(1);
    // }
     string first_line;
    while( getline(first_file, first_line)){
        n++;
    }
    first_file.close();
    first_file.open(argv[1]);
    Employee* employees = new Employee[n];
    int num_employee = n-1; // n before
    while ( getline(first_file, first_line)){
        // passing the first line
        if (i == -1){
            i++;
            continue;
        }

        employees[i].set_id( stoi(first_line.substr(0, first_line.find(";"))));
        employees[i].set_salary( stoi(first_line.substr(first_line.find(";") + 1, first_line.find_last_of(";") - first_line.find(";") - 1)));
        employees[i].set_department( stoi(first_line.substr(first_line.find_last_of(";") + 1, first_line.length() - first_line.find_last_of(";") - 1)));
        i++;
    }
    first_file.close();


     ifstream file(argv[2]);
    // file.open("operations.txt");
    // if (!file.is_open()){
    //      cout << "Error: file open failed." <<  endl;
    //     exit(1);
    // }
     string line;
    while ( getline(file, line)){
        if ( line.substr(0, line.find(";")) == "ADD"){
            // clock_t start = clock();
            int salary =  stoi(line.substr(line.find(";") + 1, line.find_last_of(";") - line.find(";") - 1));
            int department =  stoi(line.substr(line.find_last_of(";") + 1, line.length() - line.find_last_of(";") - 1));
            add(employees, num_employee, salary, department);
            // // clock_t end = clock();
            // double time = (end - start)*1000 / CLOCKS_PER_SEC;  
            // cout<<"ADD array solution "<<time<<" miliseconds."<<endl;
        }
        else if ( line.substr(0, line.find(";")) == "UPDATE"){
            // clock_t start = clock();
            int id =  stoi(line.substr(line.find(";") + 1, line.find_last_of(";") - line.find(";") - 1));
            int salary =  stoi(line.substr(line.find_last_of(";") - 4, line.find_last_of(";")));
            int department =  stoi(line.substr(line.find_last_of(";") + 1, line.length() - line.find_last_of(";") - 1));
            update(employees, num_employee, id, salary, department);
            // clock_t end = clock();
            // double time = (end - start)*1000 / CLOCKS_PER_SEC;  
            // cout<<"UPDATE array solution "<<time<<" miliseconds."<<endl;
            // cout<<"upd"<<endl;
        }
        else if ( line.substr(0, line.find(";")) == "DELETE"){
            // clock_t start = clock();
            int id =  stoi(line.substr(line.find(";") + 1, line.length() - line.find(";") - 1));
            deletee(employees, num_employee, id);
            // clock_t end = clock();
            // double time = (end - start)*1000 / CLOCKS_PER_SEC;  
            // cout<<"DELETE array solution "<<time<<" miliseconds."<<endl;
            // cout<<"del"<<endl;
        }
        
    }
    file.close();


    newcsv(employees, num_employee);
    
    return 0;

// operations1.txt results:
//  ADD array solution 10 miliseconds.      ~ADD;3500;2
//  ADD array solution 6 miliseconds.       ~ADD;5300;5
//  UPDATE array solution 3 miliseconds.    ~UPDATE;3;4200;1
//  UPDATE array solution 0 miliseconds.    ~UPDATE;6;2600;7
//  ADD array solution 7 miliseconds.       ~ADD;7200;2
//  DELETE array solution 4 miliseconds.    ~DELETE;2
//  DELETE array solution 8 miliseconds.    ~DELETE;8
//  ADD array solution 6 miliseconds.       ~ADD;2900;1

// operations2.txt results:
// DELETE array solution 7 miliseconds.                                         ~DELETE;5000
// (ERROR) DELETE array solution 4 miliseconds.                                 ~DELETE;5000
// (ERROR) UPDATE array solution 4 miliseconds.                                 ~UPDATE;5000;5000;5000
// ADD array solution 10 miliseconds.                                           ~ADD;5000;5000
// ADD array solution 13 miliseconds.                                           ~ADD;5000;5000
// DELETE array solution 17 miliseconds.                                        ~DELETE;5000
// DELETE array solution 13 miliseconds.                                        ~DELETE;5000
// (ERROR) UPDATE array solution 4 miliseconds.                                 ~UPDATE;5000;5000;5000
// DELETE array solution 14 miliseconds.                                        ~DELETE;5000
// UPDATE array solution 3 miliseconds.                                         ~UPDATE;5000;5000;5000
// UPDATE array solution 6 miliseconds.                                         ~UPDATE;5000;5000;5000
// UPDATE array solution 4 miliseconds.                                         ~UPDATE;5000;5000;5000
// ADD array solution 13 miliseconds.                                           ~ADD;5000;5000
// ADD array solution 4 miliseconds.                                            ~ADD;5000;5000
// ADD array solution 17 miliseconds.                                           ~ADD;5000;5000
// ADD array solution 9 miliseconds.                                            ~ADD;5000;5000

}
