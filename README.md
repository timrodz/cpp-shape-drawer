# Shape Drawer

Welcome to Shape Drawer, a program that allows you to view different shapes with custom movement types.

## Features

- **Drawing of 2d/3D primitives**: Square (Quad), Triangle, Circle, Hexagon, Pentagon, Heptagon and Cube.
- **Customise your shapes with**: Dimensions (Scale), Colour, Movement Type, Movement rate, Position, Rotation.
- **Load shapes through a file**: Create custom shapes from an **.ini** file (More information below).
- **Cubemap**: Got a skybox with .jpg? Load it in! Just remember the image order.
- **Scene clearing**: Clears every object in the scene, with exception to the cubemap.

### Key Design Decisions

Shape Drawer was built with a OpenGL framework I developed a year ago. I feel comfortable working with OpenGL in a Windows environment, as it is what has been taught to me at University. This program works by having a main function that initialises OpenGL/Glew/Glut, proceed to create global variables and holds a scene singleton that contains models. For more information, refer to the **Systems** section of this document below.

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

**Recommendation**: Movement rates for types that are not Box should be set to a value between *1.0f* and *10.0f*. For Box, try to stick with *0.5f*.

### Systems

- **Camera**: Creates a camera that displays object in the scene. Options:
  - Dimensions (Width, Height). Default is window size.
  - Field Of View. Defaults at 45. **Be careful**: this value can render the scene very from far away!
- **Cubemap**: Creates a cubemap that works as a skybox.
- **Model**: Holds basic functionality for models (Camera, Position, Scale, Rotation).
- **GameModel**: Holds basic functionality for mode advanced models (Cubemap, GameObject).
- **GameObject**: Creates the object that will be drawn. Options:
  - Model Type: See enum above.
  - Movement Type: See enum above.
  - Colour: Vector3(1, 1, 1). Alpha value is always 1.
  - Scale: Vector3(1, 1, 1).
  - Position Vector3(0, 0, 0).
  - Rotation Vector3(0, 0, 0).
  - Speed: float value.
- **GameScene**: Handles creation, rendering and updating of objects. Options:
  - LoadDefaultGameScene: Creates a game scene with all the available models/movement types.
- **INIParser**: The file reader that creates models. Options:
  - SaveFile: Saves current map keys to **SaveFile.ini**. Can be used as backup.
  - LoadFile: Loads and generates a map with appropiate keys.
- **Shader Loader**: Load any type of you want. Options:
  - Skybox vs/fs: Holds the cubemap textures.
  - Unlit vs/fs: Draws unlit polygons.
- **Utilities**: Provides constant definitions and static members/methods that ease up on common tasks. Options:
  - Populate Vertex/Index data for specific and polygonal shapes.
  - Convert RGB (255, 255, 255) to Alpha (1, 1, 1, 1).
  - MoveTowards: Moves a vector3 towards another with given time.
  - ToLower: Converts a string to lowercase.
  - Get Model/Movement/Vector3 from string. Useful for parsing.

## Getting started

To run Shape Drawer, simply open ShapeDrawer.exe and enjoy! You will find yourself in a clear background. Please refer to the `Controls` Menu below for navigation.

### Controls

- `1`: Load default game scene with all shapes.
- `2`: Load game scene with shapes loaded from an external file. Automatically detects new shapes added to your **.ini** file.
- `3`: Load default game scene with external shapes.
- `R`: Clear the scene.
- `Q`: Quit the program.

Options `1`, `2`, and `3` automatically clear the scene before adding any new elements.

### Loading shapes from .ini files

1. Go to the Resources folder located in the root. If it does not exist, create one.
2. Locate the file "shapes.ini". If it does not exist, create a .txt file, give it a name and make sure the extension is **.ini**. e.g.: **shapes.ini**.
3. Edit the file with the desired information.

**IMPORTANT**: Your **.ini** file *must* adhere to the following standards:

```text
[sectionN] (N is the shape number - Starts from 1 upwards, section can be any string)
ModelType = enum (Refer to Model Types enum)
MovementType = enum (Refer to Movement Types enum)
Colour = (x, y, z) (int/float/double values are valid)
Scale = (x, y, z) (int/float/double values are valid)
Position = (x, y, z) (int/float/double values are valid)
Rotation = (x, y, z) (int/float/double values are valid]
Speed = float value (Use low values)
```

Requirements for successful **.ini** file loading:

- Make sure there are no empty lines in the file.
- Speed must either be set to an integer number (5) or a float number (5.0f). *5f* will return an error.
- Please adhere to the format if the program breaks. In the case of leaving any fields blank, they will be populated with default data.

#### Example of correct usage

```text
[shape1]
ModelType = Triangle
MovementType = Box
Scale = (1, 1, 1)
Position = (3, -3, 0)
Rotation = (15, 15, 0)
Speed = 0.05f
[shape2]
ModelType = Hexagon
MovementType = Circular
Colour = (124, 64, 105)
Scale = (1, 1, 1)
Position = (-3, -3.0, 0)
Speed = 5
```

In the above case, **shape1** does not have a colour, so it defaults to white (255, 255, 255). Same goes for the rotation of **shape2**, where it defaults to (0, 0, 0).

## Source code

Shape Drawer is a 32-bit program that was built with Windows 10 and Visual Studio 2015 using OpenGL, Glew and Glut.

### Requirements

- [Visual Studio 2015 Community](https://www.visualstudio.com/vs/older-downloads/)
- [OpenGL](https://www.khronos.org/opengl/wiki/Getting_Started#Downloading_OpenGL/)
- [Glew](http://glew.sourceforge.net/install.html/)
- [Glut](https://www.opengl.org/resources/libraries/glut/)

### Compiling/Running from source

1. Open the solution (.sln) file located in the root folder. Select Visual Studio 2015 Community edition for this.
2. Under the top toolbar, select the "x64"/"x86" dropdown that is located left of the "Local Windows Debugger" and select "x86".
3. At the top toolbar, select Build > Build Solution. Alternatively, press CTRL+SHIFT+B to build.
4. Click on the "Local Windows Debugger" or press F5 to run.
5. Enjoy!

### Global settings

The following settings that can be found under **Utils.h**:

- **WIDTH**: The width of the window. Default is 1280.
- **HEIGHT**: The height of the window. Default is 720.
- **VERTICAL_LIMIT**: The vertical movement limit. Default is 2.
- **HORIZONTAL_LIMIT**: The horizontal movement limit. Default is 2.
- **CIRCULAR_RADIUS**: The circular movement limit. Default is 1.

## Known problems and how to avoid them

1. Having empty lines inside **.ini** files crashes the program. To avoid this: Remove unnecessary empty lines.
2. Duplicate headers inside **.ini** files crash the program. To avoid this: Use different names.
3. **.ini** files can be very problematic. To avoid this: Stick to the format given.
4. Skipping **.ini** file entries may crash the program. To avoid this: Do not remove sections.
