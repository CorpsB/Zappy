# Zappy – README

Bienvenue ! Ce document présente **Zappy**, le projet réseau/IA/graphismes que vous venez de cloner.  
Il est rédigé en Markdown afin d’être copié-collé directement dans votre dépôt GitLab/GitHub.

---

## Sommaire
- Présentation générale  
- Architecture des exécutables  
- Prérequis & dépendances  
- Compilation  
- Lancement rapide  
- Paramètres détaillés  
- Règles du gameplay  
- Arborescence conseillée  
- Contribuer  
- Auteurs & licence

---

## Présentation générale
Zappy est un **jeu en réseau** dans lequel plusieurs équipes de drones s’affrontent sur une carte torique.  
Le but : être la première équipe à élever **six joueurs** au niveau 8 grâce à la collecte de ressources et à des rituels d’incantation collaboratifs.

Le projet se divise en trois programmes :

| Binaire       | Rôle principal | Langage |
|---------------|----------------|---------|
| zappy_server  | Moteur de jeu / serveur TCP | C |
| zappy_gui     | Visualisation temps réel du monde | C++ (SFML) |
| zappy_ai      | Client autonome pilotant un drone | Libre (ex : C, Python…) |

Un protocole texte simple (terminé par « \n ») régit toutes les communications ; la spécification complète est disponible dans `B-YEP-400_zappy_GUI_protocol.pdf` et `B-YEP-400_zappy .pdf`.

---

## Architecture des exécutables
- **Serveur**  
  - Processus unique, mono-thread, multiplexage via poll.  
  - Génère la carte, applique l’IA serveur (respawn, gestion du temps), relaie toutes les commandes.
- **GUI**  
  - S’identifie comme client « GRAPHIC » auprès du serveur.  
  - Affiche les tuiles, ressources, joueurs, incantations et messages.
- **AI**  
  - Se connecte à une équipe donnée.  
  - Envoie jusqu’à 10 commandes en file sans blocage, interprète les réponses du serveur.  
  - Objectifs : survie (nourriture), collecte, reproduction (`Fork`) et incantations.

---

## Prérequis & dépendances
- **Système** : Linux recommandé, support de POSIX sockets.  
- **Compilateur C/C++** : GCC ≥ 9 ou Clang ≥ 11.  
- **GUI** : SFML 2.5, OpenGL, libX11, libglew (ou équivalent), CMake ≥ 3.16 si vous utilisez CMake côté GUI.  
- **Outils** : make, pkg-config, valgrind (tests mémoire).

---

## Compilation
Un *Makefile* racine fournit trois cibles :

make zappy_server # compile le serveur
make zappy_gui # compile la GUI
make zappy_ai # compile l’IA de référence (optionnelle)
make # compile serveur + GUI
make clean / fclean / re


> Les règles doivent fonctionner sans connexion Internet (aucun fetch externe).

---

## Lancement rapide

1. **Démarrer un serveur**  
   Exemple de carte 20×20, deux équipes de 5 slots, fréquence 100 :

./zappy_server -p 4242 -x 20 -y 20 -n Red Blue -c 5 -f 100


2. **Ouvrir la GUI**  

./zappy_gui -h localhost -p 4242

3. **Connecter un client IA**  

./zappy_ai -n Red -h localhost -p 4242


---

## Paramètres détaillés (serveur)

| Option | Description | Valeur minimale |
|--------|-------------|-----------------|
| `-p`   | Port TCP d’écoute | > 0 |
| `-x`   | Largeur de la carte | 10 |
| `-y`   | Hauteur de la carte | 10 |
| `-n`   | Liste des noms d’équipes | ≥ 1 équipe |
| `-c`   | Slots initiaux par équipe | 1 |
| `-f`   | Fréquence (unités de temps par seconde) | 2 – 10000 |
| `-d`   | Active le mode debug (logs `debug.log`) | — |

La GUI (`GRAPHIC`) et les IA partagent le même protocole texte ; chaque ligne envoyée/recue est terminée par `\n`.

---

## Règles du gameplay (rappel)

- **Ressources** : food, linemate, deraumere, sibur, mendiane, phiras, thystame.  
Densité de génération = surface × coefficient (voir PDF).
- **Vision** : cône qui s’élargit avec le niveau.  
- **Incantation** : requiert un nombre précis de joueurs et de pierres sur la même tuile (cf. tableau).
- **Temps** : chaque commande est divisée par `f` (ex. `Forward` = 7 / f s).  
Un drone possède 10 unités de nourriture lors du spawn (1260 / f s de vie).
- **Victoire** : 6 drones de la même équipe atteignent le niveau 8.  
Le serveur diffuse alors `seg TEAMNAME`.

---

## Arborescence conseillée

/include # headers partagés (protocol, structures)
/src/server # logique serveur
/src/gui # GUI C++
/src/ai # IA de référence
/assets # sprites, sons
/tests # unit / integration
/docs # pdf protocol + ce README
Makefile # cibles : zappy_server, zappy_gui, zappy_ai


---

## Contribuer
1. Forkez le dépôt.  
2. Créez une branche descriptive (`feature/minimap`, `fix/memory-leak`).  
3. Respectez les lignes directrices du *coding style* EPITECH.  
4. Rédigez des commits clairs (impératif, anglais).  
5. Ouvrez une *merge request* ; la CI (tests + valgrind) doit passer.

---

## Auteurs & licence

Projet développé en juin 2025 par l’équipe suivante :

- 🥇 **CorpsB** — 92 commits (5493++ / 2226--)  
- 🥈 **OkotEgarim** — 47 commits (5393++ / 2342--)  
- 🥉 **brice9478** — 46 commits (4914++ / 2783--)  
- **Turtelthib** — 39 commits (4959++ / 1336--)  
- **Tomaraptor67** — 38 commits (4658++ / 4625--)  
- **PCyrian** — 1 commit (981++ / 0--)

> Code sous licence MIT, ressources graphiques sous CC-BY-SA 4.0 (sauf mention contraire).

---

Bon jeu.
