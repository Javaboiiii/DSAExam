// 28.	An operating system assigns job to print queues based on the number of pages to be printed (1 to 50 pages).
//  You may assume that the system printers are able to print 10 page per minute. Smaller print jobs are printed before
//  larger print jobs and print jobs are processed from a single print queue implemented as a priority queue). The
//  system administrators would like to compare the time required to process a set of print jobs using 1, 2,
//  or 3 system printers. Write a program which simulates processing 100 print jobs of varying lengths using either 1, 2
// , or 3 printers. Assume that a print request is made every minute and that the number of pages to print varies
//  from 1 to 50 pages. To be fair, you will need to process the same set of print jobs each time you add
//  a printer. The output from your program should indicate the order in which the jobs were received, the
//  order in which they were printed, and the time required to process the set of print jobs. If more than one
//  printer is being used, indicate which printer each job was printed on.
// (Hint: Can implement job queue using suitable queue data structure)

#include <iostream>
#include <queue>
#include <vector>
#include <random>
#include <algorithm>
#include <iomanip>
#include <climits>  // For INT_MAX
using namespace std;

// Structure to represent a print job
struct PrintJob {
    int jobId;         // Unique job identifier
    int pages;         // Number of pages to print
    int arrivalTime;   // Time when the job arrived
    int startTime;     // Time when printing started
    int finishTime;    // Time when printing completed
    int printerId;     // Which printer processed the job
};

// Custom comparator for priority queue (smallest number of pages first)
struct CompareJobs {
    bool operator()(const PrintJob& j1, const PrintJob& j2) {
        return j1.pages > j2.pages; // Min heap based on number of pages
    }
};

// Function to generate random print jobs
vector<PrintJob> generatePrintJobs(int numJobs) {
    vector<PrintJob> jobs;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> pageDist(1, 50); // 1 to 50 pages
    
    for (int i = 0; i < numJobs; i++) {
        PrintJob job;
        job.jobId = i + 1;
        job.pages = pageDist(gen);
        job.arrivalTime = i; // One job arrives every minute
        job.startTime = -1;  // Not started yet
        job.finishTime = -1; // Not finished yet
        job.printerId = -1;  // Not assigned yet
        
        jobs.push_back(job);
    }
    
    return jobs;
}

// Function to simulate printing with a specific number of printers
void simulatePrinters(vector<PrintJob> jobs, int numPrinters) {
    cout << "\n=== Simulation with " << numPrinters << " printer" << (numPrinters > 1 ? "s" : "") << " ===\n";
    
    // Create a priority queue for the print jobs
    priority_queue<PrintJob, vector<PrintJob>, CompareJobs> jobQueue;
    
    // Create a vector to store the available time for each printer
    vector<int> printerAvailableTime(numPrinters, 0);
    
    int currentTime = 0;
    int jobsCompleted = 0;
    vector<PrintJob> completedJobs;
    
    // Continue until all jobs are processed
    while (jobsCompleted < jobs.size()) {
        // Add new jobs that have arrived by current time
        while (currentTime < jobs.size() && jobs[currentTime].arrivalTime <= currentTime) {
            jobQueue.push(jobs[currentTime]);
            currentTime++;
        }
        
        // If no jobs have arrived yet, advance time
        if (jobQueue.empty() && currentTime < jobs.size()) {
            currentTime = jobs[currentTime].arrivalTime;
            continue;
        }
        
        // Find an available printer
        bool printerAssigned = false;
        for (int i = 0; i < numPrinters; i++) {
            if (!jobQueue.empty() && printerAvailableTime[i] <= currentTime) {
                // Get the next job (smallest first)
                PrintJob currentJob = jobQueue.top();
                jobQueue.pop();
                
                // Assign this printer to the job
                currentJob.printerId = i + 1;
                currentJob.startTime = currentTime;
                currentJob.finishTime = currentTime + (currentJob.pages + 9) / 10; // Ceiling division (pages / 10)
                
                // Update printer availability
                printerAvailableTime[i] = currentJob.finishTime;
                
                // Add to completed jobs
                completedJobs.push_back(currentJob);
                jobsCompleted++;
                
                printerAssigned = true;
            }
        }
        
        // If no printer was assigned, advance time to the next printer availability
        if (!printerAssigned && jobsCompleted < jobs.size()) {
            int nextTime = INT_MAX;
            for (int i = 0; i < numPrinters; i++) {
                if (printerAvailableTime[i] < nextTime) {
                    nextTime = printerAvailableTime[i];
                }
            }
            
            if (nextTime > currentTime) {
                currentTime = nextTime;
            } else {
                currentTime++; // Ensure time advances
            }
        }
    }
    
    // Calculate total time (when the last job finishes)
    int totalTime = 0;
    for (const auto& job : completedJobs) {
        totalTime = max(totalTime, job.finishTime);
    }
    
    // Sort completed jobs by finish time
    sort(completedJobs.begin(), completedJobs.end(), 
         [](const PrintJob& a, const PrintJob& b) { return a.finishTime < b.finishTime; });
    
    // Print results
    cout << "Total time to process all jobs: " << totalTime << " minutes\n\n";
    
    cout << "Order Received vs. Order Printed:\n";
    cout << "--------------------------------------------------------------\n";
    cout << left << setw(10) << "Job ID" << setw(15) << "Pages" << setw(15) 
         << "Arrival Time" << setw(15) << "Finish Time" << setw(10) << "Printer" << endl;
    cout << "--------------------------------------------------------------\n";
    
    for (const auto& job : completedJobs) {
        cout << left << setw(10) << job.jobId << setw(15) << job.pages << setw(15) 
             << job.arrivalTime << setw(15) << job.finishTime << setw(10) << job.printerId << endl;
    }
    cout << "--------------------------------------------------------------\n";
}

int main() {
    const int NUM_JOBS = 100;
    
    cout << "Print Job Simulation\n";
    cout << "====================\n";
    cout << "Generating " << NUM_JOBS << " random print jobs...\n";
    
    // Generate the same set of print jobs for all simulations
    vector<PrintJob> jobs = generatePrintJobs(NUM_JOBS);
    
    // Display job information
    cout << "\nPrint Jobs Generated:\n";
    cout << "-------------------------------\n";
    cout << left << setw(10) << "Job ID" << setw(15) << "Pages" << setw(15) << "Arrival Time" << endl;
    cout << "-------------------------------\n";
    
    for (const auto& job : jobs) {
        cout << left << setw(10) << job.jobId << setw(15) << job.pages << setw(15) << job.arrivalTime << endl;
    }
    
    // Run simulations with 1, 2, and 3 printers
    simulatePrinters(jobs, 1);
    simulatePrinters(jobs, 2);
    simulatePrinters(jobs, 3);
    
    return 0;
}
