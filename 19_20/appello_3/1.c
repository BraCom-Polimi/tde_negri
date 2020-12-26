#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define dim 70

struct tF{
	int id;
	char name[70];
	char street[70];
};

struct tR{
	int id;
	int pos;
};

int main(int argc, char *argv[]){
	int i = 0, max, min, FF_counter = 0, NOT_SAVED = 0;
	FILE *f1, *f2;
	struct tR R;
	struct tF FF[50];
	char file_name[dim];

	if (argc < 4)
		return -1;

	strcpy(file_name, argv[1]);
	//first file
	f1 = fopen(file_name, "r");
	
	if (f == NULL){
		printf ("file err\n");
		return -1;
	}

	//second file
	file_name[strlen(argv[1]] = 'R';
	file_name[strlen(argv[1])+1] = 'I';
	file_name[strlen(argv[1])+2] = 'C';
	file_name[strlen(argv[1])+3] = '\0';

	f2 = fopen(file_name, "r");
	
	if (f2 == NULL){
		printf ("file err\n");
		return -1;
	}
	
	min = atoi(argv[2]);
	max = atoi(arhv[3]); 
	
	while (feof(f2) != 1){
		fread(&R, struct tR, 1, f2);
		if (R->id >= min && R->id <= max){
				fseek(f1, R->pos, SEEK_SET);
				if (FF_counter < 50){
					fread(FF[FF_counter], struct tF, 1, f1);
					FF_counter++;
				}
				else
					NOT_SAVED++;
		}
	}
	fclose(f1);
	fclose(f2);

	if (FF_counter == 0)
		printf ("no insert\n");
	else if (FF_counter == 49)
		printf ("array full\n");

	return 0;

}
