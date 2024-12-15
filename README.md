CONTEXTE

Dans le cadre d'un Projet scolaire en programmation en C.
On avait le choit avec divers projet et celui choisi pour ma part est le moteur de recherche avec les wildcard.
J'ai choisi le moteur de recherche car je n'ai jamais fait de projet de qui permet de faire des recherches surtout que cela pourra me servir pour des projets personnel ou professionel lors de projet de conception de site ou d'application contenant beaucoup d'information dans différente page ou de jeu avec des indices numérique etc..


SUJET

Moteur de recherche plein texte

Un moteur de recherche plein texte est un système permettant de rechercher
des informations dans un ensemble de textes ou de documents en analysant leur
contenu dans son intégralité, mot par mot. Contrairement aux simples recherches
par mots-clés ou par index, un moteur de recherche plein texte parcourt tous les
mots du texte pour retrouver les résultats les plus pertinents.
Votre moteur doit supporter: - Recherche exacte - Sensibilité ou non à la casse -
Wildcards: ex. Jun* pour Junia

Points bonus: - Support d’opérateurs logiques: OR, AND

HYPOTHESE DE RESOLUTION

J'ai pour objectif de faire fonctionner le moteur de recherche dans la console avec un rajout front si le temps est suffisant.
J'ai une vision des choses pour accomplir le code de faire une fonction de Recherche exacte, de sensibilité ou non à la casse et des wildcards ce qui permettrait de trouver un mot sans même l'écrire en entier.
Si on reprend point par point la recherche exacte sera basé sur les caractères inscrit par l'utilisateur pour former ce qu'il désir trouver.
Les wildcards lui sera pertinant pour ne pas à avoir à écrire tout le mot.

DEVELOPPEMENT

On utilisera le langage C avec divers librairie afin de pouvoir effectuer les recherches.
Dans le code il me faudra une structure qui me permet de vérifier dans les divers fichiers la recherche du mot rechercher en fouillant dans le dossier qu'on veut vérifié en particulier.
Pour finir avec le développement il faut trouver un moyen d'effectuer des recherches grace à "*" après le début de mot rentrée afin de raccourcir le temps de recherche et de ne pas s'embêter à écrire tout le mot.
Petit rajout, il ne faut pas oublier de libérer la mémoire.
