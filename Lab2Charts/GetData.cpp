#include "GetData.h"

double average(double a, double b, double c) {
    return max(min(a, b), min(b, c));
}

double filter(double a, double b, double c) {
    const double epsilon = 1.2;
    const double approximation_coefficient = 0.5;
    if (a > epsilon * b || a > epsilon * c) return approximation_coefficient * (b + c);
    else if (b > epsilon * a || b > epsilon * c) return approximation_coefficient * (a + c);
    else if (c > epsilon * b || c > epsilon * a) return approximation_coefficient * (b + a);
    else return average(a, b, c);
}


void processing_results(vector<pair<int, float>>* current_array) {
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
    }
    processing_results(&DATA);
    return DATA;
}