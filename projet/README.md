# TODO 05/11/26

1. Finaliser le CRUD (prochaine étape logique) — device.c
    => dans update : fignoler handleUpdateAddressAndMask


2. Fonctions utilitaires IP — main.c / network.c

Ton TODO: conversion IP 4 bytes ↔ binaire (déjà IPV4(a,b,c,d) en macro, il manque l'inverse: uint8_t × 4 depuis une Ipv4).
3. Menu interactif — brancher displayMainPage() et l'IHM pour que l'utilisateur puisse réellement ajouter/consulter/modifier/supprimer (consigne 3.1 complète).

4. Recherche, filtre, tri (consigne 3.2)

Recherche par nom (déjà fait via findDevice), par IP; filtres par type/état; tris (nom, IP, type). C'est là que tu pourras utiliser la transmission de fonctions en argument (critère d'évaluation) — ex. Device* findDeviceBy(Park*, bool (*predicate)(const Device*)).
5. Plus tard (selon avancement du cours) — park dynamique (double ** mentionné dans ton TODO), persistance fichier, algorithmes récursifs.

6. Vérifier tous les TODO

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


