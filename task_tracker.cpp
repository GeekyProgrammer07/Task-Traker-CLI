#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <fstream>
#include "json.hpp" //JSON library for C++ 
#include <ctime>

using namespace std;

using json = nlohmann::json;

struct Task 
{
    int id;
    string description;
    string status;
    string createdAt;
    string updatedAt;
};

vector<Task> tasks;

void load_tasks();
void add_task();
void update_task();
void delete_task();
void list_tasks();
void list_tasks_not_done();
void progress_tasks();

void save_tasks();

int main(int  argc, char *argv[]) { //argv[] is an containing the command line arguments passed & argc is the number of arguments
    load_tasks(); // Load existing tasks from JSON file

    if (argc < 2)
    {
        cout << "Correct format: ./cli <command> [args]" << endl;
        return 1;
    }
    string command = argv[1];
    if (command == "add" && argc == 3)
    {
        add_task(argv[2]);
    } 
    else if (command == "update" && argc == 4)
    {
        int id = stoi(argv[2]);
        update_task(id, argv[3]);
    } 
    else if (command == "delete" && argc == 3)
    {
        int id = stoi(argv[2]);
        delete_task(id);
    }
    else if (command == "list")
    {
        list_tasks();
    }
    else if (command == "list_not_done")
    {
        list_tasks_not_done();
    }
    else if (command == "progress" && argc == 3)
    {
        int id = stoi(argv[2]);
        progress_tasks(id);
    }
    else 
    {
        cout << "Unknown Command: " << command << endl;
    }

    save_tasks(); // Save updated tasks to JSON file
    return 0;
}

void load_tasks()
{
    ifstream file("tasks.json");
    if (file)
    {
        json j; //JSON Object
        file >> j;
        {
            for (auto& item : j)
            {
                Task t;
                t.id = item["id"];
                t.description = item["description"];
                t.status = item["status"];
                t.createdAt = item["created_at"];
                t.updatedAt = item["updated_at"];
                tasks.push_back(t);
            }
        }
    }
}

void add_task(const string description)
{
    Task new_task;
    new_task.id = tasks.size() + 1;
    new_task.description = description;
    new_task.status = "todo";
    time_t time_in_seconds = time(0);
    string time = ctime(&time_in_seconds);
    time.pop_back(); //removes the newline added by ctime()
    new_task.createdAt = time;
    new_task.updatedAt = time;
    tasks.push_back(new_task);
    cout << "Task added: " << description << endl;
}

void update_task(int id, const string new_description)
{
    for (auto& task: tasks)
    {
        if(task.id == id)
        {
            task.description = new_description;
            cout << "Task updated: " << new_description << endl;
            return;
        }
    }
}

void delete_task(int id)
{
    
}
