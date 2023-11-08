#include "../include/Toybox.h"

namespace ParrotDomain{

    void Toybox::release() {
        std::lock_guard<decltype(mutex_)> lock(mutex_);
        if(count_ < max_slots_)
            ++count_;
        condition_.notify_one();
    }

    void Toybox::acquire() {
        std::unique_lock<decltype(mutex_)> lock(mutex_);
        while(!count_) // Handle spurious wake-ups.
            condition_.wait(lock);
        --count_;
    }

    bool Toybox::try_acquire() {
        std::lock_guard<decltype(mutex_)> lock(mutex_);
        if(count_) {
            --count_;
            return true;
        }
        return false;
    }
}