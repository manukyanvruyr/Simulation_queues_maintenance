#pragma once

struct Customer {
    Customer(int arriveMinutes, int servingDuration) :
    arriveMinutes(arriveMinutes), servingDuration(servingDuration)
    {}

    int arriveMinutes;
    int servingDuration;
};
