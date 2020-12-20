#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define max_name 20
#define max_gp 10

struct GP{
    char name[max_name];
    char location[max_name];
    int length;
    int year;
    int month;
    int day;
    int ID;
    int position;
    int hours;
    int minutes;
    int seconds;
};

struct TOTAL{
    struct GP *GP_ARRAY;
    int NUM_GP;
};

void read(char filename[], struct TOTAL *TOTAl_GP);
void print_gp(struct TOTAL TOTAL_GP);
void show(struct TOTAL TOTAL_GP);
int check(char n[], char l[], int y, int m, int d, struct TOTAL TOTAL_GP);
int flag(char n[], char l[], int y, int m, int d, struct GP THIS);
void ask(char name[], char location[], int *y, int *m, int *d);
int insert(char name[], char location[], int y, int m, int d, int hou, int min, int sec, int position, int length, int ID, struct TOTAL *TOTAL_GP);
void ask2(char name[], char location[], int *y, int *m, int *d, int *hou, int *min, int *sec, int *position, int *length, int *ID);

int main(){
    char filename[max_name] = "es1.txt", name[max_name], location[max_name];
    struct TOTAL TOTAL_GP;
    int check_error, y, m, d, hou, min, sec, position, length, ID, insert_error;

    TOTAL_GP.GP_ARRAY = (struct GP *)malloc(sizeof(struct GP)*max_gp);
    if (TOTAL_GP.GP_ARRAY == NULL){
        printf ("mem err\n");
        return -1;
    }

    read(filename, &TOTAL_GP);
    show(TOTAL_GP);
    //print_gp(TOTAL_GP);
    //ask
    ask(name, location, &y, &m, &d);
    printf ("check error: %d\n", check_error = (check(name, location, y, m, d, TOTAL_GP)));
    //insert
    ask2(name, location, &y, &m, &d, &hou, &min, &sec, &position, &length, &ID);
    printf ("insert error: %d\n", insert_error = insert(name, location, y, m, d, hou, min, sec, position, length, ID, &TOTAL_GP));
    show(TOTAL_GP);

    free(TOTAL_GP.GP_ARRAY);
    return 0;
}

void ask2(char name[], char location[], int *y, int *m, int *d, int *hou, int *min, int *sec, int *position, int *length, int *ID){
    printf ("name:\n");
    scanf ("%s", name);
    printf ("location:\n");
    scanf ("%s", location);
    printf ("year:\n");
    scanf ("%d", y);
    printf ("month:\n");
    scanf ("%d", m);
    printf ("day:\n");
    scanf ("%d", d);
    printf ("hours:\n");
    scanf ("%d", hou);
    printf ("minutes:\n");
    scanf ("%d", min);
    printf ("secods:\n");
    scanf ("%d", sec);
    printf ("position:\n");
    scanf ("%d", position);
    printf ("length:\n");
    scanf ("%d", length);
    printf ("ID:\n");
    scanf ("%d", ID);
}

int insert(char name[], char location[], int y, int m, int d, int hou, int min, int sec, int position, int length, int ID, struct TOTAL *TOTAL_GP){
    int check_error = check(name, location, y, m, d, *TOTAL_GP);
    if (check_error == 1 && TOTAL_GP->NUM_GP < max_gp){
        printf ("arleady present or mem full\n");
        return 0;
    }
    strcpy(TOTAL_GP->GP_ARRAY[TOTAL_GP->NUM_GP].name, name);
    strcpy(TOTAL_GP->GP_ARRAY[TOTAL_GP->NUM_GP].location, location);
    TOTAL_GP->GP_ARRAY[TOTAL_GP->NUM_GP].year = y;
    TOTAL_GP->GP_ARRAY[TOTAL_GP->NUM_GP].day = d;
    TOTAL_GP->GP_ARRAY[TOTAL_GP->NUM_GP].month = m;
    TOTAL_GP->GP_ARRAY[TOTAL_GP->NUM_GP].hours = hou;
    TOTAL_GP->GP_ARRAY[TOTAL_GP->NUM_GP].minutes = min;
    TOTAL_GP->GP_ARRAY[TOTAL_GP->NUM_GP].seconds = sec;
    TOTAL_GP->GP_ARRAY[TOTAL_GP->NUM_GP].position = position;
    TOTAL_GP->GP_ARRAY[TOTAL_GP->NUM_GP].length = length;
    TOTAL_GP->GP_ARRAY[TOTAL_GP->NUM_GP].ID = ID;
    TOTAL_GP->NUM_GP++;
    return 1;
}

void ask(char name[], char location[], int *y, int *m, int *d){
    printf ("name:\n");
    scanf ("%s", name);
    printf ("location:\n");
    scanf ("%s", location);
    printf ("year:\n");
    scanf ("%d", y);
    printf ("month:\n");
    scanf ("%d", m);
    printf ("day:\n");
    scanf ("%d", d);
}

int flag(char n[], char l[], int y, int m, int d, struct GP THIS){
    if (strcmp(n, THIS.name) != 0)
        return 0;
    if (strcmp(l, THIS.location) != 0)
        return 0;
    if (THIS.year != y)
        return 0;
    if (THIS.month != m)
        return 0;
    if (THIS.day != d)
        return 0;
    return 1;
}

