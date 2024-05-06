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
    return a + waiting * (b - a);
}

int randDiscreteAB(int a, int b)
{
    auto waiting = randAB(a, b);
    if (waiting + 0.5 < floor(waiting) + 1)
    {
        return floor(waiting);
    }
    return floor(waiting) + 1;
}

bool bernoulli(double value) // value should be between 0 and 1
{
    if (value < 0 || value > 1)
    {
        std::cout << "ERROR :  probability value is not between 0 and 1" << std::endl;
        return false;
    }
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
    sigma = sqrt(sigma);
    return 1.0 / (sigma * sqrt(2.0 * M_PI)) * exp(-(pow((x - mu) / sigma, 2) / 2.0));
}

double normAB(double a, double b, double mu, double sigma)
{
    sigma = sqrt(sigma); // pour avoir l'écart-type
    return normA(b, mu, sigma) - normA(a, mu, sigma);
}

double normA(double x, double mu, double sigma)
{
    // Calcul de l'intégrale de la densité de probabilité de -∞ à x
    double z  = (x - mu) / (sigma * sqrt(2.0));
    double t  = 1.0 / (1.0 + 0.3275911 * fabs(z));
    double a1 = 0.254829592;
    double a2 = -0.284496736;
    double a3 = 1.421413741;
    double a4 = -1.453152027;
    double a5 = 1.061405429;

    double erf  = 1.0 - (((((a5 * t + a4) * t) + a3) * t + a2) * t + a1) * t * exp(-z * z);
    double sign = 1.0;
    if (x < mu)
    {
        sign = -1.0;
    }

    // Fonction de répartition cumulative
    return 0.5 * (1.0 + sign * erf);
}

double normCR(double x)
{
    double mu    = 0;
    double sigma = 1;
    return norm(x, mu, sigma);
}

double normCRAB(double a, double b)
{
    return normA(b, 0, 1) - normA(a, 0, 1);
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

double exponential(double x, double lambda)
{
    if (x < 0)
    {
        return 0.0;
    }
    return lambda * exp(-lambda * x);
}

double geometric(int k, double p)
{
    if (k <= 0 || p < 0 || p > 1)
    {
        std::cout << "ERROR : wether k is not > 0, or p is not between 0 and 1";
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

double randomBoidPosition()
{
    double res     = 0;
    auto   wait    = randAB(-3, 3);
    auto   waiting = normCR(wait);
    if (wait < 0)
    {
        res = -((1 - waiting / normCR(0)) * 45);
    }
    if (wait > 0)
    {
        res = (1 - waiting / normCR(0)) * 45;
    }

    std::cout << wait << "  " << waiting << "   " << res << std::endl;
    return res;
}

glm::vec3 randomBoidPositions()
{
    return {randomBoidPosition(), randomBoidPosition(), randomBoidPosition()};
}

glm::vec3 randomBoidVelocity()
{
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
