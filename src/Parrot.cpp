#include "../include/Parrot.h"
#include <chrono>
#include <thread>
#include <chrono>
#include <random>

using namespace std;

#define COLOR_RED "\033[1;41m"
#define COLOR_GREEN "\033[1;42m"
#define COLOR_BLUE "\033[1;44m"
#define COLOR_YELLOW "\033[1;43m"
#define COLOR_YELLOW_FOREGROUND "\033[1;36m"

namespace ParrotDomain{

    ///////////////////      Mersenne Twister Engine (random generator)     ////////////////////////////////

    std::random_device rd;
    std::mt19937 gen(rd());

    //some number distributors to play around with
    std::uniform_real_distribution<double> sleep_distributor(-0.5, 1.5);    //sleep timer
    std::uniform_real_distribution<double> playTime_distributor(2.0, 10.0);
    std::uniform_real_distribution<double> mumblechance(1, 20);  // dnd style chance calculation (D20 ; 20 = 5%)
    std::uniform_real_distribution<double> playfullness(1, 20);
    std::uniform_real_distribution<double> *bathneed = &playfullness;  //distributor can be pointer   
    std::uniform_real_distribution<double> *bathtime_distributor = &playTime_distributor;  //distributor can be pointer  

    /////////////////////////////////////////////////////////////////////////////////////////////////////////

    Parrot::Parrot(ParrotColor color, int threadId, Toybox *box, BirdBath *bath) : color_(color), threadId_(threadId), toybox_(box), bath_(bath) {}

    string Parrot::getColor() const {
        switch (color_) {
            case RED:
                return COLOR_RED;
            case GREEN:
                return COLOR_GREEN;
            case BLUE:
                return COLOR_BLUE;
            case YELLOW:
                return COLOR_YELLOW;
            default:
                return "Unknown";
        }
    }

    //////////////////////////////       Parrot main working function       /////////////////////////////
    void Parrot::run(){

        //parrot lifecycle. certain activities will be more likely to occure based on parrot's internal state 
        while (true) {

            //parrot takes a moment to think ..
            double delay = 1.0 + sleep_distributor(gen);
            std::this_thread::sleep_for(std::chrono::duration<double>(delay));

            //mumble chance 10 % as per DND dice roll
            if(mumblechance(gen) >= 19)  mumble();

            if(!skipcycle_){    //can parrot act?

                //boredom will increment over time
                if(playfullness(gen) + boredom_++ >= 19)  play();

                //random distributor used pointer style
                if((*bathneed)(gen) >= 19) bath();

            }
            else{
                skipcycle_--;
            }


        }

    }
    //////////////////////////////////////////////////////////////////////////////////////////////////////


    void Parrot::mumble(){
        fprintf(stdout, "%s[ ? ] The parrot is mumbling (Thread %i)\033[0m\n", getColor().c_str(), threadId_); 
    }

    void Parrot::play(){

            if(toybox_ == nullptr)
                return;

            if(toybox_->try_acquire()){

                fprintf(stdout, "%s[ + ] Parrot %i is playing with the toybox ..\033[0m\n", toybox_->getColour().c_str(), threadId_);
                std::this_thread::sleep_for(std::chrono::duration<double>(3.0 + playTime_distributor(gen)));
                fprintf(stdout, "%s[ - ] Parrot %i finished playing ..\033[0m\n", toybox_->getColour().c_str(), threadId_);
                boredom_ = 0;
                toybox_->release();
            }
    }

    void Parrot::bath(){

            if(bath_ == nullptr)
                    return;

        
            if(bath_->try_acquire()){

                fprintf(stdout, "%s[ + ] Parrot %i is taking a bath ..\033[0m\n", COLOR_YELLOW_FOREGROUND, threadId_);
                std::this_thread::sleep_for(std::chrono::duration<double>(5.0 + (*bathtime_distributor)(gen)));
                fprintf(stdout, "%s[ - ] Parrot %i finished taking a bath ..\033[0m\n", COLOR_YELLOW_FOREGROUND, threadId_);
                bath_->release();
            }

            //parrot needs some time to dry
            skipcycle_ = 4;

    }
}