// 27.	We Fly Anywhere Airlines (WFAA) is considering redesigning their ticket counters for airline passengers. They would like
//  to have two separate waiting lines, one for regular customers and one for frequent flyers. Assuming there is only one 
// ticket agent available to serve all passengers, they would like to determine the average waiting time for both types of
//  passengers using various strategies for taking passengers from the waiting lines. WAP to simulate this situation.

#include <iostream>
#include <queue>
#include <random>
#include <string>
#include <iomanip>
#include <vector>
using namespace std;

// Passenger structure
struct Passenger {
    int id;
    bool isFrequentFlyer;
    int arrivalTime;
    int serviceTime;
    int waitingTime;
};

// Function to generate random number within a range
int generateRandomNumber(int min, int max) {
    static random_device rd;
    static mt19937 gen(rd());
    uniform_int_distribution<> distr(min, max);
    return distr(gen);
}

// Strategy 1: Alternate between regular and frequent flyer lines
void alternateLineStrategy(queue<Passenger> regularLine, queue<Passenger> frequentFlyerLine, int simulationTime) {
    cout << "\n===== STRATEGY: ALTERNATE BETWEEN LINES =====\n";
    
    int currentTime = 0;
    bool serveFrequentFlyer = true; // Start with frequent flyer
    
    int regularServed = 0;
    int frequentFlyerServed = 0;
    int totalRegularWaitTime = 0;
    int totalFrequentFlyerWaitTime = 0;
    
    while (currentTime < simulationTime && (!regularLine.empty() || !frequentFlyerLine.empty())) {
        // Determine which line to serve next
        Passenger nextPassenger;
        bool passengerServed = false;
        
        if (serveFrequentFlyer) {
            if (!frequentFlyerLine.empty()) {
                nextPassenger = frequentFlyerLine.front();
                frequentFlyerLine.pop();
                passengerServed = true;
                frequentFlyerServed++;
                
                // Calculate waiting time
                nextPassenger.waitingTime = currentTime - nextPassenger.arrivalTime;
                totalFrequentFlyerWaitTime += nextPassenger.waitingTime;
                
                cout << "Time " << currentTime << ": Serving Frequent Flyer #" << nextPassenger.id 
                     << " (waited " << nextPassenger.waitingTime << " minutes)\n";
            }
        } else {
            if (!regularLine.empty()) {
                nextPassenger = regularLine.front();
                regularLine.pop();
                passengerServed = true;
                regularServed++;
                
                // Calculate waiting time
                nextPassenger.waitingTime = currentTime - nextPassenger.arrivalTime;
                totalRegularWaitTime += nextPassenger.waitingTime;
                
                cout << "Time " << currentTime << ": Serving Regular Customer #" << nextPassenger.id 
                     << " (waited " << nextPassenger.waitingTime << " minutes)\n";
            }
        }
        
        // If we couldn't serve from the preferred line, try the other line
        if (!passengerServed) {
            if (serveFrequentFlyer && !regularLine.empty()) {
                nextPassenger = regularLine.front();
                regularLine.pop();
                regularServed++;
                
                // Calculate waiting time
                nextPassenger.waitingTime = currentTime - nextPassenger.arrivalTime;
                totalRegularWaitTime += nextPassenger.waitingTime;
                
                cout << "Time " << currentTime << ": Serving Regular Customer #" << nextPassenger.id 
                     << " (waited " << nextPassenger.waitingTime << " minutes)\n";
            } else if (!serveFrequentFlyer && !frequentFlyerLine.empty()) {
                nextPassenger = frequentFlyerLine.front();
                frequentFlyerLine.pop();
                frequentFlyerServed++;
                
                // Calculate waiting time
                nextPassenger.waitingTime = currentTime - nextPassenger.arrivalTime;
                totalFrequentFlyerWaitTime += nextPassenger.waitingTime;
                
                cout << "Time " << currentTime << ": Serving Frequent Flyer #" << nextPassenger.id 
                     << " (waited " << nextPassenger.waitingTime << " minutes)\n";
            } else {
                // No one in either line, just advance time
                currentTime++;
                continue;
            }
        }
        
        // Advance time by service time
        currentTime += nextPassenger.serviceTime;
        
        // Toggle the line for next service
        serveFrequentFlyer = !serveFrequentFlyer;
    }
    
    // Print statistics
    cout << "\nResults for Alternating Strategy:\n";
    cout << "Regular Customers Served: " << regularServed << endl;
    cout << "Frequent Flyers Served: " << frequentFlyerServed << endl;
    
    double avgRegularWaitTime = regularServed > 0 ? (double)totalRegularWaitTime / regularServed : 0;
    double avgFrequentFlyerWaitTime = frequentFlyerServed > 0 ? (double)totalFrequentFlyerWaitTime / frequentFlyerServed : 0;
    
    cout << "Average Wait Time for Regular Customers: " << fixed << setprecision(2) << avgRegularWaitTime << " minutes\n";
    cout << "Average Wait Time for Frequent Flyers: " << fixed << setprecision(2) << avgFrequentFlyerWaitTime << " minutes\n";
}

