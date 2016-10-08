#include <vector>

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#include <par_shapes.h>

enum Shape {
    SHAPE_SPHERE,
    SHAPE_BOX,
    SHAPE_ROCK,
	SHAPE_CYLINDER,
	SHAPE_CONE,
};

class Mesh
{
public:
    Mesh(Shape, GLuint shader, glm::vec4 objectColor);
    ~Mesh();
    void draw();
    void drawShadow();
    std::vector<float>& getTriangleVec();
    std::vector<float>& getNormalVec();
private:
    void faceVertexToFlat(par_shapes_mesh* mesh);
    void dumpMesh();

    std::vector<float> triangle_vec_;
    std::vector<float> normal_vec_;

    GLuint programId_;
    glm::vec4 objectColor_;

    GLuint vertexBufId_;
	GLuint normalBufId_;
};
