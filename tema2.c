// ALEXE Adelina Maria - 312CC

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// definirea structurii pentru arbore
typedef struct Tree {
  char *value;
  int end;
  int level;
  struct Tree **children;
} Tree;

// functie pentru initializarea structurii si alocarea memoriei corespunzatoare
void initT(struct Tree **tree, char value, int end, int level) {
  *tree = malloc(sizeof(struct Tree));
  if (*tree == NULL) {
    printf("Error in memory allocation\n");
    exit(1);
  }

  (*tree)->children = malloc(27 * sizeof(struct Tree *));
  if ((*tree)->children == NULL) {
    printf("Error in memory allocation\n");
    exit(1);
  }

  int i;
  for (i = 0; i < 27; i++) (*tree)->children[i] = NULL;

  (*tree)->value = malloc(100 * sizeof(char));
  if ((*tree)->value == NULL) {
    printf("Error in memory allocation\n");
    exit(1);
  }

  (*tree)->end = end;
  (*tree)->value[0] = value;
  (*tree)->value[1] = '\0';
  (*tree)->level = level;
}

// functie care calculeaza pozitia din vector corespunzatoare fiecarui caracter
int charToIndex(char ch) {
  if (ch == '$') return 0;

  return ch - 'a' + 1;
}

// functie care adauga un nou caracter in arbore, impreuna cu celelalte campuri
// aferente
void insertChild(struct Tree **tree, char value, int end) {
  if (*tree != NULL) {
    int idx = charToIndex(value);
    if ((*tree)->children[idx] == NULL) {
      initT(&((*tree)->children[idx]), value, end, (*tree)->level + 1);
    }
  }
}

// functie recursiva pentru adaugarea unui intreg cuvant in arbore, caracter cu
// caracter
void insertWord(struct Tree **tree, char *word, int index) {
  if (word[index] == '\0')
    (*tree)->end = 1;

  else if (*tree != NULL) {
    int idx = charToIndex(word[index]);
    if ((*tree)->children[idx] == NULL)
      initT(&((*tree)->children[idx]), word[index], 0, (*tree)->level + 1);
    insertWord(&((*tree)->children[idx]), word, index + 1);
  }
}

// functie care calculeaza inaltimea maxima a arborelui
void heightT(struct Tree *tree, int *max_height) {
  if (tree != NULL) {
    if (tree->level > *max_height) *max_height = tree->level;

    int i;
    for (i = 0; i < 27; i++)
      if (tree->children[i] != NULL) heightT(tree->children[i], max_height);
  }
}

// functie care afiseaza caracterele pe nivel
void printLevel(struct Tree *tree, int level, FILE *f) {
  if (tree != NULL) {
    if (tree->level == level) fprintf(f, "%s ", tree->value);

    int i;
    for (i = 0; i < 27; i++)
      if (tree->children[i] != NULL) printLevel(tree->children[i], level, f);
  }
}

// functie care afiseaza tot arborele
void printT(struct Tree *tree, int level, FILE *f) {
  if (tree != NULL) {
    int i;
    for (i = 1; i <= level; i++) {
      printLevel(tree, i, f);
      fprintf(f, "\n");
    }
  }
}

// functie care numara cate frunze are arborele
void leavesT(struct Tree *tree, int *count) {
  if (tree != NULL) {
    if (tree->value[0] == '$') *count = *count + 1;

    int i;
    for (i = 0; i < 27; i++)
      if (tree->children[i] != NULL) leavesT(tree->children[i], count);
  }
}

// functie care numara cate sufixe de lungime k exista in arbore
void kSufix(struct Tree *tree, int *nrSufix, int k) {
  if (tree != NULL) {
    if (tree->value[0] == '$' && tree->level == k + 1) *nrSufix = *nrSufix + 1;

    int i;
    for (i = 0; i < 27; i++)
      if (tree->children[i] != NULL) kSufix(tree->children[i], nrSufix, k);
  }
}

// functie care numara cati descendenti directi are un nod
int nrDesc(struct Tree *tree) {
  int nr = 0, i;
  if (tree != NULL) {
    for (i = 0; i < 27; i++)
      if (tree->children[i] != NULL) nr++;
  }
  return nr;
}