// Strategy 2: Serve frequent flyers first until their line is empty
void frequentFlyerPriorityStrategy(queue<Passenger> regularLine, queue<Passenger> frequentFlyerLine, int simulationTime) {
    cout << "\n===== STRATEGY: FREQUENT FLYER PRIORITY =====\n";
    
    int currentTime = 0;
    
    int regularServed = 0;
    int frequentFlyerServed = 0;
    int totalRegularWaitTime = 0;
    int totalFrequentFlyerWaitTime = 0;
    
    while (currentTime < simulationTime && (!regularLine.empty() || !frequentFlyerLine.empty())) {
        // Serve frequent flyers first, then regular customers
        Passenger nextPassenger;
        
        if (!frequentFlyerLine.empty()) {
            nextPassenger = frequentFlyerLine.front();
            frequentFlyerLine.pop();
            frequentFlyerServed++;
            
            // Calculate waiting time
            nextPassenger.waitingTime = currentTime - nextPassenger.arrivalTime;
            totalFrequentFlyerWaitTime += nextPassenger.waitingTime;
            
            cout << "Time " << currentTime << ": Serving Frequent Flyer #" << nextPassenger.id 
                 << " (waited " << nextPassenger.waitingTime << " minutes)\n";
        } else if (!regularLine.empty()) {
            nextPassenger = regularLine.front();
            regularLine.pop();
            regularServed++;
            
            // Calculate waiting time
            nextPassenger.waitingTime = currentTime - nextPassenger.arrivalTime;
            totalRegularWaitTime += nextPassenger.waitingTime;
            
            cout << "Time " << currentTime << ": Serving Regular Customer #" << nextPassenger.id 
                 << " (waited " << nextPassenger.waitingTime << " minutes)\n";
        } else {
            // No one in either line, just advance time
            currentTime++;
            continue;
        }
        
        // Advance time by service time
        currentTime += nextPassenger.serviceTime;
    }
    
    // Print statistics
    cout << "\nResults for Frequent Flyer Priority Strategy:\n";
    cout << "Regular Customers Served: " << regularServed << endl;
    cout << "Frequent Flyers Served: " << frequentFlyerServed << endl;
    
    double avgRegularWaitTime = regularServed > 0 ? (double)totalRegularWaitTime / regularServed : 0;
    double avgFrequentFlyerWaitTime = frequentFlyerServed > 0 ? (double)totalFrequentFlyerWaitTime / frequentFlyerServed : 0;
    
    cout << "Average Wait Time for Regular Customers: " << fixed << setprecision(2) << avgRegularWaitTime << " minutes\n";
    cout << "Average Wait Time for Frequent Flyers: " << fixed << setprecision(2) << avgFrequentFlyerWaitTime << " minutes\n";
}

