#include "../include/Foodbowl.h"

namespace ParrotDomain{

    Foodbowl::Foodbowl(int maxVal): maxVal_(maxVal){}

    void Foodbowl::fill(int amount){
        
        if(amount <= 0 || amount >= INT32_MAX)
            return;

        acquire();
        if((currVal_ + amount) > maxVal_)
            currVal_ = maxVal_;
        else
            currVal_+=amount;

        release();

    }

    int Foodbowl::eat_from(int amount){

        int retVal = amount;

        if(currVal_ - amount <= 0)
        {
            retVal = amount - currVal_;
            currVal_ = 0;
        }
        else
            currVal_-=amount;

        return retVal;
    }

    bool Foodbowl::is_empty(){
        return currVal_ == 0 ? true : false;
    }

    void Foodbowl::release() {
        std::lock_guard<decltype(mutex_)> lock(mutex_);
        if(count_ < max_slots_)
            ++count_;
        condition_.notify_one();
    }

    void Foodbowl::acquire() {
        std::unique_lock<decltype(mutex_)> lock(mutex_);
        while(!count_) // Handle spurious wake-ups.
            condition_.wait(lock);
        --count_;
    }

    bool Foodbowl::try_acquire() {
        std::lock_guard<decltype(mutex_)> lock(mutex_);
        if(count_) {
            --count_;
            return true;
        }
        return false;
    }
}