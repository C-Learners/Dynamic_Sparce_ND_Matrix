#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLINE 256

typedef struct node{
	void* v;					//the element of this index for this level
	int i;						//index
	int level;					//Level, if 0, v is an element
	struct node *left, *right;	//subtrees
} Node;

Node* push(Node* m, char* string, int* index, int level){
	if (!m) {
		m = malloc(sizeof *m);
		m->left = m->right = NULL;
		m->i = index[level];
		m->level = level;
		if (level)
			m->v = push(NULL, string, index, level-1);
		else
			m->v = string;
	} else {
		if (index[level-1] > m->i)
			m->right = push(m->right, string, index, level);
		else if (index[level-1] < m->i)
			m->left = push(m->left, string, index, level);
		else {
			if (level)
				m->v = push(m->v, string, index, level-1);
			else
				m->v = string;
		}
	}
	return m;
}

void* peek(Node* m, int* index){
	if (!m)
		return NULL;

	if (*index > m->i)
		return peek(m->right, index);
	if (*index < m->i)
		return peek(m->left, index);

	if (m->level)
		return peek(m->v, --index);
	return m->v;
}


void menuInsert(Node** m, int n){
	printf("\nInsert position: ");
    int i;
    int* index = calloc(n, sizeof *index);
    for (i=n-1; i>=0; --i) scanf("%d", index+i);

    printf("\nInsert element (string): ");
    char* string = calloc(MAXLINE, sizeof *string);
    fflush(stdin);
    fgets(string, MAXLINE-1, stdin);
    string[strlen(string)] = 0; //set null character

    *m = push(*m, string, index, n-1);
}

void menuGet(Node** m, int n){
	printf("\nInsert position: ");
    int i;
    int* index = calloc(n, sizeof *index);
    for (i=n-1; i>=0; --i) scanf("%d", index+i);

	char* string = calloc(MAXLINE, sizeof *string);
	string = peek(*m, index+n-1);
	if (string) printf("\n-- Found: %s", string);
	else printf("\n-- Not Found!\n");
}




int main()
{
	int n;
    printf("Numer of dimentions: ");
    scanf("%d", &n);

    Node* m = NULL; //matrix
    int choice = 1;
    while (choice) {
		printf("\n1 - Insert a value;");
		printf("\n2 - Get a value;");
		printf("\n0 - Exit.");
		printf("\nYour choice: ");
		scanf("%d", &choice);
		switch(choice){
		case 1:
			menuInsert(&m, n);
			break;
		case 2:
			menuGet(&m, n);
			break;
		default:
			break;
		}
    }
    return 0;
}
