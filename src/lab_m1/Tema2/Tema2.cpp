#include "lab_m1/Tema2/Tema2.h"
#include "lab_m1/Tema2/transform3D.h"

#include <vector>
#include <string>
#include <iostream>

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema2::Tema2()
{
}


Tema2::~Tema2()
{
}


void Tema2::Init()
{
    renderCameraTarget = false;

    translateX = -1.9f;
    translateZ = 2.0f;

    camera = new implemented::Camera_Tema2();
    camera->Set(glm::vec3(-1, 1, 2.f), glm::vec3(-1.9, 0.3f, 2.0f), glm::vec3(0, 1, 0));

    // Sets the resolution of the small viewport
    glm::ivec2 resolution = window->GetResolution();
    miniViewportArea = ViewportArea(50, 50, resolution.x / 5.f, resolution.y / 5.f);

    zoom = 10.0f;
    initialFov = 60;
    changeFov = 1;


    angle_car = 0;
    masina_pista = true;

    srand(time(NULL));

    projectionMatrix = glm::perspective(RADIANS(90), window->props.aspectRatio, 0.01f, 200.0f);

    polygonMode = GL_FILL;
    // Create race track
    {
        // puncte ce definesc traseul

        puncte.push_back(glm::vec3(4.86f, 0, 0.29f)); // A
        puncte.push_back(glm::vec3(4.21f, 0, 1.4f)); // B
        puncte.push_back(glm::vec3(2.79f, 0, 2.14f)); // C
        puncte.push_back(glm::vec3(1.5f, 0, 1.95f)); // D
        puncte.push_back(glm::vec3(0.59f, 0, 1.25f)); // E
        puncte.push_back(glm::vec3(-0.48f, 0, 0.6f)); // F
        puncte.push_back(glm::vec3(-1.76f, 0, 1.15f)); // G
        puncte.push_back(glm::vec3(-2.83f, 0, 1.43f)); // H
        puncte.push_back(glm::vec3(-3.79f, 0, 0.81f)); // I
        puncte.push_back(glm::vec3(-3.93f, 0, -0.19f)); // J
        puncte.push_back(glm::vec3(-3.45f, 0, -1.05f)); // K
        puncte.push_back(glm::vec3(-2.11f, 0, -1.55f)); // L
        puncte.push_back(glm::vec3(-0.68f, 0, -1.62f)); // M
        puncte.push_back(glm::vec3(0.44f, 0, -0.98f)); // N
        puncte.push_back(glm::vec3(1.39f, 0, -0.23f)); // O
        puncte.push_back(glm::vec3(2.58f, 0, -0.74f)); // P
        puncte.push_back(glm::vec3(3.44f, 0, -1.44f)); // Q
        puncte.push_back(glm::vec3(4.56f, 0, -1.2f)); // R 17 
        puncte.push_back(glm::vec3(4.86f, 0, 0.29f)); // A = 18

        for (int i = 0; i < puncte.size(); i++) {
            puncte[i] *= 2.25f;
        }

        for (int i = 0; i < 18; i++) {
            puncte_interior.push_back(glm::vec3(0, 0, 0));
        }
        for (int i = 0; i < puncte.size() - 1; i++) {
            glm::vec3 D = puncte[i + 1] - puncte[i];
            glm::vec3 perpendicular = cross(D, glm::vec3(0, 1, 0));
            glm::vec3 pct_ext = puncte[i] + 0.4f * perpendicular;
            puncte_exterior.push_back(pct_ext);
            glm::vec3 pct_interior = puncte[i] - 0.4f * perpendicular;
            puncte_interior.push_back(pct_interior);

            perpendiculars.push_back(perpendicular);
        }
        vector<VertexFormat> vertices{
            // contur exterior
            VertexFormat(puncte_exterior[0], glm::vec3(1, 0, 1)),
            VertexFormat(puncte_exterior[1], glm::vec3(1, 0, 1)),
            VertexFormat(puncte_exterior[2], glm::vec3(1, 0, 1)),
            VertexFormat(puncte_exterior[3], glm::vec3(1, 0, 1)),
            VertexFormat(puncte_exterior[4], glm::vec3(1, 0, 1)),
            VertexFormat(puncte_exterior[5], glm::vec3(1, 0, 1)),
            VertexFormat(puncte_exterior[6], glm::vec3(1, 0, 1)),
            VertexFormat(puncte_exterior[7], glm::vec3(1, 0, 1)),
            VertexFormat(puncte_exterior[8], glm::vec3(1, 0, 1)),
            VertexFormat(puncte_exterior[9], glm::vec3(1, 0, 1)),
            VertexFormat(puncte_exterior[10], glm::vec3(1, 0, 1)),
            VertexFormat(puncte_exterior[11], glm::vec3(1, 0, 1)),
            VertexFormat(puncte_exterior[12], glm::vec3(1, 0, 1)),
            VertexFormat(puncte_exterior[13], glm::vec3(1, 0, 1)),
            VertexFormat(puncte_exterior[14], glm::vec3(1, 0, 1)),
            VertexFormat(puncte_exterior[15], glm::vec3(1, 0, 1)),
            VertexFormat(puncte_exterior[16], glm::vec3(1, 0, 1)),
            VertexFormat(puncte_exterior[17], glm::vec3(1, 0, 1)),

            // contur interior
            VertexFormat(puncte_interior[18], glm::vec3(1, 0, 1)),
            VertexFormat(puncte_interior[19], glm::vec3(1, 0, 1)),
            VertexFormat(puncte_interior[20], glm::vec3(1, 0, 1)),
            VertexFormat(puncte_interior[21], glm::vec3(1, 0, 1)),
            VertexFormat(puncte_interior[22], glm::vec3(1, 0, 1)),
            VertexFormat(puncte_interior[23], glm::vec3(1, 0, 1)),
            VertexFormat(puncte_interior[24], glm::vec3(1, 0, 1)),
            VertexFormat(puncte_interior[25], glm::vec3(1, 0, 1)),
            VertexFormat(puncte_interior[26], glm::vec3(1, 0, 1)),
            VertexFormat(puncte_interior[27], glm::vec3(1, 0, 1)),
            VertexFormat(puncte_interior[28], glm::vec3(1, 0, 1)),
            VertexFormat(puncte_interior[29], glm::vec3(1, 0, 1)),
            VertexFormat(puncte_interior[30], glm::vec3(1, 0, 1)),
            VertexFormat(puncte_interior[31], glm::vec3(1, 0, 1)),
            VertexFormat(puncte_interior[32], glm::vec3(1, 0, 1)),
            VertexFormat(puncte_interior[33], glm::vec3(1, 0, 1)),
            VertexFormat(puncte_interior[34], glm::vec3(1, 0, 1)),
            VertexFormat(puncte_interior[35], glm::vec3(1, 0, 1)),
        };
        vector<unsigned int> indices = {
            0, 18, 1,
            18, 19, 1,
            19, 1, 2,
            20, 19, 2,
            20, 3, 2,
            3, 20, 21,
            4, 3, 21,
            4, 22, 21,
            5, 4, 22,
            5, 23, 22,
            6, 5, 23,
            6, 24, 23,
            7, 6, 24,
            7, 25, 24,
            8, 7, 25,
            8, 25, 26,
            9, 8, 26,
            9, 26, 27,
            9, 10, 27,
            10, 28, 27,
            10, 11, 28,
            11, 28, 29,
            11, 12, 29,
            12, 29, 30,
            12, 13, 30,
            30, 31, 13,
            13, 14, 31,
            31, 32, 14,
            14, 15, 32,
            32, 33, 15,
            15, 16, 33,
            33, 34, 16,
            34, 16, 17,
            34, 35, 17,
            17, 35, 0,
            35, 18, 0
        };
        CreateMesh("raceTrack", vertices, indices);
    }

    // masini 
    for (int i = 0; i < 10; i++) {
        indici.push_back(i);
        poz_cr_masina.push_back(puncte[i]);
        poz_urm_masina.push_back(puncte[i + 1]);

    }
    // Creare iarba 
    {
        vector<VertexFormat> vertices{
            VertexFormat(glm::vec3(0, 0, 0), glm::vec3(0.3372f, 0.4156f, 0.0235f)),
            VertexFormat(glm::vec3(1, 0, 0), glm::vec3(0.3372f, 0.4156f, 0.0235f)),
            VertexFormat(glm::vec3(0, 0, 1), glm::vec3(0.3372f, 0.4156f, 0.0235f)),
        };
        vector<unsigned int> indices = {
            0, 1, 2
        };
        CreateMesh("grass", vertices, indices);
    }
    // Creare iarba 
    {
        vector<VertexFormat> vertices{
            VertexFormat(glm::vec3(0, 0, 0), glm::vec3(0.3372f, 0.4156f, 0.0235f)),
            VertexFormat(glm::vec3(-1, 0, 0), glm::vec3(0.3372f, 0.4156f, 0.0235f)),
            VertexFormat(glm::vec3(0, 0, 1), glm::vec3(0.3372f, 0.4156f, 0.0235f)),
        };
        vector<unsigned int> indices = {
            0, 1, 2
        };
        CreateMesh("grass1", vertices, indices);
    }

    // Creare iarba 
    {
        vector<VertexFormat> vertices{
            VertexFormat(glm::vec3(0, 0, 0), glm::vec3(0.3372f, 0.4156f, 0.0235f)),
            VertexFormat(glm::vec3(1, 0, 0), glm::vec3(0.3372f, 0.4156f, 0.0235f)),
            VertexFormat(glm::vec3(0, 0, -1), glm::vec3(0.3372f, 0.4156f, 0.0235f)),
        };
        vector<unsigned int> indices = {
            0, 1, 2
        };
        CreateMesh("grass2", vertices, indices);
    }
    // Creare iarba 
    {
        vector<VertexFormat> vertices{
            VertexFormat(glm::vec3(0, 0, 0), glm::vec3(0.3372f, 0.4156f, 0.0235f)),
            VertexFormat(glm::vec3(-1, 0, 0), glm::vec3(0.3372f, 0.4156f, 0.0235f)),
            VertexFormat(glm::vec3(0, 0, -1), glm::vec3(0.3372f, 0.4156f, 0.0235f)),
        };
        vector<unsigned int> indices = {
            0, 1, 2
        };
        CreateMesh("grass3", vertices, indices);
    }
    {
        Mesh* mesh = new Mesh("plane50");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "plane50.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    // Creare trunchi copac
    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(0, 0, 0), glm::vec3(0.4039f, 0.2784f, 0.0235f)),
            VertexFormat(glm::vec3(0.5f, 0, 0), glm::vec3(0.4039f, 0.2784f, 0.0235f)),
            VertexFormat(glm::vec3(0.5f, 1, 0), glm::vec3(0.4039f, 0.2784f, 0.0235f)),
            VertexFormat(glm::vec3(0, 1, 0), glm::vec3(0.4039f, 0.2784f, 0.0235f)),
            VertexFormat(glm::vec3(0, 0, 0.5f), glm::vec3(0.4039f, 0.2784f, 0.0235f)),
            VertexFormat(glm::vec3(0.5f, 0, 0.5f), glm::vec3(0.4039f, 0.2784f, 0.0235f)),
            VertexFormat(glm::vec3(0.5f, 1, 0.5f), glm::vec3(0.4039f, 0.2784f, 0.0235f)),
            VertexFormat(glm::vec3(0, 1, 0.5f), glm::vec3(0.4039f, 0.2784f, 0.0235f))
        };

        vector<unsigned int> indices =
        {
            0, 1, 2,
            0, 3, 2,
            0, 3, 7,
            0, 4, 7,
            1, 2, 6,
            1, 5, 6,
            3, 2, 7,
            2, 6, 7,
            0, 1, 4,
            1, 5, 4,
            4, 5, 6,
            5, 6, 7,
        };
        CreateMesh("trunchi", vertices, indices);
    }
    // Creare cub pt copac
    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(0, 0, 1), glm::vec3(0.0235f, 0.4039f, 0.2862f)),
            VertexFormat(glm::vec3(1, 0, 1), glm::vec3(0.0235f, 0.4039f, 0.2862f)),
            VertexFormat(glm::vec3(0, 1, 1), glm::vec3(0.0235f, 0.4039f, 0.2862f)),
            VertexFormat(glm::vec3(1, 1, 1), glm::vec3(0.0235f, 0.4039f, 0.2862f)),
            VertexFormat(glm::vec3(0, 0, 0), glm::vec3(0.0235f, 0.4039f, 0.2862f)),
            VertexFormat(glm::vec3(1, 0, 0), glm::vec3(0.0235f, 0.4039f, 0.2862f)),
            VertexFormat(glm::vec3(0, 1, 0), glm::vec3(0.0235f, 0.4039f, 0.2862f)),
            VertexFormat(glm::vec3(1, 1, 0), glm::vec3(0.0235f, 0.4039f, 0.2862f))
        };

        vector<unsigned int> indices =
        {
            0, 1, 2,
            1, 3, 2,
            2, 3, 7,
            2, 7, 6,
            1, 7, 3,
            1, 5, 7,
            6, 7, 4,
            7, 5, 4,
            0, 4, 1,
            1, 4, 5,
            2, 6, 4,
            0, 2, 4
        };
        CreateMesh("cub", vertices, indices);
    }
    // Creare masina, forma paralelipiped
    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(0, 0, 0), glm::vec3(0.9607f, 0.6901f, 0.2549f)),
            VertexFormat(glm::vec3(0.25, 0, 0), glm::vec3(0.9607f, 0.6901f, 0.2549f)),
            VertexFormat(glm::vec3(0.25, 0.125, 0), glm::vec3(0.9607f, 0.6901f, 0.2549f)),
            VertexFormat(glm::vec3(0, 0.125, 0), glm::vec3(0.9607f, 0.6901f, 0.2549f)),
            VertexFormat(glm::vec3(0, 0, 0.125), glm::vec3(0.9607f, 0.6901f, 0.2549f)),
            VertexFormat(glm::vec3(0.25, 0, 0.125), glm::vec3(0.9607f, 0.6901f, 0.2549f)),
            VertexFormat(glm::vec3(0.25, 0.125, 0.125), glm::vec3(0.9607f, 0.6901f, 0.2549f)),
            VertexFormat(glm::vec3(0, 0.125, 0.125), glm::vec3(0.9607f, 0.6901f, 0.2549f))
        };

        vector<unsigned int> indices =
        {
            0, 1, 2,
            0, 3, 2,
            0, 3, 7,
            0, 4, 7,
            1, 2, 6,
            1, 5, 6,
            3, 2, 7,
            2, 6, 7,
            0, 1, 4,
            1, 5, 4,
            4, 5, 6,
            5, 6, 7,
        };
        CreateMesh("masina", vertices, indices);
    }
    // obstacol 1
    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(0, 0, 0), glm::vec3(0.6607f, 0.3901f, 0.7549f)),
            VertexFormat(glm::vec3(0.5, 0, 0),glm::vec3(0.6607f, 0.3901f, 0.7549f)),
            VertexFormat(glm::vec3(0.5, 0.25, 0), glm::vec3(0.6607f, 0.3901f, 0.7549f)),
            VertexFormat(glm::vec3(0, 0.25, 0), glm::vec3(0.6607f, 0.3901f, 0.7549f)),
            VertexFormat(glm::vec3(0, 0, 0.25), glm::vec3(0.6607f, 0.3901f, 0.7549f)),
            VertexFormat(glm::vec3(0.5, 0, 0.25), glm::vec3(0.6607f, 0.3901f, 0.7549f)),
            VertexFormat(glm::vec3(0.5, 0.25, 0.25), glm::vec3(0.6607f, 0.3901f, 0.7549f)),
            VertexFormat(glm::vec3(0, 0.25, 0.25), glm::vec3(0.6607f, 0.3901f, 0.7549f))
        };

        vector<unsigned int> indices =
        {
            0, 1, 2,
            0, 3, 2,
            0, 3, 7,
            0, 4, 7,
            1, 2, 6,
            1, 5, 6,
            3, 2, 7,
            2, 6, 7,
            0, 1, 4,
            1, 5, 4,
            4, 5, 6,
            5, 6, 7,
        };
        CreateMesh("obstacol1", vertices, indices);
    }
    // obstacol 2 
    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(0, 0, 0), glm::vec3(0.2549f, 0.2980f, 0.9607f)),
            VertexFormat(glm::vec3(0.5, 0, 0),glm::vec3(0.2549f, 0.2980f, 0.9607f)),
            VertexFormat(glm::vec3(0.5, 0.25, 0), glm::vec3(0.2549f, 0.2980f, 0.9607f)),
            VertexFormat(glm::vec3(0, 0.25, 0), glm::vec3(0.2549f, 0.2980f, 0.9607f)),
            VertexFormat(glm::vec3(0, 0, 0.25), glm::vec3(0.2549f, 0.2980f, 0.9607f)),
            VertexFormat(glm::vec3(0.5, 0, 0.25), glm::vec3(0.2549f, 0.2980f, 0.9607f)),
            VertexFormat(glm::vec3(0.5, 0.25, 0.25), glm::vec3(0.2549f, 0.2980f, 0.9607f)),
            VertexFormat(glm::vec3(0, 0.25, 0.25), glm::vec3(0.2549f, 0.2980f, 0.9607f))
        };

        vector<unsigned int> indices =
        {
            0, 1, 2,
            0, 3, 2,
            0, 3, 7,
            0, 4, 7,
            1, 2, 6,
            1, 5, 6,
            3, 2, 7,
            2, 6, 7,
            0, 1, 4,
            1, 5, 4,
            4, 5, 6,
            5, 6, 7,
        };
        CreateMesh("obstacol2", vertices, indices);
    }
    // obstacol 3
    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(0, 0, 0), glm::vec3(0.9607f, 0.3941f, 0.2549f)),
            VertexFormat(glm::vec3(0.5, 0, 0),glm::vec3(0.9607f, 0.3941f, 0.2549f)),
            VertexFormat(glm::vec3(0.5, 0.25, 0), glm::vec3(0.9607f, 0.3941f, 0.2549f)),
            VertexFormat(glm::vec3(0, 0.25, 0), glm::vec3(0.9607f, 0.3941f, 0.2549f)),
            VertexFormat(glm::vec3(0, 0, 0.25), glm::vec3(0.9607f, 0.3941f, 0.2549f)),
            VertexFormat(glm::vec3(0.5, 0, 0.25), glm::vec3(0.9607f, 0.3941f, 0.2549f)),
            VertexFormat(glm::vec3(0.5, 0.25, 0.25), glm::vec3(0.9607f, 0.3941f, 0.2549f)),
            VertexFormat(glm::vec3(0, 0.25, 0.25), glm::vec3(0.9607f, 0.3941f, 0.2549f))
        };

        vector<unsigned int> indices =
        {
            0, 1, 2,
            0, 3, 2,
            0, 3, 7,
            0, 4, 7,
            1, 2, 6,
            1, 5, 6,
            3, 2, 7,
            2, 6, 7,
            0, 1, 4,
            1, 5, 4,
            4, 5, 6,
            5, 6, 7,
        };
        CreateMesh("obstacol3", vertices, indices);
    }
    {
        Shader* shader = new Shader("LabShader");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }


}
Mesh* Tema2::CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned int>& indices)
{
    unsigned int VAO = 0;
    // Create the VAO and bind it
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Create the VBO and bind it
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Send vertices data into the VBO buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

    // Create the IBO and bind it
    unsigned int IBO;
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

    // Send indices data into the IBO buffer
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

    // ========================================================================
    // This section demonstrates how the GPU vertex shader program
    // receives data.

    // TODO(student): If you look closely in the `Init()` and `Update()`
    // functions, you will see that we have three objects which we load
    // and use in three different ways:
    // - LoadMesh   + LabShader (this lab's shader)
    // - CreateMesh + VertexNormal (this shader is already implemented)
    // - CreateMesh + LabShader (this lab's shader)
    // To get an idea about how they're different from one another, do the
    // following experiments. What happens if you switch the color pipe and
    // normal pipe in this function (but not in the shader)? Now, what happens
    // if you do the same thing in the shader (but not in this function)?
    // Finally, what happens if you do the same thing in both places? Why?

    // Set vertex position attribute
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

    // Set vertex normal attribute
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));

    // Set texture coordinate attribute
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));

    // Set vertex color attribute
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));
    // ========================================================================

    // Unbind the VAO
    glBindVertexArray(0);

    // Check for OpenGL errors
    CheckOpenGLError();

    // Mesh information is saved into a Mesh object
    meshes[name] = new Mesh(name);
    meshes[name]->InitFromBuffer(VAO, static_cast<unsigned int>(indices.size()));
    meshes[name]->vertices = vertices;
    meshes[name]->indices = indices;
    return meshes[name];
}
void Tema2::FrameStart()
{
    glClearColor(0.1137f, 0.5294f, 0.8901f, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Sets the screen area where to draw
    glm::ivec2 resolution = window->GetResolution();
    glViewport(0, 0, resolution.x, resolution.y);
}
void Tema2::RenderScene(float deltaTimes) {

    // generare iarba
    {
        modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0.15f, 0));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(2.f));
        RenderSimpleMesh(meshes["plane50"], shaders["LabShader"], modelMatrix, glm::vec3(0.3372f, 0.4156f, 0.0235f));
    }
    // generare pista
    {
        modelMatrix = glm::mat4(1);
        modelMatrix *= transform3D::Translate(0, 0.25f, 0);
        RenderSimpleMesh(meshes["raceTrack"], shaders["LabShader"], modelMatrix, glm::vec3(1, 0, 1));
    }
   

    // generare copaci

    // pomi in interiorul pistei
    std::vector<glm::vec3> pomi_ext;
    pomi_ext.push_back(glm::vec3(1.9f, 0.15f, 0.1f));
    pomi_ext.push_back(glm::vec3(3.5f, 0.15f, 0.6f));
    pomi_ext.push_back(glm::vec3(4.9f, 0.15f, 0.1f));
    pomi_ext.push_back(glm::vec3(6.4f, 0.15f, -0.5f));
    pomi_ext.push_back(glm::vec3(7.5f, 0.15f, -1.8f));
    pomi_ext.push_back(glm::vec3(8.5f, 0.15f, -0.8f));
    pomi_ext.push_back(glm::vec3(1.9f, 0.25f, 1.4f));
    pomi_ext.push_back(glm::vec3(3.5f, 0.15f, 2.6f));
    pomi_ext.push_back(glm::vec3(4.9f, 0.15f, 3.1f));
    pomi_ext.push_back(glm::vec3(6.4f, 0.15f, 2.9f));
    pomi_ext.push_back(glm::vec3(8.4f, 0.15f, 0.8f));
    pomi_ext.push_back(glm::vec3(9.4f, 0.15f, 0.2f));
    pomi_ext.push_back(glm::vec3(1.9f, 0.15f, -0.1f));
    pomi_ext.push_back(glm::vec3(0.1f, 0.15f, -0.9f));
    pomi_ext.push_back(glm::vec3(-1.9f, 0.15f, -1.8f));
    pomi_ext.push_back(glm::vec3(-3.9f, 0.15f, -2.2f));
    pomi_ext.push_back(glm::vec3(-5.9f, 0.15f, -1.4f));
    pomi_ext.push_back(glm::vec3(-7.9f, 0.15f, -0.1f));
    pomi_ext.push_back(glm::vec3(-7.4f, 0.15f, 1.5f));
    pomi_ext.push_back(glm::vec3(-5.9f, 0.15f, 1.7f));
    pomi_ext.push_back(glm::vec3(-3.9f, 0.15f, 0.9f));
    pomi_ext.push_back(glm::vec3(-2.5f, 0.15f, 0.2f));
    pomi_ext.push_back(glm::vec3(-0.5f, 0.15f, 0.4f));

    for (int i = 0; i < pomi_ext.size(); i++) {

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform3D::Translate(pomi_ext[i].x, pomi_ext[i].y, pomi_ext[i].z);
        modelMatrix *= transform3D::Scale(0.5f, 0.5f, 0.5f);
        RenderSimpleMesh(meshes["trunchi"], shaders["LabShader"], modelMatrix, glm::vec3(0.4039f, 0.2784f, 0.0235f));

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform3D::Translate(pomi_ext[i].x - 0.1f, pomi_ext[i].y + 0.5f, pomi_ext[i].z - 0.1f);
        modelMatrix *= transform3D::Scale(0.5f, 0.5f, 0.5f);
        RenderSimpleMesh(meshes["cub"], shaders["LabShader"], modelMatrix, glm::vec3(0.0235f, 0.4039f, 0.2862f));
    }

    // pomi in exteriorul pistei
    std::vector<glm::vec3> pomi_int;
    pomi_int.push_back(glm::vec3(1.9f, 0.15f, 4.9f));
    pomi_int.push_back(glm::vec3(3.5f, 0.15f, 5.6f));
    pomi_int.push_back(glm::vec3(4.9f, 0.15f, 5.9f));
    pomi_int.push_back(glm::vec3(6.4f, 0.15f, 5.9f));
    pomi_int.push_back(glm::vec3(7.4f, 0.15f, 5.7f));
    pomi_int.push_back(glm::vec3(9.0f, 0.15f, 4.9f));
    pomi_int.push_back(glm::vec3(10.5f, 0.15f, 3.8f));
    pomi_int.push_back(glm::vec3(12.0f, 0.15f, 1.4f));
    pomi_int.push_back(glm::vec3(12.0f, 0.15f, 0.f));
    pomi_int.push_back(glm::vec3(0.8f, 0.15f, 4.2f));
    pomi_int.push_back(glm::vec3(-1.1f, 0.15f, 3.2f));
    pomi_int.push_back(glm::vec3(-3.1f, 0.15f, 3.5f));
    pomi_int.push_back(glm::vec3(-5.1f, 0.15f, 3.9f));
    pomi_int.push_back(glm::vec3(-7.1f, 0.15f, 4.2f));
    pomi_int.push_back(glm::vec3(-9.1f, 0.15f, 3.0f));
    pomi_int.push_back(glm::vec3(-7.1f, 0.15f, -4.4f));
    pomi_int.push_back(glm::vec3(-5.1f, 0.15f, -5.1f));
    pomi_int.push_back(glm::vec3(-3.1f, 0.15f, -5.2f));
    pomi_int.push_back(glm::vec3(-1.1f, 0.15f, -5.2f));
    pomi_int.push_back(glm::vec3(0.8f, 0.15f, -4.2f));
    pomi_int.push_back(glm::vec3(-9.9f, 0.15f, 0.1f));
    pomi_int.push_back(glm::vec3(-9.1f, 0.15f, -2.6f));
    pomi_int.push_back(glm::vec3(1.9f, 0.15f, -3.1f));
    pomi_int.push_back(glm::vec3(3.2f, 0.15f, -2.2f));
    pomi_int.push_back(glm::vec3(4.9f, 0.15f, -3.1f));
    pomi_int.push_back(glm::vec3(6.4f, 0.15f, -3.8f));
    pomi_int.push_back(glm::vec3(8.5f, 0.15f, -4.5f));
    pomi_int.push_back(glm::vec3(10.1f, 0.15f, -3.9f));
    pomi_int.push_back(glm::vec3(12.1f, 0.15f, -2.9f));
    pomi_int.push_back(glm::vec3(12.1f, 0.15f, -1.2f));
    pomi_int.push_back(glm::vec3(11.6f, 0.15f, 2.9f));

    for (int i = 0; i < pomi_int.size(); i++) {

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform3D::Translate(pomi_int[i].x, pomi_int[i].y, pomi_int[i].z);
        modelMatrix *= transform3D::Scale(0.5f, 0.5f, 0.5f);
        RenderSimpleMesh(meshes["trunchi"], shaders["LabShader"], modelMatrix, glm::vec3(0.4039f, 0.2784f, 0.0235f));

        modelMatrix = glm::mat4(1);
        modelMatrix *= transform3D::Translate(pomi_int[i].x - 0.1f, pomi_int[i].y + 0.5f, pomi_int[i].z - 0.1f);
        modelMatrix *= transform3D::Scale(0.5f, 0.5f, 0.5f);
        RenderSimpleMesh(meshes["cub"], shaders["LabShader"], modelMatrix, glm::vec3(0.0235f, 0.4039f, 0.2862f));
    }
    {
        // masina
        P = glm::vec3(translateX, 0.3f, translateZ);
        {
            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, P);
            modelMatrix *= transform3D::Translate(0.125f, 0.0625f, 0.0625f);
            modelMatrix *= transform3D::RotateOY(RADIANS(angle_car));
            modelMatrix *= transform3D::Translate(-0.025f, -0.0625f, -0.0625f);
            RenderSimpleMesh(meshes["masina"], shaders["LabShader"], modelMatrix, glm::vec3(0.9607f, 0.6901f, 0.2549f));
        }
    }

    for (int i = 0; i < 10; i++) {
        glm::mat4 aux = glm::mat4(1);
        glm::vec3 pozz_cr = poz_cr_masina[i];
        pozz_cr.y = 0.3f;
        aux = glm::translate(aux, pozz_cr);
        aux = glm::scale(aux, glm::vec3(0.5));
        if (i % 3 == 0) {
            RenderSimpleMesh(meshes["obstacol1"], shaders["LabShader"], aux, glm::vec3(0.6607f, 0.3901f, 0.7549f));
        }
        if(i % 3 == 1) {
            RenderSimpleMesh(meshes["obstacol2"], shaders["LabShader"], aux, glm::vec3(0.2549f, 0.2980f, 0.9607f));
        }
        if (i % 3 == 2) {
            RenderSimpleMesh(meshes["obstacol3"], shaders["LabShader"], aux, glm::vec3(0.9607f, 0.3941f, 0.2549f));
        }
    }
}

