#include <iostream>
#include <vector>
#include "get_vertices.h"
using std::vector;
using std::string;
using std::cout;

vector<float> view = {-5.0,0.0,0.0};

vector<vector<vector<float>>> get_cube(vector<float> color){

    vector<vector<vector<float>>> standard_cube;

    vector<vector<float>> generating_points;
    generating_points.push_back({-(float)0.5,-(float)0.5,-(float)0.5, color[0], color[1], color[2]});
    generating_points.push_back({ (float)0.5, (float)0.5, (float)0.5, color[0], color[1], color[2]});


    for (int k = 0; k < 2; k++){

        vector<float> point_1 = generating_points[k];

        for (int i = 0; i < 3; i++){

            vector<float> point_adjacent = point_1;
            point_adjacent[i] *= -1;

            for (int j = 0; j < 3; j++){
                if (i == j) continue;

                vector<float> point_diagonal = point_adjacent;
                point_diagonal[j] *= -1;
                
                standard_cube.push_back({point_1,point_adjacent,point_diagonal});
            }
        }
    }

    return standard_cube;
}

vector<vector<vector<float>>> get_tetra(vector<float> color){
    vector<vector<vector<float>>> standard_tetra;

    vector<vector<float>> generating_points;
    generating_points.push_back({ (float)1, (float)0,-(float)(1/sqrt(2)), color[0], color[1], color[2]});
    generating_points.push_back({-(float)1, (float)0,-(float)(1/sqrt(2)), color[0], color[1], color[2]});
    generating_points.push_back({ (float)0, (float)1, (float)(1/sqrt(2)), color[0], color[1], color[2]});
    generating_points.push_back({ (float)0,-(float)1, (float)(1/sqrt(2)), color[0], color[1], color[2]});

    for (int i = 0; i < 2; i++){
        for (int j = i+1; j < 3; j++){
            for (int k = j+1; k < 4; k++){
                standard_tetra.push_back({generating_points[i],generating_points[j],generating_points[k]});
            }
        }
    }

    return standard_tetra;
}

vector<vector<vector<float>>> get_pyra(vector<float> color){
    vector<vector<vector<float>>> standard_pyra;

    vector<vector<float>> generating_points;
    generating_points.push_back({ (float)1, (float)1,-(float)(1/sqrt(2)), color[0], color[1], color[2]});
    generating_points.push_back({-(float)1, (float)1,-(float)(1/sqrt(2)), color[0], color[1], color[2]});
    generating_points.push_back({ (float)1,-(float)1,-(float)(1/sqrt(2)), color[0], color[1], color[2]});
    generating_points.push_back({-(float)1,-(float)1,-(float)(1/sqrt(2)), color[0], color[1], color[2]});
    generating_points.push_back({ (float)0, (float)0, (float)(1/sqrt(2)), color[0], color[1], color[2]});

    for (int i = 0; i < 3; i++){
        for (int j = i+1; j < 4; j++){
            for (int k = j+1; k < 5; k++){
                standard_pyra.push_back({generating_points[i],generating_points[j],generating_points[k]});
            }
        }
    }

    return standard_pyra;
}

vector<vector<vector<float>>> transform(vector<vector<vector<float>>> geometry, vector<float> scale, vector<float> COM, vector<float> rotate, vector<int> rotate_order){  // rotation_order entries contain 0,1, or 2 for rotations about x, y, z axis respectively
    //apply rotation matrices

    for (int i = 0; i < rotate_order.size(); i++){
        for (int j = 0; j < geometry.size(); j++){
            for (int k = 0; k < 3; k++){

                vector<float> point = geometry[j][k];
                float theta = rotate[i];
                int axis = rotate_order[i];

                geometry[j][k][(axis+1)%3] = (point[(axis+1)%3]*cos(theta) - point[(axis+2)%3]*sin(theta));
                geometry[j][k][(axis+2)%3] = (point[(axis+1)%3]*sin(theta) + point[(axis+2)%3]*cos(theta));
            }
        }
    }

    // now scale and translate by COM vector (center of mass)

    for (int i = 0; i < geometry.size(); i++){
        for (int j = 0; j < 3; j++){

            vector<float> point = geometry[i][j];

            geometry[i][j][0] = point[0]*scale[0]+COM[0];
            geometry[i][j][1] = point[1]*scale[1]+COM[1];
            geometry[i][j][2] = point[2]*scale[2]+COM[2];
        }
    }

    return geometry;   // if a different order of sequence transformation is desired, like scaling before rotation, multiple transformations may be used. But in general, almost any orientation is attainable with one call.

}
