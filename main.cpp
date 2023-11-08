#include <stdio.h>
#include <thread>
#include <vector>
#include <chrono>
#include <random>
#include "include/Parrot.h"
#include "include/Toybox.h"
#include "include/BirdBath.h"

using namespace ParrotDomain;
using namespace std;

// Parrot factory
Parrot createParrot(ParrotColor color, int parrotCounter, Toybox *box = nullptr, BirdBath *bath = nullptr) {
    return Parrot(color, parrotCounter, box, bath);
}

int main()
{
    vector<thread> parrotThreads;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> colorDistribution(0, 3);

    Toybox box_1("\033[1;31m");
    Toybox box_2("\033[1;34m");

    ParrotDomain::BirdBath bath;

    ParrotColor parrotColor;
    for (int i = 0; i < 10; i++) {

        Toybox *boxPtr;

        switch (colorDistribution(gen)) {
            case 0:
                parrotColor = RED;
                boxPtr = &box_1;
                break;
            case 1:
                parrotColor = BLUE;
                boxPtr = &box_1;
                break;
            case 2:
                parrotColor = GREEN;
                boxPtr = &box_2;
                break;
            case 3:
                parrotColor = YELLOW;
                boxPtr = &box_2;
                break;
        }

        parrotThreads.push_back(thread (&Parrot::run, createParrot(parrotColor, i, boxPtr, &bath)));  
    }

    for (thread &t : parrotThreads) {
        t.join();
    }

    return 0;
}