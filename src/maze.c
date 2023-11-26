#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct
{
    int rows;
    int cols;
    unsigned char *cells;
} Map;

void checkArgs(int argc, char *argv, int r, int c, int leftright, char *nazovSuboru, Map mapa);

int mapInit(Map *mapa, char *nazovSuboru);

bool isborder(Map *mapa, int r, int c, int border);

int start_border(Map *mapa, int r, int c, int leftright);

//void pathFinder();

int main(int argc, char *argv[])
{
    printf("args count %d\n", argc);
    char nazovSuboru[100];
    int r,c;
    int leftright;
    int border;
    Map mapa;

    checkArgs(argc, *argv, r, c, leftright, nazovSuboru, mapa);
    mapInit(&mapa, nazovSuboru);
    //pathFinder();
    
    free(mapa.cells);
    return 0;
}

void checkArgs(int argc, char *argv, int r, int c, int leftright, char *nazovSuboru, Map mapa)
{
    r = 2;
    printf("r: %d", r);
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

                if (!(strcmp("--help", argument)))
                {
                    printf("do this blah blah blah\n");
                    ///TO DO
                } else if (!(strcmp("--test", argument)))
                { 
                    ///TO DO  
                } else if (!(strcmp("--lpath", argument)))
                { 
                    leftright = 0; // pravidlo lavej ruky
                } else if (!(strcmp("--rpath", argument)))
                { 
                    leftright = 1; //pravidlo pravej ruky
                }
                if (strstr(argument, ".txt") != NULL)
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
            return 1;
            /*for (int i = 0; i < mapa->rows; i++)
            {
                for (int j = 0; j < mapa->cols; j++)
                {
                    printf("%hhu ", mapa->cells[i * mapa->cols + j]);
                }
                printf("\n");
            }// NEVYPISE NIC KVOLI RETURN 1
            */
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
    }
}

int start_border(Map *mapa, int r, int c, int leftright) {
    //TODO
}