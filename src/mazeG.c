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
        for (int i = 0; i < 100 && cnt < argc; i++)
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
                    return;
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
    const char *bludisko = nazovSuboru;
    FILE *subor = fopen(bludisko, "r");

    if (subor != NULL)
    {
        printf("%s", nazovSuboru);
        char buffer[sizeof(mapa->cols)*sizeof(mapa->rows)];
    }
}

bool isborder(Map *map, int r, int c, int border);

int start_border(Map *map, int r, int c, int leftright);

int main(int argc, char *argv[])
{
    printf("args count %d\n", argc);
    char nazovSuboru[20];
    checkArgs(argc, *argv, nazovSuboru);
    Map mapa;
    mapInit(&mapa, nazovSuboru);
    return 0;
}
