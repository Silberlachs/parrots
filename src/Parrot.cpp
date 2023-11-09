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
#define COLOR_BLUE_FOREGROUND "\033[1;94m"

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
    std::uniform_real_distribution<double> *bathtime_distributor = &playTime_distributor;
    std::uniform_real_distribution<double> *poop_distributor = &playTime_distributor;
    std::uniform_real_distribution<double> food_distributor(0.0, 5.0); 
    std::uniform_real_distribution<double> stamina_distributor(15.0, 25.0); 

    /////////////////////////////////////////////////////////////////////////////////////////////////////////

    //multi purpose constructor that will accept nullptr 
    Parrot::Parrot(
            ParrotColor color, 
            int threadId, 
            Toybox *box, 
            BirdBath *bath, 
            Foodbowl *foodbowl
        ): 
            color_(color), 
            threadId_(threadId), 
            toybox_(box), 
            bath_(bath), 
            foodbowl_(foodbowl) 
        {
            stomache_food_  = 10 + (int)food_distributor(gen);
            poopcounter_    = (*poop_distributor)(gen);    //calling rng generator via pointer
            stamina_        = (int)stamina_distributor(gen);
            sleeptimer_      = stamina_;
        }

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

            if(!skipcycle_ && stamina_>0){    //can parrot act? (test against 0)

                if(!stomache_food_) eat();

                //boredom will increment over time
                if(playfullness(gen) + boredom_++ >= 19)  play();

                //random distributor used pointer style
                if((*bathneed)(gen) >= 19) bath();

            }
            else
                skipcycle_--;
            
            //a parrot needs to sleep as long as his stamina is completely refilled
            //sleeping has a various timing (sleep_distributor) and needs to update poopcounter
            //so we need to include it into our main working loop (and not as a member function)
            if(stamina_>0)
                stamina_--;
            else{
                sleeptimer_--;
                if(sleeptimer_ == 0){
                    stamina_ = (int)stamina_distributor(gen);
                    sleeptimer_ = stamina_;
                }
            }

            if(!poopcounter_--)
                poop();

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
                bath_->release();
            }

            //parrot needs some time to dry
            skipcycle_ = 6;
    }

    void Parrot::poop(){

        if(!stomache_food_)
            return;

        poopcounter_ = (int)(*poop_distributor)(gen);
        stomache_food_--;
    }

    void Parrot::eat(){

            if(foodbowl_ == nullptr || foodbowl_->is_empty())
                return;
        
            if(foodbowl_->try_acquire()){

                fprintf(stdout, "%s[ + ] Parrot %i is eating food ..\033[0m\n", COLOR_BLUE_FOREGROUND, threadId_);

                //give the parrot some randomness in how statiated it is
                int food_amount = foodbowl_->eat_from(10 + (int)food_distributor(gen));
                stomache_food_ = food_amount;

                //simulate the eating process ( 1 second per food unit )
                for ( int c = 0; c < food_amount; c++){
                    std::this_thread::sleep_for(std::chrono::duration<double>(1.0));
                }

                foodbowl_->release();
            }

            //parrot needs some time to rest after eating
            skipcycle_ = 4;
    }
}