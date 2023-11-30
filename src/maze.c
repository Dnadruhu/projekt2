#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct
{
    int rows;
    int cols;
    unsigned char *cells;
} Map;

void checkArgs(int argc, char *argv, int *r, int *c, int *leftright, char *nazovSuboru);

int mapInit(Map *mapa, char *nazovSuboru);

bool isborder(Map *mapa, int r, int c, int border);

int start_border(Map *mapa, int r, int c, int leftright);

void pathFinder(int *r, int *c, Map *mapa, int leftright, int *direction);

int main(int argc, char *argv[])
{
    printf("args count %d\n", argc);
    char nazovSuboru[100];
    int r = 0;
    int c = 0;
    int leftright = 0;
    int direction = 0;
    Map mapa;

    checkArgs(argc, *argv, &r, &c, &leftright, nazovSuboru);
    mapInit(&mapa, nazovSuboru);
    direction = start_border(&mapa, r, c, leftright);
    pathFinder(&r, &c, &mapa, leftright, &direction);
    
    free(mapa.cells);
    return 0;
}

void checkArgs(int argc, char *argv, int *r, int *c, int *leftright, char *nazovSuboru)
{
    /*r = 2;
    printf("r: %d", r);*/
    if (argc > 1)
    {
        
        int cnt = 0;
        char argument[20];
        int j = 0;

        for (int i = 1; i < 100 && cnt < argc; i++)
        {
            if (argv[i] != '\0')
            {
                argument[j] = argv[i];
                j++;
            } else {

                argument[j] = '\0';
                cnt++;
                j = 0;
                //printf("printing argument: %s\n", argument);
                if (isdigit(argument[0]))
                {
                    if (*r == 0)
                    {
                        *r = atoi(argument);
                        *r = *r - 1;
                        printf("Start row: %d\n", *r + 1);
                    }
                    else if (*c == 0)
                    {
                        *c = atoi(argument);
                        *c = *c - 1;
                        printf("Start column: %d\n", *c + 1);
                    }
                    else
                    {
                        fprintf(stderr, "Prilis vela vstupnych suradnic\n");
                        exit(1);
                    }
                }else if (!(strcmp("--help", argument)))
                {
                    printf("do this blah blah blah\n");
                    ///TO DO
                } else if (!(strcmp("--test", argument)))
                { 
                    ///TO DO  
                } else if (!(strcmp("--lpath", argument)))
                { 
                    *leftright = 0; // pravidlo lavej ruky
                } else if (!(strcmp("--rpath", argument)))
                { 
                    *leftright = 1; //pravidlo pravej ruky
                } else if (strstr(argument, ".txt") != NULL)
                {
                    strcpy(nazovSuboru, argument);
                    printf("file name valid\n");
                }
            }
        }
    } else {
        fprintf(stderr, "Neplatny vstup - malo argumentov\n");
        exit(1);
    }
}

int mapInit(Map *mapa, char *nazovSuboru)
{
    FILE *subor = fopen(nazovSuboru, "r");

    if (subor != NULL)
    {

        char buffer[sizeof(mapa->cols)*sizeof(mapa->rows)];
        
        if (fgets(buffer, sizeof(buffer), subor) != NULL)
        {
            mapa->rows = atoi(&buffer[0]);
            mapa->cols = atoi(&buffer[2]);
            //printf("Velkost pola: %s\n",buffer);

            mapa->cells = malloc(mapa->rows * mapa->cols * sizeof(unsigned char));

            for (int i = 0; i < mapa->rows; i++)
            {
                if (fgets(buffer, sizeof(buffer), subor) != NULL)
                {
                    for (int j = 0; j < mapa->cols; j++)
                    {
                        mapa->cells[i * mapa->cols + j] = atoi(&buffer[2 * j]);
                    }
                }
                else
                {
                    fprintf(stderr, "Chyba pri citani zo suboru: %s\n", nazovSuboru);
                    free(mapa->cells);
                    return 0;
                }
            }
            //return 1;
            for (int i = 0; i < mapa->rows; i++)
            {
                for (int j = 0; j < mapa->cols; j++)
                {
                    printf("%hhu ", mapa->cells[i * mapa->cols + j]);
                }
                printf("\n");
            }// NEVYPISE NIC KVOLI RETURN 1
            return 1;
            
        }
        else
        {
            fprintf(stderr, "Chyba pri citani zo suboru: %s\n", nazovSuboru);
            return 0;
        }

        fclose(subor);
    }
    else
    {
        fprintf(stderr, "Chyba pri otvarani suboru: %s\n", nazovSuboru);
        return 0;
    }
}

bool isborder(Map *mapa, int r, int c, int border) {
    /*
    //{1,3,5,7} lava hranica border == 0
    //{4,5,6,7} hornadolna hranica border == 1
    //{2,3,6,7} prava hranica border == 2
    */
    unsigned char cell = mapa->cells[r * mapa->cols + c];
    if (border == 0 && (cell == 1 || cell == 3 || cell == 5 || cell == 7)) {
        return true;
    } else if (border == 1 && (cell == 4 || cell == 5 || cell == 6 || cell == 7)) {
        return true;
    } else if (border == 2 && (cell == 2 || cell == 3 || cell == 6 || cell == 7)) {
        return true;
    } else {
        return false;
    }
    /*printf("case not found\n");
    return NULL; */
}

