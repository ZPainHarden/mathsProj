#include "Boid.hpp"
#include <vector>
#include "functions.hpp"
#include "glm/fwd.hpp"
#include "glm/geometric.hpp"
#include "glm/gtc/type_ptr.hpp"

Boid::Boid()
    : position{randomBoidPosition()}, velocity{randomBoidVelocity()} {}

void Boid::drawBoid(GLuint vao, GLsizei vertexCount, glm::vec3 scale, float rotation, glm::mat4 viewMatrix, glm::mat4 ProjMatrix, glm::mat4& NormalMatrix, ObjectProgram& ObjectProgram, GLuint textureID)
{
    renderObject(vao, vertexCount, position, scale, rotation, viewMatrix, ProjMatrix, NormalMatrix, ObjectProgram, textureID);
}

void Boid::applyVelocity()
{
    position += velocity;

    // Conditions que les boids ne traversent pas les murs
    if (position.x > 90.f) // Ici on met 90.f car le cub fait 100.f et la sphere a un diametre de allant de 2.f à 6.f, ça laisse un peu de marge niveau esthétique
    {
        position.x = -90.f;
    }
    if (position.x < -90.f)
    {
        position.x = 90.f;
    }

    if (position.y > 100.f)
    {
        position.y = 20.f;
    }
    if (position.y < 20.f)
    {
        position.y = 100.f;
    }

    if (position.z > 90.f)
    {
        position.z = -90.f;
    }
    if (position.z < -90.f)
    {
        position.z = 90.f;
    }
}

vec Boid::getPosition() const
{
    return position;
}

vec Boid::getVelocity() const
{
    return velocity;
}

void Boid::alignmentBoid(const std::vector<Boid>& boids, float alignment)
{
    glm::vec3 avgPos(0.0f);
    int       counter = 0;

    for (const Boid& otherBoid : boids)
    {
        if (this != &otherBoid)
        {
            float distance = glm::distance(position, otherBoid.getPosition());

            if (distance < alignment)
            {
                avgPos += otherBoid.velocity;
                counter++;
            }
        }
    }
    if (counter > 0)
    {
        avgPos /= counter;
        this->velocity = avgPos;
    }
}

void Boid::cohesionBoid(const std::vector<Boid>& boids, float cohesion)
{
    glm::vec3 avgPos(0.0f);
    int       counter = 0;

    for (const Boid& otherBoid : boids)
    {
        if (this != &otherBoid)
        {
            float distance = glm::distance(position, otherBoid.getPosition());

            if (distance < cohesion * 10)
            {
                avgPos += otherBoid.position;
                counter++;
            }
        }
    }
    if (counter > 0)
    {
        avgPos /= counter;
        avgPos -= position;
        this->velocity += avgPos * 0.08f;
    }
}

void Boid::separationBoid(const std::vector<Boid>& allBoids, float separationDistance)
{
    int       counter = 0;
    glm::vec3 avgPos(0.0f);

    for (const Boid& otherBoid : allBoids)
    {
        if (this != &otherBoid)
        {
            float distance = glm::distance(position, otherBoid.getPosition());

            if (distance < separationDistance)
            {
                avgPos += (position - otherBoid.getPosition()) / distance;
                counter++;
            }
        }
    }
    if (counter > 0)
    {
        this->position += 0.8f * avgPos;
    }
}

void Boid::updateBoid(const std::vector<Boid>& boid, float alignment, float cohesion, float separation)
{
    applyVelocity();
    alignmentBoid(boid, alignment);
    cohesionBoid(boid, cohesion);
    separationBoid(boid, separation);
};
