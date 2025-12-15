#include <iostream>

struct Cellule {
    int valeur;
    Cellule* suivant;

    Cellule(int v, Cellule* s = nullptr) : valeur(v), suivant(s) {}
};

struct Liste {
    Cellule* tete;

    Liste() : tete(nullptr) {}

    
    

    void push_front(int v) {
        Cellule* nouvelle_cellule = new Cellule(v, tete);
        tete = nouvelle_cellule;
    }

    
};

int main () {
    Liste list;

    list.push_front(45);
    list.push_front(12);
    list.push_front(42);
    list.push_front(33);
    list.push_front(17);

    list.print(); // Affiche: 17 33 42 12 45
                  // oui l'ordre est inversé car on ajoute en tête de liste...

    list.remove(88); // Ne fait rien (et pas d'exception à générer)
    list.remove(17); // Attention on supprime la tête de liste !!
    list.remove(45); // Attention on supprime la queue de liste !!
    list.remove(42); // Supprime un élément du milieu de liste
    // que de cas à gérer... que de pointeurs à mettre à jour...

    list.print();

    return 0;
}