void Tema2::calculateCurrentPos(float deltaTimes) {

    for (int i = 0; i < 10; i++) {
        glm::vec3 poz_cr = poz_cr_masina[i];
        glm::vec3 poz_urm = poz_urm_masina[i];
        poz_cr.y = 0.3f;
        poz_urm.y = 0.3f;

        if (poz_cr.x < poz_urm.x) {
            poz_cr.x += 2 * deltaTimes / 4;
            if (poz_cr.x > poz_urm.x)
                poz_cr.x = poz_urm.x;
        }
            
        else if (poz_cr.x > poz_urm.x) {
            poz_cr.x -= 2 * deltaTimes / 4;
            if (poz_cr.x < poz_urm.x)
                poz_cr.x = poz_urm.x;
        }

        if (poz_cr.z < poz_urm.z) {
            poz_cr.z += 2 * deltaTimes / 4;
            if (poz_cr.z > poz_urm.z)
                poz_cr.z = poz_urm.z;
        }

        else if (poz_cr.z > poz_urm.z) {
            poz_cr.z -= 2 * deltaTimes / 4;
            if (poz_cr.z < poz_urm.z)
                poz_cr.z = poz_urm.z;
        }

        if(poz_cr == poz_urm) {
            int j = indici[i] + 1;
            if (j >= puncte.size() - 1)
                j = 0;
            int semn = rand() % 2;
            float dist = rand() % 21 / static_cast<float>(100);
            if (semn == 0) {
                poz_urm = puncte[j] + perpendiculars[j] * dist;
            }
            else {
                poz_urm = puncte[j] - perpendiculars[j] * dist;
            }
            
            poz_urm_masina[i] = poz_urm;
            indici[i] = j;

        }
        poz_cr_masina[i] = poz_cr;
    }
}

