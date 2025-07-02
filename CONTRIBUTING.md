# 🗭 Directive de contribution – Projet Zappy

## 📌 Objectif

Ce projet consiste à développer un jeu réseau nommé **Zappy**, dans lequel plusieurs équipes s’affrontent sur une carte contenant des ressources. Il est composé de trois binaires principaux :

* `zappy_server` (en C)
* `zappy_gui` (en C++)
* `zappy_ai` (langage libre)

## 👥 Membres du projet

| Pseudo GitHub    | Rôle supposé                      | Commits | + / - lignes  |
| ---------------- | --------------------------------- | ------- | ------------- |
| **CorpsB**       | Responsable serveur / logique jeu | 115     | +6798 / -2648 |
| **OkotEgarim**   | Développeur IA                    | 56      | +5550 / -2535 |
| **brice9478**    | Développeur IA / GUI              | 51      | +5581 / -3234 |
| **Tomaraptor67** | Développeur serveur / protocole   | 50      | +5159 / -4792 |
| **Turtelthib**   | Développeur GUI                   | 46      | +6263 / -1626 |
| **PCyrian**      | Support ou intégration ponctuelle | 1       | +981 / -0     |

## 💠 Structure du dépôt

```
/
├── server/          → Code C du serveur (zappy_server)
├── gui/             → Code C++ de l’interface graphique (zappy_gui)
├── ai/              → Clients autonomes IA (zappy_ai)
├── include/         → En-têtes partagés
├── protocol/        → Protocole de communication GUI/Server
├── docs/            → PDF, schémas, etc.
└── Makefile         → Compilation des 3 binaires
```

## 🔀 Flux de contribution

### 1. Branching

* **main** : branche stable, prête pour livraison
* **dev** : intégration continue des fonctionnalités
* **feature/xxx** : une fonctionnalité ou amélioration spécifique
* **bugfix/xxx** : correction de bug

### 2. Règles de commit

Format recommandé :

```
[type] composant: message court
```

Exemples :

* `feat(server): add fork command handling`
* `fix(gui): prevent segmentation fault on empty tile`
* `refactor(protocol): simplify message parsing`

### 3. Revue de code

* Tout *merge* vers `dev` nécessite une **Pull Request**.
* Minimum **1 review d’un autre membre** avant merge.
* Les tests manuels ou unitaires doivent être faits avant soumission.

## 📆 Compilation

Votre Makefile **doit générer** les binaires suivants :

```bash
make zappy_server
make zappy_gui
make zappy_ai
```

## 📄 Protocole GUI (obligatoire)

Le protocole défini dans `B-YEP-400_zappy_GUI_protocol.pdf` **doit être strictement respecté** par l’interface graphique (GUI).

## 📙 Documentation

* Chaque module doit comporter un README si nécessaire.
* Documentez vos fonctions via des commentaires clairs.
* Pour les projets C/C++, vous pouvez utiliser `Doxygen`.

## ✅ Bonnes pratiques

* Le code **doit compiler sans warnings** (`-Wall -Wextra -Werror` recommandé).
* Respect strict des normes de codage (norme EPITECH / entreprise si applicable).
* Les sockets doivent être **non-bloquantes** (`poll()` utilisé côté serveur).
* Aucun accès disque ou STDIN/STDOUT non contrôlé dans les IA.

---

Merci pour vos contributions ✨
