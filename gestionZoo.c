#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define nbrMaxAnimaux 200
#define longueurChaineMax 51

typedef struct animal
{
    size_t id;
    char nom[50];
    char espece[50];
    size_t age;
    char habitat[50];
    float poids;
}animal;

/*************************************Fonctions pour les Menus**************************************/
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

int subMenuRecherche(){
    char choice[2];

    printf("\n===Rechercher un animal===\n");
    printf("1. Rechercher par id.\n");
    printf("2. Rechercher par nom.\n");
    printf("3. Rechercher par espece.\n");
    printf("4. Revenir au menu principale.\n");
    printf("Entrez votre choix : ");
    gets(choice);

    return atoi(choice);
}

int subMenuStatistiques(){
    char choice[2];

    printf("\n===Statistiques===\n");
    printf("1. Nombre total des animaux dans le zoo.\n");
    printf("2. Age moyen des animaux.\n");
    printf("3. Plus vieux et plus jeune animal.\n");
    printf("4. Les especes les plus representees.\n");
    printf("5. Revenir au menu principale.\n");
    printf("Entrez votre choix : ");
    gets(choice);

    return atoi(choice);
}

/*************************************Fonctions pour la gestion du zoo**************************************/
size_t initialiserTaille(animal animaux[], size_t taille){
    size_t i;

    for(i=0; i<nbrMaxAnimaux; i++){
        if(strcmp(animaux[i].habitat, "")!=0){
            taille++;
        }
    }
    return taille;
}

void trim(char chaine[]){
    size_t d=0, f=strlen(chaine);

    while(chaine[d]==' '){
        d++;
    }
    if(d==f)
        chaine = "";
    else{
        while(chaine[f-1]==' '){
            f--;
        }
        char morceau[f-d];

        strncpy(morceau, chaine+d, f-d);
        morceau[f-d]='\0';
        strcpy(chaine, morceau);
    }
}

size_t chaineValide(char chaine[]){
    size_t j=0, cmp_espace=0, taille=strlen(chaine);

    if(taille<longueurChaineMax && taille>0){
        trim(chaine);
        while(chaine[j]!='\0'){
            if((chaine[j]<'a' || chaine[j]>'z') && (chaine[j]<'A' || chaine[j]>'Z') && chaine[j] != ' ')
                return 0;
            if(chaine[j]==' ')
                cmp_espace++;
            j++;
        }
    
        return (cmp_espace<taille) ? 1:0;
    }

    return 0;
}

void pascalCase(char nom[]){
    size_t j=0;

    while(nom[j]!='\0'){
        if(!j)
            nom[j] = toupper(nom[j]);
        else
            nom[j] = tolower(nom[j]);
        j++;
    }
    
}

void saisirNom(char nom[]){
    do{
        printf("Entrez le nom: ");
        gets(nom);
    }while(!chaineValide(nom));
    pascalCase(nom);
}

void saisirEspece(char espece[]){
    do{
        printf("Entrez l'espece: ");
        gets(espece);
    }while(!chaineValide(espece));
    pascalCase(espece);
}

void saisirHabitat(char habitat[]){
    do{
        printf("Entrez l'habitat: ");
        gets(habitat);
    }while(!chaineValide(habitat));
    pascalCase(habitat);
}

size_t ageValide(char age[]){
    size_t j=0, cmp=0, taille=strlen(age);

    if(taille){
        while(age[j]!='\0'){
            if(age[j]<'0' || age[j]>'9')
                return 0;
            // if(age[j]=='0')
            //     cmp++;
            j++;
        }

        return (cmp<taille) ? 1:0;
    }

    return 0;
}

size_t saisirAge(){
    char age[longueurChaineMax];

    do{
        printf("Entrez l'age: ");
        gets(age);
    }while(!ageValide(age));

    return atoi(age);
}

float saisirPoids(){
    float poids;
    size_t validation;

    do{
        printf("Entrez le poids: ");
        validation = scanf("%f", &poids);
        if(getchar()!='\n'){
            validation = 0;
            while(getchar()!='\n');
        }
    }while(poids<0 || !validation);

    return poids;
}

