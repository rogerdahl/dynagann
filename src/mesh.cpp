#include <cstdlib>
#include <vector>

//#include <stdio.h>

#include "int_types.h"
#include "mesh.h"

using namespace std;


static void par_shapes__cone(float const* uv, float* xyz, void* userdata)
{
    float theta = uv[1] * 2 * PAR_PI;
    xyz[0] = sinf(theta) * (1.0f - uv[0]);
    xyz[1] = cosf(theta) * (1.0f - uv[0]);
    xyz[2] = uv[0];
}

par_shapes_mesh* par_shapes_create_cone(int slices, int stacks)
{
    if (slices < 3 || stacks < 1) {
        return 0;
    }
    return par_shapes_create_parametric(par_shapes__cone, slices, stacks, 0);
}


Mesh::Mesh(Shape shape, GLuint shaderId, glm::vec4 objectColor)
: programId_(shaderId), objectColor_(objectColor)
{
    par_shapes_mesh* mesh;

    switch(shape) {
        case SHAPE_BOX:
        {
            mesh = par_shapes_create_cube();
            // We unweld and recompute the normals as shared normals at the corners breaks the phong ligthing shaders
            // we use.
            par_shapes_unweld(mesh, true);
            par_shapes_compute_normals(mesh);
            par_shapes_translate(mesh, -.5f, -.5f, -.5f);
            break;
        }
        case SHAPE_SPHERE:
        {
            mesh = par_shapes_create_subdivided_sphere(2);
            par_shapes_scale(mesh, 0.5f, 0.5f, 0.5f);
//            mesh = par_shapes_create_parametric_sphere(10, 10);
//            par_shapes_translate(mesh, -.5f, -.5f, -.5f);
            break;
        }
        case SHAPE_ROCK:
        {
            mesh = par_shapes_create_rock(rand(), 2);
            par_shapes_translate(mesh, -.5f, -.5f, -.5f);
            break;
        }
        case SHAPE_CYLINDER:
        {
            int slices = 20;
            int stacks = 20;
            // cylinder
            mesh = par_shapes_create_cylinder(slices, stacks);
//            mesh = par_shapes_create_empty();
            // caps
            float radius = 1.0f;
            float center[] = {0, 0, 1};
            float normal[] = {0, 0, 1};

            par_shapes_mesh* disk1;
            disk1 = par_shapes_create_disk(radius, slices, center, normal);
            par_shapes_merge(mesh, disk1);
            par_shapes_free_mesh(disk1);

            par_shapes_mesh* disk2;
            float center2[] = {0, 0, 0};
            float normal2[] = {0, 0, 1};
            disk2 = par_shapes_create_disk(radius, slices, center2, normal2);

            float rotate[] = {0, 1, 0};
            par_shapes_rotate(disk2, PAR_PI, rotate);

//            par_shapes_invert(disk2, 0, slices);

            par_shapes_merge(mesh, disk2);
            par_shapes_free_mesh(disk2);

            par_shapes_translate(mesh, 0, 0, -.5);
            par_shapes_scale(mesh, 0.5f, 0.5f, 0.5f);
            float rotate2[] = {0, 1, 0};
            par_shapes_rotate(mesh, PAR_PI / 2, rotate2);

//            par_shapes_unweld(mesh, true);
//            par_shapes_compute_normals(mesh);
//            par_shapes_translate(mesh, -.5f, -.5f, -.5f);
            break;
        }
        case SHAPE_CONE:
        {
            float radius = 1.0f;
            int slices = 20;
            int stacks = 10;
            // cylinder
            mesh = par_shapes_create_cone(slices, stacks);
            // cap
            par_shapes_mesh* disk2;
            float center2[] = {0, 0, 0};
            float normal2[] = {0, 0, 1};
            disk2 = par_shapes_create_disk(radius, slices, center2, normal2);
            float rotate[] = {0, 1, 0};
            par_shapes_rotate(disk2, PAR_PI, rotate);
            par_shapes_merge(mesh, disk2);
            par_shapes_free_mesh(disk2);

            par_shapes_translate(mesh, 0, 0, -.5);
            par_shapes_scale(mesh, 0.5f, 0.5f, 2.0f);
            float rotate2[] = {0, 1, 0};
            par_shapes_rotate(mesh, PAR_PI / 2, rotate2);
            break;
        }
    };

    faceVertexToFlat(mesh);
    par_shapes_free_mesh(mesh);

	glGenBuffers(1, &vertexBufId_);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufId_);
	glBufferData(GL_ARRAY_BUFFER, triangle_vec_.size() * sizeof(GL_FLOAT), &triangle_vec_[0], GL_STATIC_DRAW);

	glGenBuffers(1, &normalBufId_);
	glBindBuffer(GL_ARRAY_BUFFER, normalBufId_);
	glBufferData(GL_ARRAY_BUFFER, normal_vec_.size() * sizeof(GL_FLOAT), &normal_vec_[0], GL_STATIC_DRAW);
}

Mesh::~Mesh()
{
    glDeleteBuffers(1, &vertexBufId_);
    glDeleteBuffers(1, &normalBufId_);
}

void Mesh::drawShadow()
{
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufId_);
    glVertexAttribPointer(
        0,         // attribute
        3,         // size
        GL_FLOAT,  // type
        GL_FALSE,  // normalized?
        0,         // stride
        (void*)0   // array buffer offset
    );

    glDrawArrays(GL_TRIANGLES, 0, triangle_vec_.size());

    glDisableVertexAttribArray(0);
}

void Mesh::draw()
{
    GLuint objectColorId = glGetUniformLocation(programId_, "uniSurfaceColor");
    assert(objectColorId);
    glUniform4fv(objectColorId, 1, glm::value_ptr(objectColor_));

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufId_);
    glVertexAttribPointer(
        0,         // attribute
        3,         // size
        GL_FLOAT,  // type
        GL_FALSE,  // normalized?
        0,         // stride
        (void*)0   // array buffer offset
    );

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, normalBufId_);
    glVertexAttribPointer(
        1,         // attribute
        3,         // size
        GL_FLOAT,  // type
        GL_FALSE,  // normalized?
        0,         // stride
        (void*)0   // array buffer offset
    );

    glDrawArrays(GL_TRIANGLES, 0, triangle_vec_.size());

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}

vector<float>& Mesh::getTriangleVec()
{
    return triangle_vec_;
}

vector<float>& Mesh::getNormalVec()
{
    return normal_vec_;
}

//
// private
//

// Convert from the face-vertex format returned by par_shapes to flat lists of vertices and normals.
void Mesh::faceVertexToFlat(par_shapes_mesh* mesh)
{
    // 3 points per triangle
    for (u32 i = 0; i < (u32)mesh->ntriangles * 3; ++i) {
        PAR_SHAPES_T point_idx = mesh->triangles[i];
        float* point_ptr = mesh->points + point_idx * 3;
        float* normal_ptr = mesh->normals + point_idx * 3;
        // x, y, z = 3 values per point
        for (u32 j = 0; j < 3; ++j) {
            triangle_vec_.push_back(*point_ptr++);
            normal_vec_.push_back(*normal_ptr++);
        }
    }
}

void Mesh::dumpMesh()
{
    printf("npoints=%lld\n", triangle_vec_.size() / 3);
    printf("ntriangles=%lld\n", triangle_vec_.size() / (3 * 3));

    for (u32 i = 0; i < triangle_vec_.size(); ++i) {
        printf("%f ", triangle_vec_[i]);
        if (! ((i + 1) % 3)) {
            printf("\n");
        }
        if (! ((i + 1) % 9)) {
            printf("\n");
        }
    }
}