// Strategy 3: Serve regular customers first until their line is empty
void regularPriorityStrategy(queue<Passenger> regularLine, queue<Passenger> frequentFlyerLine, int simulationTime) {
    cout << "\n===== STRATEGY: REGULAR CUSTOMER PRIORITY =====\n";
    
    int currentTime = 0;
    
    int regularServed = 0;
    int frequentFlyerServed = 0;
    int totalRegularWaitTime = 0;
    int totalFrequentFlyerWaitTime = 0;
    
    while (currentTime < simulationTime && (!regularLine.empty() || !frequentFlyerLine.empty())) {
        // Serve regular customers first, then frequent flyers
        Passenger nextPassenger;
        
        if (!regularLine.empty()) {
            nextPassenger = regularLine.front();
            regularLine.pop();
            regularServed++;
            
            // Calculate waiting time
            nextPassenger.waitingTime = currentTime - nextPassenger.arrivalTime;
            totalRegularWaitTime += nextPassenger.waitingTime;
            
            cout << "Time " << currentTime << ": Serving Regular Customer #" << nextPassenger.id 
                 << " (waited " << nextPassenger.waitingTime << " minutes)\n";
        } else if (!frequentFlyerLine.empty()) {
            nextPassenger = frequentFlyerLine.front();
            frequentFlyerLine.pop();
            frequentFlyerServed++;
            
            // Calculate waiting time
            nextPassenger.waitingTime = currentTime - nextPassenger.arrivalTime;
            totalFrequentFlyerWaitTime += nextPassenger.waitingTime;
            
            cout << "Time " << currentTime << ": Serving Frequent Flyer #" << nextPassenger.id 
                 << " (waited " << nextPassenger.waitingTime << " minutes)\n";
        } else {
            // No one in either line, just advance time
            currentTime++;
            continue;
        }
        
        // Advance time by service time
        currentTime += nextPassenger.serviceTime;
    }
    
    // Print statistics
    cout << "\nResults for Regular Customer Priority Strategy:\n";
    cout << "Regular Customers Served: " << regularServed << endl;
    cout << "Frequent Flyers Served: " << frequentFlyerServed << endl;
    
    double avgRegularWaitTime = regularServed > 0 ? (double)totalRegularWaitTime / regularServed : 0;
    double avgFrequentFlyerWaitTime = frequentFlyerServed > 0 ? (double)totalFrequentFlyerWaitTime / frequentFlyerServed : 0;
    
    cout << "Average Wait Time for Regular Customers: " << fixed << setprecision(2) << avgRegularWaitTime << " minutes\n";
    cout << "Average Wait Time for Frequent Flyers: " << fixed << setprecision(2) << avgFrequentFlyerWaitTime << " minutes\n";
}

