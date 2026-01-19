/*
Nous souhaitons implémenter un arbre binaire.

Un arbre binaire est formé de noeuds (Node).

Chaque noeud a deux sous-arbres (left, right) potentiellement nuls et une valeur entière.

Un de ces noeuds est la racine de l'arbre, tous les noeuds de l'arbre sont accessibles à partir de cette racine.

Voici un exemple d'arbre avec 3 noeuds,
on le dessine "allongé" avec sa racine à gauche:

      37
26
      11

   la racine est 26
   l'arbre gauche est réduit au noeud 11
   l'arbre droit est réduit au noeud 37

Un autre avec les mêmes valeurs
mais une autre forme (la forme dépend de l'ordre d'insertion des éléments)
            37
      26
11

Vous l'avez compris, étant donné un noeud:
   - les valeurs des noeuds du sous-arbre gauche sont strictement inférieures à la valeur du noeud
   - les valeurs des noeuds du sous-arbre droit sont strictement supérieures à la valeur du noeud.

Voici le dessin de l'arbre nous allons prendre en exemple dans le main (8 est la racine):
en trichant on a inséré les valeurs de manière à ce qu'il soit équilibré...
Quel est la complexité en temps de la recherche d'un élément dans un arbre binaire équilibré ?

               15
          14
               13
     12
               11
          10
               9
8
               7
          6
               5
     4
               3
          2
               1

Si j'ai beaucoup moins de chance, je peux obtenir en insérant les mêmes valeurs
un arbre "dégénéré":
30
     29
          28
               27
                    26
                         25
                              24
                                   23
                                        22
                                             21
                                                  20
                                                       19
                                                            18
                                                                 17
                                                                      16

Quel est la complexité en temps de la recherche d'un élément dans des arbres binaires de cette forme ?

I) Construction de l'arbre:

L'arbre est construit de manière à être trié c'est à dire quand on est à un noeud:
   - toutes les valeurs de son sous-arbre gauche sont strictement inférieures à la valeur du noeud
   - toutes les valeurs de son sous-arbre droit sont strictement supérieures à la valeur du noeud

On donne des indices mais vous pouvez coder autrement.

L'arbre initial est créé vide - sa racine est donc le pointeur nul (nullptr).

Implémenter la méthode insert(int v) qui ajoute une valeur entière à l'arbre à la bonne place i.e.
  - on va se déplacer dans l'arbre jusqu'à trouver l'endroit où insérer cette valeur
  - si la valeur existe déjà dans l'arbre, on ne fait rien
  - sinon on crée un noeud qu'on raccorde.

  Réfléchissez à la manière de faire un tel parcours récursivement, soit codez-le soit regardez les indices ci-dessous.

Indices pour l'insertion dans l'arbre binaire:
  - si la racine n'existe pas on crée un noeud avec la valeur et ses deux sous-arbres nuls (nullptr)
  - si la racine existe on lance l'insertion sur ce noeud racine (on appelle une méthode d'insertion des noeuds)

Indices pour la méthode d'insertion sur un noeud:
  - si la valeur du noeud est égale à la valeur à insérer on ne fait rien (le noeud y est déjà)
  - si la valeur est inférieure et si l'arbre gauche existe on lance l'insertion sur le noeud gauche
  -                             et si l'arbre gauche n'existe pas, on crée un noeud avec la valeur et il devient le fils gauche
  - pareil à droite

II) Parcours de l'arbre:

Implémentez la méthode depth() qui va parcourir cet arbre en profondeur en affichant ses valeurs.
Réfléchissez à la manière de faire ce parcours de manière récursive et soit vous le codez soit vous lisez les indices ci-dessous.

Indices pour un parcours en profondeur récursif d'un arbre binaire:
   - ce parcours lance le parcours récursif du noeud racine de l'arbre (i.e. appelle la méthode depth des noeuds)
   - si ce noeud a un fils gauche, on lance le parcours sur le noeud gauche (i.e. appelle la méthode sur le noeud gauche)
   - si ce noeud n'a pas de fils gauche, on affiche la valeur du noeud et on lance le parcours sur le noeud droit
...

Lors de ce parcours on peut afficher la valeur des noeuds à plusieurs endroits:
   - si on l'affiche en début de l'appel du parcours sur un noeud: on a un affichage dit préfixe
   - si on l'affiche entre les appels à gauche et à droite on a un affichage dit infixe
   - si on l'affiche à la fin de l'appel de la méthode sur un noeud: on a un affichage dit postfixe

Pour décider de l'affichage, on peut donc passer à cette méthode le type de l'affichage désiré
(par exemple un objet qui est une énumération (enum) voir exemple ci-dessous)

*/
#include <iostream>

// the type enum
enum Order
{
     Prefix,  // will be set to 0
     Infix,   // will be set to the previous + 1
     Postfix, // idem
};

void enum_values()
{
     std::cout << "Prefix is " << Order::Prefix << std::endl;
     std::cout << "Infix is " << Order::Infix << std::endl;
     std::cout << "Postfix is " << Order::Postfix << std::endl;
}

// Les structures de base de l'arbre binaire BinaryTree et Node:
// avec les méthodes pour que le code compile.
struct Node
{
     int value;
     int rang=0;
     Node*left;
     Node*right;
     bool r=false;
     bool l=false;
     bool written=false;
     Node*dad=nullptr;

     // votre code là
     void insert_N (int nb){
          if (value<nb){
               if (right==nullptr){
                    right = new Node();
                    
                    right->value=nb;
                    ;
                    right->right=nullptr;
                    right->left=nullptr;
                    ;

               }
               else {
                    right->insert_N(nb);
               }
               
          }
          else {
               if (left==nullptr){
                    left = new Node();
                    
                    left->value=nb;
                    
                    left->right=nullptr;
                    left->left=nullptr;
                    
                    

               }
               else {
                    left->insert_N(nb);
               }
          }


     }
     void printN(int space){
          
          if (this==nullptr){
              return;
          }
          space+=5;
          if (right!= nullptr){
               right->printN(space);
          }
          std::cout<<value<<std::endl;

          std::cout<<std::string(space,' ');

          if (left!=nullptr){
               left->printN(space);
          }
          

               
          }
          

          

};



struct BinaryTree
{
     Node *root=nullptr;
     // votre code là
     // et ces fonctions à implémenter à minima
     void insert(int val) {
          if (root==nullptr){
               root = new Node();
               root->value=val;
               root->left=nullptr;
               root->right=nullptr;
          }
          else{
               root->insert_N(val);
          }
          
     }
     void depth(Order o) {}
     bool search(int v) { return false; }

     // celle là est plus difficile
     void print() {
          root->printN(0);
     }
};

int main()
{
      // exemple pour voir un enum

     // on construit l'arbre

     // cet ordre d'insertion donne un bel arbre binaire équilibré
     // ce qui n'est bien sûr pas toujours le cas...
     // il existe des algorithmes pour garder l'arbre équilibré
     // mais c'est en dehors de notre cadre d'une simple programmation
     BinaryTree b;
     b.insert(8);
     b.insert(4);
     b.insert(6);
     b.insert(12);
     b.insert(10);
     b.insert(11);
     b.insert(9);
     b.insert(2);
     b.insert(1);
     b.insert(3);
     b.insert(5);
     b.insert(14);
     b.insert(15);
     b.insert(13);
     b.insert(7);
     

     

     b.print();
}

