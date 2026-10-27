# LABO 03 : CODEBREAKER

## But
Deviner un code secret

## 3 modes de jeu
1) partie classique
2) partie personnalisée
3) partie à 2 joueurs

## Construction de l'exécutable
mingw32-make all

## Lancer le programme
mingw32-make run

## Nettoyer les objets et l'exécutable
mingw32-make clean

## Calcul score
Meilleur score possible = 1000
chaque nouvelle tentative retire des points (diminution moins sévère pour les codes plus longs)
Valable pour un code de 4 à 6 chiffres et pour des tentatives entre 1 à 15
Sinon invalide car risque de score négatif ou de division par zéro 

## Précision
Si la longueur du code = n , saisie utilisateur acceptée à n - 1 :  
le digit non saisi le plus à gauche sera = 0  
(si la règle de chaque digit distinct dans le code est respectée)