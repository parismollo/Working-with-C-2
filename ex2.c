#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NBC 10


typedef enum etat {VALIDEE, ENCOURS, EXPEDIEE} etat;

typedef struct commande
{
    int num_com;
    int prix_exp;
    int prix_prod;
    etat etat_com;
}commande;

int int_alea(int a, int b) {
    return rand() % (b + 1 - a) + a;
}

commande com_alea(int num) {
    commande com;
    com = (commande) {.num_com = num, .prix_exp = int_alea(1, 20), .prix_prod = int_alea(1, 2000), 
    .etat_com = int_alea(0, 2)};
    return com;
}


void affiche_com(commande c) {

    printf("\n");
    printf("c.num_com: %d\n",c.num_com);
    printf("c.prix_exp: %d\n",c.prix_exp);
    printf("c.prix_prod: %d\n",c.prix_prod);
    printf("c.etat_com: ");

    switch (c.etat_com) {
        case(0):
            printf("VALIDEE");
            break;
        case(1):
            printf("ENCOURS");
            break;
        case(2):
            printf("EXPEDIEE");
            break;
        default:
            printf("?");
            break;
    }

    printf("\n");
}

void affiche_exp(commande t[], int taille) {
    for(int i=0; i<taille; i++) {
        if(t[i].etat_com==EXPEDIEE) {
            affiche_com(t[i]);
        }else {
            printf("\nNOT EXPEDIEE\n");
        }
    }
}

int nbr_en_cours(commande t[], int taille) {
    int counter = 0;
    for(int i=0; i<taille; i++) {
        if(t[i].etat_com==ENCOURS) {
            counter++;
        }
    }
    return counter;
}

int count_validees(commande t[], int taille) {
    int total = 0;
    for(int i=0; i<taille; i++) {
        if(t[i].etat_com==VALIDEE) {
            total+=t[i].prix_exp;
        }
    }
    return total;
}

int main() {
    srand(time(NULL));
    // commande c = com_alea(2);
    // print_info(c);

    commande tab_commandes[NBC];
    for(int i=0; i<NBC; i++) {
        tab_commandes[i] = com_alea(i);
        affiche_com(tab_commandes[i]);
    }

    int taille = sizeof(tab_commandes)/sizeof(tab_commandes[0]);
    affiche_exp(tab_commandes, taille);
    printf("\nNb commandes encours: %d", nbr_en_cours(tab_commandes, taille));

    printf("\nCout total prix_exp: %d", count_validees(tab_commandes, taille));
    return EXIT_SUCCESS;
}