// functie care calculeaza nunarul maxim de descendenti ale unui nod
void maxDesc(struct Tree *tree, int *maxD) {
  if (tree != NULL) {
    int nrD = nrDesc(tree);
    if (nrD > *maxD) *maxD = nrD;

    int i;
    for (i = 0; i < 27; i++)
      if (tree->children[i] != NULL) maxDesc(tree->children[i], maxD);
  }
}

// functie care verifica daca un anumit cuvant exista sau nu in arbore
int findWord(struct Tree *tree, char *word, int index) {
  if (tree == NULL) return 0;

  if (word[index] == '\0') {
    if (tree->end == 1) return 1;
    return 0;
  }

  int idx = charToIndex(word[index]);
  return findWord(tree->children[idx], word, index + 1);
}

// functie care verifica daca un nod are un singur descendent
// si daca da, il returneaza
Tree *uniqChild(struct Tree *tree) {
  if (tree != NULL) {
    int count = 0;
    struct Tree *child = NULL;
    int i;
    for (i = 0; i < 27; i++)
      if (tree->children[i] != NULL) {
        count++;
        child = tree->children[i];
      }

    if (count == 1) return child;
  }

  return NULL;
}

// functie care scade recursiv cu 1 nivelele descendentilor
void decreaseLevel(struct Tree **tree) {
  if (*tree != NULL) {
    int i;
    for (i = 0; i < 27; i++) decreaseLevel(&((*tree)->children[i]));
    (*tree)->level--;
  }
}

// functie care concateaza caracterele din sufixe
void concatT(struct Tree **tree) {
  if (*tree != NULL) {
    int i;
    for (i = 0; i < 27; i++) {
      concatT(&((*tree)->children[i]));
      struct Tree *child = uniqChild((*tree)->children[i]);
      if (child != NULL && child->value[0] != '$') {
        // concateneaza valorii curente, valorea retinuta de copilul nodului
        char *value = malloc(200 * sizeof(char));
        strcpy(value, (*tree)->children[i]->value);
        strcat(value, child->value);
        strcpy(child->value, value);

        int j;
        for (j = 0; j < 27; j++)
          if ((*tree)->children[i]->children[j] != NULL &&
              (*tree)->children[i]->children[j] != child) {
            free((*tree)->children[i]->children[j]);
            (*tree)->children[i]->children[j] = NULL;
          }

        // elibereaza memoria pentru nodul curent si creeaza o noua legatura cu
        // nodului copilului
        free((*tree)->children[i]->children);
        (*tree)->children[i]->children = NULL;
        free((*tree)->children[i]->value);
        free((*tree)->children[i]);
        (*tree)->children[i] = child;

        // decrementeaza nivelele descendentilor
        decreaseLevel(&((*tree)->children[i]));

        free(value);
      }
    }
  }
}

// functie pentru eliberarea memoriei pentru intreg arborele
void freeT(struct Tree **tree) {
  if (*tree != NULL) {
    int i;
    for (i = 0; i < 27; i++) freeT(&((*tree)->children[i]));

    free((*tree)->value);
    free((*tree)->children);
    free(*tree);
  }
}

