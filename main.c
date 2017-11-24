#include <stdio.h>
#include <stdlib.h>
#include <time.h>


struct Mastermind
{
    // etablissement structure jeu
    unsigned int combinaison[4];
    unsigned int combijoueur[4];
    unsigned int nbEssaisRestants;
    unsigned int nbPartiesGagnees;
    unsigned int nbPartiesPerdues;
};
struct Verifpions
{
    unsigned int pionsPresents;
    unsigned int pionsPlaces;
};

void affichescore(struct Mastermind jeu)
{
    printf("Score : %d parties gagnees\n",jeu.nbPartiesGagnees);
    printf("%d parties perdues\n",jeu.nbPartiesPerdues);
}

//Fonction de verification des combinaisons
int verifCombinaison(struct Mastermind jeu,struct Verifpions presentplaces)
{
    unsigned int i,j;
    presentplaces.pionsPlaces=0;
    presentplaces.pionsPresents=0;


    for (i=0; i<4; i++)
    {
        for (j=0; j<4; j++)
        {
            // printf("combijoueur[%d] combinaison[%d]\n", jeu.combijoueur[i],jeu.combinaison[j]);// pour le debug

            if (jeu.combijoueur[i]==jeu.combinaison[j] && i!=j) //on compte les présents
            {

                presentplaces.pionsPresents++;//on incrémente le nombre de présents
            }
            else if (jeu.combijoueur[i]==jeu.combinaison[j]) //on compte les placés
            {

                presentplaces.pionsPlaces++; //on incrémente le nombre de placés
                if (presentplaces.pionsPlaces==4) //4 placés = victoire
                {

                    return 1; // on retourne que le joueur a gagne
                }
            }
        }
    }
    printf("Vous avez %d pions presents et %d pions places\n",presentplaces.pionsPresents,presentplaces.pionsPlaces);
    return 0; // le jeu se poursuit
}



int main()
{
    srand(time(NULL));    // initialisation de l'aleatoire
    //initialisation variables
    unsigned int i;
    unsigned int joueurGagne=0;
    unsigned int choixChiffre;// choix joueur
    unsigned int nouvellePartie=1;

    struct Mastermind jeu;
    jeu.nbPartiesGagnees=0;
    jeu.nbPartiesPerdues=0;
    do
    {

        jeu.nbEssaisRestants=10; // le joueur a 10 essais
        joueurGagne=0; // le 'booleen qui teste la victoire en retour de fonction
        for (i=0; i<4; i++)
        {
            jeu.combijoueur[i]= 50;
        }


        struct Verifpions presentplaces; // initialisation dans la fonction



        //determination combinaison aleatoire jeu
        for (i=0; i<4; i++)
        {
            jeu.combinaison [i]=rand()%10;
        }


        printf("Je suis pret, devinez le code \n");

        while (jeu.nbEssaisRestants>0 && !joueurGagne) // conditions de poursuite du jeu
        {
            nouvellePartie=1;

            printf("Vous avez %d essais\n",jeu.nbEssaisRestants);
            jeu.nbEssaisRestants-=1;

            //entree de la combinaison joueur
            printf("Entrez votre combinaison\n");
            for (i=0; i<4; i++)
            {
                do
                {
                    printf("nombre %d entre 0 et 9\n",i+1);
                    scanf("%d",&choixChiffre);
                }
                while (choixChiffre>9); // on vérifie que le joueur choisit bien en dessous de 10
                jeu.combijoueur[i]=choixChiffre;
            }
            //il faut tester la combinaison : on appelle une fonction de verification
            joueurGagne=verifCombinaison(jeu, presentplaces);
            printf("%d\n",joueurGagne);

        }
        if (joueurGagne) // si 4 pions placés
        {
            printf("Bravo vous avez gagne en %d coups\n",10-jeu.nbEssaisRestants);
            jeu.nbPartiesGagnees+=1;
        }
        else if (jeu.nbEssaisRestants==0) // plus d'essais disponibles
        {
            jeu.nbPartiesPerdues+=1;
            printf("Vous avez perdu\n");

        }
        affichescore(jeu);
        printf("Voulez-vous rejouer ? (1=oui)/(0=non)\n");
        do
        {
            scanf("%d",&nouvellePartie);
        }
        while (nouvellePartie!=0 && nouvellePartie!=1);
    }
    while (nouvellePartie);// on continue tant que le joueur le souhaite

    printf("This is the end\n");
}



