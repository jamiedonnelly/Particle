#include<chrono>
#include<cmath>
#include<thread>
#include<random>
#include "utils.h"

double randomvalue(double lower, double upper){
    std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_real_distribution<double> distribution(lower, upper);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    return distribution(generator);
}

std::vector<double> randomvector(int Nvals, double lower, double upper){
    std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_real_distribution<double> distribution(lower, upper);
    std::vector<double> results;
    for (int i=0; i<Nvals; i++){
        double val = distribution(generator);
        results.push_back(val);
    };
    return results;
};


