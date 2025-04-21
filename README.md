##              🖼️ miniRT

miniRT is a basic ray tracer written in C using the MiniLibX library.
This project is part of the 1337/42 school curriculum.

##              📸 Overview

miniRT renders 3D scenes using ray tracing techniques. It supports:
Spheres, planes, and cylinders
Ambient, diffuse, and specular lighting
Shadows
Camera movement
BMP screenshot saving
<div align="center"><img src="map/snowman.png" /></div>
<div align="center"><img src="map/room.png" /></div>

##          🚀 How to Run

###  1. Clone the repo

```
git clone https://github.com/aogbi/minirt.git
cd minirt
```

###  3. Compile

```
make
```
###  4. Run

```
./miniRT scenes/example.rt
```
##          📦 Requirements

macOS or Linux
MiniLibX
gcc / clang
make
Note: On Linux, you may need to install X11 and related libraries.

##          📂 Scenes

Scene files (.rt) describe the objects and lights in your scene.
Example format:
```
R 800 600
A 0.2 255,255,255
c -50,0,20 0,0,1 70
l -40,10,30 0.7 255,255,255
sp 0,0,20 20 255,0,0
```
##          🧠 Project Goals

Learn the basics of ray tracing
Understand camera and light in 3D
Work with vector math and geometry
Build from scratch with no external graphics engine

##          👨‍💻 Authors

@aogbi

