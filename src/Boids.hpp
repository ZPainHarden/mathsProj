#pragma once
#include <string>
#include <vector>
#include "Boid.hpp"

class Boids {
private:
    std::vector<Boid> boids;
    vec               averagePosition{};
    std::string       markovState = "initial";

public:
    void addBoid(Boid boid);
    void removeBoid();

    std::string getMarkovState();
    void        updateMarkovState(std::string markovState);

    void drawBoids(GLuint vao, GLsizei vertexCount, glm::vec3 scale, float rotation, glm::mat4 viewMatrix, glm::mat4 ProjMatrix, glm::mat4& NormalMatrix, ObjectProgram& ObjectProgram, GLuint textureID);

    void updateBoids(float alignment, float cohesion, float separation);
};