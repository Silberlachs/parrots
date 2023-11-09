#ifndef Parrot_H
#define Parrot_H

#include <string>
#include "Toybox.h"
#include "BirdBath.h"
#include "Foodbowl.h"

namespace ParrotDomain{

    enum ParrotColor {RED, BLUE, GREEN, YELLOW};

    class Parrot{
        public:
            Parrot(
                    ParrotColor color, 
                    int thradId, 
                    Toybox *box = nullptr, 
                    BirdBath *bath = nullptr, 
                    Foodbowl *foodbowl = nullptr
            );

            std::string getColor() const;
            void run(void);

        private:
            ParrotColor color_;
            int threadId_;
            int boredom_;
            int stomache_food_;
            int poopcounter_;
            int stamina_;
            int sleeptimer_;
            int skipcycle_ = 0;
            Toybox *toybox_ = nullptr;
            BirdBath *bath_ = nullptr;
            Foodbowl *foodbowl_ = nullptr;
            void mumble(void);
            void play(void);
            void bath(void);
            void poop(void);
            void eat(void);
            void sleep(void);
    };
}
#endif