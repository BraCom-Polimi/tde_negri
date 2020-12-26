#include <stdio.h>
#include <stdlib.h>

struct node{
	int v;
	struct node *n;
};

int count(struct node *H, int control);
void create_list(struct node **H);
void fL(struct node **H);
int delete(struct node **H, int value, int limit);
void pL(struct node *H);
void delel(struct node **H, struct node *C, struct node *P);
struct node *rP(struct node *H, int);

int main(){
	struct node *H = NULL;
	struct node *C = NULL;
	struct node *P = NULL;
	int count_return = 0, delete_return = 0;

	create_list(&H);
	pL(H);
	printf ("count result: %d\ndelete result: %d\n", count_return = count(H, 4), delete_return = delete(&H, 88, 2));
	pL(H);

	C = rP(H, 9);
	P = rP(H, 8);

	delel(&H, C, P);
	printf ("\n");
	pL(H);
	
	fL(&H);
	return 0;
}

void delel(struct node **H, struct node *C, struct node *P){
	struct node *c = *H;

	if (c == NULL)
		return;
	
	while (c != NULL){
		if (C == c){
			if (c == *H)
				*H = c->n;
			else{
				P->n = c->n;
			}
			free(C);
			return;
		}
		c = c->n;
	}
}

struct node *rP(struct node *H, int p){
	struct node *c = H;
	int counter = 1;

	if (c == NULL)
		return NULL;
	
	while (c != NULL){
		if (p == counter)
			return c;
		c = c->n;
		counter++;
	}
	return NULL;
}

int delete(struct node **H, int value, int limit){
	struct node *c = *H;
	struct node *p = NULL;
	struct node *element = NULL;
	struct node *prev_element = NULL;
	struct node *post_element = NULL;
	int counter = 0, change = 0;

	if (c == NULL)
		return -1;
	
	while (c != NULL){
		if (c->v == value){
			change = 1;
			element = c;
			if (p != NULL)
				prev_element = p;
			post_element = c->n;
			counter++;
		}
		p = c;
		c = c->n;
	}

	if (counter < limit && change == 1){
		if (prev_element != NULL)
			prev_element->n = post_element;
		else
			*H = post_element;
		free(element);
		return 1;
	}
	
	return 0;
}	

void fL(struct node **H){
	struct node *c = *H;
	struct node *p = NULL;

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

int count(struct node *H, int control){
	struct node *c = H;
	int count = 1, res = 0;

	if (c == NULL)
		return 0;

	while (c != NULL){
		if (c->v == control && count != 3 && c->n != NULL)
			res++;
		count++;
		c = c->n;
	}
	return res;
}
	

void create_list(struct node **H){
	struct node *c = *H;
	int i = 0;

	for (; i<10; i++){
		c = *H;
		struct node *n = (struct node *)malloc(sizeof(struct node));
		n->v = i;
		n->n = NULL;
		
		if (c == NULL)
			*H = n;
		else{
			while (c->n != NULL)
				c = c->n;
			c->n = n;
		}
	}
}

void pL(struct node *H){
	struct node *c = H;

	if (c == NULL)
		return;
	
	while (c != NULL){
		printf ("%d ", c->v);
		c = c->n;
	}
}
