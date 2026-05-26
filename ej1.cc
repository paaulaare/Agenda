
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;

struct Task{
    int hours;
    int minutes;
    char description[100];
};

void menu(){
    cout << "-------" << endl
        << "Options" << endl
        << "-------" << endl
        << "1. Add task" << endl
        << "2. Delete task" << endl
        << "q. Quit" << endl
        << "Option: ";
}

void addTask(vector<Task>& taskList){
    Task newTask;
    char dosPuntos;
    cout << "Insert task: ";

    cin >> newTask.hours >> dosPuntos >> newTask.minutes;
    
    cin.getline(newTask.description, 100);
    taskList.push_back(newTask);
}

void deleteTask(vector<Task>& taskList){
    for(size_t i = 0; i < taskList.size(); i++){
        Task t = taskList[i];
        cout << i+1 << ". ";
        if(t.hours < 10) cout << '0';
        cout << t.hours << ':';
        if(t.minutes < 10) cout << '0';
        cout << t.minutes << t.description << endl;
    }
    unsigned int numberTask;
    cout << "Insert number: ";
    cin >> numberTask;
    if(!(0 < numberTask && numberTask < taskList.size() + 1)){
        cout << "Error: wrong number" << endl;
    }
    else{
        taskList.erase(taskList.begin() + numberTask-1);
    }
}

void loadFile(vector<Task>& taskList, string fileName){
    ifstream file;
    file.open(fileName, ios::in | ios::binary);
    if(!file.is_open()){
        cout << "Error: cannot read file" << endl;
    }
    Task tempTask;
    if(file.is_open()){
        while(file.read((char*)&tempTask, sizeof(Task))){
            taskList.push_back(tempTask);
        }
        file.close();
    }
}

void saveFile(vector<Task>& taskList, string fileName){
    ofstream file;
    file.open(fileName, ios::out | ios::binary);
    if(!file.is_open()){
        cout << "Error: cannot write file" << endl;
        return;
    }
    for (size_t i = 0; i < taskList.size(); i++) {
        file.write((const char*)&taskList[i], sizeof(Task));
    }
    file.close();
}

int main(int argc, char *argv[]){
    vector<Task> list;
    bool argumentA = false;
    bool argumentF = false;
    string fileName = "tasks.bin";
    for(int i = 1; i<argc; i++){
        string argumento = argv[i];
        if(argumento == "-a") argumentA = true;
        else if(argumento == "-f"){
            if(i+1 < argc){
                fileName =  argv[i+1];
                argumentF = true;
                i++;
            }
            else cout << "Error: wrong arguments" << endl;
        }
        else cout << "Error: wrong arguments";
    }
    if(argumentF) loadFile(list, fileName);
    if(argumentA) addTask(list);

    char option;
        do{
            menu();
            cin >> option;
            cin.ignore();
            switch(option){
                case '1': // Add task
                    addTask(list);
                    break;
                case '2': // Delete task
                    deleteTask(list);
                    break;
                case 'q': // Quit
                    saveFile(list, fileName);
                    break;
                default:
                    cout << "Error: wrong option" << endl;
                    break;
            }
            cout << endl;
        }while(option != 'q');
    return 0;
}