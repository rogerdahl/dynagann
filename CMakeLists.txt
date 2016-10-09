cmake_minimum_required(VERSION 3.5)
project(dynagann)

# https://cmake.org/cmake/help/v3.0/policy/CMP0015.html
cmake_policy(SET "CMP0015" "NEW")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
set(LIBRARIES ${CMAKE_SOURCE_DIR}/libraries/linux)
else()
set(LIBRARIES ${CMAKE_SOURCE_DIR}/libraries/win64)
endif()

## GLFW
#if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
##	find_package(GLFW REQUIRED)
##	set(GLFW_LINK_DIRS "")
#	set(GLFW_LIBRARIES GLFW.lib)
#	set(GLFW_INCLUDE_DIRS ${LIBRARIES}/GLFW-2.6.3/include)
#	set(GLFW_LINK_DIRS ${LIBRARIES}/GLFW-2.6.3/builds/Release)
#else()
#	set(GLFW_LIBRARIES GLFW.lib)
#	set(GLFW_INCLUDE_DIRS ${LIBRARIES}/GLFW-2.6.3/include)
#	set(GLFW_LINK_DIRS ${LIBRARIES}/GLFW-2.6.3/builds/Release)
#endif()
#${LIBRARIES}/glfw-3.1.2/include/GLFW/

# FreeType2
#CPPFLAGS += $(shell freetype-config --cflags)
#LDFLAGS += $(shell freetype-config --libs)
if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
find_package(Freetype REQUIRED)
set(FREETYPE_LINK_DIRS "")
else()
set(FREETYPE_LIBRARIES freetype.lib)
set(FREETYPE_INCLUDE_DIRS ${LIBRARIES}/freetype-2.6.3/include)
set(FREETYPE_LINK_DIRS ${LIBRARIES}/freetype-2.6.3/builds/Release)
endif()

# Boost
if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
# https://cmake.org/cmake/help/v3.0/module/FindBoost.html
find_package(Boost 1.58.0 REQUIRED)
set(BOOST_LIBRARIES boost_filesystem boost_system)
else()
set(BOOST_LIBRARIES libboost_filesystem-vc140-mt-1_60 libboost_system-vc140-mt-1_60)
set(BOOST_INCLUDE_DIR ${LIBRARIES}/boost_1_60_0)
set(BOOST_LINK_DIR ${LIBRARIES}/boost_1_60_0/stage/lib)
endif()

# glm
if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
else()
set(GLM_INCLUDE_DIR ${LIBRARIES}/glm-0.9.7.4/glm)
endif()

# GLEW
if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
set(GLEW_LIBRARIES GLEW)
#set(GLEW_INCLUDE_DIR ${LIBRARIES}/glew-1.13.0/include)
#set(GLEW_LINK_DIR ${LIBRARIES}/glew-1.13.0/lib/Release/x64)
else()
set(GLEW_LIBRARIES glew32.lib)
set(GLEW_INCLUDE_DIR ${LIBRARIES}/glew-1.13.0/include)
set(GLEW_LINK_DIR ${LIBRARIES}/glew-1.13.0/lib/Release/x64)
endif()

# OpenGL and GLU
find_package(OpenGL REQUIRED)

# X
if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
set(X_LIBRARIES Xrandr X11 Xxf86vm Xinerama Xcursor Xi)
else()
set(X_LIBRARIES "")
endif()

# GCC
if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
set(m pthread dl)
else()
set(GCC_LIBRARIES "")
endif()

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wfatal-errors")
endif()

set(SOURCE_FILES
    ${SOURCE_DIR}/main.cpp
    ${SOURCE_DIR}/mesh.cpp
    ${SOURCE_DIR}/ogl_text.cpp
    ${SOURCE_DIR}/par_shapes.cpp
    ${SOURCE_DIR}/physics.cpp
    ${SOURCE_DIR}/shader.cpp
    ${SOURCE_DIR}/utils.cpp
)

include_directories(
    ${LIBRARIES}/par
    ${LIBRARIES}/newton-3.13/inc
    ${LIBRARIES}/fmt-3.0.0
	${GLFW_INCLUDE_DIRS}
    ${FREETYPE_INCLUDE_DIRS}
    ${BOOST_INCLUDE_DIR}
	${GLM_INCLUDE_DIR}
    ${GLEW_INCLUDE_DIR}
	${OPENGL_INCLUDE_DIR}
)

link_directories(
	${LIBRARIES}/newton-3.13/lib
    ${LIBRARIES}/glfw-3.1.2
    ${LIBRARIES}/fmt-3.0.0/fmt
	${FREETYPE_LINK_DIRS}
    ${BOOST_LINK_DIR}
    ${GLEW_LINK_DIR}
)

link_libraries(
    glfw fmt Newton
    ${FREETYPE_LIBRARIES}
	${GLEW_LIBRARIES}
	${OPENGL_LIBRARIES}
	${X_LIBRARIES}
	${GCC_LIBRARIES}
	# For Windows, the boost libraries are not required here because Boost supports VS' autolink feature.
    ${BOOST_LIBRARIES}
)

# Remove GLM warning about having switched from degrees to radians as default.
add_definitions(-DGLM_FORCE_RADIANS)

# Copy shaders to binary dir.
file(GLOB SHADER_PATHS ${SOURCE_DIR}/shaders/*)
file(COPY ${SHADER_PATHS} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/shaders)

# Copy fonts to binary dir.
file(GLOB FONT_PATHS ${CMAKE_SOURCE_DIR}/fonts/*)
file(COPY ${FONT_PATHS} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/fonts)


add_executable(dynagann ${SOURCE_FILES})
