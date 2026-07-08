# 2048 Qt 🎮

Une version graphique du célèbre jeu **2048**, développée en **C++ avec Qt**.

## 📌 Description

**2048 Qt** est une implémentation du jeu de puzzle 2048 dans laquelle le joueur doit combiner des tuiles portant les mêmes valeurs afin d'obtenir la tuile **2048**.

Le projet utilise une interface graphique réalisée avec **Qt**, avec une gestion du menu, du score, de la sauvegarde et de la progression du joueur.

## 🎯 Objectifs du projet

* Créer une application graphique en C++ avec Qt
* Implémenter la logique complète du jeu 2048
* Gérer les déplacements des tuiles
* Calculer automatiquement le score
* Sauvegarder et restaurer une partie
* Créer une interface utilisateur simple et agréable

## ✨ Fonctionnalités

✅ Menu principal
✅ Jeu 2048 complet
✅ Déplacement des tuiles :

* Haut ⬆️
* Bas ⬇️
* Gauche ⬅️
* Droite ➡️

✅ Fusion automatique des tuiles identiques
✅ Système de score
✅ Meilleur score sauvegardé
✅ Sauvegarde de partie
✅ Interface graphique personnalisée avec Qt Style Sheet (`.qss`)

## 🛠️ Technologies utilisées

* **Langage :** C++
* **Framework graphique :** Qt
* **Système de compilation :** qmake / Makefile
* **Interface :** Qt Widgets

## 📂 Organisation du projet

```
2048-Qt/
│
├── main.cpp              # Point d'entrée du programme
│
├── Game2048.cpp          # Logique principale du jeu
├── Game2048.hpp          # Déclaration de la classe Game2048
│
├── Menu.cpp              # Gestion du menu
├── Menu.hpp
│
├── style.qss             # Style graphique de l'application
│
├── Score.txt             # Score actuel
├── BestScore.txt         # Meilleur score
├── Sauvegarde.txt        # Sauvegarde de partie
│
├── Game2048.pro          # Projet Qt
└── Makefile              # Compilation
```

## ⚙️ Installation

### 1. Cloner le projet

```bash
git clone https://github.com/Anjaniaina24/2048-Qt.git
```

### 2. Accéder au dossier

```bash
cd 2048-Qt
```

### 3. Compiler le projet

Avec Qt :

```bash
qmake
make
```

### 4. Lancer l'application

```bash
./2048
```

## 🎮 Règles du jeu

* Chaque déplacement ajoute une nouvelle tuile.
* Deux tuiles ayant la même valeur peuvent fusionner.
* Le joueur gagne lorsqu'il atteint la tuile **2048**.
* La partie se termine lorsqu'aucun déplacement n'est possible.

## 💾 Sauvegarde

Le jeu permet de conserver :

* Le score actuel
* Le meilleur score
* La grille de jeu

Les données sont enregistrées automatiquement dans des fichiers texte.

## 🖼️ Capture d'écran

*(Ajouter ici une capture d'écran du jeu)*

Exemple :

```
![2048 Qt](screenshot.png)
```

## 🚀 Améliorations possibles

Quelques fonctionnalités pouvant être ajoutées :

* Mode sombre
* Animations des déplacements
* Sons
* Plusieurs niveaux de difficulté
* Classement des meilleurs scores
* Version mobile

## 👨‍💻 Auteur

**Anjaniaina24**

Projet réalisé dans le cadre de l'apprentissage de la programmation C++ et du développement d'applications graphiques avec Qt.

## 📄 Licence

Ce projet est libre d'utilisation pour un usage personnel et éducatif.
