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
    double count = 5000;
    double sum   = 0.;
    double var   = 0.;
    for (int i = 0; i <= count; i++)
    {
        sum += rand01();
    }
    double esp = sum / count;
    std::cout << "Esperance devrait etre de 0.5 et est : " << esp << std::endl;

    for (int i = 0; i < count; i++)
    {
        var += pow(rand01() - esp, 2);
    }
    var = var / count;
    std::cout << "Variance devrait etre de 1/12 = 0.083 et est de : " << var << std::endl
              << std::endl;
}

void randABTest()
{
    std::cout << "  Loi uniforme continue entre a et b avec a = 0 et b = 10 :" << std::endl;
    double X = randAB(0, 10);
    std::cout << "Exemple de 1 nombre avec la fonction : " << X << std::endl;
    // On répète plusieurs tirages pour avoir l'esperance et la variance
    double count = 500;
    double sum   = 0.;
    double var   = 0.;
    for (int i = 0; i <= count; i++)
    {
        sum += randAB(0, 10);
    }
    double esp = sum / count;
    std::cout << "Esperance devrait etre de 0.5 et est : " << esp << std::endl;

    for (int i = 0; i < count; i++)
    {
        var += pow(randAB(0, 10) - esp, 2);
    }
    var = var / count;
    std::cout << "Variance devrait etre de (10-0)^2/12 = 8.33 et est de : " << var << std::endl
              << std::endl;
}

void randABDiscreteTest()
{
    std::cout << "  Loi uniforme discrete entre a et b avec a = 0 et b = 90 :" << std::endl;
    int X = randDiscreteAB(0, 90);
    std::cout << "Exemple de 1 nombre avec la fonction : " << X << std::endl;
    // On répète plusieurs tirages pour avoir l'esperance et la variance
    double count = 5000;
    int    sum   = 0;
    double var   = 0.;
    for (int i = 0; i <= count; i++)
    {
        sum += randDiscreteAB(0, 90);
    }
    double esp = sum / count;
    std::cout << "Esperance devrait etre de 45 et est : " << esp << std::endl;

    for (int i = 0; i < count; i++)
    {
        var += pow(randDiscreteAB(0, 90) - esp, 2);
    }
    var = var / count;
    std::cout << "Variance devrait etre de 674,91667 et est de : " << var << std::endl
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
    std::cout << "On repete 1000 fois pour trouver l'esperance et la variance --> \n\nLoi Binomiale (n = 1000, p = 0.5)" << std::endl;
    int esp = binDist(1000, 0.5);
    std::cout << "Esperance devrait etre de 500 et est : " << esp << std::endl;
    double var = 0;
    for (int i = 0; i < n; i++)
    {
        var += pow(bernoulli(0.5) - 0.5, 2);
    }
    std::cout << "Variance devrait etre de 250 et est de : " << var << std::endl
              << std::endl;
}

void poissonTest()
{
    std::cout << "  Loi de Poisson avec lambda = 3 :" << std::endl;
    double lambda = 3;
    double X      = poisson(3, lambda);
    //  std::cout << "Exemple : P(X=3) = " << X << std::endl;
    //  On répète plusieurs tirages pour avoir l'esperance et la variance
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
        var += pow(i - esp, 2) * x;
    }
    std::cout << "Variance : " << var << std::endl
              << std::endl;
}

void geometricTest()
{
    std::cout << "  Loi Geometrique avec p = 1/5 :" << std::endl; // Dé à 6 faces équilibré
    double p = 0.5;
    double X = geometric(3, p);
    std::cout << "Exemple : P(X=3) = " << X << std::endl;
    // On répète plusieurs tirages pour avoir l'esperance et la variance
    double sumProb = 0.;
    double esp     = 0.;
    int    n       = 100;
    for (int i = 1; i <= n; i++)
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
    for (int i = 1; i <= n; i++)
    {
        double x = geometric(i, p);
        var += pow(i - esp, 2) * x;
    }
    std::cout << "Variance : " << var << std::endl
              << std::endl;
}

void normTest()
{
    std::cout << "  Loi normale" << std::endl;
    std::cout << "Densite de probabilite : " << std::endl;
    std::cout << "Loi normale avec mu = 2, sigma_carre = 0.25" << std::endl;
    const double mu    = 2;
    const double sigma = 0.25;
    for (int i = 0; i < 5; i++)
    {
        std::cout << "for x = " << i << ": " << norm(i, mu, sigma) << "    ";
    }
    std::cout << std::endl;
    std::cout << "Loi normale centree reduite" << std::endl;
    for (int i = -2; i < 3; i++)
    {
        std::cout << "for x = " << i << ": " << normCR(i) << "    ";
    }
    std::cout << std::endl;
    std::cout << std::endl;

    std::cout << "Fonction de repartition : " << std::endl;
    std::cout << "Loi normale avec mu = 2, sigma_carre = 0.25, a = 1, b = 2" << std::endl;
    double a = 1;
    double b = 2;
    std::cout << normAB(a, b, mu, sigma) << std::endl;
    std::cout << "Loi normale centree reduite entre a = -1 et b = 1" << std::endl;
    a = -1;
    b = 1;
    std::cout << normCRAB(a, b) << std::endl;
    std::cout << std::endl;
}

void exponentialTest()
{
    std::cout << "  Loi Exponentielle avec lambda = 0.5 :" << std::endl; // Dé à 6 faces équilibré
    double lambda = 0.5;
    double X      = exponential(0, lambda);
    std::cout << "Exemple : P(X=0) = " << X << std::endl;
    // On répète plusieurs tirages pour avoir l'esperance et la variance
    double sumProb = 0.;
    double esp     = 0.;
    int    n       = 5;
    for (double x = 0; x <= n; x++)
    {
        double Res = exponential(x, lambda);
        esp += x * Res;
        sumProb += Res;
    }
    std::cout << "Somme des P(X=k) : " << 1 << std::endl;
    std::cout << "Esperance : " << 1 / lambda << std::endl;
    // Variance
    double var = 0.;
    for (int i = 1; i <= n; i++)
    {
        double x = exponential(i, lambda);
        var += pow(i - esp, 2) * x;
    }
    std::cout << "Variance : " << 1 / (lambda * lambda) << std::endl
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
    normTest();
    exponentialTest();
    std::cout << "Example of randomBoidPosition() return :" << std::endl;
    randomBoidPosition();
    std::cout << std::endl;
    // applyColorBoid();
    // markovTest();
}