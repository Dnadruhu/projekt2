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
        char buffer[mapa -> rows][mapa -> cols];
        if (fgets(buffer, sizeof(buffer), subor) != NULL)
        {
            mapa -> rows = buffer[0][0];
            mapa -> cols = buffer[0][2];
            printf("Velkost pola: %s", buffer);
        }
        else
        {
            fprintf(stderr, "Chyba pri citani zo suboru: %s\n", bludisko);
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
