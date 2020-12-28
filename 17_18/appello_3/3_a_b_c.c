#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define col 5
#define row 4

struct COORDINATES{
	int x;
	int y;
};

struct node{
	int x;
	int y;
	struct node *next;
};

int MATRIX[row][col] = {0};

void fill_matrix();
int max_ring(struct COORDINATES *, struct node **h);
int check(struct node **, int, int);
void insert_list(struct node **, int, int);
void fL(struct node **);

int main(){
	srand(time(NULL));
	struct node *head = NULL;
	struct COORDINATES NEW_C;
	NEW_C.x = 1;
	NEW_C.y = 2;
	fill_matrix();
	printf ("max_ring error code: %d\nx: %d\ny: %d\n", max_ring(&NEW_C, &head), NEW_C.x, NEW_C.y);
	fL(&head);

	return 0;
}

void fill_matrix(){
	int r = 0, c = 0;

	for (; r<row; r++){
		for (c=0; c<col; c++){
			MATRIX[r][c] = rand()%10+1;
			printf ("%2d ", MATRIX[r][c]);
		}
		printf ("\n");
	}

}

void fL(struct node **h){
	struct node *c = *h;
	struct node *p = NULL;

	if (c == NULL)
		return;
	while (c != NULL){
		if (p != NULL)
			free(p);
		p = c;
		c = c->next;
	}
	free(p);
}

int max_ring(struct COORDINATES *NEW_C, struct node **h){
	int max = MATRIX[NEW_C->x][NEW_C->y], r, c, max_r, max_c, copy_c;
	int error = 0, recursion;

	printf ("START\n");
		
	if (NEW_C->x-1 >= 0)
		r = NEW_C->x-1;
	else
		r = NEW_C->x;
	if (NEW_C->y-1 >= 0)
		c = NEW_C->y-1;
	else
		c = NEW_C->y;
	if (NEW_C->x+1 < row)
		max_r = NEW_C->x+1;
	else
		max_r = NEW_C->x;
	if (NEW_C->y+1 < col)
		max_c = NEW_C->y+1;
	else
		max_c = NEW_C->y;

	copy_c = c;
	for (; r<=max_r; r++){
		c = copy_c;
		for (c=copy_c; c<=max_c; c++){
			if (r == NEW_C->x && c == NEW_C->y)
				continue;
			if (MATRIX[r][c] > max){
				max = MATRIX[r][c];
				NEW_C->x = r;
				NEW_C->y = c;
				//printf ("%d, %d\n", r, c);
				error = 1;
			}
		}
	}
	if (check(h, NEW_C->x, NEW_C->y) == 1)
		return 0;
	printf ("%d - %d\n", NEW_C->x, NEW_C->y);
	if (error == 1){
		insert_list(h, NEW_C->x, NEW_C->y);
		recursion = max_ring(NEW_C, h);
	}
	return error;
}

int check(struct node **h, int x, int y){
	struct node *c = *h;

	if (c == NULL)
		return 0;

	while (c != NULL){
		if (c->x == x && c->y == y)
			return 1;
		c = c->next;
	}
	return 0;
}

void insert_list(struct node **h, int x, int y){
	struct node *n = (struct node *)malloc(sizeof(struct node));
	struct node *c = *h;

	if (n != NULL){
		n->x = x;
		n->y = y;
		n->next = NULL;

		if (*h == NULL)
			*h = n;
		else{
			while (c->next != NULL)
				c = c->next;
			c->next = n;
		}
	}
	else
		printf ("all err\n");
}


