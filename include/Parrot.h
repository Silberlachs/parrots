#ifndef Parrot_H
#define Parrot_H

#include <string>

namespace ParrotDomain{

    enum ParrotColor {RED, BLUE, GREEN, YELLOW};

    class Parrot{
        public:
            Parrot();
            Parrot(ParrotColor color, int thradId);
            std::string getColor() const;
            void run(void);

        private:
            ParrotColor color_;
            int threadId_;
            void mumble(void);

    };
}
#endif