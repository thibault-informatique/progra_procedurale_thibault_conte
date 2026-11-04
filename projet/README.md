# TODO 04/11/26

1. Finaliser le CRUD (prochaine étape logique) — device.c

removeDevice() : trouver l'index du device, décaler les éléments suivants d'une case vers la gauche (memmove), décrémenter nbOfDevice. Note: la signature actuelle prend un Device* seul, mais il te faut probablement le Park* et le nom/index pour savoir quoi supprimer.
updateDevice() : réutiliser initDevice (ou une variante) pour re-valider les nouvelles valeurs IP/masque avant modification.
Ajouter ERR_NOT_FOUND à Return_crud pour les cas device introuvable.
2. Fonctions utilitaires IP — main.c / network.c

Ton TODO: conversion IP 4 bytes ↔ binaire (déjà IPV4(a,b,c,d) en macro, il manque l'inverse: uint8_t × 4 depuis une Ipv4).
3. Menu interactif — brancher displayMainPage() et l'IHM pour que l'utilisateur puisse réellement ajouter/consulter/modifier/supprimer (consigne 3.1 complète).

4. Recherche, filtre, tri (consigne 3.2)

Recherche par nom (déjà fait via findDevice), par IP; filtres par type/état; tris (nom, IP, type). C'est là que tu pourras utiliser la transmission de fonctions en argument (critère d'évaluation) — ex. Device* findDeviceBy(Park*, bool (*predicate)(const Device*)).
5. Plus tard (selon avancement du cours) — park dynamique (double ** mentionné dans ton TODO), persistance fichier, algorithmes récursifs.


# Network Manager 
**Projet fin de cours Programmation Procédurale ITLg**

*Bac Info orientation réseau et Télécom*

Langage C

Décembre 2026



## Compilation
```gcc -Wall -Wextra -Wpedantic -std=c23 *.c -o prog```

## Idées BONUS:

- ajout IPv6

- utiliser argc / argv pour permettre d'appeler le programme avec paramètres via
    - h : info général du programme
    - f : find a device
    - a : add a device


