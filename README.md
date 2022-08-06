
# CAD2022_E
ICCAD Contest 2022 Problem E, using C/C++ and OpenGL.

URL: http://iccad-contest.org/tw/03_problems.html




## Screenshots

![Screenshot](https://user-images.githubusercontent.com/100282257/182859864-9aeff98d-e80b-4910-9a73-76ccea52ea02.png)


## Libraries
All libraries and *.h files are in the Dependencies.
* GLEW
* GLFW

### Loading all of the OpenGL functions
**Step one**\
open Project Property -> Additional Include Directories -> Edit...

![Screenshot](https://user-images.githubusercontent.com/100282257/182866068-8a6bccda-1185-4b66-9236-3d711e063a5f.png)

Type the following directories
* $(SolutionDir)Dependencies\GLEW\include
* $(SolutionDir)Dependencies\GLFW\include

![Screenshot](https://user-images.githubusercontent.com/100282257/182868569-afa9039d-f373-4073-a436-f31c0971181e.png)
\
**Step two**\
Linker -> General -> Additional Library Directories -> Edit...

![Screenshot](https://user-images.githubusercontent.com/100282257/182879987-05ffeaee-22be-42e9-a021-a99b362b54af.png)

Type the following directories
* $(SolutionDir)Dependencies\GLEW\lib\x64
* $(SolutionDir)Dependencies\GLFW\lib

![Screenshot](https://user-images.githubusercontent.com/100282257/182880865-bd2c8aa5-7268-46fe-a06f-493d57ccaafb.png)

**Step three**\
Linker -> Input -> Additional Dependencies -> Edit... -> remove default dependencies

![Screenshot](https://user-images.githubusercontent.com/100282257/182881732-881a9cf7-ba52-44a6-b178-900d617edcad.png)

Type the following dependencies
* glew32s.lib
* glfw3.lib
* opengl32.lib
* User32.lib
* Gdi32.lib
* Shell32.lib

![Screenshot](https://user-images.githubusercontent.com/100282257/182883877-ec5623ae-c390-4217-8761-67b97b9480de.png)

**Step four**\
Apply -> OK