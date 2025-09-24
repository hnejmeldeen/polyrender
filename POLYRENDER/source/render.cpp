#include <iostream>
#include <vector>
#include "render.h"
using std::vector;
using std::string;
using std::cout;

float FOV_x = 100 * pi/360;
float FOV_y = 100 * pi/360;     //FOV (degree) to radians, divided by 2

bool compare_faces(vector<vector<float>> face1, vector<vector<float>> face2, vector<float> camera_pos){

   float dist1 = 0;
    for (vector<float> point : face1){
        dist1 += sqrt(pow((point[0]-camera_pos[0]),2)+pow((point[1]-camera_pos[1]),2)+pow((point[2]-camera_pos[2]),2))/3;
    }

    float dist2 = 0;
    for (vector<float> point : face2){
        dist2 += sqrt(pow((point[0]-camera_pos[0]),2)+pow((point[1]-camera_pos[1]),2)+pow((point[2]-camera_pos[2]),2))/3;
    }

    return dist1 > dist2;
}

vector<float> to_perspective(vector<vector<vector<float>>> geometry, vector<float> camera_pos, float theta, float phi){

    vector<float> right = {cos(phi),sin(phi),0};
    vector<float> up = {sin(phi)*sin(theta),cos(phi)*sin(theta),cos(theta)};
    vector<float> forward = {up[1]*right[2]-up[2]*right[1], up[2]*right[0]-up[0]*right[2], up[0]*right[1]-up[1]*right[0]};

    vector<float> to_render;

    //std::sort(geoemetry.begin(),geometry.end(),compare_faces)
    std::sort(geometry.begin(), geometry.end(),
    [camera_pos](vector<vector<float>> face1, vector<vector<float>> face2) {
        return compare_faces(face1, face2, camera_pos);
    });

    for (int i = 0; i < geometry.size(); i++){
        for (int j = 0; j < 3; j++){

            vector<float> point = geometry[i][j];
            point[0] -= camera_pos[0];
            point[1] -= camera_pos[1];
            point[2] -= camera_pos[2];

            float opp_right = point[0]*right[0]+point[1]*right[1]+point[2]*right[2];
            float opp_up    = point[0]*up[0]+point[1]*up[1]+point[2]*up[2];
            float adjacent  = point[0]*forward[0]+point[1]*forward[1]+point[2]*forward[2];

            float point_phi = atan(opp_up/adjacent);
            float point_theta = atan(opp_right/adjacent);

            if (adjacent < 0){
                point_phi += pi/2 * point_phi/abs(point_phi);
                point_theta += pi/2 * point_phi/abs(point_theta);
            }

            point_phi /= FOV_x;
            point_theta /= FOV_y;

            to_render.push_back(point_phi);
            to_render.push_back(point_theta);
            to_render.push_back(point[3]);
            to_render.push_back(point[4]);
            to_render.push_back(point[5]);
        }
    }

    return to_render;
    
}