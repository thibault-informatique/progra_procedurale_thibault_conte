# TODO 05/11/26
1. Finaliser le CRUD (prochaine étape logique) — addDevice

4. Recherche, filtre, tri (consigne 3.2)

Recherche par nom (déjà fait via findDevice), par IP; filtres par type/état; tris (nom, IP, type). C'est là que tu pourras utiliser la transmission de fonctions en argument (critère d'évaluation) — ex. Device* findDeviceBy(Park*, bool (*predicate)(const Device*)).
5. Plus tard (selon avancement du cours) — park dynamique (double ** mentionné dans ton TODO), persistance fichier, algorithmes récursifs.

6. Vérifier tous les TODO

0. TODO :

Compléter la saisie utilisateur d'un équipement — c'est le vrai goulot d'étranglement : tu sais valider une IP, mais tu n'as aucun moyen de rentrer un device complet. Il manque :

saisie du masque (décimal ou préfixe /n) ;
saisie du nom, du type et du statut (menus numériques).


Ensuite seulement : les calculs réseau (§3.3 — adresse réseau, broadcast, /préfixe — les TODO de device.h), puis recherche/tri (§3.2), stats (§3.6), et sauvegarde fichier (§3.5) en tout dernier.



## Network Manager 
**Projet fin de cours Programmation Procédurale ITLg**

*Bac Info orientation réseau et Télécom*

Langage C

Décembre 2026

## Choix pour le projet

- encoder une adresse IP va de pair avec un encodage de masque de réseau et vice-versa

## Compilation
```gcc -Wall -Wextra -Wpedantic -std=c23 *.c -o prog```

## BONUS:

- ajout IPv6

- en ligne de commandes, en paramètres lors du lancement du programme

 => utiliser argc / argv pour récupérer les arguments via
    --help : info général du programme
    --add : add a device
    --show: affiche le parc d'équipements


