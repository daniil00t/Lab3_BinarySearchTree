#pragma once
#include <vector>
#include "../Lab3_BinaryTree/BST.h"
#include <chrono>

using namespace std;
using namespace MAIN;

vector<pair<int, float>> getTimePoints__Add(int count);
vector<pair<int, float>> getTimePoints__Remove(int count);
vector<pair<int, float>> getTimePoints__Find(int count);
vector<pair<int, float>> getTimePoints__Balancing(int count);