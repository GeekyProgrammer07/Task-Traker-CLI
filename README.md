
# Task Tracker CLI

The Task Tracker CLI is a command-line application designed for efficient task management. Users can easily add, update, delete, and track tasks through simple commands.


## Key Features

- Add, Update, and Delete Tasks: Manage tasks with ease.
- Status: In-progress

## Data Storage

Tasks are stored in a JSON file, which is created automatically if it doesn’t exist, ensuring persistence across sessions.

## Technologies Used
- Language: C++
- Storage: JSON file

## How to Run
Clone the repository and run the following command:

```bash
cd Task-Tracker-CLI
```
Run the following command to build and run the Project:

```bash
g++ -o task-cli task_tracker.cpp -std=c++11
```
### To add a Task:

```bash
./task-cli add "Your Item"
```
### To list all Tasks:

```bash
./task-cli list
```
### To Update a Task:

```bash
./task-cli update <id> "New Task"
```
### To Delete a Task:

```bash
./task-cli delete <id>
```
### To List Tasks that are not Done:

```bash
./task-cli list-not-done
```
### To mark a task in progress:
```bash
./task-cli progress <id>
```
<hr>
<br>
<b>
This project enhances programming skills while providing a practical tool for organizing tasks efficiently.
</b>