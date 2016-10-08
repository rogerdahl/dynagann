// Style: http://geosoft.no/development/cppstyle.html

#include <cstdio>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>
#include <deque>

#include <boost/filesystem.hpp>
#include <GL/glew.h>
#include <glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <cppformat/format.h>

#include "mesh.h"
#include "physics.h"
#include "shader.h"
#include "utils.h"
#include "ogl_text.h"
#include "gl_error.h"

using namespace std;
using namespace boost::filesystem;

GLFWwindow* window;

int window_w = 1920;
int window_h = 1080;
bool fullScreen = true;

// Shadow map width and height.
int shadowMapWH = 4096;

const char* FONT_PATH = "./fonts/LiberationMono-Regular.ttf";
//const char* FONT_PATH = "C:/windows/Fonts/Gabriola.ttf";
//const char* FONT_PATH = "./fonts/Sitka.ttc";
const u32 FONT_SIZE = 20;

int main(int argc, char** argv)
{
    path recDirPath;
    if (argc == 2) {
        recDirPath = argv[1];
    }

    srand((unsigned int)time(NULL));

    // Initialise GLFW OpenGL windowing framework.
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }

    if (!glfwJoystickPresent(GLFW_JOYSTICK_1)) {
        cerr << "Joystick not found" << endl;
    }

    // Joystick test.
//    while (1) {
//        int count;
//        const float* axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &count);
//        for (int i = 0; i < count; ++i) {
//            cout << i << "=" << axes[i] << " ";
//        }
//        const unsigned char* buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &count);
//        for (int i = 0; i < count; ++i) {
//            if (buttons[i] == GLFW_PRESS) {
//                cout << i + 1 << " ";
//            }
//        }
//        cout << endl;
//    }

    // Create window and OpenGL context.
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWmonitor* glfwMonitor = fullScreen ? glfwGetPrimaryMonitor() : NULL;
    window = glfwCreateWindow(window_w, window_h, "dynagann", glfwMonitor, NULL);
    if (window == NULL) {
        fprintf(stderr, "Failed to create GLFW window.\n");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Initialize GLEW.
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        glfwTerminate();
        return -1;
    }

    // Clear GL Error
    glGetError();

    // Cause glfwGetKey() to return a GLFW_PRESS on first call even if the key has already been released.
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    glClearColor(0.3f, 0.3f, 0.3f, 0.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);

    // State is automatically stored here.
    GLuint vertexArrayId;
    glGenVertexArrays(1, &vertexArrayId);
    glBindVertexArray(vertexArrayId);

	GLuint phongProgramId = createProgram("phong.vert", "phong.frag");
    GLuint shadowProgramId = createProgram("shadow.vert", "shadow.frag");

    glUseProgram(phongProgramId);

	GLint phongModelMatrixId = glGetUniformLocation(phongProgramId, "uniModel");
    if (phongModelMatrixId < 0) {
        fmt::print(stderr, "Warning: phongModelMatrixId={}\n", phongModelMatrixId);
    }
	GLint phongViewMatrixId = glGetUniformLocation(phongProgramId, "uniView");
    if (phongViewMatrixId < 0) {
        fmt::print(stderr, "Warning: viewMatrixId={}\n", phongViewMatrixId);
    }
	GLint phongProjectionMatrixId = glGetUniformLocation(phongProgramId, "uniProj");
    if (phongProjectionMatrixId < 0) {
        fmt::print(stderr, "Warning: phongProjectionMatrixId={}\n", phongProjectionMatrixId);
    }
    GLint phongCameraPosId = glGetUniformLocation(phongProgramId, "uniCameraPos");
    if (phongCameraPosId < 0) {
        fmt::print(stderr, "Warning: cameraPosId={}\n", phongCameraPosId);
    }
	GLint phongLightPosId = glGetUniformLocation(phongProgramId, "uniLightPos");
    if (phongLightPosId < 0) {
        fmt::print(stderr, "Warning: lightPosId={}\n", phongLightPosId);
    }

    Mesh floorMesh(SHAPE_BOX, phongProgramId, glm::vec4(1, 1, 1, 1));
    Mesh boxMesh(SHAPE_BOX, phongProgramId, glm::vec4(1, 0, 0, 1));
    Mesh sphereMesh(SHAPE_SPHERE, phongProgramId, glm::vec4(0, 1, 0, 1));
    Mesh cylinderMesh(SHAPE_CYLINDER, phongProgramId, glm::vec4(0, 0, 1, 1));
    Mesh coneMesh(SHAPE_CONE, phongProgramId, glm::vec4(0, 1, 1, 1));

    auto cameraPos = glm::vec3(0, 4, 9);
    glUniform3fv(phongCameraPosId, 1, glm::value_ptr(cameraPos));

    auto lightPos = glm::vec3(10, 10, 15);
    glUniform3fv(phongLightPosId, 1, glm::value_ptr(lightPos));

    float aspect_ratio = (float)window_w / (float)window_h;

    // The model matrix translates from model to world space.
    // The model's position, scaling and rotation should all be in this matrix.
    // The default matrix is the identity matrix, which does not cause any translations.
    auto floorModelMatrix = glm::mat4();
