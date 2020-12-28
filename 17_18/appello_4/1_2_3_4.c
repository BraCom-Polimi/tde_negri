#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct node{
	char d;
	struct node *n;
};

struct vet{
	char *v;
	int size;
};

//creaVet is inside sub
int load(char file_name[], struct node **h);
void fL(struct node **h);
void pL(struct node *h);
int sub(struct node **h, char replace[], char dest, struct vet *VET);

int main(){
	struct vet NEW_VET;
	struct node *head = NULL;
	char file_name[100] = "input.txt", CHG[6] = "BBB";
	char CH = 'G';
	int load_error = load(file_name, &head), se;
	pL(head);
	se = sub(&head, CHG, CH, &NEW_VET);
	if (se == 1)
		printf ("%s\n", NEW_VET.v);

	fL(&head);
	free(NEW_VET.v);
	return 0;
}

int sub(struct node **h, char replace[], char dest, struct vet *VET){
	int dest_counter = 0, string_counter = 0;
	struct node *c = *h;

	if (c == NULL)
		return 0;

	while (c != NULL){
		if (c->d == dest)
			dest_counter++;
		else
			string_counter++;
		c = c->n;
	}

	VET->v = (char *)malloc(sizeof(char)*(string_counter+(dest_counter*strlen(replace))+1));
	VET->size = string_counter+(dest_counter*strlen(replace))+1;
	if (VET->v == NULL)
		return 0;

	VET->v[VET->size-1] = '\0';

	c = *h;
	string_counter = 0;
	while (c != NULL){
		if (c->d != dest){
			VET->v[string_counter] = c->d;
			string_counter++;
		}\
		else{
			for (int i=0; i<strlen(replace); i++){
				VET->v[string_counter] = replace[i];
				string_counter++;
			}
		}
		c = c->n;
	}
	return 1;
}


int load(char file_name[], struct node **h){
	struct node *c = *h;
	FILE *f = fopen(file_name, "r");
	char letter;

	if (f == NULL || *h != NULL)
		return 0;
	
	letter = fgetc(f);
	if (letter == EOF)
		return 0;
	while (feof(f) != 1){
		c = *h;
		struct node *n = (struct node *)malloc(sizeof(struct node));
		if (n == NULL)
			return 0;
		n->d = letter;
		n->n = NULL;

		if (*h == NULL)
			*h = n;
		else{
			while (c->n != NULL)
				c = c->n;
			c->n = n;
		}
		letter = fgetc(f);
		if (letter == EOF)
			break;
	}

	fclose(f);

	return 1;
}

void fL(struct node **h){
	struct node *c = *h, *p = NULL;
	if (c == NULL)
		return;
	while (c != NULL){
		if (p != NULL)
			free(p);
		p = c;
		c = c->n;
	}
	free(p);
}

void pL(struct node *h){
	struct node *c = h;
	if (c == NULL)
		printf ("empty\n");
	while (c != NULL){
		printf ("%c", c->d);
		c = c->n;
	}
	printf ("\n");
}


