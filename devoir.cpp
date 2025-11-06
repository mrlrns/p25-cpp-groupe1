#include <iostream> // pour std::cout, std::cerr
#include <cstdlib>  // pour std::atoi
using namespace std;

int main(int argc, char *argv[])
{
    // argc contient le nombre d'arguments (programme inclus)
    // argv est un tableau de chaînes de caractères

    if (argc < 2)
    {
        cerr << "not enough arguments" << endl;
        return -1;
    }

    int somme = 0;

    // On commence à 1 car argv[0] = nom du programme ("./add")
    for (int i = 1; i < argc; ++i)
    {
        somme += std::atoi(argv[i]); // conversion chaîne → entier
    }

    cout << "le résultat est " << somme << endl;
    return 0;
}