int main(int argc, char *argv[]) {
  // deschide fisierele in functie de pozitia din vectorul
  // de argumente la care se afla numele acestuia
  FILE *f = fopen(argv[argc - 2], "r");
  FILE *g = fopen(argv[argc - 1], "w");
  int n, i;

  // aloca memorie pentru sirurile de caractere in care se citesc cuvintele
  char *string = malloc(100 * sizeof(char));
  if (string == NULL) {
    printf("Error in memory allocation\n");
    exit(1);
  }
  char *extension = malloc(100 * sizeof(char));
  if (extension == NULL) {
    printf("Error in memory allocation\n");
    exit(1);
  }
  char *sufix = malloc(100 * sizeof(char));
  if (sufix == NULL) {
    printf("Error in memory allocation\n");
    exit(1);
  }

  // initileaza arborele
  struct Tree *tree;
  initT(&tree, '#', 0, 0);

  // in functie de cerinta, citeste din fisier
  if (argc == 4) {
    if (strcmp(argv[1], "-c1") == 0) {
      fscanf(f, "%d", &n);
      fgetc(f);

      for (i = 0; i < n; i++) {
        fgets(string, 100, f);
        string[strlen(string) - 1] = '\0';

        // concateaza fiecarui cuvant citit caracterul '$'
        extension[0] = '$';
        extension[1] = '\0';
        insertWord(&tree, extension, 0);

        int j;
        for (j = strlen(string) - 1; j >= 0; j--) {
          // insereaza in arbore sufix cu sufix
          sufix[0] = string[j];
          sufix[1] = '\0';
          strcat(sufix, extension);
          strcpy(extension, sufix);
          insertWord(&tree, extension, 0);
          sufix[1] = '\0';
        }

        extension[1] = '\0';
      }

      // in functie de cerinta, apeleaza functiile corespunzatoare
      int max_height = -1;
      heightT(tree, &max_height);
      printT(tree, max_height, g);
    }

    else if (strcmp(argv[1], "-c3") == 0) {
      int m;
      char *compare = malloc(100 * sizeof(char));
      if (compare == NULL) {
        printf("Error in memory allocation\n");
        exit(1);
      }

      fscanf(f, "%d%d", &n, &m);
      fgetc(f);

      for (i = 0; i < n; i++) {
        fgets(string, 100, f);
        string[strlen(string) - 1] = '\0';

        extension[0] = '$';
        extension[1] = '\0';
        insertWord(&tree, extension, 0);

        int j;
        for (j = strlen(string) - 1; j >= 0; j--) {
          sufix[0] = string[j];
          sufix[1] = '\0';
          strcat(sufix, extension);
          strcpy(extension, sufix);
          insertWord(&tree, extension, 0);
          sufix[1] = '\0';
        }

        extension[1] = '\0';
      }

      for (i = 0; i < m; i++) {
        fgets(compare, 100, f);
        compare[strlen(compare) - 1] = '\0';
        int len = strlen(compare);
        compare[len] = '$';
        compare[len + 1] = '\0';
        fprintf(g, "%d\n", findWord(tree, compare, 0));
      }

      free(compare);
    }

    else if (strcmp(argv[1], "-c4") == 0) {
      fscanf(f, "%d", &n);
      fgetc(f);

      for (i = 0; i < n; i++) {
        fgets(string, 100, f);
        string[strlen(string) - 1] = '\0';

        extension[0] = '$';
        extension[1] = '\0';
        insertWord(&tree, extension, 0);

        int j;
        for (j = strlen(string) - 1; j >= 0; j--) {
          sufix[0] = string[j];
          sufix[1] = '\0';
          strcat(sufix, extension);
          strcpy(extension, sufix);
          insertWord(&tree, extension, 0);
          sufix[1] = '\0';
        }

        extension[1] = '\0';
      }

      concatT(&tree);

      int max_height = -1;
      heightT(tree, &max_height);
      printT(tree, max_height, g);
    }

  }

  else {
    fscanf(f, "%d", &n);
    fgetc(f);

    for (i = 0; i < n; i++) {
      fgets(string, 100, f);
      string[strlen(string) - 1] = '\0';

      extension[0] = '$';
      extension[1] = '\0';
      insertWord(&tree, extension, 0);
      
      int j;
      for (j = strlen(string) - 1; j >= 0; j--) {
        sufix[0] = string[j];
        sufix[1] = '\0';
        strcat(sufix, extension);
        strcpy(extension, sufix);
        insertWord(&tree, extension, 0);
        sufix[1] = '\0';
      }

      extension[1] = '\0';
    }

    int count = 0;
    leavesT(tree, &count);
    fprintf(g, "%d\n", count);

    int k = atoi(argv[2]);
    int nrSufix = 0;
    kSufix(tree, &nrSufix, k);
    fprintf(g, "%d\n", nrSufix);

    int maxD = -1;
    maxDesc(tree, &maxD);
    fprintf(g, "%d\n", maxD);
  }

  // elibereaza memoria pentru arbore si pentru celelalte variabile folosite
  free(string);
  free(extension);
  free(sufix);
  freeT(&tree);
  fclose(f);
  fclose(g);

  return 0;
}
