#include <imgui.h>
#include <FreeflyCamera.hpp>
#include <chrono>
#include <glimac/common.hpp>
#include <glimac/cone_vertices.hpp>
#include <glimac/default_shader.hpp>
#include <glimac/object_vertices.hpp>
#include <glimac/sphere_vertices.hpp>
#include <iostream>
#include <thread>
#include <vector>
#include "glm/fwd.hpp"
#define DOCTEST_CONFIG_IMPLEMENT
#include "Boid.hpp"
#include "Boids.hpp"
#include "ObjectProgram.hpp"
#include "doctest/doctest.h"
#include "functions.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "maths.hpp"
#include "p6/p6.h"
#include "renderObject.hpp"

bool mousePressed           = false;
bool collisionDetectedUp    = false;
bool collisionDetectedDown  = false;
bool collisionDetectedLeft  = false;
bool collisionDetectedRight = false;

bool is3D       = false; // set to true to launch boids program
bool mathTest   = false;
bool testMarkov = true;  // set to true to have an example of the markov chain applied to the number of boids
bool runMaths   = false; // set to true to test maths functions and laws

void collisions(const auto& ctx, FreeflyCamera& camera, bool upPressed, bool downPressed, bool leftPressed, bool rightPressed, float move)
{
    if (upPressed)
    {
        collisionDetectedUp = true;
        if (ctx->key_is_pressed(GLFW_KEY_W))
        {
            camera.moveFront(-move);
        }
    }
    else
    {
        collisionDetectedUp = false;
    }
    if (downPressed)
    {
        collisionDetectedDown = true;
        if (ctx->key_is_pressed(GLFW_KEY_S))
        {
            camera.moveFront(move);
        }
    }
    else
    {
        collisionDetectedDown = false;
    }
    if (leftPressed)
    {
        collisionDetectedLeft = true;
        if (ctx->key_is_pressed(GLFW_KEY_A))
        {
            camera.moveLeft(-move);
        }
    }
    else
    {
        collisionDetectedLeft = false;
    }
    if (rightPressed)
    {
        collisionDetectedRight = true;
        if (ctx->key_is_pressed(GLFW_KEY_D))
        {
            camera.moveLeft(move);
        }
    }
    else
    {
        collisionDetectedRight = false;
    }
}

