#include <iostream>
#include <vector>
#include <algorithm>
#include "clip_polygons.h"
using std::vector;
using std::string;
using std::cout;

float tolerance = 0.001;

vector<float> cross(vector<float> v1, vector<float> v2){
    vector<float> product;

    for (int i = 0; i < 3; i++){
        product.push_back(v1[(i+1)%3]*v2[(i+2)%3]-v1[(i+2)%3]*v2[(i+1)%3]);
    }
    
    return product;
}

vector<float> intersect_line_plane(vector<float> N, vector<float> point0, vector<float> V, vector<float> point1){
    float t = (N[0]*(point0[0]-point1[0])+N[1]*(point0[1]-point1[1])+N[2]*(point0[2]-point1[2])) / (N[0]*V[0] + N[1]*V[1] + N[2]*V[2]);
    return {V[0]*t+point1[0], V[1]*t+point1[1], V[2]*t+point1[2], point1[3], point1[4], point1[5]};
}

bool mag(vector<vector<float>> face_A, vector<vector<float>> face_B, float tolerance){

    bool no_overlap = false;

    for (int i = 0; i < 3; i++){
        float min_i_A = std::min({face_A[0][i],face_A[1][i],face_A[2][i]});
        float max_i_A = std::max({face_A[0][i],face_A[1][i],face_A[2][i]});

        float min_i_B = std::min({face_B[0][i],face_B[1][i],face_B[2][i]});
        float max_i_B = std::max({face_B[0][i],face_B[1][i],face_B[2][i]});

        if (min_i_A > max_i_B - tolerance || max_i_A < min_i_B + tolerance) no_overlap = true;
    }
    return no_overlap;

}

vector<vector<vector<float>>> clip_geometry(vector<vector<vector<float>>> geometry){
    int n = geometry.size();
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (i==j) continue;
            if (mag(geometry[i],geometry[j],tolerance)) continue;


            vector<float> v1 = {geometry[i][1][0]-geometry[i][0][0], geometry[i][1][1]-geometry[i][0][1], geometry[i][1][2]-geometry[i][0][2]};
            vector<float> v2 = {geometry[i][2][0]-geometry[i][0][0], geometry[i][2][1]-geometry[i][0][1], geometry[i][2][2]-geometry[i][0][2]};

            vector<float> n_A = cross(v1, v2);

            int overs = 0;
            int unders = 0;
            int find = 0;
            for (int k = 0; k < 3; k++){

                vector<float> from_point = {geometry[j][k][0]-geometry[i][0][0], geometry[j][k][1]-geometry[i][0][1], geometry[j][k][2]-geometry[i][0][2]};
                float dot = from_point[0]*n_A[0] + from_point[1]*n_A[1] + from_point[2]*n_A[2];

                if (dot >= -tolerance) overs += 1;
                if (dot <= tolerance) unders += 1;
            }

            if (overs == 3 or unders == 3) continue;
            else if (overs == 2) find = -1;
            else find = 1;

            int odd_vertice = -1;
            for (int k = 0; k < 3; k++){

                vector<float> from_point = {geometry[j][k][0]-geometry[i][0][0], geometry[j][k][1]-geometry[i][0][1], geometry[j][k][2]-geometry[i][0][2]};
                float dot = from_point[0]*n_A[0] + from_point[1]*n_A[1] + from_point[2]*n_A[2];
                if (abs(dot) > tolerance && dot/abs(dot) == find) odd_vertice = k;

            }
            
            vector<float> point0 = geometry[j][odd_vertice];
            vector<float> point1 = geometry[j][(odd_vertice+1)%3];
            vector<float> point2 = geometry[j][(odd_vertice+2)%3];
            vector<float> intersect1 = intersect_line_plane(n_A, geometry[i][0], {point2[0]-point0[0], point2[1]-point0[1], point2[2]-point0[2]}, point0);
            vector<float> intersect2 = intersect_line_plane(n_A, geometry[i][0], {point1[0]-point0[0], point1[1]-point0[1], point1[2]-point0[2]}, point0);

            geometry[j] = {point0,intersect1,intersect2};

            geometry.push_back({intersect1, intersect2, point2});
            geometry.push_back({point1, intersect2, point2});
            n += 2;

        }
    }
return geometry;
}