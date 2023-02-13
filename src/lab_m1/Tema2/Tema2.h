#pragma once

#include "components/simple_scene.h"
#include "lab_m1/Tema2/Tema2_camera.h"
#define Z_FAR		(200.f)
#define Z_NEAR		(.01f)

namespace m1
{
    class Tema2 : public gfxc::SimpleScene
    {
     public:
        struct ViewportArea
        {
            ViewportArea() : x(0), y(0), width(1), height(1) {}
            ViewportArea(int x, int y, int width, int height)
                : x(x), y(y), width(width), height(height) {}
            int x;
            int y;
            int width;
            int height;
        };

        Tema2();
        ~Tema2();

        void Init() override;
        Mesh* CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned int>& indices);

     private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

        void RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color);
        void RenderMesh2(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix);
        void RenderScene(float deltaTimes);

        bool insideTriangle(glm::vec3 P, glm::vec3 A, glm::vec3 B, glm::vec3 C);
        float TriangleArea(glm::vec3 A, glm::vec3 B, glm::vec3 C);
        bool checkCar(glm::vec3 P);

        bool coliziune(glm::vec3 obstacolPos);
        bool checkColiziune();

        void calculateCurrentPos(float deltaTimes);

     protected:
        implemented::Camera_Tema2 *camera;
        glm::mat4 modelMatrix;
        glm::mat4 projectionMatrix;
        bool renderCameraTarget;
        float initialFov;
        float changeFov;
        float zoom;
        ViewportArea miniViewportArea;
        GLenum polygonMode;
        std::vector <glm::vec3> puncte;
        std::vector <glm::vec3> puncte_interior;
        std::vector <glm::vec3> puncte_exterior;
        float translateX, translateZ;
        glm::vec3 P;
        float angle_car;
        bool masina_pista;

        std::vector<glm::vec3> perpendiculars;

        // obstacole
        std::vector <glm::vec3> poz_cr_masina;
        std::vector <glm::vec3> poz_urm_masina;
        std::vector<int> indici;

    };
}   // namespace m1

