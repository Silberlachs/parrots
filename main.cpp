#include <stdio.h>
#include <thread>
#include <vector>
#include <chrono>
#include <random>
#include "include/Parrot.h"
#include "include/Toybox.h"

using namespace ParrotDomain;
using namespace std;

// Parrot factory
Parrot createParrot(ParrotColor color, int parrotCounter, Toybox *box) {
    return Parrot(color, parrotCounter, box);
}

int main()
{
    vector<thread> parrotThreads;

    // Create a random number generator for colorc++
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> colorDistribution(0, 3);

    Toybox box;

    ParrotColor parrotColor;
    for (int i = 0; i < 10; i++) {

        switch (colorDistribution(gen)) {
            case 0:
                parrotColor = RED;
                break;
            case 1:
                parrotColor = BLUE;
                break;
            case 2:
                parrotColor = GREEN;
                break;
            case 3:
                parrotColor = YELLOW;
                break;
        }

        parrotThreads.push_back(thread (&Parrot::run, createParrot(parrotColor, i, &box)));  
    }

    for (thread &t : parrotThreads) {
        t.join();
    }

    return 0;
}