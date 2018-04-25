# Shape Drawer

Welcome to Shape Drawer, a program that allows you to view different shapes with custom movement types.

TODO: Insert a screenshot / GIF of the program.

## Features

- *Draw shapes such as*: Square (Quad), Triangle, Circle, Hexagon, Pentagon, Heptagon and Cube.
- *Customise your shapes with*: Dimensions (Scale), Colour, Movement Type and Movement rate.
- *Load shapes through a file*: Create custom shapes from an **.ini** file (More information below).
- *Cubemap*: Got a skybox with .jpg? Load it in! Just remember the image order.
- *Live-reloading*: Press R to reload your program.

### Key Design Decisions

Shape Drawer was built with a OpenGL framework I developed a year ago. I feel comfortable working with OpenGL in a Windows environment, as it is what has been taught to me at University. This program works by having a main function that initialises OpenGL/Glew/Glut, proceed to create global variables and holds a scene singleton that contains models.

### Useful enums

The following enums dictate the types of model that can be drawn (and expanded upon) as well as the different kinds of movements.

#### Model Types

- Square
- Triangle
- Circle
- Hexagon
- Cube
- Pentagon
- Heptagon

#### Movement Types

- Idle
- UpDown
- LeftRight
- Circular
- Box

### Systems

- Camera: Allows for a camera to be placed in the scene. Specify the position and dimensions of it.
- Cubemap: Creates a Skybox
- GameScene: Holds the models to be displayed
- Utilities: Provides constant definitions and static members/methods that ease up on common tasks e.g. Filling up vertices/indices as well as custom polygon shapes, Converting from RGB to Alpha, Vector3.MoveTowards, etc.
- Shader Loader: Load any type of you want. I have included a texture unlit shader as well as a cubemap shader.

## Getting started

To run Shape Drawer, simply open ShapeDrawer.exe and enjoy! You will find yourself in a clear background. Please refer to the `Controls` Menu below for navigation.

## Controls

- `1`: Load default game scene with all shapes.
- `2`: Load game scene with shapes loaded from an external file.
- `3`: Load default game scene with external shapes.
- `R`: Clear the scene.

### Loading custom shapes from external files

1. Go to the Resources folder located in the root. If it does not exist, create one.
2. Locate the file "shapes.ini". If it does not exist, create a .txt file and rename it to shapes.ini. Make sure the extension is **.ini**. Alternatively, you can change the file's name, just make sure you also do this in code!

**IMPORTANT**: Your **.ini** must adhere to the following standards:

``` text
[shapeN] (N is the number of the shape)
ModelType = enum (Refer to Model Types enum)
MovementType = enum (Refer to Movement Types enum)
Texture = string (Use NULL if you do not want to use a texture)
Colour = (x, y, z) (int/float/double values are valid)
Scale = (x, y, z) (int/float/double values are valid)
Position = (x, y, z) (int/float/double values are valid)
Rotation = (x, y, z) (int/float/double values are vali)]
Speed = float value (Recommended: [0.05f for non-circular movement], [3-5 for circular movement])
[shapeN+1] (N is the number of the shape)
```

Requirements for smooth **.ini** file loading:

- No empty lines
- No missing entries / characters that should not be used, especially for textures.

## Source code

Shape Drawer is a 32-bit program that was built with Windows 10 and Visual Studio 2015 using OpenGL, Glew and Glut.

### Requirements

- [Visual Studio 2015 Community](https://www.visualstudio.com/vs/older-downloads/)
- [OpenGL](https://www.khronos.org/opengl/wiki/Getting_Started#Downloading_OpenGL)
- [Glew](http://glew.sourceforge.net/install.html)
- [Glut](https://www.opengl.org/resources/libraries/glut/)

### Compiling from source

1. Open the solution (.sln) file located in the root folder.
2. Under the top toolbar, select the "x64"/"x86" dropdown that is located left of the "Local Windows Debugger" and select "x86".
3. At the top toolbar, select Build > Build Solution. Alternatively, press CTRL+SHIFT+B to build.
4. Click on the "Local Windows Debugger" or press F5 to run.
5. Enjoy!

## Known problems

1. Having empty lines inside **.ini** files crashes the program. To avoid this: remove unnecessary empty lines.
2. Duplicate headers inside **.ini** files crash the program. To avoid this: Use different names.