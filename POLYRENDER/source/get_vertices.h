#include <iostream>
#include <vector>
using std::vector;
using std::string;

extern vector<float> view;
extern vector<vector<vector<float>>> get_cube(vector<float> color);
extern vector<vector<vector<float>>> get_tetra(vector<float> color);
extern vector<vector<vector<float>>> get_pyra(vector<float> color);
vector<vector<vector<float>>> transform(vector<vector<vector<float>>> geometry, vector<float> scale, vector<float> COM, vector<float> rotate, vector<int> rotate_order);