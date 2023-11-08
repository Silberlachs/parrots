#include "../include/Parrot.h"
#include <chrono>
#include <thread>
#include <chrono>
#include <random>

using namespace std;

namespace ParrotDomain{

    // Mersenne Twister Engine
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(-0.5, 1.5);

    Parrot::Parrot(): color_(RED){}

    Parrot::Parrot(ParrotColor color, int threadId, Toybox *box) : color_(color), threadId_(threadId), toybox_(box) {
        
    }

    void Parrot::mumble(){
        fprintf(stdout, "[ ? ] The %s parrot is mumbling (Thread %i)\n", getColor().c_str(), threadId_); 
    }

    string Parrot::getColor() const {
        switch (color_) {
            case RED:
                return "Red";
            case GREEN:
                return "Green";
            case BLUE:
                return "Blue";
            case YELLOW:
                return "Yellow";
            default:
                return "Unknown";
        }
    }

    void Parrot::run(){

        while (true) {

            if(toybox_->try_acquire()){

                fprintf(stdout, "%s[ + ] Parrot %i is playing with the toybox ..\033[0m\n", toybox_->getColour().c_str(), threadId_);
                std::this_thread::sleep_for(std::chrono::duration<double>(5.0));
                fprintf(stdout, "%s[ - ] Parrot %i finished playing ..\033[0m\n", toybox_->getColour().c_str(), threadId_);
                toybox_->release();
            }


            //mumble chance 75 % ??
            if(0.75 - dis(gen) >= 0)  mumble();

            // Generate a random delay between -0.5 and 1.5 seconds
            double delay = 1.0 + dis(gen);
            std::this_thread::sleep_for(std::chrono::duration<double>(delay));
        }

    }

}