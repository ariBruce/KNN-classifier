#include <cmath>
#include <iostream>
#include <vector>
#include "DistancesCalculate.hpp"
using namespace std;

/*
    This class calculate diffrenet ways of distances between 2 vectors
*/

//constructor
DistancesCalculate::DistancesCalculate(vector<double> &get_vec1)
{
    //unclassify vector
    vec1 = get_vec1;
}

DistancesCalculate::~DistancesCalculate()
{
}


// calculate the euclidean distance
double DistancesCalculate::VectorEuclideanDistance(vector<double> &vec2)
{
    double temp = 0;
    double num;
    for (int i = 0; i < this->vec1.size(); ++i)
    {
        num = this->vec1[i] - vec2[i];
        temp += pow(num, 2);
    }

    return sqrt(temp);
};

// calculate the canberra distance
double DistancesCalculate::VectorCanberraDistance(vector<double> &vec2)
{
    double temp = 0;
    double num;
    for (int i = 0; i < this->vec1.size(); ++i)
    {
        num = abs(this->vec1[i] - vec2[i]);
        if ((abs(this->vec1[i]) + abs(vec2[i])) != 0)
        {
            num = num / (abs(this->vec1[i]) + abs(vec2[i]));
            temp += num;
        }
    }
    return temp;
};

// calculate the Manhattan distance
double DistancesCalculate::VectorManhattanDistance(vector<double> &vec2)
{
    double temp = 0;
    double num;
    for (int i = 0; i < this->vec1.size(); ++i)
    {
        num = abs(this->vec1[i] - vec2[i]);
        if (num != 0)
        {
            temp += num;
        }
    }
    return temp;
};

// calculate the Chebyshev distance
double DistancesCalculate::VectorChebyshevDistance(vector<double> &vec2)
{
    double temp = 0;
    double num;
    for (int i = 0; i < this->vec1.size(); ++i)
    {
        num = abs(this->vec1[i] - vec2[i]);
        if (num > temp)
        {
            temp = num;
        }
    }
    return temp;
};

// calculate the Minkowski  distance
double DistancesCalculate::VectorMinkowskiDistance(vector<double> &vec2, double p)
{
    double temp = 0;
    double num;
    for (int i = 0; i < this->vec1.size(); ++i)
    {
        num = abs(this->vec1[i] - vec2[i]);
        temp += pow(num, p);
    }

    return pow(temp, 1.0 / p);
};