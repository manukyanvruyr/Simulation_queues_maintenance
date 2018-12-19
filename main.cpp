#include <iostream>
#include <thread>
#include <future>
#include <fstream>

#include "Line.h"
#include "Customer.h"

std::string getCurrentTime() {
    time_t theTime = time(nullptr);
    struct tm *time = localtime(&theTime);
    return std::to_string(time->tm_hour) + ":" + std::to_string(time->tm_min) + "\n";
}

std::string simulate(int arrivalMinute) {
    Line line;
    srand(time(nullptr));
    std::string output;

    output += "Start time ";
    output += getCurrentTime();

    auto start = std::chrono::system_clock::now();
    auto end = std::chrono::system_clock::now();
    end += std::chrono::hours(2);
    //end += std::chrono::minutes(2);

    while (true) {
        Customer customer(1 + rand() % arrivalMinute, 1 + rand() % 4);
        auto now = std::chrono::system_clock::now();
        now += std::chrono::minutes(customer.arriveMinutes);
        //now += std::chrono::seconds(customer.arriveMinutes);
        if (now > end) {
            break;
        }
        std::this_thread::sleep_for(std::chrono::seconds(customer.arriveMinutes));
        line.pop(customer.arriveMinutes);
        line.push(customer);
    }

    output += "End time ";
    output += getCurrentTime();
    output += "The maximum number of customers in the queue is " + std::to_string(line.getMaxNumber()) + "\n";
    output += "The longest wait before serving is " + std::to_string(line.getLongestWait()) + " minutes\n";
    return output;
}

int main() {
    auto f = std::async(std::launch::async, simulate, 3); // run with 3 minutes arrival interval in other thread;
    std::string fourMinutes = simulate(4);

    // If you want to print into output file uncomment the next 2 lines
    //std::ofstream out("output.txt");
    //std::cout.rdbuf(out.rdbuf()); // redirect std::cout to output.txt

    std::cout << "Results for customers arrival interval 1-4 minutes:\n";
    std::cout << fourMinutes;

    std::cout << std::endl;
    std::cout << "Results for customers arrival interval 1-3 minutes:\n";
    std::cout << f.get();
    return 0;
}
