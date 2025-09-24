#define GL_SILENCE_DEPRECATION      
#include <GLFW/glfw3.h>
#include <OpenGL/gl3.h> 
#include <OpenGL/gl3ext.h> 
#include <iostream> 
#include <fstream>
#include <filesystem>
#include <sstream>
#include "render.h" 
#include "get_vertices.h" 
#include "clip_polygons.h"

int execute(vector<float> vertices){

    for (int i = 0; i < vertices.size(); i+=15){
        glBegin(GL_TRIANGLES);
            glColor3f(vertices[i+2],vertices[i+3],vertices[i+4]); glVertex2f(vertices[i+1], vertices[i]);
            glColor3f(vertices[i+7],vertices[i+8],vertices[i+9]); glVertex2f(vertices[i+6], vertices[i+5]);
            glColor3f(vertices[i+12],vertices[i+13],vertices[i+14]); glVertex2f(vertices[i+11], vertices[i+10]);
        glEnd();
        
        
        for (int j = 0; j < 2; j++){
            for (int k = j+1; k < 3; k++){
                glColor3f(0.0f, 0.0f, 0.0f); // black
                glBegin(GL_LINES);
                    glVertex2f(vertices[i+(5*j+1)], vertices[i+5*j]);  // start point (left)
                    glVertex2f(vertices[i+(5*k+1)], vertices[i+5*k]);  // end point (right)
                glEnd();
            }
        }
    }
    return 0;


}

vector<float> split_string(string s){
    std::istringstream iss(s);
    std::vector<float> numbers;
    float value;

    while (iss >> value) {
        numbers.push_back(value);
    }

    return numbers;
}

int main() {

    vector<vector<vector<float>>> geometry;

    string filename;
    std::cout << "File to Access? (must be in current directory) ";
    std::cin >> filename;

    std::ifstream file(filename);
    std::vector<std::string> lines; 
    std::string line;

    if (!file) {
        std::cerr << "Error: could not open file\n";
        return 1;
    }

    while (std::getline(file, line)) {
        lines.push_back(line);
    }

    file.close();

    int n_shapes = std::stoi(lines[0]);
    vector<float> camera_pos = split_string(lines[1]);
    vector<float> camera_angle = split_string(lines[2]);
    float camera_theta = camera_angle[0];
    float camera_phi = camera_angle[1];

    for (int i = 0; i < n_shapes*6; i+=6){
        vector<float> color = split_string(lines[i+4]);
        string geometry_type = lines[i+5];
        vector<float> position = split_string(lines[i+6]);
        vector<float> rotate = split_string(lines[i+7]);
        vector<float> scale = split_string(lines[i+8]);
        vector<vector<vector<float>>> temp_geometry;

        if (geometry_type == "cube" or geometry_type == "cube " or geometry_type == "cube  "){
            temp_geometry = get_cube(color);
        }
        if (geometry_type == "tetra" or geometry_type == "tetra " or geometry_type == "tetra  "){
            temp_geometry = get_tetra(color);
        }
        if (geometry_type == "pyra" or geometry_type == "pyra " or geometry_type == "pyra  "){
            temp_geometry = get_pyra(color);
        }

        temp_geometry = transform(temp_geometry, scale, position, rotate, {0,1,2});

        geometry.insert(geometry.end(),temp_geometry.begin(),temp_geometry.end());
    }




    geometry = clip_geometry(geometry);
    vector<float> vertices = to_perspective(geometry, camera_pos, camera_theta, camera_phi);


    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }
    GLFWwindow* window = glfwCreateWindow(1000, 1000, filename.c_str(), nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    while (!glfwWindowShouldClose(window)) {

        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        execute(vertices);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
