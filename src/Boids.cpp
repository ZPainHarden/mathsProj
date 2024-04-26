#include "Boids.hpp"
#include <vector>
#include "Boid.hpp"
#include "functions.hpp"

void Boids::addBoid(Boid boid)
{
    boids.push_back(boid);
}

void Boids::removeBoid()
{
    boids.pop_back();
}

std::string Boids::getMarkovState()
{
    return markovState;
}

/*
void Boids::updateMarkovState(std::string state)
{
    std::string currentState = getMarkovState();
    std::string nextState    = markov(currentState);
    if (nextState == "addOne")
    {
        addBoid(Boid{});
    }
    if (nextState == "removeOne")
    {
        removeBoid();
    }
    markovState = currentState;
}
*/

void Boids::drawBoids(GLuint vao, GLsizei vertexCount, glm::vec3 scale, float rotation, glm::mat4 viewMatrix, glm::mat4 ProjMatrix, glm::mat4& NormalMatrix, ObjectProgram& ObjectProgram, GLuint textureID)
{
    for (Boid& boid : boids)
    {
        boid.drawBoid(vao, vertexCount, scale, rotation, viewMatrix, ProjMatrix, NormalMatrix, ObjectProgram, textureID);
    }
}

void Boids::updateBoids(float alignment, float cohesion, float separation)
{
    for (Boid& boid : boids)
    {
        boid.updateBoid(boids, alignment, cohesion, separation);
    }
}
