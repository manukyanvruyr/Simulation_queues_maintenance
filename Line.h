#pragma once

#include <queue>
#include "Customer.h"

class Line {
public:
    void push(Customer customer);
    void pop(int minutes);
    unsigned int getMaxNumber() const;
    unsigned int getLongestWait() const;

private:
    std::queue<Customer> queue;
    unsigned int maxNumber = 0;
    unsigned int longestWait = 0;
    unsigned int currentWait = 0;
};
