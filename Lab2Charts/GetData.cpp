#include "GetData.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "interpolation.h"

//#include "../libs/ALGLIB/src/interpolation.cpp"



float getMax(vector<pair<int, float>>* current_array, float* MAX) {
    float max = *MAX;
    for (size_t i = 0; i < current_array->size(); i++){
        if (max < (*current_array)[i].second) max = (*current_array)[i].second;
    }
    *MAX = max;
    return max;
}
float getMin(vector<pair<int, float>>* current_array, float* MIN) {
    float min = *MIN;
    for (size_t i = 0; i < current_array->size(); i++) {
        if (min > (*current_array)[i].second) min = (*current_array)[i].second;
    }
    *MIN = min;
    return min;
}
float getAverage(vector<pair<int, float>>* current_array, float* AVERAGE) {
    float av = *AVERAGE;
    if (*AVERAGE == 0) {
        float summ = 0;
        for (size_t i = 0; i < current_array->size(); i++){
            summ += (*current_array)[i].second;
        }
        av = summ / current_array->size();
    }
    else {
        float summ = 0;
        for (size_t i = 0; i < current_array->size(); i++) {
            summ += (*current_array)[i].second;
        }
        av = (av + summ / current_array->size()) / 2;
    }
    *AVERAGE = av;
    return av;
}


double average(double a, double b, double c) {
    
    return max(min(a, b), min(b, c));
}

double filter(double a, double b, double c) {
    const double epsilon = 1.005;
    const double approximation_coefficient = 0.5;
    if (a > epsilon * b || a > epsilon * c) return approximation_coefficient * (b + c);
    else if (b > epsilon * a || b > epsilon * c) return approximation_coefficient * (a + c);
    else if (c > epsilon * b || c > epsilon * a) return approximation_coefficient * (b + a);
    else return average(a, b, c);
}


void processing_results(vector<pair<int, float>>* current_array) {

    //approximation(current_array);

    for (size_t i = 1; i < current_array->size() - 1; i++){
        (*current_array)[i].second = filter((*current_array)[i - 1].second, (*current_array)[i].second, (*current_array)[i + 1].second);
    }
}


vector<pair<int, float>> getTimePoints__Add(int count) {
    vector<pair<int, float>> DATA; 
    for (int i = 0; i < count; i++) {
        BST<int>* tree = new BST<int>();
        auto begin = std::chrono::steady_clock::now();
        for (int j = 0; j < i; j++)
            tree->Insert(j);
        auto end = std::chrono::steady_clock::now();
        auto elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
        DATA.push_back({ i + 1, std::chrono::duration<double>(elapsed_ms).count() });
        tree->clear();
    }
    processing_results(&DATA);
    return DATA;
}

vector<pair<int, float>> getTimePoints__Find(int count) {
    vector<pair<int, float>> DATA; 
    for (int i = 0; i < count; i++) {
        BST<int>* tree = new BST<int>();
        for (int j = 0; j < i; j++)
            tree->Insert(j);
        auto begin = std::chrono::steady_clock::now();
        for (int j = 0; j < i; j++)
            tree->Find(j);
        auto end = std::chrono::steady_clock::now();
        auto elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
        DATA.push_back({ i + 1, std::chrono::duration<double>(elapsed_ms).count() });
        tree->clear();
    }
    processing_results(&DATA);
    return DATA;
}

vector<pair<int, float>> getTimePoints__Remove(int count) {
    vector<pair<int, float>> DATA; 
    for (int i = 0; i < count; i++) {
        BST<int>* tree = new BST<int>();
        for (int j = 0; j < i; j++)
            tree->Insert(j);
        auto begin = std::chrono::steady_clock::now();
        for (int j = i; j > 0; j--)
            tree->Remove(j);
        auto end = std::chrono::steady_clock::now();
        auto elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
        DATA.push_back({ i + 1, std::chrono::duration<double>(elapsed_ms).count() });
        tree->clear();
    }
    processing_results(&DATA);
    return DATA;
}


vector<pair<int, float>> getTimePoints__Balancing(int count) {
    vector<pair<int, float>> DATA; 
    for (int i = 0; i < count; i++) {
        BST<int>* tree = new BST<int>();
        for (int j = 0; j < i; j++)
            tree->Insert(j);
        auto begin = std::chrono::steady_clock::now();
        tree->Balancing();
        auto end = std::chrono::steady_clock::now();
        auto elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
        DATA.push_back({ i + 1, std::chrono::duration<double>(elapsed_ms).count() });
        tree->clear();
    }
    processing_results(&DATA);
    return DATA;
}