/*
 *	Author: Roberto Giaconia
 *	Date: March the 10th 2018
 *	This code is provided for educational purposes.
 *	Feel free to commit, edit and use this software free of charge.
 *
 */

//A dynamic sparse n-dimentional matrix.
//The number of dimentions is defined upon creation.
//To push and peek elements, the user must provide an array of indices.
//Keep in mind these indices are given in reverse order. See menu functions.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLINE 256		//maximum string lenght

typedef struct node{
	void* v;					//the element of this index for this level
	int i;						//index
	int level;					//Level, if 0, v is an element
	struct node *left, *right;	//subtrees
} Node;

//Recursive push function.
//Searches and eventually creates the right position for the given indices.
//Usage: myRoot = push(myRoot, myData, myArrayOfIndices, matrixDimentions-1);
Node* push(Node* m, void* data, int* index, int level)
{
	if (!m) {		//If this node does not exist
		m = malloc(sizeof *m);		//allocate it
		m->left = m->right = NULL;	//initialize left and right branches
		m->i = index[level];		//set the index for this node (taken from the indices array)
		m->level = level;			//set the level
		if (level)									//if we aren't at level 0
			m->v = push(NULL, data, index, level-1);	//push to the sub-matrix
		else										//if we are at level 0
			m->v = data;								//set the data
	} else {		//If this node already exists, search for the right position
		if (index[level-1] > m->i)
			m->right = push(m->right, data, index, level);
		else if (index[level-1] < m->i)
			m->left = push(m->left, data, index, level);
		else {		//If this is the right position
			if (level)								//if we aren't at level 0
				m->v = push(m->v, data, index, level-1);//push to the sub-matrix
			else									//if we are at level 0
				m->v = data;							//set the data
		}
	}
	return m;	//Needed when a new node was allocated somewhere in the matrix
}

//Recursive peek function.
//Searches for the given position (array of indices)
//Usage: &data = peek(myRoot, myArrayOfIndices);
void* peek(Node* m, int* index)
{
	if (!m)				//if we got to a non-existed position
		return NULL;	//return NULL as there is no data in the searched position
	//else, search for the right position on this dimension
	if (*index > m->i)
		return peek(m->right, index);
	if (*index < m->i)
		return peek(m->left, index);
	//if we are at the right position
	if (m->level)				//if we aren't at level 0
		return peek(m->v, --index);	//search in the sub-matrix
	return m->v;				//if we are, return the data
}

void menuInsert(Node** m, int n)
{
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

void menuGet(Node** m, int n)
{
	printf("\nInsert position: ");
	int i;
	int* index = calloc(n, sizeof *index);
	for (i=n-1; i>=0; --i) scanf("%d", index+i);

	char* string = calloc(MAXLINE, sizeof *string);
	string = peek(*m, index+n-1);
	if (string) printf("\n-- Found: %s", string);
	else printf("\n-- Not Found!\n");
}

int main()	//Usage example with strings
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