size_t reponseValide(char rep[]){
    trim(rep);
    if(stricmp(rep, "O")==0 || stricmp(rep, "N")==0)
        return 1;
    
    return 0;
}

size_t ajouterAnimal(animal animaux[], size_t nbrAnimaux){
    char reponse[2];

    if(nbrAnimaux<=nbrMaxAnimaux){
        animaux[nbrAnimaux].id = nbrAnimaux+1;
        saisirNom(animaux[nbrAnimaux].nom);
        saisirEspece(animaux[nbrAnimaux].espece);
        animaux[nbrAnimaux].age = saisirAge();
        saisirHabitat(animaux[nbrAnimaux].habitat);
        do{
            printf("Voulez-vous entrer le poids? [O/N]\n");
            gets(reponse);
        }while(!reponseValide(reponse));
        if(stricmp(reponse, "O")==0)
            animaux[nbrAnimaux].poids = saisirPoids();
        else
            animaux[nbrAnimaux].poids = -1;
        nbrAnimaux++;
        printf("Animal ajoute avec succes.\n");
    }
    else{
        printf("Pas de place pour ajouter un autre.\n");
    }

    return nbrAnimaux;
}

size_t nombreValide(char nombre[]){
    size_t j=0, taille=strlen(nombre);

    if(taille){
        while(nombre[j]!='\0'){
            if(nombre[j]<'0' || nombre[j]>'9')
                return 0;
            j++;
        }

        return 1;
    }

    return 0;
}

size_t ajouterAnimaux(animal animaux[], size_t nbrAnimaux){
    char nombre[longueurChaineMax];

    do{
        printf("Entrez le nombre d'animaux a ajouter: ");
        gets(nombre);
    }while(!nombreValide(nombre));

    int nbr=atoi(nombre);
    size_t i;

    if(nbr){
        for(i=0;i<nbr;i++){
            nbrAnimaux = ajouterAnimal(animaux, nbrAnimaux);
        }
    }
    else{
        printf("Rien a ajoute.\n");
    }

    return nbrAnimaux;
}

void afficherAnimal(animal a){
    if(a.id){
        printf("***Animal:%zu***\n\tNom:%s\n\tEspece:%s\n\tAge:%zu\n\tHabitat:%s\n", a.id, a.nom, a.espece, a.age, a.habitat);
        if(a.poids!=-1)
            printf("\tPoids:%.1f\n\n", a.poids);
        else
            printf("\tPoids:non specifie\n\n");
    }
    else
        printf("Animal introuvable.\n\n");
}

void afficherAnimaux(animal animaux[], size_t nbrAnimaux){
    size_t i;

    for(i=0;i<nbrAnimaux;i++){
        afficherAnimal(animaux[i]);
    }
}

void trierAnimauxParNom(animal animaux[], size_t nbrAnimaux){
    size_t i, j, indice_min;
    animal temp;

    for(i=0;i<nbrAnimaux;i++){
        indice_min = i;
        for(j=i+1;j<nbrAnimaux;j++){
            if(strcmp(animaux[indice_min].nom, animaux[j].nom)>0){
                indice_min = j;
            }
        }
        temp = animaux[indice_min];
        animaux[indice_min]=animaux[i];
        animaux[i]=temp;
    }
}

void afficherAnimauxParNom(animal animaux[], size_t nbrAnimaux){
    trierAnimauxParNom(animaux, nbrAnimaux);
    afficherAnimaux(animaux, nbrAnimaux);
}

void trierAnimauxParAge(animal animaux[], size_t nbrAnimaux){
    size_t i, j, min, indice_min;
    animal temp;

    for(i=0;i<nbrAnimaux;i++){
        min = animaux[i].age;
        indice_min = i;
        for(j=i+1;j<nbrAnimaux;j++){
            if(min>animaux[j].age){
                min = animaux[j].age;
                indice_min = j;
            }
        }
        temp = animaux[indice_min];
        animaux[indice_min]=animaux[i];
        animaux[i]=temp;
    }
}

