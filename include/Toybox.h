#ifndef Toybox_H
#define Toybox_H

#include <mutex>
#include <condition_variable>
#include <string>

namespace ParrotDomain{

    class Toybox{

        public:
                Toybox(std::string colour);
                std::string getColour(void);
                void release(void);
                void acquire(void);
                bool try_acquire(void);

        private:
                std::string colour_;
                std::mutex mutex_;
                std::condition_variable condition_;
                uint8_t count_ = 2;
                uint8_t max_slots_ = 2;

    };

}

#endif