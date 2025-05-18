// 25.	A person is living in house having 5 rooms. These rooms are adjacent to each other. There is
//  a treasure which is electronically locked and to unlock it we need a code. In last room there is a box
//  in which some decimal number is written. We need to convert that number into binary to open treasure which is kept in room
//  no.1. We need to move from room no.1 to 2 to 3 and so on and follow the reverse way to come back i.e. from 5 to 4 to 3
//  etc. Apply suitable logic to implement this scenario by using stacks.

#include <iostream>
#include <stack>
#include <string>
using namespace std;

// Structure to represent a room
struct Room {
    int roomNumber;
    string description;
};

// Function to convert decimal to binary
string decimalToBinary(int decimal) {
    if (decimal == 0) {
        return "0";
    }
    
    string binary = "";
    while (decimal > 0) {
        binary = to_string(decimal % 2) + binary;
        decimal /= 2;
    }
    return binary;
}

// Function to display the room and add it to the stack
void enterRoom(stack<Room>& path, Room room) {
    cout << "\nEntering Room " << room.roomNumber << "..." << endl;
    cout << room.description << endl;
    path.push(room);
}

// Function to leave a room (pop from stack and return to previous room)
void leaveRoom(stack<Room>& path) {
    Room currentRoom = path.top();
    path.pop();
    
    cout << "\nLeaving Room " << currentRoom.roomNumber << "..." << endl;
    
    if (!path.empty()) {
        Room previousRoom = path.top();
        cout << "Returning to Room " << previousRoom.roomNumber << "..." << endl;
    }
}

// Function to display the contents of the stack
void displayPath(stack<Room> path) {
    cout << "\nCurrent Path (from current to start):" << endl;
    stack<Room> tempPath = path;
    
    while (!tempPath.empty()) {
        Room room = tempPath.top();
        cout << "Room " << room.roomNumber;
        tempPath.pop();
        
        if (!tempPath.empty()) {
            cout << " <- ";
        }
    }
    cout << endl;
}

int main() {
    stack<Room> path;
    int decimalCode;
    string binaryCode;
    
    // Initialize rooms
    Room room1 = {1, "This is the entrance room. The treasure is here but locked with an electronic code."};
    Room room2 = {2, "This is the second room. It has a passage to room 3."};
    Room room3 = {3, "This is the third room. It connects rooms 2 and 4."};
    Room room4 = {4, "This is the fourth room. It has a door leading to room 5."};
    Room room5 = {5, "This is the fifth room. There is a box with a decimal number written on it."};
    
    cout << "=== TREASURE HUNT SCENARIO ===" << endl;
    cout << "You need to navigate through 5 rooms, find a code in the last room," << endl;
    cout << "convert it to binary, and use it to unlock the treasure in room 1." << endl;
    
    // Forward journey (Room 1 to 5)
    cout << "\n=== FORWARD JOURNEY (Finding the Code) ===" << endl;
    
    enterRoom(path, room1);
    displayPath(path);
    
    enterRoom(path, room2);
    displayPath(path);
    
    enterRoom(path, room3);
    displayPath(path);
    
    enterRoom(path, room4);
    displayPath(path);
    
    enterRoom(path, room5);
    displayPath(path);
    
    // Finding the decimal number in Room 5
    cout << "\nYou found a box in Room 5 with a decimal number on it." << endl;
    cout << "Enter the decimal number: ";
    cin >> decimalCode;
    
    // Convert decimal to binary
    binaryCode = decimalToBinary(decimalCode);
    cout << "Converting " << decimalCode << " to binary: " << binaryCode << endl;
    cout << "Remember this binary code to unlock the treasure!" << endl;
    
    // Reverse journey (Room 5 to 1)
    cout << "\n=== REVERSE JOURNEY (Returning with the Code) ===" << endl;
    
    // Leave rooms in reverse order
    leaveRoom(path);
    displayPath(path);
    
    leaveRoom(path);
    displayPath(path);
    
    leaveRoom(path);
    displayPath(path);
    
    leaveRoom(path);
    displayPath(path);
    
    // Now we're back in Room 1, try to unlock the treasure
    cout << "\n=== UNLOCKING THE TREASURE ===" << endl;
    cout << "You've returned to Room 1 with the binary code: " << binaryCode << endl;
    cout << "Entering the code into the electronic lock..." << endl;
    
    cout << "\nTreasure unlocked! Congratulations!" << endl;
    cout << "The decimal code was: " << decimalCode << endl;
    cout << "The binary code was: " << binaryCode << endl;
    
    return 0;
}