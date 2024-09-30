#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "json.hpp" // Include the JSON library for C++

using namespace std;

using json = nlohmann::json;

struct Task {
    int id;
    string description;
    string status; // "todo", "in-progress", "done"
};

vector<Task> tasks; // Vector to hold tasks

void load_tasks() {
    ifstream file("tasks.json");
    if (file) {
        json j;
        file >> j;
        for (auto& item : j) {
            Task t;
            t.id = item["id"];
            t.description = item["description"];
            t.status = item["status"];
            tasks.push_back(t);
        }
    }
}

void add_task(const string& description) {
    Task new_task;
    new_task.id = tasks.size() + 1; // Simple ID generation
    new_task.description = description;
    new_task.status = "todo";
    tasks.push_back(new_task);
    cout << "Task added: " << description << endl;
}

void update_task(int id, const string& new_description) {
    for (auto& task : tasks) {
        if (task.id == id) {
            task.description = new_description;
            cout << "Task updated: " << new_description << endl;
            return;
        }
    }
    cout << "Task not found!" << endl;
}

void delete_task(int id) {
    auto it = remove_if(tasks.begin(), tasks.end(), [id](Task& t) { return t.id == id; });
    if (it != tasks.end()) {
        tasks.erase(it, tasks.end());
        cout << "Task deleted: ID " << id << endl;
    } else {
        cout << "Task not found!" << endl;
    }
}

void list_tasks() {
    cout << "Tasks:" << endl;
    for (const auto& task : tasks) {
        cout << "ID: " << task.id << ", Description: " << task.description << ", Status: " << task.status << endl;
    }
}

void list_tasks_not_done() {
    cout << "Tasks not done:" << endl;
    for (const auto& task : tasks) {
        if (task.status != "done") {
            cout << "ID: " << task.id << ", Description: " << task.description << endl;
        }
    }
}

void progress_tasks(int id) {
    for (auto& task : tasks) {
        if (task.id == id) {
            task.status = "in-progress";
            cout << "Task marked as in-progress: " << task.description << endl;
            return;
        }
    }
    cout << "Task not found!" << endl;
}

void save_tasks() {
    json j;
    for (const auto& task : tasks) {
        j.push_back({{"id", task.id}, {"description", task.description}, {"status", task.status}});
    }
    ofstream file("tasks.json");
    file << j.dump(4); // Save with pretty print
}

int main(int argc, char *argv[]) {
    load_tasks(); // Load existing tasks from JSON file

    if (argc < 2) {
        cout << "Correct format: ./cli <command> [args]" << endl;
        return 1;
    }

    string command = argv[1];

    if (command == "add" && argc == 3) {
        add_task(argv[2]);
    } else if (command == "update" && argc == 4) {
        int id = stoi(argv[2]);
        update_task(id, argv[3]);
    } else if (command == "delete" && argc == 3) {
        int id = stoi(argv[2]);
        delete_task(id);
    } else if (command == "list") {
        list_tasks();
    } else if (command == "list-not-done") {
        list_tasks_not_done();
    } else if (command == "progress" && argc == 3) {
        int id = stoi(argv[2]);
        progress_tasks(id);
    } else {
        cout << "Unknown command: " << command << endl;
    }

    save_tasks(); // Save tasks to JSON file on exit
    return 0;
}
