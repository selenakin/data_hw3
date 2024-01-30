/* @Author
    StudentName: Nurselen Akın
    StudentID: 150200087
    Date: 29.10.2023
*/

//FYI: Results of the time measurements are at the end of the file.


#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <map>
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
    cout << id << ";" << salary << ";" << department << "\n";
}


void print_map_to_file(map<int, Employee*> employee_map){
    ofstream output_file;
    output_file.open("output.csv");
    output_file << "Employee_ID;Salary;Department" << "\n";
    for (auto it = employee_map.begin(); it != employee_map.end(); ++it){
        output_file << it->first << ";" << it->second->get_salary() << ";" << it->second->get_department() << "\n";
    }
    output_file.close();
}

int main(int argc, char** argv) {
   
    int i = -1;
    ifstream first_file;
    first_file.open(argv[1]);
    string first_line;

    map<int, Employee*> employee_map;


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
            
        employee_map.insert(pair<int, Employee*>(id, employee));
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
        size_t pos3 = line.find(";", pos2 + 1);
        string command = line.substr(0, pos1);

        if (command == "ADD") {
            // add_count++;
            // clock_t add_start = clock();
            int max_id = employee_map.rbegin()->first;
            int id = max_id + 1;
            int salary = stoi(line.substr(pos1 + 1, pos2 - pos1 - 1));
            int department = stoi(line.substr(pos2 + 1));
            Employee* employee = new Employee(id, salary, department);
            employee_map.insert(pair<int, Employee*>(id, employee));
            // clock_t add_end = clock();
            // add_time += (double)(add_end - add_start) / CLOCKS_PER_SEC;
        } 
        else if (command == "UPDATE") {
            // update_count++;
            // clock_t update_start = clock();
            int id = stoi(line.substr(pos1 + 1, pos2 - pos1 - 1));
            int salary = stoi(line.substr(pos2 + 1, pos3 - pos2 - 1));
            int department = stoi(line.substr(pos3 + 1));
            auto it = employee_map.find(id);
            if (it != employee_map.end()) {
                Employee* employee = it->second;
                employee->set_salary(salary);
                employee->set_department(department);
            }
            else {
                cout << "ERROR: An invalid ID to update" << "\n";
            }
            // clock_t update_end = clock();
            // update_time += (double)(update_end - update_start) / CLOCKS_PER_SEC;
        }
        else if (command == "DELETE") {
            // delete_count++;
            // clock_t delete_start = clock();
            int id = stoi(line.substr(pos1 + 1));
            auto it = employee_map.find(id);
            if (it == employee_map.end()) {
                cout << "ERROR: An invalid ID to delete" << "\n";
            }
            else {
                employee_map.erase(it);
            }
            // clock_t delete_end = clock();
            // delete_time += (double)(delete_end - delete_start) / CLOCKS_PER_SEC;
        }
    }

    file.close();
    
    print_map_to_file(employee_map);

    // cout<<"ADD average time: "<<double(add_time/add_count)<<" miliseconds."<<endl;  
    // cout<<"UPDATE average time: "<<double(update_time/update_count)<<" miliseconds."<<endl;
    // cout<<"DELETE average time: "<<double(delete_time/delete_count)<<" miliseconds."<<endl;


    return 0;
}

// Results of the time measurements ordered:
// ADD average time: 7.17489e-006 miliseconds.
// UPDATE average time: 8.93921e-007 miliseconds.
// DELETE average time: 9.09366e-007 miliseconds.

// Results of the time measurements shuffled:
// ADD average time: 8.96861e-007 miliseconds.
// UPDATE average time: 2.08582e-006 miliseconds.
// DELETE average time: 1.21249e-006 miliseconds.