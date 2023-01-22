#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <regex>
#include "Knn.hpp"
#include "DistancesCalculate.hpp"


using namespace std;

//class Knn inheritance DistanceCalculate
Knn::Knn(int value, vector<double> vec, string type_calc) : DistancesCalculate(vec)
{
    k = value;
    unclassify_vec = vec;
    vector<string> k_nearest;
    type = type_calc;
};



Knn::~Knn()
{
    //
};


/*
    find the k closest labels to the unclassify vector
*/
void Knn::findKnearest(vector<data_struct> *mappings){
    //create a struct for storing the lable and distance together
     struct distance_struct{
     int d_from_point;
     string my_lable;
    };
    vector<double> distances;
    vector<distance_struct> distance_structs;
    int orech = mappings->size();

    //itirate over map and find the correct distance from each lable and hold an array of them as well
    for (auto& element: *mappings)
    {
        distance_struct distance_labled;
        distance_labled.d_from_point = distance(element.points);
        distances.push_back(distance_labled.d_from_point);
        distance_labled.my_lable = element.label;
        distance_structs.push_back(distance_labled);
    }
    //sort array of distances and then find the five smallest in struct array and return thier lables
    sort(distances.begin(), distances.end());
    for(int i = 0; i < this->k; i++){
        for(int j = 0; j < mappings -> size(); j++)
        if (distances[i] == distance_structs[j].d_from_point){
            this->k_nearest.push_back(distance_structs[j].my_lable);
            j = mappings -> size();
        }
    }
};

/*
    after training, we can predict what the classify can be
*/
string Knn::predict(){
    sort(this->k_nearest.begin(), this->k_nearest.end());
    string predict_type;
    int repeats = 1;
    int most_repeated = 1;
    //check which label is the most repeated
    for(int i=0; i < k_nearest.size() - 1 ; i++){
        //if this label is more repeat labels than the previous
        if (this->k_nearest[i] == this->k_nearest[i + 1] && repeats > most_repeated) {
            predict_type = k_nearest[i];
            repeats++;
            most_repeated = repeats;
        //if there sre less repeats than the most_repeated
        } else if (this->k_nearest[i] == this->k_nearest[i + 1] && repeats <= most_repeated) {
            repeats++;
        //if the labels name are different
        } else if (this->k_nearest[i] != this->k_nearest[i + 1]) {
            repeats = 1;
        }
    }
    //the case where all names appear once enter the first by default
    if (predict_type == "") {
        predict_type = k_nearest[0];
    }
    return predict_type;
};

/*
    get the type of distance and 2 vectors
    return the distance between 2 vectors
*/
double Knn::distance(vector<double> &vec2)
{
    if (type == "AUC"){
        return this->VectorEuclideanDistance(vec2);
    } else if (type == "MAN"){
        return this->VectorManhattanDistance(vec2);
    } else if (type == "CHB"){
        return this->VectorChebyshevDistance(vec2);
    } else if (type == "CAN"){
        return this->VectorCanberraDistance(vec2);
    } else if (type == "MIN") {
        //check what to do about p
        return this->VectorMinkowskiDistance(vec2, 2.0);
    } 
    //exeption throwing
    else throw std::invalid_argument("INVALID DISTANCE NAME!");
};

bool Knn::is_double(const std::string& s) {
  std::regex double_regex("^[-+]?(0|[1-9][0-9]*)(\\.[0-9]+)?$");
  return std::regex_match(s, double_regex);
}
