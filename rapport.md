---
jupytext:
  text_representation:
    extension: .md
    format_name: myst
    format_version: 0.13
kernelspec:
  display_name: Python 3 (ipykernel)
  language: python
  name: python3
---

# Rapport de projet 2048

*Les paragraphes en italique comme celui-ci vous donnent des
indications sur le contenu attendu; ils sont à supprimer une fois
votre rapport rédigé.*

*Ce rapport pourra servir de support pour votre présentation orale.*

*Soyez objectifs et factuels! Vous ne serez pas évalué sur ce que vous
affirmez, mais sur la pertinence et la justesse de ce que vous
affirmez.*

+++

## Auteurs

- NASSAR Elie, nassarelie.contact@gmail.com, MI (LDD IM1)
- SENSAOUI Charaf, ...

+++

## Résumé du travail effectué

:::{admonition} Niveau 0

- La structure de jeu est respectée.
- Tous les fichiers compilent.
- Le jeu est fonctionnel.
- Le jeu respecte les règles (déplacement, game over, ajout des 2 et 4).
- Le score est mis à jour à chaque mouvement.
- Toutes les fonctions sont spécifiées, documentées (./header/2048.hpp) et testées (./Tests/2048_Tests.cpp).
- Lors de l'affichage, il n'y a pas de problèmes avec la taille des colonnes.

:::

:::{admonition} Niveau 1

Nous avons utilisé Ncurses afin d'avoir une console plus interactive et plus esthétique.
- Le jeu est colorié en vert.
- La fonction ``getch()`` de ncurses nous a permis d'utiliser les flèches directionnelles.
- La fonction ``clear()`` de ncurses nous a permis de rafraîchir la console avant le prochain affichage.
- Pour plus de modularité, le jeu est considéré comme une ``class`` avec un plateau et un score, munis de méthodes nous permettant d'effectuer les modifications directement sur l'instance du jeu.
Exemple :
```
Jeu jeu;
jeu.deplacement('h');
jeu.ajouterDeuxOuQuatre();

:::

:::{admonition} Niveau 2

- Pour faciliter la compilation du projet dans ses différentes versions (console,ncurses,UI), nous avons créé un makefile dont l'utilisation est expliquée plus en détail dans la partie Démonstration.
- Pour faciliter le travail collaboratif, nous avons mis en place git. Notre répertoire github est disponible via ce lien : https://github.com/CodeByElie/2048.

:::

:::{admonition} Niveau 3

- Pour avoir une interface bien plus jolie que sur une console, nous avons utilisé la bibliothèque SDL2. Nous avons redéfinie de nouvelles fonctions pour afficher le plateau, les tuiles ainsi que le score.
- Nous avons aussi tenté d'implémenter une IA jouant à 2048. Son score moyen est d'environ 55 000 et son record est de 160 000. Nous cherchons encore à l'améliorer mais nous sommes tout de même fiers du travail accompli.
:::

+++

## Démonstration

:::{consignes}

Soutenez ce que vous affirmez dans la section précédente au moyen de
quelques exemples **bien choisis**. Vous pouvez par exemple compiler
et lancer certains de vos programmes, lancer des tests, etc.

À titre d'inspiration, vous trouverez ci-dessous comment compiler un
programme du projet depuis cette feuille. 

Notez comment on lance une commande shell en la préfixant d'un point
d'exclamation (mais cela ne permet pas l'interaction avec
l'utilisateur).

Ne gardez que des exemples pertinents qui mettent en valeur votre
travail. Inutile de perdre du temps sur le premier programme si vous
avez fait les suivants plus compliqués; l'auditeur se doutera bien que
vous avez réussi à le faire.

:::

+++

Pour connaître les différentes commandes possibles au sein du projet, effectuez la commande dans le terminal :
```
make help
```
Elle affichera la liste des commandes :
```
Liste des commandes :
        make Console    - Compile 2048 en version console (./2048)
        make Ncurses    - Compile 2048 en version console colorée avec ncurses (./2048)
        make UI         - Compile 2048 avec une interface graphique avec SDL2 (./2048)
        make IA         - Compile l'IA de 2048 (./2048_IA)
        make Tests      - Compile les tests de la bibliothèque 2048 (./2048_Tests)
```
Effectuez la commande ``make [nom de la version]`` pour compiler la version que vous souhaitez.

+++

## Organisation du travail

:::{admonition} Consignes
Décrivez en quelques phrases comment vous vous êtes organisés pour
travailler sur le projet: nombre d'heures consacrées au projet,
répartition du travail dans le binôme, moyens mis en œuvre pour
collaborer, etc. Si vous avez bénéficié d'aide (en dehors de celle de
vos enseigants), précisez le.
:::

+++

## Prise de recul

:::{admonition} Consignes
Décrivez en quelques phrases les difficultés rencontrées, ce que vous
avez appris à l'occasion du projet, le cas échéant comment vous vous y
prendriez si vous aviez à le refaire.
:::
