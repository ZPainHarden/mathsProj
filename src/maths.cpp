#include <cmath>
#include <iostream>
#include <random>
#include <string>
#include "functions.hpp"
#include "glm/fwd.hpp"

void rand01Test()
{
    std::cout << "  Loi uniforme entre 0 et 1 :" << std::endl;
    double X = rand01();
    std::cout << "Exemple de 1 nombre avec la fonction : " << X << std::endl;
    // On répète plusieurs tirages pour avoir l'esperance et la variance
    double count = 0.;
    double sum   = 0.;
    double var   = 0.;
    for (int i = 0; i <= 500; i++)
    {
        sum += rand01();
        var += (i * (500 - i + 1)) / ((500 + 2) * pow(500 + 1, 2));
        count++;
    }
    std::cout << "Esperance devrait etre de 0.5 et est : " << sum / count << std::endl;
    std::cout << "Variance devrait etre de 1/12 = 0.083 et est de : " << var / 2 << std::endl
              << std::endl;
}

void randABTest()
{
    std::cout << "  Loi uniforme continue entre a et b avec a = 0 et b = 10 :" << std::endl;
    double X = randAB(0, 10);
    std::cout << "Exemple de 1 nombre avec la fonction : " << X << std::endl;
    // On répète plusieurs tirages pour avoir l'esperance et la variance
    double count = 0.;
    double sum   = 0.;
    double var   = 0.;
    for (int i = 0; i <= 500; i++)
    {
        sum += randAB(0, 10);
        count++;
    }
    std::cout << "Esperance devrait etre de 5 et est : " << sum / count << std::endl;
    std::cout << "Variance devrait etre de (10-0)^2/12 et est de : " << 100. / 12. << std::endl
              << std::endl;
}

void randABDiscreteTest()
{
    std::cout << "  Loi uniforme discrete entre a et b avec a = 0 et b = 90 :" << std::endl;
    int X = randDiscreteAB(0, 90);
    std::cout << "Exemple de 1 nombre avec la fonction : " << X << std::endl;
    // On répète plusieurs tirages pour avoir l'esperance et la variance
    int count = 0;
    int sum   = 0;
    for (int i = 0; i <= 500; i++)
    {
        sum += randDiscreteAB(0, 90);
        count++;
    }
    std::cout << "Esperance devrait etre de 45 et est : " << sum / count << std::endl;
    std::cout << "Variance devrait etre de 674,91667 et est de : " << (pow(90, 2) - 1) / 12 << std::endl
              << std::endl;
}

void bernoulliTest()
{
    std::cout << "  Loi de Bernoulli avec p = 0.5 :" << std::endl;
    double p = 0.5;
    int    n = 1000;
    double X = bernoulli(p);
    std::cout << "Exemple de 1 nombre avec la fonction : " << X << std::endl;
    // On répète plusieurs tirages pour avoir l'esperance et la variance
    std::cout << "On repete n fois pour trouver l'esperance et la variance --> Loi Binomiale (n, p = 0.5)" << std::endl;
    std::cout << "Esperance devrait etre de 500 et est : " << binDist(n, p) << std::endl;
    std::cout << "Variance devrait etre de 250 et est de : " << binDist(n, p) * p << std::endl
              << std::endl;
}

void poissonTest()
{
    std::cout << "  Loi de Poisson avec lambda = 3 :" << std::endl;
    double lambda = 3;
    double X      = poisson(3, lambda);
    std::cout << "Exemple : P(X=3) = " << X << std::endl;
    // On répète plusieurs tirages pour avoir l'esperance et la variance
    double sumProb = 0.;
    double esp     = 0.;
    int    n       = 10;
    for (int i = 0; i < n; i++)
    {
        double x = poisson(i, lambda);
        if (i < 5)
        {
            std::cout << "P(X=" << i << ") = " << x << "   ";
        }
        esp += x * i;
        sumProb += x;
    }
    std::cout << "etc." << std::endl;
    std::cout << "Somme des P(X=k) : " << sumProb << std::endl;
    std::cout << "Esperance : " << esp << std::endl;
    // Variance
    double var = 0.;
    for (int i = 0; i < n; i++)
    {
        double x = poisson(i, lambda);
        var += abs((pow(x, 2) * i - esp)) / n;
    }
    std::cout << "Variance : " << var << std::endl
              << std::endl;
}

void geometricTest()
{
    std::cout << "  Loi Geometrique avec p = 1/5 :" << std::endl; // Dé à 6 faces équilibré
    double p = 1. / 5.;
    double X = geometric(1, p);
    std::cout << "Exemple : P(X=3) = " << X << std::endl;
    // On répète plusieurs tirages pour avoir l'esperance et la variance
    double sumProb = 0.;
    double esp     = 0.;
    int    n       = 100;
    for (int i = 0; i <= n; i++)
    {
        double x = geometric(i, p);
        if (i <= 5)
        {
            std::cout << "P(X=" << i << ") = " << x << "   ";
        }
        esp += x * i;
        sumProb += x;
    }
    std::cout << "etc." << std::endl;
    std::cout << "Somme des P(X=k) : " << sumProb << std::endl;
    std::cout << "Esperance : " << esp << std::endl;
    // Variance
    double var = 0.;
    for (int i = 1; i <= n; i++) // Commence à 1 et pas 0 pour la loi géométrique
    {
        double x = geometric(i, p);
        var += pow(x - esp, 2);
    }
    std::cout << "Variance : " << (var / n) - esp << std::endl
              << std::endl;
}

void markovTest()
{
    int         count = 0;
    int         nb    = 3;
    std::string state = "";
    for (int i = 0; i < 3; i++)
    {
        if (nb > 0)
        {
            if (markov(state) == "addOne")
            {
                nb += 1;
                state = "addOne";
            }
            if (markov(state) == "removeOne")
            {
                nb -= 1;
                state = "initial";
            }
            count++;
        }
    }
    std::cout << "Test de la chaine de markov avec 3 boids au départ" << std::endl;
    std::cout << "Au bout de " << count << " iterations, il y a " << nb << " boids" << std::endl;
}

void runMathsTest()
{
    std::cout << "\n    ===========\n    MATHS TESTS\n    ===========\n"
              << std::endl;

    rand01Test();
    randABTest();
    randABDiscreteTest();
    bernoulliTest();
    poissonTest();
    geometricTest();
    applyColorBoid();
    markovTest();
}