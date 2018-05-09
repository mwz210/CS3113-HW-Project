#pragma once

#include <vector>
#include <utility>
#include <algorithm>

bool CheckSATCollision(const std::vector<std::pair<float, float>> &e1Points, const std::vector<std::pair<float, float>> &e2Points, std::pair<float, float> &penetration);
