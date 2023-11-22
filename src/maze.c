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

void checkArgs(int argc, char *argv, char *nazovSuboru){
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
                printf("printing argument: %s\n", argument);
                if (!(strcmp("--help", argument)))
                {
                    printf("i will help you blah blah blah\n");
                    ///TO DO
                } else if (!(strcmp("--test", argument)))
                {
                    /* code */
                } else if (strstr(argument, ".txt") != NULL)
                {
                    strcpy(nazovSuboru, argument);
                }
                  
            }
        }
    } else {
        fprintf(stderr, "Neplatny vstup - malo argumentov\n");
        exit(1);
    }
}

void mapInit(Map *mapa, char *nazovSuboru)
{
    printf("tu: %s\n", nazovSuboru);
    FILE *subor = fopen(nazovSuboru, "r");

    if (subor != NULL)
    {
        char buffer[sizeof(mapa->cols)*sizeof(mapa->rows)];
        if (fgets(buffer, sizeof(buffer), subor) != NULL)
        {
            mapa->rows = atoi(&buffer[0]);
            mapa->cols = atoi(&buffer[2]);
            printf("Velkost pola: %s\n",buffer);

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
                    exit(1);
                }
            }
            for (int i = 0; i < mapa->rows; i++)
            {
                for (int j = 0; j < mapa->cols; j++)
                {
                    printf("%hhu ", mapa->cells[i * mapa->cols + j]);
                }
                printf("\n");
            }
        }
        else
        {
            fprintf(stderr, "Chyba pri citani zo suboru: %s\n", nazovSuboru);
            exit(1);
        }

        fclose(subor);
    }
    else
    {
        fprintf(stderr, "Chyba pri otvarani suboru: %s\n", nazovSuboru);
        exit(1);
    }
}

bool isborder(Map *map, int r, int c, int border);

int start_border(Map *map, int r, int c, int leftright);

int main(int argc, char *argv[])
{
    printf("args count %d\n", argc);
    char nazovSuboru[100];
    checkArgs(argc, *argv, nazovSuboru);
    Map mapa;
    //printf("%s", nazovSuboru);
    mapInit(&mapa, nazovSuboru);
    return 0;
}
