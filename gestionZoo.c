#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define nbrMaxAnimaux 2000

typedef struct animal
{
    size_t id;
    char* nom;
    char* espece;
    size_t age;
    char* habitat;
    float poids;
}animal;

int menu(){
    char choix[2];

    printf("\n=== Gerer Zoo ===\n");
    printf("1. Ajouter un animal.\n");
    printf("2. Afficher les animaux.\n");
    printf("3. Modifier un animal.\n");
    printf("4. Supprimer un animal.\n");
    printf("5. Rechercher un animal.\n");
    printf("6. Statistiques.\n");
    printf("7. Quitter.\n");
    printf("Entrez votre choix : ");
    gets(choix);

    return atoi(choix);
}

int subMenuAjout(){
    char choice[2];

    printf("\n===Ajouter un animal===\n");
    printf("1. Ajouter un seul animal.\n");
    printf("2. Ajouter plusieurs animaux.\n");
    printf("3. Revenir au menu principale.\n");
    printf("Entrez votre choix : ");
    gets(choice);

    return atoi(choice);
}

int subMenuAffichage(){
    char choice[2];

    printf("\n===Afficher les animaux===\n");
    printf("1. Afficher tout les animaux.\n");
    printf("2. Trier les animaux par nom.\n");
    printf("3. Trier les animaux par age.\n");
    printf("4. Afficher les animaux par habitat.\n");
    printf("5. Revenir au menu principale.\n");
    printf("Entrez votre choix : ");
    gets(choice);

    return atoi(choice);
}

int subMenuModification(){
    char choice[2];

    printf("\n===Modifier un animal===\n");
    printf("1. Modifier l'habitat d'un animal.\n");
    printf("2. Modifier l'age d'un animal.\n");
    printf("3. Revenir au menu principale.\n");
    printf("Entrez votre choix : ");
    gets(choice);

    return atoi(choice);
}


void main(){
    int choix, subChoix;
    size_t nbrAnimaux = 0;
    animal animaux[nbrMaxAnimaux] = {
        {1,"Simba","Lion",5,"Savane",190.5},
        {2,"Nala","Lion",4,"Savane",175.0},
        {3,"ShereKhan","Tigre",8,"Jungle",220.3},
        {4,"Baloo","Ours",12,"Forêt",310.0},
        {5,"Raja","Éléphant",15,"Savane",540.7},
        {6,"Marty","Zèbre",6,"Savane",300.2},
        {7,"Gloria","Hippopotame",10,"Rivière",450.0},
        {8,"Alex","Lion",7,"Savane",200.0},
        {9,"Julien","Lémurien",3,"Jungle",12.5},
        {10,"Melman","Girafe",9,"Savane",390.8},
        {11,"Timon","Suricate",2,"Désert",1.2},
        {12,"Pumbaa","Phacochère",5,"Savane",120.0},
        {13,"Scar","Lion",11,"Savane",210.4},
        {14,"Kaa","Serpent",6,"Jungle",45.0},
        {15,"Iko","Perroquet",4,"Jungle",2.1},
        {16,"Dumbo","Éléphant",3,"Savane",320.0},
        {17,"Kiki","Chien" "sauvage",7,"Savane",25.0},
        {18,"Donatello","Tortue",40,"Rivière",90.5},
        {19,"Polly","Oiseau",5,"Jungle",1.5},
        {20,"Kong","Gorille",13,"Jungle",180.0}
    };

    do{
        choix = menu();

        switch(choix){
            case 1:
                do{
                    subChoix = subMenuAjout();
                    switch(subChoix){
                        case 1: 
                            printf("===Ajouter un animal===");
                            break;
                        case 2: 
                            printf("===Ajouter plusieurs animaux===");
                            break;
                        case 3: 
                            break;
                        default:
                            printf("Veuillez entrer un nombre valide.");
                    }
                }while(subChoix!=3);
                break;
            case 2: 
                do{
                    subChoix = subMenuAffichage();
                    switch(subChoix){
                        case 1: 
                            printf("===Liste complete===");
                            break;
                        case 2: 
                            printf("===Animaux par nom===");
                            break;
                        case 3: 
                            printf("===Animaux par age===");
                            break;
                        case 4: 
                            printf("===Animaux par habitat===");
                            break;
                        case 5: 
                            break;
                        default:
                            printf("Veuillez entrer un nombre valide.");
                    }
                }while(subChoix!=5);
                break;
            case 3:
                do{
                    subChoix = subMenuModification();
                    switch(subChoix){
                        case 1: 
                            printf("===Modifier habitat===");
                            break;
                        case 2: 
                            printf("===Modifier age===");
                            break;
                        case 3: 
                            break;
                        default:
                            printf("Veuillez entrer un nombre valide.");
                    }
                }while(subChoix!=3);
                break;
            case 4: 
                printf("===Supprimer un animal===");
                break;
            case 5: 
                printf("===Rechercher un animal===");
                break;
            case 6: 
                printf("===Statistiques===");
                break;
            case 7: 
                printf("Au revoir!");
                break;
            default:
                printf("Veuillez entrer un nombre valide.");
        }
    }while(choix!=7);
}