int start_border(Map *mapa, int r, int c, int leftright) {
    //directions -> up = 0, right = 1, left = 2, down = 3
    if ((c + 1) == 1) {//vstup z lava
        return 1; //smer do prava
    } else if ((r + 1) == 1) { //vstup z hora
        return 3; //smer dole
    } else if ((r + 1) == mapa->rows) { //vstup z dola
        return 0;
    } else if ((c + 1) == mapa->cols) {
        return 2;
    } else {
        return -1;
    }
}

void pathFinder(int *r, int *c, Map *mapa, int leftright, int *direction) {
    //directions -> up = 0, right = 1, left = 2, down = 3
    int a = 6;
    while (1)
    //while (a)
    {
        if (*r < 0 || *r >= mapa->rows || *c < 0 || *c >= mapa->cols) {
            printf("out of bounds\n");
            return;
        }
        printf("%d, %d\n", *r+1, *c+1);
        if (leftright) /*prava ruka*/ {
            //printf("v podmienke 1\n((*r + *c)2) == 0: %d\n", ((*r + *c)%2) == 0);
            if ((*r + *c)%2) /*neparny sucet suradnic - trojuholnik orientovany nahor*/ {
                if (*direction == 1) /*smer do prava*/ {
                    if (isborder(mapa, *r, *c, 1)) /*checknut dolnu hranicu */ {
                        if (isborder(mapa, *r, *c, 2)) /*checknut pravu hranicu*/ {
                            *c = *c - 1; //move left - go back
                            *direction = 2; //smer do lava
                            //continue;
                        } else {
                            *c = *c + 1; //move right
                            *direction = 1; //smer do prava
                            //continue;
                        }
                    } else {
                        *r = *r + 1; //move down
                        *direction = 3;
                        //continue;
                    }
                } else if (*direction == 2) /*smer do lava*/ {
                    if (isborder(mapa, *r, *c, 0)) /*checknut lavu hranicu */ {
                        if (isborder(mapa, *r, *c, 1)) /*checknut dolnu hranicu*/ {
                            *c = *c + 1; //move right - go back
                            *direction = 1; //smer do prava
                            //continue;
                        } else {
                            *r = *r + 1; //move down
                            *direction = 3; //smer dole
                            //continue;
                        }
                    } else {
                        *c = *c - 1; //move left
                        *direction = 2; //smer do lava
                        //continue;
                    }
                } else if (*direction == 0) /*smer hore*/ {
                    if (isborder(mapa, *r, *c, 2)) /*checknut pravu hranicu */ {
                        if (isborder(mapa, *r, *c, 0)) /*checknut lavu hranicu*/ {
                            *r = *r + 1; //move down - go back
                            *direction = 3; //smer dole
                            //continue;
                        } else {
                            *c = *c - 1; //move left
                            *direction = 2; //smer do lava
                            //continue;
                        }
                    } else {
                        *c = *c + 1; //move right
                        *direction = 1; //smer do prava
                        //continue;
                    }
                }
            } else if (((*r + *c)%2) == 0) { //parny sucet suradnic - trojuholnik orientovany nadol
                if (*direction == 1) /*smer do prava*/ {
                    if (isborder(mapa, *r, *c, 2)) /*checknut pravu hranicu */ {
                        if (isborder(mapa, *r, *c, 1)) /*checknut hornu hranicu*/ {
                            *c = *c - 1; //move left - go back
                            *direction = 2; //smer do lava
                            //continue;
                        } else {
                            *r = *r - 1; //move up
                            *direction = 0; //smer hore
                            //continue;
                        }
                    } else {
                        *c = *c + 1; //move right
                        *direction = 1; //smer do prava 
                        //continue;
                    }
                } else if (*direction == 3) /*smer dole*/ {
                    if (isborder(mapa, *r, *c, 0)) /*checknut lavu hranicu */ {
                        if (isborder(mapa, *r, *c, 2)) /*checknut pravu hranicu*/ {
                            *r = *r - 1; //move up - go back
                            *direction = 0; //smer hore
                            //continue;
                        } else {
                            *c = *c + 1; //move right
                            *direction = 1; //smer do prava
                            //continue;
                        }
                    } else {
                        *c = *c - 1; //move left
                        *direction = 2; //smer do lava
                        //continue;
                    }
                } else if (*direction == 2) /*smer do lava*/ {
                    if (isborder(mapa, *r, *c, 1)) /*checknut hornu hranicu */ {
                        if (isborder(mapa, *r, *c, 0)) /*checknut lavu hranicu*/ {
                            *c = *c + 1; //move right - go back
                            *direction = 1; //smer do prava
                            //continue;
                        } else {
                            *c = *c - 1; //move left
                            *direction = 2; //smer do lava
                            //continue;
                        }
                    } else {
                        *r = *r - 1; //move up
                        *direction = 0; //smer hore
                        //continue;
                    }
                }
            }
        } else /*lava ruka*/ {

        }
    //a--;
    }
}