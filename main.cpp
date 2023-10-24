#include <stdio.h>
#include <thread>
#include <vector>
#include <chrono>
#include <random>
#include "include/Parrot.h"

using namespace ParrotDomain;
using namespace std;

// Parrot factory
Parrot createParrot(ParrotColor color, int parrotCounter) {
    return Parrot(color, parrotCounter);
}

int main()
{
    vector<thread> parrotThreads;

    // Create a random number generator for color
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> colorDistribution(0, 3);

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

        fprintf(stdout, "DEBUG running loop #%i DEBUG\n",i);
        parrotThreads.push_back(thread (&Parrot::run, createParrot(parrotColor, i)));  
    }

    for (thread &t : parrotThreads) {
        t.join();
    }

    return 0;
}