/* @Author
    StudentName: Nurselen Akın
    StudentID: 150200087
    Date: 29.10.2023
*/

//FYI: Results of the time measurements are at the end of the file.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <time.h>

using namespace std;

int main(int argc, char **argv)
{
    int length = 0;
    ifstream csv_file(argv[1]);
    string csv_line;
    while( getline(csv_file, csv_line)){
        length++;
    }
    csv_file.close();

    ifstream txt_file(argv[2]);
    string txt_line;
    while( getline(txt_file, txt_line)){
        if(txt_line.substr(0, txt_line.find(";")) == "ADD"){
            clock_t start = clock();
            // cout << "ADD" << endl;
            ofstream outfile;
            outfile.open(argv[1], ios_base::app); 
            outfile << to_string(length) <<";" <<txt_line.substr(txt_line.find(";") + 1, txt_line.find_last_of(";") - txt_line.find(";") - 1) << ";" << txt_line.substr(txt_line.find_last_of(";") + 1, txt_line.length() - txt_line.find_last_of(";") - 1) << endl;
            outfile.close();
            length++;
             clock_t end = clock();
            double time = (end - start)*1000 / CLOCKS_PER_SEC;  
            cout<<"ADD array solution "<<time<<" miliseconds."<<endl;
        }

        else if(txt_line.substr(0, txt_line.find(";")) == "UPDATE"){
            
             clock_t start = clock();
            // cout << "UPDATE" << endl;

            int line_to_change = stoi(txt_line.substr(txt_line.find(";") + 1, txt_line.find_last_of(";") - txt_line.find(";") - 1));
            int salary_to_change = stoi(txt_line.substr(txt_line.find_last_of(";") - 4, txt_line.find_last_of(";")));
            int department_to_change = stoi(txt_line.substr(txt_line.find_last_of(";") + 1, txt_line.length() - txt_line.find_last_of(";") - 1));
            
            ifstream csv_file2(argv[1]);
            string csv_line2;
            ofstream temp_file("temp.csv");
            int i = -1;
            bool found = false;
            ifstream csv_file3(argv[1]);
            string csv_line3;
            while( getline(csv_file3, csv_line3)){
                if(csv_line3.substr(0, csv_line3.find(";")) == to_string(line_to_change)){
                    found = true;
                    break;
                }
            }
            csv_file3.close();
            if(!found){
                cout << "ERROR: An invalid ID to update" << endl;
                continue;
            }
            while( getline(csv_file2, csv_line2)){

                if (i == -1){
                    i++;
                    temp_file << csv_line2 << endl;
                    continue;
                }
                int line_cnt = stoi(csv_line2.substr(0, csv_line2.find(";")));
                if(line_cnt == line_to_change){
                    temp_file << to_string(line_to_change) << ";" << to_string(salary_to_change) << ";" << to_string(department_to_change) << endl;
                }
                else{
                    temp_file << csv_line2 << endl;
                }
            }
            csv_file2.close();
            temp_file.close();

            if( remove(argv[1]) != 0){
                cout << "Error deleting file" << endl;
            }
            if( rename("temp.csv", argv[1]) != 0){
                cout << "Error renaming file" << endl;
            }

            clock_t end = clock();
            double time = (end - start)*1000 / CLOCKS_PER_SEC;  
            cout<<"UPDATE array solution "<<time<<" miliseconds."<<endl;
            // cout<<"upd"<<endl;
        }

        else if(txt_line.substr(0, txt_line.find(";")) == "DELETE"){
           clock_t start = clock();
        //    cout << "DELETE"<< endl;
            if(length == 1){
                cout << "ERROR: There is no Employee" << endl;
                continue;
            }

            int line_to_delete = stoi(txt_line.substr(txt_line.find(";") + 1, -1));
            ifstream csv_file2(argv[1]);
            string csv_line2;
            ofstream temp_file("temp.csv");
            int i = -1;
            while( getline(csv_file2, csv_line2)){
                if (i == -1){
                    i++;
                    temp_file << csv_line2 << endl;
                    continue;
                }
                int line_cnt = stoi(csv_line2.substr(0, csv_line2.find(";")));
                if(line_cnt == line_to_delete){
                    continue;
                }
                else{
                    temp_file << csv_line2 << endl;
                }
            }
            csv_file2.close();
            temp_file.close();
            if( remove(argv[1]) != 0){
                cout << "Error deleting file" << endl;
            }
            if( rename("temp.csv", argv[1]) != 0){
                cout << "Error renaming file" << endl;
            }
            clock_t end = clock();
            double time = (end - start)*1000 / CLOCKS_PER_SEC;  
            cout<<"DELETE array solution "<<time<<" miliseconds."<<endl;
            // cout<<"del"<<endl;
        }
    }
    return 0;
}

// operations1.txt results:
// ADD array solution 0 miliseconds.
// ADD array solution 0 miliseconds.
// UPDATE array solution 13 miliseconds.
// UPDATE array solution 2 miliseconds.
// ADD array solution 1 miliseconds.
// DELETE array solution 8 miliseconds.
// DELETE array solution 3 miliseconds.
// ADD array solution 1 miliseconds.

// operations2.txt results:
// DELETE array solution 0 miliseconds. 
// DELETE array solution 4 miliseconds.
// ERROR: An invalid ID to update
// ADD array solution 0 miliseconds.
// ADD array solution 0 miliseconds.
// DELETE array solution 14 miliseconds.
// DELETE array solution 9 miliseconds.
// ERROR: An invalid ID to update
// DELETE array solution 1 miliseconds.
// UPDATE array solution 2 miliseconds.
// UPDATE array solution 8 miliseconds.
// UPDATE array solution 8 miliseconds.
// ADD array solution 1 miliseconds.
// ADD array solution 0 miliseconds.
// ADD array solution 1 miliseconds.
// ADD array solution 1 miliseconds.