# Polyrender
------------------------------------------------------------------------------------------------

POLYRENDER - Sept. 23 2025

------------------------------------------------------------------------------------------------

Overview:

Polyrender is a 3D graphics rendering software written in C++ using OpenGL and GLFW. It takes a simple user-provided text file as input and produces a rendering of 3D shapes.


User provides a .txt file containing shape definitions and transformation parameters (see examples).

The program parses the file and builds vertex data.

Shapes are rendered using OpenGL with the specified rotations, translations, and scalings applied.

------------------------------------------------------------------------------------------------

Prerequisites:

C++17 compiler

GLFW installed (with Homebrew, apt, vcpkg, etc.)

OpenGL available (typically comes with macOS/Windows/Linux)

------------------------------------------------------------------------------------------------

To compile Polyrender:

MACOS:

clang++ -std=c++17 main.cpp render.cpp get_vertices.cpp clip_polygons.cpp \
    -I/opt/homebrew/include -L/opt/homebrew/lib -lglfw -framework OpenGL -o polyrender


WINDOWS:

g++ -std=c++17 main.cpp render.cpp get_vertices.cpp clip_polygons.cpp \
    -lglfw3 -lopengl32 -lgdi32 -o polyrender.exe


LINUX:

g++ -std=c++17 main.cpp render.cpp get_vertices.cpp clip_polygons.cpp \
    -lglfw -lGL -o polyrender

------------------------------------------------------------------------------------------------

To use Polyrender:

1. Create text file with input shapes or use example script in examples directory. See FORMAT.txt for structure of input file.

2. From terminal, navigate to executable directory. Ex: "cd ~/PATH_TO_EXECUTABLE"

3. Run  "./polyrender" from terminal.

4. Input directory to input file. Ex: "../examples/scene.txt"

Polyrender will automatically read and render the scene.

