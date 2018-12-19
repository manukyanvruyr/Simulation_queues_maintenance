#include "Line.h"
#include <iostream>

void Line::push(Customer customer) {
    // calculate the longest wait
    if (currentWait > longestWait) {
        longestWait = currentWait;
    }

    queue.push(customer);

    // calculate the max number of customers
    if (queue.size() > maxNumber) {
        maxNumber = queue.size();
    }
    currentWait += customer.servingDuration;
}

void Line::pop(int minutes) {
    if (queue.empty()) {
        return;
    }

    // calculate the current wait
    if (minutes > currentWait) {
        currentWait = 0;
    } else {
        currentWait -= minutes;
    }

    while (minutes > 0 && !queue.empty()) {
        Customer& firstCustomer = queue.front();
        if (firstCustomer.servingDuration > minutes) {
            // first customer still serving
            firstCustomer.servingDuration -= minutes;
            break;
        } else {
            // first customer already served
            minutes -= firstCustomer.servingDuration;
            queue.pop();
        }
    }
}

unsigned int Line::getMaxNumber() const {
    return maxNumber;
}

unsigned int Line::getLongestWait() const {
    return longestWait;
}
