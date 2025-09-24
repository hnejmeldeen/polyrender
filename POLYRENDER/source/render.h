#include <iostream>
#include <vector>
using std::vector;
using std::string;

constexpr double pi = 3.141592653589793;
extern float FOV_x;
extern float FOV_y;
extern vector<float> to_perspective(vector<vector<vector<float>>> geometry, vector<float> camera_pos, float theta, float phi);
extern bool compare_faces(vector<vector<float>> face1, vector<vector<float>> face2);