#ifndef Parrot_H
#define Parrot_H

#include <string>
#include "Toybox.h"

namespace ParrotDomain{

    enum ParrotColor {RED, BLUE, GREEN, YELLOW};

    class Parrot{
        public:
            Parrot(ParrotColor color, int thradId, Toybox *box);
            std::string getColor() const;
            void run(void);

        private:
            ParrotColor color_;
            int threadId_;
            int boredom_;
            Toybox *toybox_;
            void mumble(void);
            void play(void);

    };
}
#endif