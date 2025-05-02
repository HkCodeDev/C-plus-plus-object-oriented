/*****************************************************************************
                  Workshop - #2 (Part - 2)>
Full Name : Hoda Karimi
Student ID# : 138611223
 Email : hkarimi9@myseneca.ca
 Section : NAA
 File: TimedTask.h
 Date:
    Authenticity Declaration :
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider.This submitted
piece of work is entirely of my own creation.
* ****************************************************************************/
#ifndef SENECA_TIMEDTASK_H
#define SENECA_TIMEDTASK_H

#include <chrono>
#include <string>
#include <iostream>
#include <iomanip>

namespace seneca {
    // Maximum number of tasks that can be recorded
    const int MAX_TASKS = 10;

    struct Task {
        std::string name;// Name of the task
        std::string units;// Measurement units for the task duration
        std::chrono::nanoseconds duration;// Duration of the task
        // Default constructor
        Task() : name(""), units("nanoseconds"), duration(0) {}
    };

    class TimedTask {
        int numRecords;// Current number of recorded tasks
        Task tasks[MAX_TASKS];// Array to store task records
        // Start time for measurement
        std::chrono::steady_clock::time_point startTime;
        // End time for measurement
        std::chrono::steady_clock::time_point endTime;

    public:
        TimedTask();// Constructor
        void startClock();// Start the timer
        void stopClock();// Stop the timer
        void addTask(const char* taskName); // Add a new task record
        // Output stream overload for printing tasks
        friend std::ostream& operator<<(std::ostream& os, const TimedTask& tt);
    };
}
#endif // TIMEDTASK_H
