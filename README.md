## DynaGann

[![DynaGann Demo](https://youtu.be/Sa7ZHlGxsnc/0.jpg)](https://youtu.be/Sa7ZHlGxsnc)

### Compiling on Linux

* Tested on Linux Mint 18 64-bit.

#### Packaged dependencies

* `$ sudo apt-get install --yes cmake git build-essential libglm-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev libboost-dev libboost-filesystem-dev libglew-dev libfreetype6-dev libglfw3-dev` 

#### DynaGann source

* `$ git clone <copy and paste the "Clone with HTTPS " URL from the top of this page>`

#### par

* `$ cd dynagann/libraries/build`
* `$ git clone https://github.com/prideout/par.git`
* `$ mv par/ ../linux/`

#### fmt

* $ `cd dynagann/libraries/build`
* $ `wget https://github.com/fmtlib/fmt/archive/3.0.0.tar.gz`
* $ `tar xf 3.0.0.tar.gz `
* $ `cd fmt-3.0.0`
* $ `cmake -G 'Unix Makefiles'`
* $ `make`
* $ `cd ..`
* $ `cp -r --parents fmt-3.0.0/fmt ../linux`

#### Newton Dynamics

* $ `cd dynagann/libraries/build`
* $ `wget https://github.com/MADEAPPS/newton-dynamics/archive/newton-3.13.tar.gz`
* $ `tar xf newton-3.13.tar.gz`
* $ `cd newton-dynamics-newton-3.13/coreLibrary_300`
* $ `cmake -G 'Unix Makefiles'`
* $ `make`
* $ `mkdir -p ../../../linux/newton-3.13/{lib,inc}`
* $ `mv libNewton.* ../../../linux/newton-3.13/lib/`
* $ `cp source/newton/Newton.h ../../../linux/newton-3.13/inc/`

### Build

* $` cd dynagann/build`
* $ `cmake -G 'Unix Makefiles' ..`
* $ `make` 

### Run

* $` cd dynagann/bin`
* $ `./dynagann`


---


### Setting up the dependencies for compiling on Windows.

Move and rename the files as required for matching the paths in CMakeLists.txt

#### Visual Studio Community 2015
https://go.microsoft.com/fwlink/?LinkId=691978&clcid=0x409
* Select: Programming Languages > Visual C++ > Common Tools for Visual C++ 2015
* Unselect everything else including the other Visual C++ features

#### CMake
https://cmake.org/download/ > `cmake-3.5.1-win32-x86.msi`
* There's no 64-bit version for Windows.

#### FreeType
https://sourceforge.net/projects/freetype/ > ft263.zip (2.6.3)
* Open the CMake GUI and browse to the source.
* Use default native compilers
* Source: ft263/freetype-2.6.3
* Build: ft263/freetype-2.6.3/builds
* Click Configure
* Specify the generator for this project > Visual Studio 14 2015 Win64
* Ignore error: "Could NOT find PkgConfig (missing:  PKG_CONFIG_EXECUTABLE)"
* Click Generate
* Open freetype-2.6.3\builds\freetype.sln
* Solution Configurations > Release
* Build > Build Solution

#### GLFW
http://www.glfw.org/download.html > 64-bit Windows binaries
* Move:

From | To
--- | ---
`glfw-3.1.2.bin.WIN64` | `dynagann\libraries\win64\glfw-3.1.2`
`.lib` and `.dll` files from `lib-vc2015` | to parent (glfw-3.1.2) dir

#### cppformat
https://github.com/cppformat/cppformat/releases > 2.1.0
* Same procedure as with FreeType for generating the 64-bit VS project files
* Open libraries\win64\cppformat-2.1.0\build\FORMAT.sln
* Right click Solution "FORMAT" > Retarget solution
* Solution Configurations > release
* Right click "cppformat" > Build
* Move:

\libraries\win64\cppformat-2.1.0\build\cppformat\Release\cppformat.lib ->
\libraries\win64\cppformat-2.1.0\cppformat\cppformat.lib

#### Newton Dynamics
https://github.com/MADEAPPS/newton-dynamics/releases > 3.1.3
* Don't use the CMake build, it doesn't work on Windows.
* Open packages\projects\visualStudio_2013_dll\build.sln
* As explained in http://newtondynamics.com/forum/viewtopic.php?f=12&t=8881:
  * Add a preprocessor define of HAVE_STRUCT_TIMESPEC in the pthread project properties
  * In coreLibrary_300\source\core\dgTypes.h add:

```
#ifdef _MSC_VER 
   #ifdef _M_X64
      #ifndef _WIN_64_VER
         #define _WIN_64_VER
      #endif
   #else       
      #ifndef _WIN_32_VER
         #define _WIN_32_VER
      #endif
   #endif

   // ADD THIS PART
   #if _MSC_VER >= 1400
      #define HAVE_STRUCT_TIMESPEC
   #endif
#endif
```
Move:

From | To
--- | ---
`libraries\win64\newton\coreLibrary_300\projects\windows\project_vs2013_dll\x64\newton\release\newton.lib` | `libraries\win64\newton\lib\newton.lib`
`libraries\win64\newton\coreLibrary_300\projects\windows\project_vs2013_dll\x64\newton\release\newton.dll` | `dynagann\bin`

#### Boost
https://sourceforge.net/projects/boost/ > 1.60.0
`bootstrap.bat`
`b2.exe address-model=64`

#### glm
https://github.com/g-truc/glm/releases > 0.9.7.4
* Same procedure as with FreeType for generating the 64-bit VS project files

#### GLEW
https://sourceforge.net/projects/glew/ > 1.13.0

Move:

From | To
--- | ---
`bin\Release\x64\glew32.dll` | `dynagann\bin`
`lib\Release\x64\glew32.lib` is the corresponding 64-bit lib.

`glew32.dll` is the 64-bit DLL despite the conflicting name.
