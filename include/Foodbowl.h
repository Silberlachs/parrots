#ifndef Foodbowl_H
#define Foodbowl_H

#include <mutex>
#include <condition_variable>

namespace ParrotDomain{

    class Foodbowl{

        public:
                Foodbowl(int maxVal);
                void fill(int value);
                void release(void);
                void acquire(void);
                int eat_from(int amount);
                bool try_acquire(void);
                bool is_empty(void);

        private:
                int maxVal_;
                int currVal_;
                std::mutex mutex_;
                std::condition_variable condition_;
                uint8_t count_ = 1;
                uint8_t max_slots_ = 1;
    };

}

#endif