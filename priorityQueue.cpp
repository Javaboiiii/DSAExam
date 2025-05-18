// Write a Program to simulate the following situation. Computer is a multitasking device. We need to
//  download some document as well as listen music and play game simultaneously. There is a system queue which
//  decides which task to be done first. Assume that for download application priority is highest and 
// game playing is having lowest priority. After completion of one type of tasks like all download operations
//  then the second queue will be processed. (Hint: Can implement priority queue)

#include <iostream>
#include <queue>
#include <string>
#include <vector>
using namespace std;

// Enum to represent task types with their priorities
enum TaskType {
    DOWNLOAD = 0,   // Highest priority
    MUSIC = 1,      // Medium priority
    GAME = 2        // Lowest priority
};

// Task structure to store task details
struct Task {
    int id;             // Unique task identifier
    TaskType type;      // Type of task (Download, Music, Game)
    string description; // Description of the task
    int executionTime;  // Time required to execute the task (in seconds)
    
    // Constructor
    Task(int taskId, TaskType taskType, string desc, int time) {
        id = taskId;
        type = taskType;
        description = desc;
        executionTime = time;
    }
    
    // Get task type as string
    string getTypeString() const {
        switch (type) {
            case DOWNLOAD: return "Download";
            case MUSIC: return "Music";
            case GAME: return "Game";
            default: return "Unknown";
        }
    }
};

// Custom comparator for priority queue
struct TaskComparator {
    bool operator()(const Task& t1, const Task& t2) {
        // Lower value means higher priority
        return t1.type > t2.type;
    }
};

// Function to simulate task execution
void executeTask(const Task& task) {
    cout << "Executing " << task.getTypeString() << " Task #" << task.id 
         << ": " << task.description << " (Time: " << task.executionTime << " seconds)" << endl;
    
    // In a real system, we would actually wait for the execution time
    // Here we're just simulating it
}

int main() {
    // Create a priority queue for tasks
    priority_queue<Task, vector<Task>, TaskComparator> taskQueue;
    
    // Counters for tasks of each type
    int downloadCount = 0;
    int musicCount = 0;
    int gameCount = 0;
    
    int choice, id = 1, executionTime;
    string description;
    
    cout << "=== Computer Multitasking Simulation ===\n";
    cout << "Priority Order: Download (Highest) > Music > Game (Lowest)\n\n";
    
    do {
        cout << "\n=== MENU ===\n";
        cout << "1. Add Download Task\n";
        cout << "2. Add Music Task\n";
        cout << "3. Add Game Task\n";
        cout << "4. Process Next Task\n";
        cout << "5. Process All Tasks\n";
        cout << "6. Display Current Queue Status\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1: // Add Download Task
                cout << "Enter download description: ";
                cin.ignore();
                getline(cin, description);
                cout << "Enter execution time (in seconds): ";
                cin >> executionTime;
                
                taskQueue.push(Task(id++, DOWNLOAD, description, executionTime));
                downloadCount++;
                cout << "Download task added to queue." << endl;
                break;
                
            case 2: // Add Music Task
                cout << "Enter music description: ";
                cin.ignore();
                getline(cin, description);
                cout << "Enter execution time (in seconds): ";
                cin >> executionTime;
                
                taskQueue.push(Task(id++, MUSIC, description, executionTime));
                musicCount++;
                cout << "Music task added to queue." << endl;
                break;
                
            case 3: // Add Game Task
                cout << "Enter game description: ";
                cin.ignore();
                getline(cin, description);
                cout << "Enter execution time (in seconds): ";
                cin >> executionTime;
                
                taskQueue.push(Task(id++, GAME, description, executionTime));
                gameCount++;
                cout << "Game task added to queue." << endl;
                break;
                
            case 4: // Process Next Task
                if (taskQueue.empty()) {
                    cout << "Queue is empty. No tasks to process." << endl;
                } else {
                    Task task = taskQueue.top();
                    taskQueue.pop();
                    
                    cout << "\nProcessing next task from queue..." << endl;
                    executeTask(task);
                    
                    // Update counters
                    switch (task.type) {
                        case DOWNLOAD: downloadCount--; break;
                        case MUSIC: musicCount--; break;
                        case GAME: gameCount--; break;
                    }
                }
                break;
                
            case 5: // Process All Tasks
                if (taskQueue.empty()) {
                    cout << "Queue is empty. No tasks to process." << endl;
                } else {
                    cout << "\nProcessing all tasks in priority order...\n" << endl;
                    
                    // Process all download tasks first
                    while (!taskQueue.empty()) {
                        Task task = taskQueue.top();
                        taskQueue.pop();
                        
                        executeTask(task);
                        
                        // Update counters
                        switch (task.type) {
                            case DOWNLOAD: downloadCount--; break;
                            case MUSIC: musicCount--; break;
                            case GAME: gameCount--; break;
                        }
                        
                        // Visual separator between task types
                        if (!taskQueue.empty() && taskQueue.top().type != task.type) {
                            cout << "\n--- Moving to next priority level ---\n" << endl;
                        }
                    }
                    
                    cout << "\nAll tasks have been processed." << endl;
                }
                break;
                
            case 6: // Display Queue Status
                cout << "\n=== Current Queue Status ===\n";
                cout << "Download Tasks: " << downloadCount << endl;
                cout << "Music Tasks: " << musicCount << endl;
                cout << "Game Tasks: " << gameCount << endl;
                cout << "Total Tasks: " << (downloadCount + musicCount + gameCount) << endl;
                break;
                
            case 0: // Exit
                cout << "Exiting program..." << endl;
                break;
                
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 0);
    
    return 0;
}