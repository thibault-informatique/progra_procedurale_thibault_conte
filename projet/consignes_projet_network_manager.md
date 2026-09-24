\# Projet – Network Manager



\## 1. Description du projet



Dans le cadre de l’unité d’enseignement Techniques de programmation procédurale, il est demandé à chaque étudiant de développer individuellement une application en langage C permettant de gérer un parc d’équipements informatiques et réseau.



L’objectif de ce projet est de mettre progressivement en pratique les différentes notions abordées durant le cours au sein d’une application unique et cohérente. Le projet constitue ainsi un fil rouge : sa première version restera volontairement simple et devra être enrichie, restructurée et améliorée au fur et à mesure de l’apprentissage.



Le choix d’un gestionnaire de parc réseau permet d’inscrire le développement dans le contexte du Bachelier en Informatique, orientation Réseaux et Télécommunications. L’application devra permettre de représenter différents équipements d’une infrastructure, d’en gérer la configuration et d’effectuer plusieurs traitements sur les données enregistrées.



Une attention particulière sera accordée à la démarche de développement. L’objectif n’est pas uniquement d’obtenir une application fonctionnelle, mais de produire un programme structuré, lisible, maintenable et dont les choix techniques peuvent être expliqués et justifiés.



\---



\## 2. Acquis d’apprentissage



Le projet participe à l’évaluation des acquis d’apprentissage définis dans le dossier pédagogique de l’unité d’enseignement Techniques de programmation procédurale – 2982 31 U31 D2.



Pour atteindre le seuil de réussite, l’étudiant doit notamment être capable d’effectuer l’analyse informatique, de programmer et de tester une application technique nécessitant l’emploi :



\- de procédures et fonctions avec plusieurs niveaux d’appel ;

\- de structures de données dynamiques linéaires ;

\- de la transmission de fonctions et de procédures en arguments.



Le projet permettra également d’évaluer progressivement la capacité de l’étudiant à utiliser des algorithmes classiques de recherche et de tri, des structures de données dynamiques ainsi que des algorithmes récursifs.



Au-delà du fonctionnement de l’application, une attention sera portée à la pertinence de l’analyse, à la fiabilité des tests, à l’organisation et à l’optimisation du programme, à sa documentation ainsi qu’au degré d’autonomie atteint.



\---



\## 3. Fonctionnalités attendues



\### 3.1. Gestion des équipements réseau -> CRUD



L’application doit permettre de représenter et de gérer différents équipements appartenant à un parc informatique : routeurs, switches, serveurs, postes de travail, points d’accès ou autres équipements pertinents.



Chaque équipement doit disposer d’un ensemble d’informations permettant de l’identifier et de décrire sa configuration. On retrouvera notamment son nom, son type, son adresse IP, son masque réseau et son état.



L’utilisateur doit pouvoir ajouter, consulter, modifier et supprimer un équipement.



Les données utilisées par l’application devront être organisées de manière cohérente et la manière de les stocker devra évoluer en fonction des notions abordées durant le cours.



\### 3.2. Recherche, filtrage et tri >Algorythmie



L’application doit permettre d’exploiter les informations contenues dans le parc.



L’utilisateur devra notamment pouvoir rechercher un équipement selon certains critères, filtrer la liste des équipements et les trier.



Les critères proposés sont laissés en partie à l’appréciation de l’étudiant. Il doit néanmoins être possible, par exemple, de rechercher un équipement par son nom ou son adresse IP, de filtrer les équipements selon leur type ou leur état et de les trier selon différents critères.



Les traitements devront être réalisés à partir des données enregistrées et ne pourront pas reposer sur des résultats prédéfinis.



\### 3.3. Calculs réseau



L’application doit proposer plusieurs traitements liés à l’adressage IPv4.



À partir des informations d’un équipement, elle devra notamment être capable d’effectuer des calculs permettant de déterminer certaines informations réseau telles que l’adresse réseau et l’adresse de broadcast.



D’autres calculs ou outils liés à l’adressage pourront être ajoutés au cours du développement.



\### 3.4. Validation de la configuration -> conditions



L’application doit contrôler les informations introduites par l’utilisateur et éviter autant que possible l’enregistrement de configurations incohérentes.



Elle devra notamment vérifier la validité des informations relatives à l’adressage IP.



L’étudiant devra réfléchir aux différentes situations pouvant rendre une configuration invalide ou incohérente et prévoir un comportement approprié de l’application.



\### 3.5. Sauvegarde et chargement -> save dans fichier binaire ou textes classiques au choix (justifier)



Les données du parc doivent pouvoir être conservées entre deux exécutions du programme.



L’application devra donc permettre de sauvegarder les équipements dans un ou plusieurs fichiers et de reconstruire le parc à partir de ces fichiers lors d’une exécution ultérieure.



Le format utilisé devra être documenté et rester cohérent avec les données manipulées par l’application.



\### 3.6. Statistiques -> calculs



L’application doit proposer une vue synthétique du parc à travers plusieurs statistiques calculées à partir des données enregistrées.



Il pourra notamment s’agir du nombre total d’équipements, de leur répartition par type, du nombre d’équipements actifs ou inactifs ou encore de leur répartition entre différents réseaux.



Les statistiques devront être calculées dynamiquement à partir du contenu réel du parc.



\### 3.7. Interface utilisateur - CLI



L’application sera développée sous la forme d’une application en ligne de commande (CLI).



L’utilisateur devra pouvoir naviguer entre les différentes fonctionnalités à l’aide d’un système de menus clair et cohérent.



L’interface devra notamment permettre d’accéder à la gestion des équipements, aux recherches et tris, aux outils réseau ainsi qu’aux statistiques, puis de revenir au menu principal ou de quitter proprement l’application.



Une attention particulière sera portée à la gestion des saisies incorrectes et à la clarté des informations affichées.



\---



\## 4. Développement du projet -> blabla



Le projet est individuel et sera développé progressivement pendant toute la durée de l’unité d’enseignement.



Il n’est pas attendu que l’ensemble des fonctionnalités soit développé dès le début. Les différentes notions abordées durant le cours devront progressivement être intégrées au projet.



Certaines parties du programme pourront donc être modifiées ou entièrement restructurées au cours du quadrimestre. Cette évolution fait partie intégrante du travail demandé.



Le projet devra être versionné avec Git et disponible sur le dépôt GitHub personnel de l’étudiant. L’historique du dépôt devra permettre d’observer une progression régulière du travail.



L’utilisation d’outils d’intelligence artificielle est autorisée comme aide au développement. L’étudiant reste cependant entièrement responsable du code remis et doit être capable d’en expliquer le fonctionnement ainsi que les choix réalisés.



\---



\## 5. Évaluation et formalités -> qualité code avant fonctionnalité



Le projet représente 40 % de la note finale de l’unité d’enseignement :



\- 25 % : réalisation technique et qualité du projet ;

\- 15 % : présentation et défense orale individuelle.



La version définitive du projet devra être disponible sur le dépôt GitHub personnel de l’étudiant au plus tard le 16 décembre 2026 à 17 h 30.



La version présente sur le dépôt à cette échéance sera considérée comme la version remise pour évaluation.



Lors de la défense orale, l’étudiant devra présenter son application, expliquer son organisation et justifier les principaux choix techniques réalisés.



Des questions pourront porter sur n’importe quelle partie du code remis ainsi que sur les notions du cours mises en œuvre dans le projet. L’étudiant pourra également être invité à expliquer, corriger ou modifier une partie de son programme.



La qualité de la défense doit permettre de démontrer que l’ensemble du code remis est compris et maîtrisé par son auteur.