// Strategy 4: Serve frequent flyer after every 3 regular customers
void ratioStrategy(queue<Passenger> regularLine, queue<Passenger> frequentFlyerLine, int simulationTime, int regularRatio, int frequentFlyerRatio) {
    cout << "\n===== STRATEGY: SERVE " << regularRatio << " REGULAR CUSTOMERS THEN " 
         << frequentFlyerRatio << " FREQUENT FLYERS =====\n";
    
    int currentTime = 0;
    int regularCount = 0;
    int frequentFlyerCount = 0;
    bool serveRegular = true;
    
    int regularServed = 0;
    int frequentFlyerServed = 0;
    int totalRegularWaitTime = 0;
    int totalFrequentFlyerWaitTime = 0;
    
    while (currentTime < simulationTime && (!regularLine.empty() || !frequentFlyerLine.empty())) {
        Passenger nextPassenger;
        bool passengerServed = false;
        
        if (serveRegular) {
            if (!regularLine.empty()) {
                nextPassenger = regularLine.front();
                regularLine.pop();
                regularServed++;
                regularCount++;
                passengerServed = true;
                
                // Calculate waiting time
                nextPassenger.waitingTime = currentTime - nextPassenger.arrivalTime;
                totalRegularWaitTime += nextPassenger.waitingTime;
                
                cout << "Time " << currentTime << ": Serving Regular Customer #" << nextPassenger.id 
                     << " (waited " << nextPassenger.waitingTime << " minutes)\n";
                
                // Check if we should switch to frequent flyers
                if (regularCount >= regularRatio) {
                    regularCount = 0;
                    serveRegular = false;
                }
            } else {
                // No regular customers, try to serve frequent flyer
                serveRegular = false;
                regularCount = 0;
            }
        }
        
        if (!serveRegular && !passengerServed) {
            if (!frequentFlyerLine.empty()) {
                nextPassenger = frequentFlyerLine.front();
                frequentFlyerLine.pop();
                frequentFlyerServed++;
                frequentFlyerCount++;
                passengerServed = true;
                
                // Calculate waiting time
                nextPassenger.waitingTime = currentTime - nextPassenger.arrivalTime;
                totalFrequentFlyerWaitTime += nextPassenger.waitingTime;
                
                cout << "Time " << currentTime << ": Serving Frequent Flyer #" << nextPassenger.id 
                     << " (waited " << nextPassenger.waitingTime << " minutes)\n";
                
                // Check if we should switch to regular customers
                if (frequentFlyerCount >= frequentFlyerRatio) {
                    frequentFlyerCount = 0;
                    serveRegular = true;
                }
            } else {
                // No frequent flyers, try to serve regular customer
                serveRegular = true;
                frequentFlyerCount = 0;
                
                // Try again in the next iteration
                if (!passengerServed && regularLine.empty()) {
                    currentTime++;
                    continue;
                }
            }
        }
        
        // If no passenger was served from either line
        if (!passengerServed) {
            // Try the other line if current preference is empty
            if (serveRegular && regularLine.empty() && !frequentFlyerLine.empty()) {
                nextPassenger = frequentFlyerLine.front();
                frequentFlyerLine.pop();
                frequentFlyerServed++;
                
                // Calculate waiting time
                nextPassenger.waitingTime = currentTime - nextPassenger.arrivalTime;
                totalFrequentFlyerWaitTime += nextPassenger.waitingTime;
                
                cout << "Time " << currentTime << ": Serving Frequent Flyer #" << nextPassenger.id 
                     << " (waited " << nextPassenger.waitingTime << " minutes)\n";
                
                passengerServed = true;
            } else if (!serveRegular && frequentFlyerLine.empty() && !regularLine.empty()) {
                nextPassenger = regularLine.front();
                regularLine.pop();
                regularServed++;
                
                // Calculate waiting time
                nextPassenger.waitingTime = currentTime - nextPassenger.arrivalTime;
                totalRegularWaitTime += nextPassenger.waitingTime;
                
                cout << "Time " << currentTime << ": Serving Regular Customer #" << nextPassenger.id 
                     << " (waited " << nextPassenger.waitingTime << " minutes)\n";
                
                passengerServed = true;
            } else {
                // No one in either line, just advance time
                currentTime++;
                continue;
            }
        }
        
        // Advance time by service time
        currentTime += nextPassenger.serviceTime;
    }
    
    // Print statistics
    cout << "\nResults for " << regularRatio << ":" << frequentFlyerRatio << " Ratio Strategy:\n";
    cout << "Regular Customers Served: " << regularServed << endl;
    cout << "Frequent Flyers Served: " << frequentFlyerServed << endl;
    
    double avgRegularWaitTime = regularServed > 0 ? (double)totalRegularWaitTime / regularServed : 0;
    double avgFrequentFlyerWaitTime = frequentFlyerServed > 0 ? (double)totalFrequentFlyerWaitTime / frequentFlyerServed : 0;
    
    cout << "Average Wait Time for Regular Customers: " << fixed << setprecision(2) << avgRegularWaitTime << " minutes\n";
    cout << "Average Wait Time for Frequent Flyers: " << fixed << setprecision(2) << avgFrequentFlyerWaitTime << " minutes\n";
}

