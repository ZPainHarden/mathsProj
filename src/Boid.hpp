#pragma once
#include <glimac/object_vertices.hpp>
#include <vector>
#include "ObjectProgram.hpp"
#include "glimac/common.hpp"
#include "glm/fwd.hpp"
#include "p6/p6.h"
#include "renderObject.hpp"

using vec = glm::vec3; // utilisation de vec3 pour les coordonnées en 3D

class Boid {
private:
    vec position; // Stocke la position du boid
    vec velocity; // Stocke la vitesse du boid

public:
    Boid();

    void drawBoid(GLuint vao, GLsizei vertexCount, glm::vec3 scale, float rotation, glm::mat4 viewMatrix, glm::mat4 ProjMatrix, glm::mat4& NormalMatrix, ObjectProgram& ObjectProgram, GLuint textureID);
    void applyVelocity();

    vec getPosition() const;
    vec getVelocity() const;

    // Propriétés du boid
    vec  distance(const Boid& boid1, const Boid& boid2);
    void alignmentBoid(const std::vector<Boid>& boids, float alignment);
    void cohesionBoid(const std::vector<Boid>& boids, float cohesion);
    void separationBoid(const std::vector<Boid>& boids, float separation);

    void updateBoid(const std::vector<Boid>& boids, float alignment, float cohesion, float separation);
};