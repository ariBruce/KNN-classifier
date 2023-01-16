#ifndef DistanceCalculate_H_
#define DistanceCalculate_H_

#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

/*
    This class calculate diffrenet ways of distances between 2 vectors
*/
class DistancesCalculate
{
public:
    //the unclassify vector
    vector<double> vec1;
    
public:
    DistancesCalculate(vector<double> &get_vec1);
    ~DistancesCalculate();
    double VectorEuclideanDistance(vector<double> &get_vec2);
    double VectorCanberraDistance(vector<double> &get_vec2);
    double VectorManhattanDistance(vector<double> &get_vec2);
    double VectorChebyshevDistance(vector<double> &get_vec2);
    double VectorMinkowskiDistance(vector<double> &get_vec2, double p);

};

#endif