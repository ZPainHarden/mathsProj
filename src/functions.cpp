#include "functions.hpp"
#include <cmath>
#include <iostream>
#include <random>
#include <string>
#include "glm/fwd.hpp"

// Probability laws

double rand01()
{
    thread_local std::default_random_engine gen{std::random_device{}()};
    thread_local auto                       distrib = std::uniform_real_distribution<double>{0.0, 1.0};

    return distrib(gen);
}

double randAB(auto a, auto b)
{
    auto waiting = rand01();
    return (a / 2) + waiting * (b - a);
}

int randDiscreteAB(int a, int b)
{
    auto waiting = randAB(a, b);
    if (waiting + 0.5 < floor(waiting))
    {
        return floor(waiting);
    }
    return floor(waiting) + 1;
}

bool bernoulli(double value) // value should be between 0 and 1
{
    return rand01() < value;
}

double binDist(double N, double value)
{
    float count = 0;
    for (int i = 0; i < N; i++)
    {
        count += bernoulli(value);
    }
    return count;
}

double norm(double x, double mu, double sigma)
{
    return 1.0 / (sigma * sqrt(2.0 * M_PI)) * exp(-(pow((x - mu) / sigma, 2) / 2.0));
}

double gauss(double x)
{
    double mu    = 0;
    double sigma = 1;
    return 1.0 / (sigma * sqrt(2.0 * M_PI)) * exp(-(pow((x - mu) / sigma, 2) / 2.0)), sigma;
}

double poisson(double k, double lambda)
{
    if (k < 0)
    {
        return 0.;
    }
    return (pow(lambda, k) / fact(k)) * exp(-lambda);
}

double unif(double a, double b) //
{
    return 1 / (b - a);
}

double exponential(double value, double lambda)
{
    if (value < 0)
    {
        return 0;
    }
    return lambda * exp(-lambda * value);
}

double geometric(double k, double p)
{
    if (k <= 0)
    {
        return 0.;
    }
    return p * pow((1 - p), (k - 1));
}

// Markov
std::string markov(std::string state)
{
    if (state == "initial")
    {
        double nextState = rand01();
        // std::cout << nextState << std::endl;
        if (nextState <= 0.7)
        {
            return "initial";
        }
        if (nextState > 0.7 && nextState <= 0.9)
        {
            return "removeOne";
        }
        return "addOne";
    }

    if (state == "addOne")
    {
        double nextState = rand01();
        // std::cout << nextState << std::endl;
        if (nextState <= 0.9)
        {
            return "initial";
        }
        return "addOne";
    }

    if (state == "removeOne")
    {
        double nextState = rand01();
        // std::cout << nextState << std::endl;
        if (nextState <= 0.9)
        {
            return "initial";
        }
        return "removeOne";
    }
}

// Useful functions

int fact(int number)
{
    if (number < 0)
    {
        return (-1); // Wrong number
    }
    if (number == 0)
    {
        return (1); // Terminating condition
    }
    return (number * fact(number - 1));
}

// Boid
glm::vec3 applyColorBoid() // A MODIFIER AVEC SWITCH
{
    int colorNumber = randDiscreteAB(0, 5);
    std::cout << colorNumber << std::endl;
    if (colorNumber == 0)
    {
        return {
            0, 0, 0
        };
    }
    if (colorNumber == 1)
    {
        return {
            1, 0, 0
        };
    }
    if (colorNumber == 2)
    {
        return {
            0, 1, 0
        };
    }
    if (colorNumber == 3)
    {
        return {
            0, 0, 1
        };
    }
    if (colorNumber == 4)
    {
        return {
            .5, .5, .5
        };
    }
    if (colorNumber == 5)
    {
        return {
            1, 1, 1
        };
    }
}

glm::vec3 randomBoidPosition()
{
    /*std::cout << "Test boidPosition()" << std::endl;
    auto x = randDiscreteAB(-45, 45);
    auto y = randDiscreteAB(-45, 45);
    auto z = randDiscreteAB(-45, 45);
    std::cout << "x: " << x << "    y: " << y << "  z: " << z << std::endl;*/
    return {randDiscreteAB(-45, 45), randDiscreteAB(-45, 45), randDiscreteAB(-45, 45)};
}

glm::vec3 randomBoidVelocity()
{
    /*std::cout << "Test boidVelocity()" << std::endl;
    auto x = rand01() - 0.5;
    auto y = rand01() - 0.5;
    auto z = rand01() - 0.5;
    std::cout << "x: " << x << "    y: " << y << "  z: " << z << std::endl;*/
    return {rand01() - 0.5, rand01() - 0.5, rand01() - 0.5};
}

float randomSphereSize()
{
    auto x = randDiscreteAB(0, 2);
    switch (x)
    {
    case 0:
        return 1.;
    case 1:
        return 2.;
    case 2:
        return 3.;
    }
}

std::string randomSphereTexture()
{
    auto x = randDiscreteAB(0, 2);
    switch (x)
    {
    case 0:
        return "assets/textures/boid01.jpg";
    case 1:
        return "assets/textures/boid02.jpg";
    case 2:
        return "assets/textures/boid03.jpg";
    }
}