//    floorModelMatrix = glm::rotate(floorModelMatrix, 0.25f, glm::vec3(0, 0, 1));
    floorModelMatrix = glm::translate(floorModelMatrix, glm::vec3(0.0f, -0.75f, 0.0f));
    floorModelMatrix = glm::scale(floorModelMatrix, glm::vec3(10.0f, 0.5f, 10.0f));

    // The modelViewProjectionMatrix translates directly from model to screen space.
    // auto modelViewProjectionMatrix = projectionMatrix * viewMatrix * floorModelMatrix;
    // std::cout << glm::to_string(ProjectionMatrix) << std::endl;

    Pys pys;

    OglText oglText(window_w, window_h, FONT_PATH, FONT_SIZE);

    averageSec averageNewtonStep;
    averageSec averageRendering;

    auto m = glm::mat4();
    m = glm::rotate(m, 0.001f, glm::vec3(1, 1, 0));

    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0) {
//        break; //////////////////////
        // glPushAttrib() and glPopAttrib() are deprecated in OpenGL 4 and I couldn't find a good alternative, so
        // I just reset values here that get changed by OglText.print().
        glEnable(GL_DEPTH_TEST);
//        glDisable(GL_DEPTH_TEST);

//        m = glm::translate(m, glm::vec3(0.0f, -1.0f, 0.0f));

        glm::vec4 v(cameraPos, 1.0);
        v = m * v;
        cameraPos = glm::vec3(v);

        glfwSetTime(0.0);

        pys.step();

        averageNewtonStep.addSec(glfwGetTime());
        glfwSetTime(0.0);

        const int dropRate = 10;
        static int nextDrop = dropRate;
        static int dropType = 0;
        if (!--nextDrop) {
            nextDrop = dropRate;
            if (dropType++ == 4) {
                dropType = 0;
            }
            //
//            dropType = 1;
            //
            switch (dropType) {
                case 0:
                    pys.addBox();
                    break;
                case 1:
                    pys.addSphere();
                    break;
                case 2:
                    pys.addCylinder();
                    break;
                case 3:
                    pys.addCone();
                    break;
            }
        }

        // Shadow Map

        // http://learnopengl.com/#!Advanced-Lighting/Shadows/Shadow-Mapping
//        glCullFace(GL_FRONT);
//        glCullFace(GL_BACK); // don't forget to reset original culling face


//        glm::vec3 lightInvDir = glm::vec3(0.5f, 2, 2);
//        auto lightInvDir = glm::vec3(4, -4, 8);
        auto lightInvDir = lightPos;
//        auto lightInvDir = cameraPos;

        glUseProgram(shadowProgramId);

        // The framebuffer, which regroups 0, 1, or more textures, and 0 or 1 depth buffer.
        GLuint FramebufferName = 0;
        glGenFramebuffers(1, &FramebufferName);
        glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);
        // Depth texture. Slower than a depth buffer, but you can sample it later in your shader
        GLuint depthTexture;
        glGenTextures(1, &depthTexture);
        glBindTexture(GL_TEXTURE_2D, depthTexture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, shadowMapWH, shadowMapWH, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthTexture, 0);
        glViewport(0, 0, shadowMapWH, shadowMapWH);

        glDrawBuffer(GL_NONE); // No color buffer is drawn to.
        glReadBuffer(GL_NONE);

        // Check that framebuffer is ok
        if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
            fmt::print(stderr, "Invalid framebuffer\n");
            exit(0);
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 depthProjectionMatrix = glm::ortho<float>(-10.0f, 10.0f, -10.0f, 10.0f, 0.1f, 30.0f);
        glm::mat4 depthViewMatrix = glm::lookAt(lightInvDir, glm::vec3(0,0,0), glm::vec3(0,1,0));

        GLint depthMatrixID = glGetUniformLocation(shadowProgramId, "depthMVP");
        if (depthMatrixID < 0) {
            fmt::print(stderr, "Warning: depthMatrixID={}\n", depthMatrixID);
        }

        auto floorDepthMVP = depthProjectionMatrix * depthViewMatrix * floorModelMatrix;
        glUniformMatrix4fv(depthMatrixID, 1, GL_FALSE, glm::value_ptr(floorDepthMVP));
        floorMesh.drawShadow();

        for (int i = 0; i < pys.getLen(); ++i) {
            auto modelMatrix = pys.get(i);
            auto depthMVP = depthProjectionMatrix * depthViewMatrix * modelMatrix;
            glUniformMatrix4fv(depthMatrixID, 1, GL_FALSE, glm::value_ptr(depthMVP));
            switch (pys.getType(i)) {
                case 0:
                    boxMesh.drawShadow();
                    break;
                case 1:
                    sphereMesh.drawShadow();
                    break;
                case 2:
                    cylinderMesh.drawShadow();
                    break;
                case 3:
                    coneMesh.drawShadow();
                    break;
            }
        }

