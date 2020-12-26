#include <stdio.h>
#include <stdlib.h>

struct node{
	int v;
	struct node *n;
};

void create_list(struct node **H);
void fL(struct node **H);
void pL(struct node *H);
int triple(struct node *H, struct node **pos1, struct node **pos2);
int replace(struct node **H, struct node *p1, struct node *p2);

int main(){
	struct node *H = NULL, *p1 = NULL, *p2 = NULL;
	int triple_return = 0, replace_return = 0;
	
	create_list(&H);

	printf ("triple error: %d\n", triple_return = triple(H, &p1, &p2));
	pL(H);
	
	printf ("pos1: %d\npos2: %d\n", p1->v, p2->v);

	replace_return = replace(&H, p1, p2);
	printf ("replace error: %d\n", replace_return);
	pL(H);

	fL(&H);
	
	return 0;
}

int replace(struct node **H, struct node *p1, struct node *p2){
	struct node *c = *H;
	struct node *p1c = p1;
	int i = 1, sum = 0;

	while (i <= 3){
		sum += p1c->v;
		p1c = p1c->n;
		i++;
	}

	while (c != p1){
		c = c->n;
	}
	p1 = p1->n;
	c->n = p2->n;
	free(p1);
	free(p2);

	c->v = sum;
	pL(*H);

	return 1;
}

int triple(struct node *H, struct node **p1, struct node **p2){
	struct node *c = H;
	struct node *p = NULL;

	if (c == NULL)
		return 0;

	while (c->n->n != NULL){
		if (c->v == c->n->v && c->v == c->n->n->v){
			if (p != NULL && p->v != c->v && c->n->n->n != NULL && c->n->n->n->v != c->v){
				*p1 = c;
				*p2 = c->n->n;
				return 1;
			}
		}
		p = c;
		c = c->n;
	}
	return 0;
}

void create_list(struct node **H){
	struct node *c = *H;
	int i = 0;

	for (; i<10; i++){
		c = *H;
		struct node *n = (struct node *)malloc(sizeof(struct node));
		if (i < 5)
			n->v = i;
		else if (i > 7)
			n->v = i;
		else
			n->v = 2;
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