int check(char n[], char l[], int y, int m, int d, struct TOTAL TOTAL_GP){
    int i = 0;

    for (; i<TOTAL_GP.NUM_GP; i++){
        if (flag(n, l, y, m, d, TOTAL_GP.GP_ARRAY[i]) == 1)
            return 1;
    }
    return 0;
}
//order by year
void show(struct TOTAL TOTAL_GP){
    int i, k;
    struct GP TEMP;

    for (i=0; i<TOTAL_GP.NUM_GP-1; i++){
        for (k=0; k<TOTAL_GP.NUM_GP-1; k++){
            if (TOTAL_GP.GP_ARRAY[k].year > TOTAL_GP.GP_ARRAY[k+1].year){
                TEMP = TOTAL_GP.GP_ARRAY[k];
                TOTAL_GP.GP_ARRAY[k] = TOTAL_GP.GP_ARRAY[k+1];
                TOTAL_GP.GP_ARRAY[k+1] = TEMP;
            }
        }
    }
    print_gp(TOTAL_GP);
}

void print_gp(struct TOTAL TOTAL_GP){
    int i = 0;

    for (; i<TOTAL_GP.NUM_GP; i++){
        //these printf arent requersted, the exam requires u to print ggmmaa for the date and '*' * length
        printf ("%s\n", TOTAL_GP.GP_ARRAY[i].name);
        printf ("%s\n", TOTAL_GP.GP_ARRAY[i].location);
        printf ("%d\n", TOTAL_GP.GP_ARRAY[i].length);
        printf ("%d\n", TOTAL_GP.GP_ARRAY[i].year);
        printf ("%d\n", TOTAL_GP.GP_ARRAY[i].month);
        printf ("%d\n", TOTAL_GP.GP_ARRAY[i].day);
        printf ("%d\n", TOTAL_GP.GP_ARRAY[i].ID);
        printf ("%d\n", TOTAL_GP.GP_ARRAY[i].position);
        printf ("%d\n", TOTAL_GP.GP_ARRAY[i].hours);
        printf ("%d\n", TOTAL_GP.GP_ARRAY[i].minutes);
        printf ("%d\n", TOTAL_GP.GP_ARRAY[i].seconds);
        printf ("\n\n");
    }
}

//assume that the file is ordered
void read(char filename[], struct TOTAL *TOTAl_GP){
    int counter = 0, gp_counter = 0, value;
    char *temp;
    FILE *f = fopen(filename, "r");

    if (f == NULL){
        printf ("file err\n");
        return;
    }
    temp = (char *)malloc(sizeof(char)*max_name);
    //free the array to delete possible datas
    free((*TOTAl_GP).GP_ARRAY);
    (*TOTAl_GP).NUM_GP = 0;
    (*TOTAl_GP).GP_ARRAY = (struct GP *)malloc(sizeof(struct GP)*max_gp);
    if ((*TOTAl_GP).GP_ARRAY == NULL){
        printf ("mem err\n");
        return;
    }

    fgets(temp, max_name, f);
    counter++;
    strncpy((*TOTAl_GP).GP_ARRAY[gp_counter].name, temp, strlen(temp)-1);
    while (feof(f) != 1){
        switch (counter){

            case 0:
                fgets(temp, max_name, f);
                strncpy((*TOTAl_GP).GP_ARRAY[gp_counter].name, temp, strlen(temp)-1);
                break;
            case 1:
                fgets(temp, max_name, f);
                strncpy((*TOTAl_GP).GP_ARRAY[gp_counter].location, temp, strlen(temp)-1);
                break;
            case 2:
                fgets(temp, max_name, f);
                value = atoi(temp);
                (*TOTAl_GP).GP_ARRAY[gp_counter].length = value;
                break;
            case 3:
                fgets(temp, max_name, f);
                value = atoi(temp);
                (*TOTAl_GP).GP_ARRAY[gp_counter].year = value;
                break;
            case 4:
                fgets(temp, max_name, f);
                value = atoi(temp);
                (*TOTAl_GP).GP_ARRAY[gp_counter].month = value;
                break;
            case 5:
                fgets(temp, max_name, f);
                value = atoi(temp);
                (*TOTAl_GP).GP_ARRAY[gp_counter].day = value;
                break;
            case 6:
                fgets(temp, max_name, f);
                value = atoi(temp);
                (*TOTAl_GP).GP_ARRAY[gp_counter].ID = value;
                break;
            case 7:
                fgets(temp, max_name, f);
                value = atoi(temp);
                (*TOTAl_GP).GP_ARRAY[gp_counter].position = value;
                break;
            case 8:
                fgets(temp, max_name, f);
                value = atoi(temp);
                (*TOTAl_GP).GP_ARRAY[gp_counter].hours = value;
                break;
            case 9:
                fgets(temp, max_name, f);
                value = atoi(temp);
                (*TOTAl_GP).GP_ARRAY[gp_counter].minutes = value;
                break;
            case 10:
                fgets(temp, max_name, f);
                value = atoi(temp);
                (*TOTAl_GP).GP_ARRAY[gp_counter].seconds = value;
                break;
        }
        counter++;
        if (counter == 11){
            counter = 0;
            gp_counter++;
            (*TOTAl_GP).NUM_GP++;
        }
    }
    fclose(f);

}