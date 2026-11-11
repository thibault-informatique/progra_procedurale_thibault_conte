# TODO 05/11/26
1. Finaliser le CRUD (prochaine étape logique) — addDevice

4. Recherche, filtre, tri (consigne 3.2)

Recherche par nom (déjà fait via findDevice), par IP; filtres par type/état; tris (nom, IP, type). C'est là que tu pourras utiliser la transmission de fonctions en argument (critère d'évaluation) — ex. Device* findDeviceBy(Park*, bool (*predicate)(const Device*)).
5. Plus tard (selon avancement du cours) — park dynamique (double ** mentionné dans ton TODO), persistance fichier, algorithmes récursifs.

6. Vérifier tous les TODO

0. TODO :

Compléter la saisie utilisateur d'un équipement — c'est le vrai goulot d'étranglement : tu sais valider une IP, mais tu n'as aucun moyen de rentrer un device complet. Il manque :

getDecimalIPv4Address() (décommenter/finir) — plus naturel que l'hexa pour un utilisateur ;
saisie du masque (décimal ou préfixe /n) ;
saisie du nom, du type et du statut (menus numériques).
Finition CRUD : updateDevice et removeDevice — au passage leurs signatures sont bancales : removeDevice(Device* device) ne peut pas le retirer du Park. Il faudrait plutôt removeDevice(Park *park, int index) avec décalage du tableau, et updateDevice(Device *device) qui redemande chaque champ via les fonctions de saisie du point 3.

Brancher le menu dans main.c : displayMainPage existe, mais rien ne l'utilise. Objectif : pouvoir ajouter, lister, chercher, modifier, supprimer un équipement de bout en bout. Ça te donne un CRUD démontrable (section 3.1 des consignes).

Ensuite seulement : les calculs réseau (§3.3 — adresse réseau, broadcast, /préfixe — les TODO de device.h), puis recherche/tri (§3.2), stats (§3.6), et sauvegarde fichier (§3.5) en tout dernier.

L'idée directrice : viser d'abord un parcours utilisateur complet pour un seul équipement ("ajouter → afficher → modifier → supprimer"), plutôt que de polir chaque module isolément. Les points 2–3 sont le prochain commit logique. Veux-tu que je commence par corriger le build et implémenter isValidMask ?


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


