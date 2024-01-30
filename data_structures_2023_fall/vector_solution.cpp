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
#include <vector>
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

void add_employee(vector<Employee> &employees, int id ,int salary, int department){
    Employee employee;
    employee.set_id(id);
    employee.set_salary(salary);
    employee.set_department(department);
    employees.push_back(employee);
}

void delete_employee(vector<Employee> &employees, int id){
  
    if (employees.empty()){
        cout << "ERROR: There is no Employee";
    }
    
    bool found = false;
    for (int i = 0; i < employees.size(); i++){
        if (employees[i].get_id() == id){
            found = true;
            break;
        }
    }
    if (!found){
        cout << "ERROR: An invalid ID to delete";
        return;
    }

    for (int i = 0; i < employees.size(); i++){
        if (employees[i].get_id() == id){
            employees.erase(employees.begin() + i);
        }
    }
}

void update_employee(vector<Employee> &employees, int id, int salary, int department){
  
    bool found = false;
    for (int i = 0; i < employees.size(); i++){
        if (employees[i].get_id() == id){
            found = true;
            break;
        }
    }
    if (!found){
        cout << "ERROR: An invalid ID to update";
    }


    for (int i = 0; i < employees.size(); i++){
        if (employees[i].get_id() == id){
            employees[i].set_salary(salary);
            employees[i].set_department(department);
        }
    }
}

void newscv(vector<Employee> &employees){
    ofstream myfile;
    myfile.open ("vector_solution.csv");
    myfile << "Employee_ID;Salary;Department\n";
    for (int i = 0; i < employees.size(); i++){
        myfile << employees[i].get_id() << ";" << employees[i].get_salary() << ";" << employees[i].get_department() << "\n";
    }
    myfile.close();
}

int main(int argc, char **argv){
    vector<Employee> employees;
    Employee employee;
  
    ifstream first_file(argv[1]);
    string first_line;
    getline(first_file, first_line);
    while( getline(first_file, first_line)){
        int id, salary, department;
        sscanf(first_line.c_str(), "%d;%d;%d", &id, &salary, &department);
        employee.set_id(id);
        employee.set_salary(salary);
        employee.set_department(department);
        employees.push_back(employee);
    }
    first_file.close();

    // for (int i = 0; i < employees.size(); i++){
    //     cout << employees[i].get_id() << " " << employees[i].get_salary() << " " << employees[i].get_department() << endl;
    // }

    ifstream file(argv[2]);
    string line;
    while (getline(file, line)) {
    size_t pos1 = line.find(";");
    size_t pos2 = line.find(";", pos1 + 1);
    string command = line.substr(0, pos1);
    int id, salary, department;

    if (command == "ADD") {
        clock_t start = clock();
        id = employees.empty() ? 1 : employees.back().get_id() + 1;
        salary = stoi(line.substr(pos1 + 1, pos2 - pos1 - 1));
        department = stoi(line.substr(line.find_last_of(";") + 1, line.length() - line.find_last_of(";") - 1));
        add_employee(employees, id, salary, department);
        clock_t end = clock();
        double time = (end - start)*1000 / CLOCKS_PER_SEC;
        cout << "ADD vector solution " << time << " miliseconds." << endl;

    } else if (command == "UPDATE") {
        clock_t start = clock();
        id = stoi(line.substr(pos1 + 1, pos2 - pos1 - 1));
        salary = stoi(line.substr(pos2 + 1));
        department = stoi(line.substr(line.find_last_of(";") + 1, line.length() - line.find_last_of(";") - 1));
        update_employee(employees, id, salary, department);
        clock_t end = clock();
        double time = (end - start)*1000 / CLOCKS_PER_SEC;
        cout << "UPDATE vector solution " << time << " miliseconds." << endl;
    } else if (command == "DELETE") {
        clock_t start = clock();
        id = stoi(line.substr(pos1 + 1));
        delete_employee(employees, id);
        clock_t end = clock();
        double time = (end - start)*1000 / CLOCKS_PER_SEC;
        cout << "DELETE vector solution " << time << " miliseconds." << endl;

    }
}
    file.close();
    newscv(employees);

  return 0;
}

// ADD vector solution 0 miliseconds.
// ADD vector solution 0 miliseconds.
// UPDATE vector solution 0 miliseconds.
// UPDATE vector solution 0 miliseconds.
// ADD vector solution 0 miliseconds.
// DELETE vector solution 16 miliseconds. ?? Interesting result :D
// DELETE vector solution 6 miliseconds.