void afficherAnimauxParAge(animal animaux[], size_t nbrAnimaux){
    trierAnimauxParAge(animaux, nbrAnimaux);
    afficherAnimaux(animaux, nbrAnimaux);
}

void afficherAnimauxDunHabitat(animal animaux[], size_t nbrAnimaux){
    char habitat[longueurChaineMax];
    size_t i, cmp=0;

    saisirHabitat(habitat);
    for(i=0;i<nbrAnimaux;i++){
        if(strcmp(animaux[i].habitat, habitat)==0){
            afficherAnimal(animaux[i]);
            cmp++;
        }
    }
    if(!cmp)
        printf("*** Pas d'animaux dans: %s ou vous l'avez malsaisie***", habitat);
}

animal rechercherAnimalParId(animal animaux[], size_t nbrAnimaux, size_t id){
    size_t i;
    animal a;

    a.id = 0;
    if(id<=nbrAnimaux){
        for(i=0;i<nbrAnimaux;i++){
            if(animaux[i].id==id)
                return animaux[i];
        }
    }
    return a;
}

size_t saisirId(){
    char nombre[longueurChaineMax];

    do{
        printf("\nEntrez l'id de l'animal: ");
        gets(nombre);
    }while(!nombreValide(nombre));

    return atoi(nombre);
}

void trierAnimauxParId(animal animaux[], size_t nbrAnimaux){
    size_t i, j, indice_min;
    animal temp;

    for(i=0;i<nbrAnimaux;i++){
        indice_min = i;
        for(j=i+1;j<nbrAnimaux;j++){
            if(animaux[indice_min].id>animaux[j].id){
                indice_min = j;
            }
        }
        temp = animaux[indice_min];
        animaux[indice_min]=animaux[i];
        animaux[i]=temp;
    }
}

animal modifierHabitat(animal animaux[], size_t nbrAnimaux){
    size_t nbr=saisirId();

    trierAnimauxParId(animaux, nbrAnimaux);
    animal a = rechercherAnimalParId(animaux, nbrAnimaux, nbr);
    if(a.id){
        a=animaux[a.id-1];
        saisirHabitat(animaux[a.id-1].habitat);
        printf("\nAnimal apres modification: \n");
    }
    afficherAnimal(animaux[a.id-1]);
    return a;
}

animal modifierAge(animal animaux[], size_t nbrAnimaux){
    size_t nbr=saisirId();

    trierAnimauxParId(animaux, nbrAnimaux);
    animal a = rechercherAnimalParId(animaux, nbrAnimaux, nbr);
    if(a.id){
        a=animaux[a.id-1];
        animaux[a.id-1].age=saisirAge();
        printf("Animal apres modification: \n");
    }
    afficherAnimal(animaux[a.id-1]);
    return a;
}

size_t supprimerAnimal(animal animaux[], size_t nbrAnimaux){
    size_t i, nbr=saisirId();
    animal temp = rechercherAnimalParId(animaux, nbrAnimaux, nbr);

    trierAnimauxParId(animaux, nbrAnimaux);
    if(temp.id){
        for(i=nbr-1;i<nbrAnimaux;i++){
            animaux[i]=animaux[i+1];
            animaux[i].id--;
        }
        animaux[i]=temp;
        animaux[i].id--;
        nbrAnimaux--;
    }

    return nbrAnimaux;
}

size_t rechercherAnimalParNom(animal animaux[], size_t nbrAnimaux, animal animauxTrouves[], char nom[]){
    size_t i, nbrAnimauxTrouves=0;

    for(i=0;i<nbrAnimaux;i++){
        if(strcmp(animaux[i].nom, nom)==0){
            animauxTrouves[nbrAnimauxTrouves]=animaux[i];
            nbrAnimauxTrouves++;
        }
    }

    return nbrAnimauxTrouves;
}