//        static int c = 0;
//        if (c++ == 50) {
//            save_screenshot("tex.tga", 1024, 1024);
//            exit(0);
//        }

//        exit(0);

//        // Switch back to regular frame buffer.
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glViewport(0, 0, window_w, window_h);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//        GLuint testTextureId;
//        glGenTextures(1, &testTextureId);
//        glBindTexture(GL_TEXTURE_2D, testTextureId);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, testTexW, testTexH, 0, GL_RGBA, GL_UNSIGNED_BYTE, &testVec[0]);
////        glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA, 1024, 1024);
////        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 1024, 1024, GL_RGBA, GL_UNSIGNED_BYTE, &testVec[0]);

//        showTexture(window_w, window_h, depthTexture);

//        glBindTexture(GL_TEXTURE_2D, 0);
//        glDeleteTextures(1, &testTextureId);


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        glBindTexture(GL_TEXTURE_2D, depthTexture);
        glActiveTexture(GL_TEXTURE0);

        glUseProgram(phongProgramId);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);

        // 45 deg = 0.785 radians, 60 = 1.04, 80 = 1.40
        auto projectionMatrix = glm::perspective(1.04f, aspect_ratio, 0.1f, 100.0f);
        glUniformMatrix4fv(phongProjectionMatrixId, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
        auto viewMatrix = glm::lookAt(cameraPos, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
        glUniformMatrix4fv(phongViewMatrixId, 1, GL_FALSE, glm::value_ptr(viewMatrix));

        glm::mat4 biasMatrix(
            0.5, 0.0, 0.0, 0.0,
            0.0, 0.5, 0.0, 0.0,
            0.0, 0.0, 0.5, 0.0,
            0.5, 0.5, 0.5, 1.0
        );

        glm::mat4 depthMVP = depthProjectionMatrix * depthViewMatrix * floorModelMatrix;
        glm::mat4 depthBiasMVP = biasMatrix * depthMVP;
        GLint depthBiasMVPId = glGetUniformLocation(phongProgramId, "depthBiasMVP");
        if (depthBiasMVPId < 0) {
            fmt::print(stderr, "Warning: depthBiasMVPId={}\n", depthBiasMVPId);
        }
        glUniformMatrix4fv(depthBiasMVPId, 1, GL_FALSE, glm::value_ptr(depthBiasMVP));
        glUniformMatrix4fv(phongModelMatrixId, 1, GL_FALSE, glm::value_ptr(floorModelMatrix));
        floorMesh.draw();

        for (int i = 0; i < pys.getLen(); ++i) {
            auto modelMatrix = pys.get(i);

            glm::mat4 depthMVP = depthProjectionMatrix * depthViewMatrix * modelMatrix;
            glm::mat4 depthBiasMVP = biasMatrix * depthMVP;
            GLint depthBiasMVPId = glGetUniformLocation(phongProgramId, "depthBiasMVP");
            if (depthBiasMVPId < 0) {
                fmt::print(stderr, "Warning: depthBiasMVPId={}\n", depthBiasMVPId);
            }
            glUniformMatrix4fv(depthBiasMVPId, 1, GL_FALSE, glm::value_ptr(depthBiasMVP));
            glUniformMatrix4fv(phongModelMatrixId, 1, GL_FALSE, glm::value_ptr(modelMatrix));

            switch (pys.getType(i)) {
                case 0:
                    boxMesh.draw();
                    break;
                case 1:
                    sphereMesh.draw();
                    break;
                case 2:
                    cylinderMesh.draw();
                    break;
                case 3:
                    coneMesh.draw();
                    break;
            }
        }

        glDeleteFramebuffers(1, &FramebufferName);
        glBindTexture(GL_TEXTURE_2D, 0);
        glDeleteTextures(1, &depthTexture);

        // Can be very bad for performance.
        glFinish();

        averageRendering.addSec(glfwGetTime());
        glfwSetTime(0.0);

        auto avgNewtonStepSec = averageNewtonStep.calcAverage();
        auto avgRenderingSec = averageRendering.calcAverage();

        double avgTotalSec = avgNewtonStepSec + avgRenderingSec;

        auto nLine = 0;
        oglText.print(0, 0, nLine++, fmt::format("Objects: {}", pys.getLen()));
        oglText.print(0, 0, nLine++, fmt::format("Newton: {:.1f}ms", avgNewtonStepSec * 1000));
        oglText.print(0, 0, nLine++, fmt::format("Render: {:.1f}ms", avgRenderingSec * 1000));
        oglText.print(0, 0, nLine++, fmt::format("Total: {:.1f}ms", avgTotalSec * 1000));
        oglText.print(0, 0, nLine++, fmt::format("FPS: {:d}", static_cast<int>(1.0 / avgTotalSec)));

		glfwSwapBuffers(window);

        // Create movie
        // avconv -framerate 60 -i img/frame_%06d.tga -c:v libx264 -pix_fmt yuv420p -r 60 -crf 16 video.mp4
        if (!recDirPath.empty()) {
            create_directories(recDirPath);
            static int frameIdx = 0;
            char fileName[100];
            sprintf(fileName, "frame_%06d.tga", frameIdx++);
//            auto filePath = recDirPath;
//            filePath += path(fileName);
//            cout << filePath.c_str() << endl;
            save_screenshot((recDirPath / path(fileName)).string(), window_w, window_h);
            if (frameIdx == 3 * 60 * 60) {
                break;
            }
        }

        checkGlError();

		glfwPollEvents();
    }

	glDeleteProgram(phongProgramId);
	glDeleteVertexArrays(1, &vertexArrayId);

	glfwTerminate();

    return 0;
}

