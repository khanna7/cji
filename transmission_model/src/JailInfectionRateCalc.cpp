#include <numeric>

#include "JailInfectionRateCalc.h"

JailInfRateCalculator::JailInfRateCalculator(unsigned int window_size, double multiplier, double default_rate) : 
    window_size_{window_size}, multiplier_{multiplier}, default_rate_(default_rate) {}

JailInfRateCalculator::~JailInfRateCalculator() {}

void JailInfRateCalculator::addInfectionRate(unsigned int infected, unsigned int uninfected) {
    if (rates.size() == window_size_) {
        rates.pop_front();
    }

    rates.push_back(uninfected == 0 ? 0 : ((double)infected) / uninfected);
}

double JailInfRateCalculator::calculateRate() {
    if (rates.size() == window_size_) {
        return std::accumulate(rates.begin(), rates.end(), 0.0) / rates.size() * multiplier_;
    } else {
        return default_rate_;
    }
}