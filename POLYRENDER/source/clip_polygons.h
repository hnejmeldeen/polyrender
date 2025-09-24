#include <iostream>
#include <vector>
using std::vector;
using std::string;

extern float tolerance;
extern vector<float> cross(vector<float> v1, vector<float> v2);
extern vector<float> intersect_line_plane(vector<float> N, vector<float> point0, vector<float> V, vector<float> point1);
extern bool mag(vector<vector<float>> face_A, vector<vector<float>> face_B, float tolerance);
extern vector<vector<vector<float>>> clip_geometry(vector<vector<vector<float>>> geometry);