int main()
{
    std::cout << std::endl;

    if (is3D)
    {
        // Initialisation de GLFW
        if (!glfwInit())
        {
            std::cerr << "Erreur lors de l'initialisation de GLFW" << std::endl;
            return -1;
        }

        auto ctx = p6::Context{{1280, 720, "BoidsIn3D_IMAC2"}};
        ctx.maximize_window();

        /*********************************
         * HERE SHOULD COME THE INITIALIZATION CODE
         *********************************/

        // Run the tests
        if (doctest::Context{}.run() != 0)
            return EXIT_FAILURE;

        Boids boids{}; // initialise boids

        // paramètres à changer si on veut tester autre chose
        int   numberBoid = 50;
        float alignment  = 5.f;
        float cohesion   = 0.f;
        float separation = 7.f;

        for (int i = 0; i < numberBoid; i++) // Loop pour ajouter les boids
        {
            boids.addBoid(Boid{});
        }

        // Initialisation caméra
        FreeflyCamera camera;

        ObjectProgram ObjectProgram{};

        // Textures
        img::Image textureSky   = p6::load_image_buffer("assets/textures/sky.jpg");
        img::Image textureFloor = p6::load_image_buffer("assets/textures/floor.jpg");
        img::Image textureBoid  = p6::load_image_buffer(randomSphereTexture());

        std::vector<GLuint> textureID(50);
        glGenTextures(50, textureID.data());

        bindTexture(textureID, 0, textureBoid);
        bindTexture(textureID, 1, textureSky);
        bindTexture(textureID, 2, textureFloor);

        // const std::vector<glimac::ShapeVertex> boid     = glimac::boids_vertices(3.f);
        const std::vector<glimac::ShapeVertex> floor        = glimac::floor_vertices(100.f); // floor
        const std::vector<glimac::ShapeVertex> cube         = glimac::cube_vertices(100.f, 100.f, 100.f);
        const std::vector<glimac::ShapeVertex> boids_sphere = glimac::sphere_vertices(randomSphereSize(), 8, 4);

        // Créer vao et vbo

        GLuint vboBoid = bindVBO(boids_sphere);
        GLuint vaoBoid = bindVAO(vboBoid);

        GLuint vboFloor = bindVBO(floor);
        GLuint vaoFloor = bindVAO(vboFloor);

        GLuint vboCube = bindVBO(cube);
        GLuint vaoCube = bindVAO(vboCube);

        // Activer le test de profondeur du GPU
        glEnable(GL_DEPTH_TEST);

        int timer = 0;

        // Declare your infinite update loop.
        ctx.update = [&]() {
            // ImGui
            ImGui::Begin("Choice of parameters");
            ImGui::SliderFloat("Alignment distance", &alignment, 0.f, 10.f);
            ImGui::SliderFloat("Cohesion distance", &cohesion, 0.f, 1.f);
            ImGui::SliderFloat("Separation distance", &separation, 6.f, 20.f); // 6.f car la taille de la sphere est de 6.f max
            ImGui::End();

            // Gestion des mouvements de la caméra et des collisions avec les murs
            bool upPressed    = false;
            bool downPressed  = false;
            bool leftPressed  = false;
            bool rightPressed = false;

            if (ctx.key_is_pressed(GLFW_KEY_W))
            {
                if (collisionDetectedUp)
                {
                    return;
                }
                camera.moveFront(0.5);
                upPressed = true;
            }
            else
            {
                upPressed = false;
            }
            if (ctx.key_is_pressed(GLFW_KEY_S))
            {
                if (collisionDetectedDown)
                {
                    return;
                }
                camera.moveFront(-0.5);
                downPressed = true;
            }
            else
            {
                downPressed = false;
            }
            if (ctx.key_is_pressed(GLFW_KEY_A))
            {
                if (collisionDetectedLeft)
                {
                    return;
                }
                camera.moveLeft(0.5);
                leftPressed = true;
            }
            else
            {
                leftPressed = false;
            }
            if (ctx.key_is_pressed(GLFW_KEY_D))
            {
                if (collisionDetectedRight)
                {
                    return;
                }
                if (!collisionDetectedRight)
                {
                    camera.moveLeft(-0.5);
                    rightPressed = true;
                }
            }
            else
            {
                rightPressed = false;
            }
            if (ctx.key_is_pressed(GLFW_KEY_LEFT))
            {
                camera.rotateLeft(50.f);
            }
            if (ctx.key_is_pressed(GLFW_KEY_RIGHT))
            {
                camera.rotateLeft(-50.f);
            }
            if (ctx.key_is_pressed(GLFW_KEY_UP))
            {
                camera.rotateUp(50.f);
            }
            if (ctx.key_is_pressed(GLFW_KEY_DOWN))
            {
                camera.rotateUp(-50.f);
            }

            ctx.mouse_pressed = [&](p6::MouseButton button) {
                mousePressed = true;

                ctx.mouse_dragged = [&](p6::MouseDrag drag) {
                    camera.rotateLeft(drag.delta.x * -5000.f);
                    camera.rotateUp(drag.delta.y * 5000.f);
                };

                ctx.mouse_released = [&](p6::MouseButton button) {
                    mousePressed       = false;
                    ctx.mouse_dragged  = nullptr;
                    ctx.mouse_released = nullptr;
                };
            };

            glClearColor(0.0f, 0.3f, 1.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            ObjectProgram.m_Program.use(); // Shader

            // Calcul des matrices utiles
            glm::mat4 viewMatrix   = camera.getViewMatrix();
            glm::mat4 ProjMatrix   = glm::perspective(glm::radians(70.f), ctx.aspect_ratio(), 0.1f, 500.f);
            glm::mat4 MVMatrix     = viewMatrix * glm::translate(glm::mat4(1.0f), glm::vec3(0.f, 0.f, -5.f));
            glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));

            MVMatrix = glm::rotate(MVMatrix, -1.57f, {0.f, 1.f, 0.f});

            // rendu des objets
            renderObject(vaoCube, static_cast<GLsizei>(cube.size()), glm::vec3{0.f, 0.f, 0.f}, glm::vec3{1.f}, 0.f, viewMatrix, ProjMatrix, NormalMatrix, ObjectProgram, textureID[1]);
            renderObject(vaoFloor, static_cast<GLsizei>(floor.size()), glm::vec3{0}, glm::vec3{1.f}, 0.f, viewMatrix, ProjMatrix, NormalMatrix, ObjectProgram, textureID[2]);

            // rendu et update des boids
            boids.drawBoids(vaoBoid, static_cast<GLsizei>(boids_sphere.size()), glm::vec3{1.f}, 1.57f, viewMatrix, ProjMatrix, NormalMatrix, ObjectProgram, textureID[0]);
            boids.updateBoids(alignment, cohesion, separation);

            glBindVertexArray(0);

            timer++;
            if (timer == 10)
            {
                timer = 0;
                boids.updateMarkovState(); // When uncommented, stops the program when number of boids equals to 0
            }
        };

        // Should be done last. It starts the infinite loop.
        ctx.start();

        glDeleteVertexArrays(1, &vaoCube);
        glDeleteVertexArrays(1, &vaoBoid);
        glDeleteVertexArrays(1, &vaoFloor);

        glDeleteTextures(static_cast<GLsizei>(textureID.size()), textureID.data());
    }

    if (mathTest)
    {
        std::cout << "\n===== MATHS TESTS =====" << std::endl;

        double N = 1000.; // Should be a float to be able to cout mean

        //          Test de la loi uniforme
        std::cout << "  rand01() test:" << std::endl;
        // std::cout << "example of a random number:   " << rand01() << std::endl;
        double count = 0;
        for (int i = 0; i < N; i++)
        {
            count += rand01();
        }
        std::cout << "mean: " << count / N << std::endl
                  << std::endl;

        //          Test de la loi uniforme continue sur un intervalle [A,B]
        std::cout << "  randAB(A=0, B=10) test:" << std::endl;
        // std::cout << "example of a random number:   " << rand01() << std::endl;
        count = 0;
        for (int i = 0; i < N; i++)
        {
            count += randAB(0, 10);
        }
        std::cout << "mean: " << count / N << std::endl
                  << std::endl;

        //          Test de la loi uniforme discrete sur un intervalle [A,B]
        std::cout << "  randDiscreteAB(A=0, B=5) test:" << std::endl;
        // std::cout << "example of a random number:   " << rand01() << std::endl;
        int countBis = 0;
        for (int i = 0; i < N; i++)
        {
            countBis += randDiscreteAB(0, 5);
        }
        std::cout << "mean: " << countBis / N << std::endl
                  << std::endl;

        //          Test de la loi binomiale (qui utilise bernoulli)

        std::cout << "  binomial(N ,value = 0.5) test:" << std::endl;
        const double value = .5;
        std::cout << " mean: " << binDist(N, value) << std::endl
                  << std::endl;

        //          Test de la loi normale
        std::cout << "  norm(x, mean, sigma) test:" << std::endl; // sigma est la variance et pas l'ecart-type
        const double mean  = 2;
        const double sigma = 0.25;
        std::cout << "mean chosen :" << mean << std::endl;
        std::cout << "sigma chosen :" << sigma << std::endl;
        for (int i = 0; i < 5; i++)
        {
            std::cout << "for x = " << i << " norm(x) = " << norm(i, mean, sigma) << std::endl;
        }
        std::cout << std::endl;

        //          Test de la loi gaussienne
        std::cout << "  gauss(x) test:" << std::endl;
        for (int i = -2; i < 3; i++)
        {
            std::cout << "for x = " << i << " gauss(x) = " << normCR(i) << std::endl;
        }
        std::cout << std::endl;

        //          Test de la loi poisson
        std::cout << "  poisson(x, lambda=1) test:" << std::endl;
        double lambda = 1;
        for (int i = 0; i < 5; i++)
        {
            std::cout << "for x = " << i << " poisson(x) = " << poisson(i, lambda) << std::endl;
        }
        std::cout << std::endl;

        //          Test de la loi uniforme
        std::cout << "  unif(0, 10) test:" << std::endl;
        std::cout << " unif(0, 10) = " << unif(0., 10.) << std::endl;
        std::cout << std::endl;

        //          Test de la loi exponentielle
        std::cout << "  exponential(x = 0, lambda = 0.5) test:" << std::endl;
        std::cout << " exponential(0, 0.5) = " << exponential(0, 0.5) << std::endl;
        std::cout << std::endl;

        //          Test de la loi geometrique
        /*
        std::cout << "  geometric(p=6) test:" << std::endl;
        count = 0;
        for (int i = 0; i < N; i++)
        {
            count += static_cast<double>(geometric(6));
        }
        std::cout << "mean: " << count / N << std::endl
                  << std::endl;
        */

        // Test fact(int number)
        std::cout << "factorial 5: " << fact(5) << std::endl;
    }

    if (testMarkov)
    {
        // Test de la chaîne de Markov avec N occurrences
        int         N_boids       = 3; // Nombre de boids au départ du test
        int         N_occurrences = 0; // Sert à compter en combien d'occurrence on arrive à la fin
        std::string currentState  = "initial";

        std::cout << "Test of the Markov chain with 3 boids in initial state" << std::endl;
        while (N_boids > 0)
        {
            N_occurrences++;
            currentState = markov(currentState);
            if (currentState == "addOne")
            {
                N_boids++;
            }
            if (currentState == "removeOne")
            {
                N_boids--;
            }
            std::cout << currentState << " --> After " << N_occurrences << " occurrences: " << N_boids << " boid(s)" << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

        std::cout << N_occurrences << " occurrences to remove all boids" << std::endl;
    }

    if (runMaths)
    {
        runMathsTest();
    }
}