void Tema2::RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color)
{
    if (!mesh || !shader || !shader->GetProgramID())
        return;

    glUseProgram(shader->program);
    GLint colours = glGetUniformLocation(shader->program, "Colours");
    glUniform3fv(colours, 1, glm::value_ptr(color));

    int location = glGetUniformLocation(shader->program, "car_pos");
    glm::vec3 carr = glm::vec3(translateX, 0.3f, translateZ);
    glUniform3fv(location, 1, glm::value_ptr(carr));

    // Bind model matrix
    GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
    glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    // Bind view matrix
    glm::mat4 viewMatrix = camera->GetViewMatrix();
    int loc_view_matrix = glGetUniformLocation(shader->program, "View");
    glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));
    // Bind projection matrix
    int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
    glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    // Draw the object


    glBindVertexArray(mesh->GetBuffers()->m_VAO);
    glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
}

void Tema2::RenderMesh2(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix) {
    if (!mesh || !shader || !shader->program)
        return;

    // Render an object using the specified shader and the specified position
    shader->Use();
    glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
    glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    mesh->Render();
}

float Tema2::TriangleArea(glm::vec3 A, glm::vec3 B, glm::vec3 C) {
    glm::vec3 AB = glm::vec3(B.x - A.x, B.y - A.y, B.z - A.z);
    glm::vec3 AC = glm::vec3(C.x - A.x, C.y - A.y, C.z - A.z);
    float cross_prod = AB.y * AC.z - AB.z * AC.y - AB.x * AC.z + AB.z * AC.x + AB.x * AC.y - AB.y * AC.x;
    return abs(cross_prod) / 2;
}
bool Tema2::insideTriangle(glm::vec3 P, glm::vec3 A, glm::vec3 B, glm::vec3 C) {
    float triangle_area = TriangleArea(A, B, C);
    float area_sum = 0;
    area_sum = area_sum + TriangleArea(A, B, P);
    area_sum = area_sum + TriangleArea(A, C, P);
    area_sum = area_sum + TriangleArea(B, C, P);

    ///cout << "triangle " << triangle_area << endl;
    ///cout << "area_sum " << area_sum << endl;

    if (abs(triangle_area - area_sum) <= 0.001)
        return true;
    return false;

}
// puncte exterioare : 0 ... 17
// puncte interioare : 18 ... 35
bool Tema2::checkCar(glm::vec3 P) {
    if (insideTriangle(P, puncte_exterior[0], puncte_exterior[1], puncte_interior[18]) == true)
        return true;

    if (insideTriangle(P, puncte_exterior[1], puncte_exterior[2], puncte_interior[19]) == true)
        return true;

    if (insideTriangle(P, puncte_exterior[2], puncte_exterior[3], puncte_interior[20]) == true) 
        return true;

    if (insideTriangle(P, puncte_exterior[3], puncte_exterior[4], puncte_interior[21]) == true)
        return true;

    if (insideTriangle(P, puncte_exterior[4], puncte_exterior[5], puncte_interior[22]) == true)
        return true;

    if (insideTriangle(P, puncte_exterior[5], puncte_exterior[6], puncte_interior[23]) == true)
        return true;

    if (insideTriangle(P, puncte_exterior[6], puncte_exterior[7], puncte_interior[24]) == true)
        return true;

    if (insideTriangle(P, puncte_exterior[7], puncte_exterior[8], puncte_interior[25]) == true)
        return true;

    if (insideTriangle(P, puncte_exterior[8], puncte_exterior[9], puncte_interior[26]) == true)
        return true;

    if (insideTriangle(P, puncte_exterior[9], puncte_exterior[10], puncte_interior[27]) == true)
        return true;

    if (insideTriangle(P, puncte_exterior[10], puncte_exterior[11], puncte_interior[28]) == true)
        return true;

    if (insideTriangle(P, puncte_exterior[11], puncte_exterior[12], puncte_interior[29]) == true) 
        return true;

    if (insideTriangle(P, puncte_exterior[12], puncte_exterior[13], puncte_interior[30]) == true) 
        return true;
      
    if (insideTriangle(P, puncte_exterior[13], puncte_exterior[14], puncte_interior[31]) == true)
        return true;

    if (insideTriangle(P, puncte_exterior[14], puncte_exterior[15], puncte_interior[32]) == true) 
        return true;

    if (insideTriangle(P, puncte_exterior[15], puncte_exterior[16], puncte_interior[33]) == true) 
        return true;

    if (insideTriangle(P, puncte_exterior[16], puncte_exterior[17], puncte_interior[34]) == true) 
        return true;

    if (insideTriangle(P, puncte_exterior[17], puncte_exterior[0], puncte_interior[35]) == true)  
        return true;
    
    if (insideTriangle(P, puncte_interior[18], puncte_interior[19], puncte_exterior[1]) == true)
        return true;

    if (insideTriangle(P, puncte_interior[19], puncte_interior[20], puncte_exterior[2]) == true) 
        return true;

    if (insideTriangle(P, puncte_interior[20], puncte_interior[21], puncte_exterior[3]) == true) 
        return true;

    if (insideTriangle(P, puncte_interior[21], puncte_interior[22], puncte_exterior[4]) == true) 
        return true;

    if (insideTriangle(P, puncte_interior[22], puncte_interior[23], puncte_exterior[5]) == true) 
        return true;

    if (insideTriangle(P, puncte_interior[23], puncte_interior[24], puncte_exterior[6]) == true) 
        return true;

    if (insideTriangle(P, puncte_interior[24], puncte_interior[25], puncte_exterior[7]) == true) 
        return true;

    if (insideTriangle(P, puncte_interior[25], puncte_interior[26], puncte_exterior[8]) == true) 
        return true;

    if (insideTriangle(P, puncte_interior[26], puncte_interior[27], puncte_exterior[9]) == true) 
        return true;

    if (insideTriangle(P, puncte_interior[27], puncte_interior[28], puncte_exterior[10]) == true) 
        return true;

    if (insideTriangle(P, puncte_interior[28], puncte_interior[29], puncte_exterior[11]) == true) 
        return true;

    if (insideTriangle(P, puncte_interior[29], puncte_interior[30], puncte_exterior[12]) == true) 
        return true;

    if (insideTriangle(P, puncte_interior[30], puncte_interior[31], puncte_exterior[13]) == true) 
        return true;

    if (insideTriangle(P, puncte_interior[31], puncte_interior[32], puncte_exterior[14]) == true) 
        return true;

    if (insideTriangle(P, puncte_interior[32], puncte_interior[33], puncte_exterior[15]) == true) 
        return true;

    if (insideTriangle(P, puncte_interior[33], puncte_interior[34], puncte_exterior[16]) == true) 
        return true;

    if (insideTriangle(P, puncte_interior[34], puncte_interior[35], puncte_exterior[17]) == true) 
        return true;

    if (insideTriangle(P, puncte_interior[35], puncte_interior[18], puncte_exterior[0]) == true)
        return true;

    return false;
    
}