int main() {
    int numRegularCustomers, numFrequentFlyers, simulationTime;
    
    cout << "===== We Fly Anywhere Airlines (WFAA) Ticketing Simulation =====\n\n";
    
    cout << "Enter the number of regular customers: ";
    cin >> numRegularCustomers;
    
    cout << "Enter the number of frequent flyers: ";
    cin >> numFrequentFlyers;
    
    cout << "Enter the simulation time (in minutes): ";
    cin >> simulationTime;
    
    // Create queues for both types of passengers
    queue<Passenger> regularLine;
    queue<Passenger> frequentFlyerLine;
    
    // Generate regular customers with random arrival and service times
    cout << "\nGenerating " << numRegularCustomers << " regular customers...\n";
    for (int i = 1; i <= numRegularCustomers; i++) {
        Passenger passenger;
        passenger.id = i;
        passenger.isFrequentFlyer = false;
        passenger.arrivalTime = generateRandomNumber(0, simulationTime / 2); // Arrive in first half of simulation
        passenger.serviceTime = generateRandomNumber(1, 10); // Service takes 1-10 minutes
        passenger.waitingTime = 0;
        
        regularLine.push(passenger);
        cout << "Regular Customer #" << i << " arrives at time " << passenger.arrivalTime 
             << " with service time " << passenger.serviceTime << " minutes\n";
    }
    
    // Generate frequent flyers with random arrival and service times
    cout << "\nGenerating " << numFrequentFlyers << " frequent flyers...\n";
    for (int i = 1; i <= numFrequentFlyers; i++) {
        Passenger passenger;
        passenger.id = i;
        passenger.isFrequentFlyer = true;
        passenger.arrivalTime = generateRandomNumber(0, simulationTime / 2); // Arrive in first half of simulation
        passenger.serviceTime = generateRandomNumber(1, 10); // Service takes 1-10 minutes
        passenger.waitingTime = 0;
        
        frequentFlyerLine.push(passenger);
        cout << "Frequent Flyer #" << i << " arrives at time " << passenger.arrivalTime 
             << " with service time " << passenger.serviceTime << " minutes\n";
    }
    
    // Make copies of the queues for each strategy
    queue<Passenger> regularLine1 = regularLine;
    queue<Passenger> frequentFlyerLine1 = frequentFlyerLine;
    
    queue<Passenger> regularLine2 = regularLine;
    queue<Passenger> frequentFlyerLine2 = frequentFlyerLine;
    
    queue<Passenger> regularLine3 = regularLine;
    queue<Passenger> frequentFlyerLine3 = frequentFlyerLine;
    
    queue<Passenger> regularLine4 = regularLine;
    queue<Passenger> frequentFlyerLine4 = frequentFlyerLine;
    
    // Run simulation with different strategies
    cout << "\n\n======= BEGINNING SIMULATION =======\n";
    
    // Strategy 1: Alternate between regular and frequent flyer lines
    alternateLineStrategy(regularLine1, frequentFlyerLine1, simulationTime);
    
    // Strategy 2: Serve frequent flyers first until their line is empty
    frequentFlyerPriorityStrategy(regularLine2, frequentFlyerLine2, simulationTime);
    
    // Strategy 3: Serve regular customers first until their line is empty
    regularPriorityStrategy(regularLine3, frequentFlyerLine3, simulationTime);
    
    // Strategy 4: Serve 3 regular customers, then 1 frequent flyer
    ratioStrategy(regularLine4, frequentFlyerLine4, simulationTime, 3, 1);
    
    return 0;
}


