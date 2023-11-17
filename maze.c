#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct
{
    int rows;
    int cols;
    unsigned char *cells;
} Map;

void mapInit(Map *mapa)
{
    const char *bludisko = "bludiste.txt";
    FILE *subor = fopen(bludisko, "r");

    if (subor != NULL)
    {
        char buffer[mapa->cols];
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
                    fprintf(stderr, "Chyba pri citani zo suboru: %s\n", bludisko);
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
            fprintf(stderr, "Chyba pri citani zo suboru: %s\n", bludisko);
            exit(1);
        }

        fclose(subor);
    }
    else
    {
        fprintf(stderr, "Chyba pri otvarani suboru: %s\n", bludisko);
        exit(1);
    }
}

bool isborder(Map *map, int r, int c, int border);

int start_border(Map *map, int r, int c, int leftright);

int main(int argc, char *argv[])
{
    int row;
    int column;
    // checkArgs(argv);
    Map mapa;
    mapInit(&mapa);
    return 0;
}
