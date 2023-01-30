#ifndef Knn_H_
#define Knn_H_

#include <vector>
#include "DistancesCalculate.hpp"
using namespace std;
//struct of the data from the csv
struct data_struct{std::string label; vector<double> points;};
/*
    This class is inheritance from the DistancesCalculate class
*/
class Knn : public DistancesCalculate
{
    public:
        int k;
        vector<double> unclassify_vec;
        string type;
        vector<string> k_nearest;
        using DistancesCalculate :: DistancesCalculate;

    Knn(int, vector<double>, string);
    ~Knn();
    //find the k closest labels to the unclassify vector
    void findKnearest(vector<data_struct> *mappings);
    //by the findKnearest the func will take the most common label and will predict it
    string predict();
    //the calculate distance by ask
    double distance(vector<double> &vec2);
    bool is_double(const std::string& s);
};

#endif