void Tema2::Update(float deltaTimeSeconds)
{
    glLineWidth(3);
    glPointSize(5);
    glPolygonMode(GL_FRONT_AND_BACK, polygonMode);
   
    calculateCurrentPos(deltaTimeSeconds);
    // proiectie perspectiva
    projectionMatrix = glm::perspective(RADIANS(90), window->props.aspectRatio, 0.01f, 200.0f);
    RenderScene(deltaTimeSeconds);
   
    
    glClear(GL_DEPTH_BUFFER_BIT);
    glViewport(miniViewportArea.x - 40, miniViewportArea.y - 60, miniViewportArea.width, miniViewportArea.height);
    // proiectie ortografica

    float scale = 2.0f;
    float aspect = static_cast<float>(miniViewportArea.width) / static_cast<float>(miniViewportArea.height);
    projectionMatrix = glm::ortho(-aspect * scale, aspect * scale, -scale, scale, 0.01f, 200.0f);
    // TODO(student): render the scene again, in the new viewport
    RenderScene(deltaTimeSeconds);
    
}

void Tema2::FrameEnd()
{
    //DrawCoordinateSystem(camera->GetViewMatrix(), projectionMatrix);
    //DrawCoordinateSystem();
}

/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */
bool Tema2::coliziune(glm::vec3 obstacolPos) {

    float dist = sqrt(
        (P.x - obstacolPos.x) * (P.x - obstacolPos.x) +
        (P.y - obstacolPos.y) * (P.y - obstacolPos.y) +
        (P.z - obstacolPos.z) * (P.z - obstacolPos.z)
    );

    return dist < 0.2;
}