size_t rechercherAnimalParEspece(animal animaux[], size_t nbrAnimaux, animal animauxTrouves[], char espece[]){
    size_t i, nbrAnimauxTrouves=0;

    for(i=0;i<nbrAnimaux;i++){
        if(strcmp(animaux[i].espece, espece)==0){
            animauxTrouves[nbrAnimauxTrouves]=animaux[i];
            nbrAnimauxTrouves++;
        }
    }

    return nbrAnimauxTrouves;
}

float ageMoyenAnimaux(animal animaux[], size_t nbrAnimaux){
    size_t i, somme=0;

    for(i=0;i<nbrAnimaux;i++){
        somme += animaux[i].age;
    }

    return (float)somme/(float)nbrAnimaux;
}

void plusJeuneAnimal(animal animaux[], size_t nbrAnimaux){
    size_t i, min=animaux[0].age;

    for(i=1;i<nbrAnimaux;i++){
        if(min>animaux[i].age){
            min = animaux[i].age;
        }
    }

    for(i=0;i<nbrAnimaux;i++){
        if(min == animaux[i].age)
            afficherAnimal(animaux[i]);
    }
}

void plusVieuxAnimal(animal animaux[], size_t nbrAnimaux){
    size_t i, max=animaux[0].age;

    for(i=1;i<nbrAnimaux;i++){
        if(max<animaux[i].age){
            max = animaux[i].age;
        }
    }

    for(i=0;i<nbrAnimaux;i++){
        if(max == animaux[i].age)
            afficherAnimal(animaux[i]);
    }
}

void trierAnimauxParEspece(animal animaux[], size_t nbrAnimaux){
    size_t i, j, indice_min;
    animal temp;

    for(i=0;i<nbrAnimaux;i++){
        indice_min = i;
        for(j=i+1;j<nbrAnimaux;j++){
            if(strcmp(animaux[indice_min].espece, animaux[j].espece)>0){
                indice_min = j;
            }
        }
        temp = animaux[indice_min];
        animaux[indice_min]=animaux[i];
        animaux[i]=temp;
    }
}

void especesLesPlusRepresentees(animal animaux[], size_t nbrAnimaux){
    size_t count=0, max=0, nbr=0;
    char especeActuelle[longueurChaineMax];

    trierAnimauxParEspece(animaux, nbrAnimaux);
    strcpy(especeActuelle, animaux[0].espece);
    while (nbr<nbrAnimaux){
        if(strcmp(especeActuelle, animaux[nbr].espece)==0){
            count++;
        }
        else{
            max = (count>max)?count:max;
            count = 0;
            strcpy(especeActuelle, animaux[nbr].espece);
        }
        nbr++;
    }
    max = (count>max)?count:max;
    count = 0;
    nbr=0;
    while (nbr<nbrAnimaux){
        if(strcmp(especeActuelle, animaux[nbr].espece)==0){
            count++;
        }
        else{
            if(count==max)
                printf("***%s***\n", especeActuelle);
            count = 0;
            strcpy(especeActuelle, animaux[nbr].espece);
        }
        nbr++;
    }
    if(count==max)
        printf("***%s***\n", especeActuelle);
}

