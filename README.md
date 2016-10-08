https://youtu.be/Sa7ZHlGxsnc

Setup

$ git clone https://github.com/prideout/par.git

$ sudo apt-get install libglm-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev libboost-dev libboost-filesystem-dev build-essential libglew-dev libfreetype6-dev 

check if required: mesa-common-dev
INSTALLING libglu1-mesa-dev BREAKS -lGL
INSTALLING the NVIDIA driver afterwards fixes -lGL again.

Found no packaged release of GLFW 3 so downloaded the 3.1.2 release from GitHub (latest as of 2016-03-15):
wget https://github.com/glfw/glfw/archive/3.1.2.tar.gz
tar xf 3.1.2.tar.gz
cd glfw-3.1.2
cmake -G 'Unix Makefiles'
make

Using cppformat 2.1.0 from https://github.com/cppformat/cppformat/releases 

OLD

$ sudo apt-get install libglfw-dev libglm-dev libglm-doc
