#include <iostream>
#include <fstream>
using namespace std;

#define CAPACITY 50000 // Size of the Hash Table


unsigned long hash_function(char* str) {
    unsigned long i = 0;
    for (int j=0; str[j]; j++)
        i += str[j];
    return i % CAPACITY;
}

bool strcmp(const char *X, const char *Y, int maxLength)
{
    bool isEqual = true;
    for(int i = 0; i < maxLength; i++) {
        if(X[i]!=Y[i]) {
            isEqual = false;
            break;
        }
        else if(X[i]==0 && Y[i]==0) {
            break;
        }
        else if(X[i]==0 || Y[i] ==0) {
            isEqual = false;
            break;
        }
    }
    return isEqual;
}

struct nodelist { /* table entry: */
    struct nodelist *next; /* next entry in chain */
    char *name; /* defined name */
    char *defn; /* replacement text */
};

int main() {
    ifstream in("tulks.i1");
    int maxLength = 21;
    char word[maxLength];
    char translation[maxLength];

    while(in) {
        in >> word;
        if( strcmp(word, "-->", maxLength)== 1) {
            cout << "----------->" << endl;
            break;
        }
        if( strcmp(word, "<--", maxLength)== 1) {
            cout << "<----------" << endl;
        }
        in >> translation;
        cout << word <<" " << translation << endl;
    }
}












struct nlist { /* table entry: */
    struct nlist *next; /* next entry in chain */
    char *name; /* defined name */
    char *defn; /* replacement text */
};

#define HASHSIZE 101
static struct nlist *hashtab[HASHSIZE]; /* pointer table */

/* hash: form hash value for string s */
unsigned hash(char *s)
{
    unsigned hashval;
    for (hashval = 0; *s != '\0'; s++)
      hashval = *s + 31 * hashval;
    return hashval % HASHSIZE;
}

/* lookup: look for s in hashtab */
struct nlist *lookup(char *s)
{
    struct nlist *np;
    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
        if (strcmp(s, np->name) == 0)
          return np; /* found */
    return NULL; /* not found */
}

char *strdup(char *);
/* install: put (name, defn) in hashtab */
struct nlist *install(char *name, char *defn)
{
    struct nlist *np;
    unsigned hashval;
    if ((np = lookup(name)) == NULL) { /* not found */
        np = (struct nlist *) malloc(sizeof(*np));
        if (np == NULL || (np->name = strdup(name)) == NULL)
          return NULL;
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } else /* already there */
        free((void *) np->defn); /*free previous defn */
    if ((np->defn = strdup(defn)) == NULL)
       return NULL;
    return np;
}

char *strdup(char *s) /* make a duplicate of s */
{
    char *p;
    p = (char *) malloc(strlen(s)+1); /* +1 for ’\0’ */
    if (p != NULL)
       strcpy(p, s);
    return p;
}