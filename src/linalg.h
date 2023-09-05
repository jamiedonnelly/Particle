#ifndef LINALG_H
#define LINALG_H

#include<vector>
#include<string>

enum class ElementWiseOps{
    Addition,
    Subtraction,
    Multiplication,
    Maximum,
    Minimum
};

enum class UnaryOps{
    Addition, 
    Scaling
};

double magnitude(std::vector<double> v);

double innerProduct(std::vector<double> v1, std::vector<double> v2);

std::vector<double> BinaryVectorOp(ElementWiseOps op, std::vector<double> v1, std::vector<double> v2);

std::vector<double> UnaryVectorOp(UnaryOps op, std::vector<double> v, double c);

std::vector<double> UnaryVectorAdd(std::vector<double> v, double c);

std::vector<double> UnaryVectorScaling(std::vector<double> v, double c);

std::vector<double> BinaryVectorAdd(std::vector<double> v1, std::vector<double> v2);

std::vector<double> BinaryVectorSub(std::vector<double> v1, std::vector<double> v2);

std::vector<double> BinaryVectorMul(std::vector<double> v1, std::vector<double> v2);

std::vector<double> vectorNormal(std::vector<double> v1, std::vector<double> v2);


#endif