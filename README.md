# Breakout3D
Reupload of a project written in 2021.\
\
Breakout3D is a "circular" variant of a classic breakout game – the goal of
the game is to break all bricks in the level using a ball, controlled by in-game physics and
paddle(s), controlled by the player.\
\
The goal of the project was to:
- develop a core of a game engine in C++ including basic graphics and physics components, and
- develop a simple game using my own engine.

## Author
Daria Vasilenko

## Requirements
OS - Windows\
OpenGL 4.3+

## Used tools
C++, OpenGL, [glew](https://github.com/nigels-com/glew), [glfw](https://github.com/glfw/glfw), [stb_image](https://github.com/nothings/stb), [stb_truetype](https://github.com/nothings/stb), [tiny_obj_loader](https://github.com/tinyobjloader/tinyobjloader)

## Controls
Arrows - move paddles and launch the ball\
1, 2, 3, 4 - change camera view\
Enter - restart level

## Screenshots
![](https://github.com/DashaVasilenko/Breakout3D/blob/main/screenshots/1.png)
![](https://github.com/DashaVasilenko/Breakout3D/blob/main/screenshots/2.png)
![](https://github.com/DashaVasilenko/Breakout3D/blob/main/screenshots/3.png)

## Game Engine Features
1. Math library (including vector and matrix arithmetic)
2. Collision detection (sphere vs sphere, sphere vs brick)
3. Phong shading
4. Shadow mapping (for directional lights)
5. Construct the geometry (ball, paddles, bricks, ground) of level from scratch (manual generation of mesh vertexes coordinates, normals, UVs)
6. Texturing 