bool Tema2::checkColiziune() {

    if (coliziune(poz_cr_masina[0]) == true
        || coliziune(poz_cr_masina[1]) == true
        || coliziune(poz_cr_masina[2]) == true
        || coliziune(poz_cr_masina[3]) == true
        || coliziune(poz_cr_masina[4]) == true
        || coliziune(poz_cr_masina[5]) == true
        || coliziune(poz_cr_masina[6]) == true
        || coliziune(poz_cr_masina[7]) == true
        || coliziune(poz_cr_masina[8]) == true
        || coliziune(poz_cr_masina[9]) == true)
        return true;
    return false;
}

void Tema2::OnInputUpdate(float deltaTime, int mods)
{

    // TODO(student): Add transformation logic
    if (window->KeyHold(GLFW_KEY_W)) {
        if (checkCar(glm::vec3(translateX - 2 * deltaTime / 4, 0, P.z)) == true && checkColiziune() == false) {
            //camera->Set(glm::vec3(translateX - deltaTime / 5 + 0.9, 1, 2.f), glm::vec3(translateX - deltaTime / 5, 0.3f, translateZ), glm::vec3(0, 1, 0));
            masina_pista = true;
            translateX -= 2 * deltaTime / 4;
            camera->position = glm::vec3(translateX + 0.9, 1, P.z);
            camera->TranslateForward(deltaTime / 4);
        }
        else
            masina_pista = false;
          
    }
    if (window->KeyHold(GLFW_KEY_S)) {
        if (checkCar(glm::vec3(translateX + 2 * deltaTime / 4, 0, P.z)) == true && checkColiziune() == false) {
            masina_pista = true;
            translateX += 2 * deltaTime / 4;
            camera->position = glm::vec3(translateX + 0.9, 1, P.z);
            camera->TranslateForward(-deltaTime / 4);
        }
        else
            masina_pista = false;  
    }
    if (window->KeyHold(GLFW_KEY_A)) {
        if (checkCar(glm::vec3(P.x, 0, translateZ + 2 * deltaTime / 4)) == true && checkColiziune() == false) {
            masina_pista = true;
            translateZ += 2 * deltaTime / 4;
            angle_car += deltaTime / 4;
            if (angle_car > 0.15) {
                angle_car = 0;
            }
            camera->position = glm::vec3(P.x + 0.9, 1, translateZ);
            camera->RotateThirdPerson_OY(angle_car / 50);
        }
        else
           masina_pista = false;
    }
    if (window->KeyHold(GLFW_KEY_D)) {
        if (checkCar(glm::vec3(P.x, 0, translateZ - 2 * deltaTime / 4)) == true && checkColiziune() == false) {
            masina_pista = true;
            translateZ -= 2 * deltaTime / 4;
            angle_car -= deltaTime / 4;
            if (angle_car < 0) {
                angle_car = 0.15;
            }
            camera->position = glm::vec3(P.x + 0.9, 1, translateZ);
            camera->RotateThirdPerson_OY(-angle_car / 50);
        }
        else
            masina_pista = false;
        
    } 
}


void Tema2::OnKeyPress(int key, int mods)
{
    // TODO(student): Add viewport movement and scaling logic
    if (key == GLFW_KEY_SPACE)
    {
        switch (polygonMode)
        {
        case GL_POINT:
            polygonMode = GL_FILL;
            break;
        case GL_LINE:
            polygonMode = GL_POINT;
            break;
        default:
            polygonMode = GL_LINE;
            break;
        }
    }
    if (key == GLFW_KEY_I) {
        miniViewportArea.x += 10;
    }
    if (key == GLFW_KEY_J) {
        miniViewportArea.x -= 10;
    }
    if (key == GLFW_KEY_K) {
        miniViewportArea.y += 10;
    }
    if (key == GLFW_KEY_L) {
        miniViewportArea.y -= 10;
    }
    if (key == GLFW_KEY_U) {
        miniViewportArea.width *= 2;
        miniViewportArea.height *= 2;
    }
    if (key == GLFW_KEY_O) {
        miniViewportArea.width /= 2;
        miniViewportArea.height /= 2;
    }

}


void Tema2::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
} 


void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema2::OnWindowResize(int width, int height)
{
}
