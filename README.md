# Shape Drawer

Welcome to Shape Drawer, a program that allows you to view different shapes with custom movement types.

TODO: Insert a screenshot / GIF of the program.

## Features

- *Draw shapes such as*: Square (Quad), Triangle, Circle, Hexagon, Pentagon, Heptagon and Cube.
- *Customise your shapes with*: Dimensions (Scale), Colour, Movement Type and Movement rate.
- *Load shapes through a file*: Read below for more instructions.

## Key Design Decisions

Shape Drawer was built with a OpenGL framework I developed a year ago. I feel comfortable working with OpenGL in a Windows environment, as it is what has been taught to me at University.

### Systems

- Camera: Allows for a camera to be placed in the scene. Specify the position and dimensions of it.
- Cubemap: Creates a Skybox
- Scene: Holds the models to be displayed
- Utilities: Provides constant definitions and static members/methods that ease up on common tasks e.g. Filling up vertices/indices as well as custom polygon shapes, Converting from RGB to Alpha, Vector3.MoveTowards, etc.
- Shader Loader: Load any type of you want. I have included a texture unlit shader as well as a cubemap shader.

## Getting started

To run Shape Drawer, simply open ShapeDrawer.exe and enjoy!

## Controls

- `R`: Reload the scene

### Loading custom shapes from external files

1. Go to the Resources folder located in the root. If it does not exist, create one.
2. Locate the file "shapes.ini". If it does not exist, create a .txt file and rename it to shapes.ini. Make sure the extension is **.ini**.

## Source code

Shape Drawer is a 32-bit program that was built with Windows 10.

### Requirements

- [Visual Studio 2015 Community](https://www.visualstudio.com/vs/older-downloads/)
- [OpenGL](https://www.khronos.org/opengl/wiki/Getting_Started#Downloading_OpenGL)
- [Glew](http://glew.sourceforge.net/install.html)
- [Glut](https://www.opengl.org/resources/libraries/glut/)

### Compiling from source

Shape Drawer was built with Visual Studio 2015 using OpenGL, Glew and Glut.

#### Debug Shape Drawer

1. Open the solution (.sln) file located in the root folder.
2. Under the top toolbar, select the "x64"/"x86" dropdown that is located left of the "Local Windows Debugger" and select "x86".
3. At the top toolbar, select Build > Build Solution. Alternatively, press CTRL+SHIFT+B to build.
4. Click on the "Local Windows Debugger" or press F5 to run.
5. Enjoy!
