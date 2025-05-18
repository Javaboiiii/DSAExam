// Write a program which simulates the operation of a busy airport which has only two
//  runways to handle all takeoffs and landings. You may assume that each takeoff or
//  landing takes 15 minutes to complete. One runway request is made during each five minute time interval and likelihood
//  of landing request is the same as for takeoff. Priority is given to planes requesting a
//  landing. If a request cannot be honored it is added to a takeoff or landing queue. Your program should simulate 120 minutes
//  of activity at the airport. Each request for runway clearance should be time-stamped and added to the appropriate queue
// . The output from your program should include the final queue contents, the number of take offs completed, the number
//  of landings completed, and the average number of minutes spent in each queue.

#include <iostream>
#include <queue>
#include <vector>
#include <random>
#include <iomanip>
using namespace std;

// Structure to represent a plane request
struct PlaneRequest {
    int id;              // Unique identifier for the plane
    bool isLanding;      // true if landing, false if takeoff
    int requestTime;     // Time when request was made
    int startTime;       // Time when request was handled
    int completionTime;  // Time when request was completed
};

// Function to print a plane request
void printRequest(const PlaneRequest& request) {
    cout << "Plane #" << request.id << " (" 
         << (request.isLanding ? "Landing" : "Takeoff") << "): "
         << "Requested at " << request.requestTime << " min, "
         << "Started at " << (request.startTime != -1 ? to_string(request.startTime) : "N/A") << " min, "
         << "Completed at " << (request.completionTime != -1 ? to_string(request.completionTime) : "N/A") << " min, "
         << "Wait time: " << (request.startTime != -1 ? to_string(request.startTime - request.requestTime) : "N/A") << " min"
         << endl;
}

int main() {
    // Constants
    const int SIMULATION_TIME = 120;    // 120 minutes of simulation
    const int REQUEST_INTERVAL = 5;     // New request every 5 minutes
    const int RUNWAY_TIME = 15;         // 15 minutes for takeoff or landing
    const int NUM_RUNWAYS = 2;          // 2 runways available
    
    // Random number generator for determining request type
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distRequestType(0, 1); // 0 for takeoff, 1 for landing
    
    // Queues for takeoff and landing requests
    queue<PlaneRequest> takeoffQueue;
    queue<PlaneRequest> landingQueue;
    
    // Track completed operations
    vector<PlaneRequest> completedLandings;
    vector<PlaneRequest> completedTakeoffs;
    
    // Track runway availability
    vector<int> runwayAvailableTime(NUM_RUNWAYS, 0);
    
    // Simulation time counter
    int currentTime = 0;
    int planeIdCounter = 1;
    
    cout << "=== Airport Runway Simulation ===" << endl;
    cout << "Simulation time: " << SIMULATION_TIME << " minutes" << endl;
    cout << "Number of runways: " << NUM_RUNWAYS << endl;
    cout << "Runway operation time: " << RUNWAY_TIME << " minutes" << endl;
    cout << "Request interval: " << REQUEST_INTERVAL << " minutes" << endl;
    cout << "Priority: Landing requests over takeoff requests" << endl << endl;
    
    // Start simulation
    while (currentTime <= SIMULATION_TIME) {
        // Generate new request every 5 minutes
        if (currentTime % REQUEST_INTERVAL == 0 && currentTime < SIMULATION_TIME) {
            // Determine if it's a landing or takeoff request
            bool isLanding = distRequestType(gen) == 1;
            
            // Create the request
            PlaneRequest request;
            request.id = planeIdCounter++;
            request.isLanding = isLanding;
            request.requestTime = currentTime;
            request.startTime = -1;
            request.completionTime = -1;
            
            // Add request to appropriate queue
            if (isLanding) {
                landingQueue.push(request);
                cout << "Time " << currentTime << ": New landing request (Plane #" << request.id << ")" << endl;
            } else {
                takeoffQueue.push(request);
                cout << "Time " << currentTime << ": New takeoff request (Plane #" << request.id << ")" << endl;
            }
        }
        
        // Check runway availability and assign requests
        for (int i = 0; i < NUM_RUNWAYS; i++) {
            if (runwayAvailableTime[i] <= currentTime) {
                // Runway is available
                PlaneRequest request;
                bool requestAssigned = false;
                
                // Priority to landing requests
                if (!landingQueue.empty()) {
                    request = landingQueue.front();
                    landingQueue.pop();
                    requestAssigned = true;
                    
                    // Mark as landing completed
                    request.startTime = currentTime;
                    request.completionTime = currentTime + RUNWAY_TIME;
                    completedLandings.push_back(request);
                    
                    cout << "Time " << currentTime << ": Runway " << i+1 << " assigned for landing to Plane #" << request.id << endl;
                } 
                // If no landing requests, process takeoff requests
                else if (!takeoffQueue.empty()) {
                    request = takeoffQueue.front();
                    takeoffQueue.pop();
                    requestAssigned = true;
                    
                    // Mark as takeoff completed
                    request.startTime = currentTime;
                    request.completionTime = currentTime + RUNWAY_TIME;
                    completedTakeoffs.push_back(request);
                    
                    cout << "Time " << currentTime << ": Runway " << i+1 << " assigned for takeoff to Plane #" << request.id << endl;
                }
                
                // Update runway availability
                if (requestAssigned) {
                    runwayAvailableTime[i] = currentTime + RUNWAY_TIME;
                }
            }
        }
        
        // Advance time
        currentTime++;
    }
    
    // Calculate statistics
    int totalLandingWaitTime = 0;
    for (const auto& landing : completedLandings) {
        totalLandingWaitTime += (landing.startTime - landing.requestTime);
    }
    
    int totalTakeoffWaitTime = 0;
    for (const auto& takeoff : completedTakeoffs) {
        totalTakeoffWaitTime += (takeoff.startTime - takeoff.requestTime);
    }
    
    double avgLandingWaitTime = completedLandings.empty() ? 0 : 
                               (double)totalLandingWaitTime / completedLandings.size();
    double avgTakeoffWaitTime = completedTakeoffs.empty() ? 0 : 
                               (double)totalTakeoffWaitTime / completedTakeoffs.size();
    
    // Print final results
    cout << "\n=== Simulation Results ===" << endl;
    cout << "Total simulation time: " << SIMULATION_TIME << " minutes" << endl;
    cout << "Total completed landings: " << completedLandings.size() << endl;
    cout << "Total completed takeoffs: " << completedTakeoffs.size() << endl;
    cout << "Average landing wait time: " << fixed << setprecision(2) << avgLandingWaitTime << " minutes" << endl;
    cout << "Average takeoff wait time: " << fixed << setprecision(2) << avgTakeoffWaitTime << " minutes" << endl;
    
    // Print remaining queue contents
    cout << "\n=== Remaining Landing Queue (" << landingQueue.size() << " planes) ===" << endl;
    if (landingQueue.empty()) {
        cout << "No planes waiting to land" << endl;
    } else {
        queue<PlaneRequest> tempLandingQueue = landingQueue;
        while (!tempLandingQueue.empty()) {
            printRequest(tempLandingQueue.front());
            tempLandingQueue.pop();
        }
    }
    
    cout << "\n=== Remaining Takeoff Queue (" << takeoffQueue.size() << " planes) ===" << endl;
    if (takeoffQueue.empty()) {
        cout << "No planes waiting to take off" << endl;
    } else {
        queue<PlaneRequest> tempTakeoffQueue = takeoffQueue;
        while (!tempTakeoffQueue.empty()) {
            printRequest(tempTakeoffQueue.front());
            tempTakeoffQueue.pop();
        }
    }
    
    return 0;
}