void main(){
    int choix, subChoix;
    char chaine[longueurChaineMax];
    size_t nbrAnimaux = 0, nbrAnimauxTrouves;
    animal animauxTrouves[nbrMaxAnimaux], animaux[nbrMaxAnimaux] = {
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

    nbrAnimaux = initialiserTaille(animaux, nbrAnimaux);
    do{
        choix = menu();

        switch(choix){
            case 1:
                do{
                    subChoix = subMenuAjout();
                    switch(subChoix){
                        case 1: 
                            printf("===Ajouter un animal===\n");
                            nbrAnimaux = ajouterAnimal(animaux, nbrAnimaux);
                            break;
                        case 2: 
                            printf("===Ajouter plusieurs animaux===\n");
                            nbrAnimaux = ajouterAnimaux(animaux, nbrAnimaux);
                            break;
                        case 3: 
                            break;
                        default:
                            printf("Veuillez entrer un choix valide.");
                    }
                }while(subChoix!=3);
                break;
            case 2:
                do{
                    subChoix = subMenuAffichage();
                    switch(subChoix){
                        case 1: 
                            printf("===Liste complete===\n");
                            afficherAnimaux(animaux, nbrAnimaux);
                            break;
                        case 2: 
                            printf("===Animaux par nom===\n");
                            afficherAnimauxParNom(animaux, nbrAnimaux);
                            break;
                        case 3: 
                            printf("===Animaux par age===\n");
                            afficherAnimauxParAge(animaux, nbrAnimaux);
                            break;
                        case 4: 
                            printf("===Animaux par habitat===\n");
                            afficherAnimauxDunHabitat(animaux, nbrAnimaux);
                            break;
                        case 5: 
                            break;
                        default:
                            printf("Veuillez entrer un choix valide.");
                    }
                }while(subChoix!=5);
                break;
            case 3:
                do{
                    subChoix = subMenuModification();
                    switch(subChoix){
                        case 1: 
                            printf("===Modifier habitat===\n");
                            modifierHabitat(animaux, nbrAnimaux);
                            break;
                        case 2: 
                            printf("===Modifier age===\n");
                            modifierAge(animaux, nbrAnimaux);
                            break;
                        case 3: 
                            break;
                        default:
                            printf("Veuillez entrer un choix valide.");
                    }
                }while(subChoix!=3);
                break;
            case 4: 
                printf("===Supprimer un animal===\n");
                nbrAnimaux = supprimerAnimal(animaux, nbrAnimaux);
                break;
            case 5: 
                do{
                    subChoix = subMenuRecherche();
                    switch(subChoix){
                        case 1: 
                            printf("===Rechercher un animal par id===\n");
                            afficherAnimal(rechercherAnimalParId(animaux, nbrAnimaux,saisirId()));
                            break;
                        case 2: 
                            printf("===Rechercher un animal par nom===\n");
                            saisirNom(chaine);
                            nbrAnimauxTrouves = rechercherAnimalParNom(animaux, nbrAnimaux, animauxTrouves, chaine);
                            afficherAnimaux(animauxTrouves, nbrAnimauxTrouves);
                            break;
                        case 3:
                            printf("===Rechercher un animal par espece===\n");
                            saisirEspece(chaine);
                            nbrAnimauxTrouves = rechercherAnimalParEspece(animaux, nbrAnimaux, animauxTrouves, chaine);
                            afficherAnimaux(animauxTrouves, nbrAnimauxTrouves);
                            break;
                        case 4: 
                            break;
                        default:
                            printf("Veuillez entrer un choix valide.");
                    }
                }while(subChoix!=4);
                break;
            case 6:
                do{
                    subChoix = subMenuStatistiques();
                    switch(subChoix){
                        case 1: 
                            printf("===Nombre total des animaux dans le zoo===\n");
                            printf("Le nombre total des animaux dans le zoo est: %d.\n", nbrAnimaux);
                            break;
                        case 2: 
                            printf("===Age moyen des animaux===\n");
                            printf("L'age moyen des animaux est: %.2f.\n", ageMoyenAnimaux(animaux, nbrAnimaux));
                            break;
                        case 3:
                            printf("===Plus vieux et plus jeune animal===\n");
                            printf("Le plus jeune animal est: \n");
                            plusJeuneAnimal(animaux, nbrAnimaux);
                            printf("Le plus vieux animal est: \n");
                            plusVieuxAnimal(animaux, nbrAnimaux);
                            break;
                        case 4:
                            printf("===Les especes les plus representees==\n");
                            especesLesPlusRepresentees(animaux, nbrAnimaux);
                            break;
                        case 5: 
                            break;
                        default:
                            printf("Veuillez entrer un choix valide.");
                    }
                }while(subChoix!=5);
                break;
            case 7: 
                printf("Au revoir!");
                break;
            default:
                printf("Veuillez entrer un choix valide.");
        }
    }while(choix!=7);
}
