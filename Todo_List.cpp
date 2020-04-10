#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <limits>

using namespace std;

int ID;

struct todo {
    int id;
    string task;
};

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void printHeader(const string& title) {
    clearScreen();
    cout << "\t\t\t***********************************************************************\n";
    cout << "\t\t\t*                                                                     *\n";
    cout << "\t\t\t*                    " << title << "                    *\n";
    cout << "\t\t\t*                                                                     *\n";
    cout << "\t\t\t***********************************************************************\n\n\n";
}

void print(const todo& s) {
    cout << "\tID    : " << s.id << endl;
    cout << "\tTask  : " << s.task << endl << endl;
}

void addTodo() {
    printHeader("ADD TASK TO YOUR TODO LIST");

    todo todo;
    cout << "\n\tEnter new task : ";
    cin.ignore();
    getline(cin, todo.task);
    ID++;

    ofstream write("todo.txt", ios::app);
    write << ID << "\n" << todo.task << "\n";
    write.close();

    ofstream idWriter("id.txt");
    idWriter << ID;
    idWriter.close();

    char ch;
    cout << "\n\tDo you want to add more tasks? (y/n): ";
    cin >> ch;

    if (ch == 'y' || ch == 'Y') {
        addTodo();
    } else {
        cout << "\n\tTask has been added successfully.\n";
    }
}

void readData() {
    printHeader("VIEW YOUR TASKS");

    todo todo;
    ifstream read("todo.txt");
    cout << "\n\t------------------ Current Tasks in the List --------------------\n\n";

    while (read >> todo.id) {
        read.ignore();
        getline(read, todo.task);
        print(todo);
    }

    read.close();
}


int main() {
    system("Color E0"); // Yellow background, black text
    system("title TODO List Application");

    printHeader("WELCOME TO YOUR TODO LIST");

    ifstream read("id.txt");
    if (!read.fail()) {
        read >> ID;
    } else {
        ID = 0;
    }
    read.close();

    while (true) {
        cout << "\n\n\tMENU";
        cout << "\n\t1. Add a Task";
        cout << "\n\t2. View All Tasks";
        cout << "\n\t3. Exit";
        cout << "\n\n\tEnter your choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1: addTodo(); break;
            case 2: readData(); break;
            case 3: cout << "\n\tExiting... Goodbye!\n"; return 0;
            default: cout << "\n\tInvalid choice. Please enter between 1 to 6.\n";
        }

        cout << "\n\tPress Enter to continue...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get(); // Wait for Enter key
        clearScreen();
    }

    return 0;
}
