#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

// Définition de la taille maximale pour une ligne de texte
#define LONGUEUR_MAX 1024

// Définition de la structure pour les options de recherche
typedef struct {
    char* modele;
    bool ignore_cas;
    bool utiliserw;
} OptionsRecherche;

// Prototypes des fonctions utilisées dans le programme
void Minuscule(char* str);
int Recherche(const char* mot, const char* modele, bool ignore_cas);
int Wildcards(const char* texte, const char* modele, bool ignore_cas);
void Affichage(const char* ligne, const OptionsRecherche* options, int numerol);

// Fonction principale du programme
int main() {
    char nomfichier[256];// Stocke le chemin du fichier
    OptionsRecherche options = { NULL, false, false };// Initialisation des options de recherche

    // Demande à l'utilisateur d'entrer le chemin du fichier
    printf("Entrez le chemin du fichier : ");
    if (!fgets(nomfichier, sizeof(nomfichier), stdin)) {
        printf("Erreur : saisie du chemin invalide.\n");
        return 1;
    }
    nomfichier[strcspn(nomfichier, "\n")] = '\0';  // Supprimer le saut de ligne
    
    // Ouvre le fichier
    FILE* fichier;
    if (fopen_s(&fichier, nomfichier, "r") != 0 || fichier == NULL) {
        printf("Erreur : impossible d'ouvrir le fichier %s.\n", nomfichier);
        return 1;
    }

    // Allocation dynamique pour le modèle de recherche
    options.modele = (char*)malloc(256 * sizeof(char));
    if (!options.modele) {
        printf("Erreur : allocation mémoire échouée.\n");
        fclose(fichier);
        return 1;
    }

    // Demande à l'utilisateur d'entrer le modèle ou le motif de recherche
    printf("Entrez le mot ou la wildcards à rechercher : ");
    if (!fgets(options.modele, 256, stdin)) {
        printf("Erreur : saisie du wildcards invalide.\n");
        free(options.modele);
        fclose(fichier);
        return 1;
    }
    options.modele[strcspn(options.modele, "\n")] = '\0';// Supprime le caractère de saut de ligne

    // Demande si la recherche doit ignorer la casse
    printf("Ignorer la casse ? (0=oui, 1=non) : ");
    if (scanf_s("%d", (int*)&options.ignore_cas) != 1) {
        printf("Erreur : saisie invalide.\n");
        free(options.modele);
        fclose(fichier);
        return 1;
    }

    // Demande si la recherche doit inclure des wildcards
    printf("Utiliser des wildcards ? (0=oui, 1=non) : ");
    if (scanf_s("%d", (int*)&options.utiliserw) != 1) {
        printf("Erreur : saisie invalide.\n");
        free(options.modele);
        fclose(fichier);
        return 1;
    }
    // Lecture et traitement du fichier ligne par ligne
    char tampon[LONGUEUR_MAX];
    int numerol = 0;// Numéro de la ligne en cours de traitement
    bool mottrouver = false;// Indique si au moins une correspondance a été trouvée

    while (fgets(tampon, sizeof(tampon), fichier)) {
        numerol++;
        Affichage(tampon, &options, numerol);// Recherche des correspondances dans la ligne actuelle
        mottrouver = true;
    }
    // Si aucune correspondance n'a été trouvée
    if (!mottrouver) {
        printf("Aucune correspondance trouvée.\n");
    }
    // Libération de la mémoire et fermeture du fichier
    free(options.modele);
    fclose(fichier);
    return 0;
}

void Affichage(const char* ligne, const OptionsRecherche* options, int numerol) {
    // Allocation dynamique d'un tampon pour manipuler la ligne
    char* tampon = (char*)malloc(strlen(ligne) + 1);
    if (!tampon) {
        printf("Erreur : allocation mémoire échouée.\n");
        return;
    }
    strcpy_s(tampon, strlen(ligne) + 1, ligne);
    // Découpe la ligne en mots en utilisant des délimiteurs
    char* token;
    char* next_token = NULL;
    token = strtok_s(tampon, " \t\n\r", &next_token);
    // Parcourt chaque mot de la ligne
    while (token != NULL) {
        int match = options->utiliserw
            ? Wildcards(token, options->modele, options->ignore_cas)// Recherche avec wildcards
            : Recherche(token, options->modele, options->ignore_cas);// Recherche exacte
        // Si une correspondance est trouvée, l'afficher
        if (match) {
            printf("Trouvé à la ligne %d : %s\n", numerol, token);
        }

        token = strtok_s(NULL, " \t\n\r", &next_token);// Passe au mot suivant
    }

    free(tampon);// Libère la mémoire allouée pour le tampon
}
// Fonction pour effectuer une recherche exacte
int Recherche(const char* mot, const char* modele, bool ignore_cas) {
    if (ignore_cas) {
        // Création de copies pour ignorer la casse
        char* motc = (char*)malloc(strlen(mot) + 1);
        char* modelec = (char*)malloc(strlen(modele) + 1);

        if (!motc || !modelec) {
            free(motc);
            free(modelec);
            return 0;
        }

        strcpy_s(motc, strlen(mot) + 1, mot);
        strcpy_s(modelec, strlen(modele) + 1, modele);

        Minuscule(motc);
        Minuscule(modelec);

        int resultat = strstr(motc, modelec) != NULL;

        free(motc);
        free(modelec);

        return resultat;
    }
    return strstr(mot, modele) != NULL;
}
// Fonction pour effectuer une recherche avec des wildcards
int Wildcards(const char* texte, const char* modele, bool ignore_cas) {
    if (ignore_cas) {
        // Création de copies pour ignorer la casse
        char* textec = (char*)malloc(strlen(texte) + 1);
        char* modelec = (char*)malloc(strlen(modele) + 1);

        if (!textec || !modelec) {
            free(textec);
            free(modelec);
            return 0;
        }

        strcpy_s(textec, strlen(texte) + 1, texte);
        strcpy_s(modelec, strlen(modele) + 1, modele);
        Minuscule(textec);
        Minuscule(modelec);

        int resultat = Wildcards(textec, modelec, false);

        free(textec);
        free(modelec);
        return resultat;
    }
    // Parcourt le modèle et compare avec le texte
    while (*modele) {
        if (*modele == '*') {
            while (*modele == '*') modele++;
            if (!*modele) return 1;
            while (*texte) {
                if (Wildcards(texte, modele, false)) return 1;
                texte++;
            }
            return 0;
        }
        else if (*modele == '?' || *modele == *texte) {
            modele++;
            texte++;
        }
        else {
            return 0;
        }
    }
    return *texte == '\0';
}
// Fonction pour convertir une chaîne en minuscules
void Minuscule(char* str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower((char)str[i]);
    }
}
