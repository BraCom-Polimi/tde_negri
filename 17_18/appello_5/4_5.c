#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define row 10
#define col 10

int M[row][col] = {0};

struct node{
	int v;
	struct node *n;
};

void cL(struct node **h);
void pL(struct node *);
void fL(struct node **);
int count(struct node *h, struct node **rp, int test);
void move(struct node **h, struct node *rp);

int main(int argc, char *argv[]){
	srand(time(NULL));
	int res = 0, r, c, p1, p2;
	struct node *head = NULL, *rp = NULL;

	for (r=0; r<row; r++)
		for (c=0; c<col; c++)
			M[r][c] = rand()%10;

	if (argc < 3)
		return -1;
	p1 = atoi(argv[1]);
	p2 = atoi(argv[2]);	
	printf ("extraction pos: %d\n", M[p1][p2]);

	cL(&head);
	pL(head);

	printf ("total occurences: %d\n", res = count(head, &rp, M[p1][p2]));
	if (res > 0)
		printf ("pointer points to: %d\n", rp->v);


	if (res >= 1)
		move(&head, rp);
	pL(head);

	fL(&head);
	return 0;
}

void move(struct node **h, struct node *rp){
	struct node *c = (*h)->n;
	struct node *before_rp = NULL;

	while (c != *h){
		if (c->n == rp)
			before_rp = c;
		c = c->n;
	}

	c = *h;

	while (c->n != *h)
		c = c->n;
	c->n = rp;
	before_rp->n = rp->n;
	rp->n = *h;
	*h = rp;
}

int count(struct node *h, struct node **rp, int test){
	struct node *c = h;
	int k = 0;

	if (h->n != NULL)
		c = h->n;
	else
		return 0;
	while (c != h){
		if (k == 0 && c->v == test){
			*rp = c;
			k++;
		}
		else if (c->v == test && k != 0)
			k++;
		c = c->n;
	}
	return k;
}

void fL(struct node **h){
	struct node *c = (*h)->n, *p = *h;
	
	while (c != *h){
		if (p != *h)
			free(p);
		p = c;
		c = c->n;
	}
	free(p->n);
	free(p);	
}

void cL(struct node **h){
	int i = 0;
	struct node *n, *c = *h;

	for (; i<20; i++){
		c = *h;
		n = (struct node *)malloc(sizeof(struct node));
		if (n == NULL)
			return;
		n->v = rand()%10;
		n->n = NULL;

		if (*h == NULL)
			*h = n;
		else{
			while (c->n != NULL)
				c = c->n;
			c->n = n;
		}
	}
	n->n = *h;
}

void pL(struct node *h){
	struct node *c = h;
	
	printf ("%d ", c->v);
	c = c->n;
	while (c != h){
		printf ("%d ", c->v);
		c = c->n;
	}
}
		
