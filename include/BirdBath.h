#ifndef BirdBath_H
#define BirdBath_H

#include <mutex>
#include <condition_variable>

namespace ParrotDomain{

    class BirdBath{

        public:
                void release(void);
                void acquire(void);
                bool try_acquire(void);

        private:
                std::mutex mutex_;
                std::condition_variable condition_;
                uint8_t count_ = 1;
                uint8_t max_slots_ = 1;
    };

}

#endif