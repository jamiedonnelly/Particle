#include<cmath>
#include "linalg.h"

double magnitude(std::vector<double> v){
    double result{};
    for (auto ref : v){
        result += pow(ref, 2);
    }
    return sqrt(result);
};

double innerProduct(std::vector<double> v1, std::vector<double> v2){
    double result{};
    for (int i=0; i<v1.size(); i++){
        result += v1[i]*v2[i];
    }
    return result;
};

std::vector<double> UnaryVectorOp(UnaryOps op, std::vector<double> v, double c){
    std::vector<double> results{};
    switch(op){
        case UnaryOps::Addition:
            for (int i=0; i<v.size(); i++){
                results.push_back(v[i]+c);
            }
            break;
        case UnaryOps::Scaling:
            for (int i=0; i<v.size(); i++){
                results.push_back(v[i]*c);
            }
            break;
    }
    return results;
};

std::vector<double> UnaryVectorAdd(std::vector<double> v, double c){
    return UnaryVectorOp(UnaryOps::Addition, v, c);
}

std::vector<double> UnaryVectorScaling(std::vector<double> v, double c){
    return UnaryVectorOp(UnaryOps::Scaling, v, c);
}

std::vector<double> BinaryVectorOp(ElementWiseOps op, std::vector<double> v1, std::vector<double> v2){
    std::vector<double> results{};
    switch(op){
        case ElementWiseOps::Addition:
            for (int i=0; i<v1.size(); i++){
                results.push_back(v1[i] + v2[i]);
            }
            break;
        case ElementWiseOps::Subtraction:
            for (int i=0; i<v1.size(); i++){
                results.push_back(v1[i] - v2[i]);
            }
            break;
        case ElementWiseOps::Multiplication:
            for (int i=0; i<v1.size(); i++){
                results.push_back(v1[i]*v2[i]);
            }
            break;
        case ElementWiseOps::Maximum:
            for (int i=0; i<v1.size(); i++){
                results.push_back(std::max(v1[i],v2[i]));
            }
            break;
        case ElementWiseOps::Minimum:
            for (int i=0; i<v1.size(); i++){
                results.push_back(std::min(v1[i],v2[i]));
            }
            break;
    }
    return results;
}

std::vector<double> BinaryVectorAdd(std::vector<double> v1, std::vector<double> v2){
    return BinaryVectorOp(ElementWiseOps::Addition, v1, v2);
};

std::vector<double> BinaryVectorSub(std::vector<double> v1, std::vector<double> v2){
    return BinaryVectorOp(ElementWiseOps::Subtraction, v1, v2);
};

std::vector<double> BinaryVectorMul(std::vector<double> v1, std::vector<double> v2){
    return BinaryVectorOp(ElementWiseOps::Multiplication, v1, v2);
};

std::vector<double> vectorNormal(std::vector<double> v1, std::vector<double> v2){
    std::vector<double> numerator = BinaryVectorSub(v1, v2);
    double denominator = magnitude(numerator);
    return UnaryVectorScaling(numerator, 1.0/denominator);
}