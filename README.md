<p align="center">
  <img 
    src="https://github.com/JorisLne/42-project-badges/blob/main/covers/cover-get_next_line-bonus.png?raw=true" 
    alt="Bannière gnl" 
    width="80%">
</p>

<p align="center">
  <img src="https://img.shields.io/badge/Score-125%2F100-brightgreen?style=flat-square" alt="Score du projet 125/100" />
  <img src="https://img.shields.io/badge/Langage-C-blue.svg?style=flat-square&logo=c" alt="Langage C" />
</p>

<p align="center">
  <img src="https://github.com/JorisLne/42-project-badges/blob/main/badges/get_next_linem.png?raw=true" alt="Badge gnl">
</p>

</p>

## 1. `Aperçu du projet`

### Points clés

- **Objectif**: Créer une fonction `get_next_line` qui lit une ligne depuis un descripteur.
- **Prototype**:  
  ```c
  char *get_next_line(int fd);
  ```
- **Comportement**:
  - Retourne la prochaine ligne (incluant le caractère newline s’il existe).
  - Retourne `NULL` en fin de fichier ou en cas d’erreur.
  - Doit fonctionner avec tout descripteur (y compris stdin).
  - Variables globales interdites.
  - Doit gérer des tailles de tampon variables via `BUFFER_SIZE`.
- **Bonus**: Support de la lecture simultanée sur plusieurs descripteurs avec une seule variable statique.

---

## 2. `get_next_line.h`

Cet en-tête fournit les prototypes et includes pour l’implémentation standard (non-bonus).

```c

size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strchr(const char *s, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);

char	*get_next_line(int fd);
```


---

## 3. `get_next_line.c`

### Fonctions principales

#### `read_until_newline(int fd, char **buffer)`

Lit depuis un descripteur dans le tampon jusqu’à trouver un newline ou EOF.

```c
char *read_until_newline(int fd, char **buffer);
```

- Alloue un tampon temporaire.
- Lit dans `buffer` jusqu’à la présence d’un newline ou absence de lecture.
- Gère les erreurs et libère la mémoire en cas d’échec.

#### `extract_line(char **buffer)`

Extrait une ligne (jusqu’au premier newline inclus) depuis le tampon.

```c
char *extract_line(char **buffer);
```

- Retourne une nouvelle chaîne contenant une ligne.
- Met à jour le tampon en retirant la ligne retournée.

#### `get_next_line(int fd)`

La fonction principale.

```c
char *get_next_line(int fd);
```

- Utilise un tampon statique pour conserver les restes entre appels.
- Appelle `read_until_newline` puis `extract_line`.
- Libère le tampon s’il est vide.

## 4. `get_next_line_utils.c`

### Fonctionnement

- À chaque appel, lit depuis `fd` dans un tampon statique jusqu’à trouver un newline ou EOF.
- Retourne un pointeur vers une nouvelle chaîne contenant la prochaine ligne.
- Gère la mémoire avec soin pour éviter les fuites.


| Fonction      | Description                                  |
|---------------|----------------------------------------------|
| ft_strlen     | Retourne la longueur d’une chaîne            |
| ft_strdup     | Duplique une chaîne (malloc)                 |
| ft_strjoin    | Concatène deux chaînes (libère la première)  |
| ft_strchr     | Trouve un caractère dans une chaîne          |
| ft_substr     | Extrait une sous-chaîne                      |


## ```Partie bonus```

- Gère plusieurs descripteurs simultanés.
- Chaque fd conserve son propre tampon et état de lecture.
- Utilise une seule variable statique (tableau de pointeurs).

---

## ```Détails d’implémentation```

### Variables statiques

- Servent à conserver l’état du tampon entre les appels.
- Le tableau statique permet un tampon par descripteur.

### Gestion des erreurs

- Retourne `NULL` en cas d’erreur ou de fin de fichier.
- Nettoie la mémoire en cas d’erreur.
- Vérifie toutes les allocations et les appels à read.

---

## ```Tableau récapitulatif```

| Fichier                       | Rôle                                         |
|------------------------------|----------------------------------------------|
| `get_next_line.h`           | En-tête de l’implémentation principale       |
| `get_next_line.c`           | Implémentation principale (un seul fd)       |
| `get_next_line_utils.c`     | Fonctions utilitaires de chaîne              |
| `get_next_line_bonus.h`     | En-tête pour le bonus (multi-fd)             |
| `get_next_line_bonus.c`     | Implémentation bonus (multi-fd)              |
| `get_next_line_utils_bonus.c` | Fonctions utilitaires pour le bonus        |

