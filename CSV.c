#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int CargarCSV(char **arreglo, const char *NombreArchivo)
{
    FILE *apu_archivo_CSV;
    char PalabrasNOPUNTERO[10000];
    char *puntero;
    int i = 0;
    **arreglo = (char **)malloc(1000 * sizeof(char *));
    int maxPalabras = 1000;

    if (arreglo == NULL)
    {
        printf("Error al asignar memoria inicial para el array de palabras.\n");
        return 1;
    }

    apu_archivo_CSV = fopen(NombreArchivo, "r");

    if (apu_archivo_CSV != NULL)
    {
        int c;

        while ((c = fgetc(apu_archivo_CSV)) != EOF && i < sizeof(PalabrasNOPUNTERO))
        {
            PalabrasNOPUNTERO[i++] = c;
        }
        PalabrasNOPUNTERO[i] = '\0';
        fclose(apu_archivo_CSV);
    }
    else
    {
        printf("No se pudo abrir el archivo.\n");
        return 1;
    }

    i = 0;
    puntero = strtok(PalabrasNOPUNTERO, " .,-\n");

    while (puntero != NULL)
    {
        if (i >= maxPalabras)

        {
            maxPalabras = maxPalabras * 2;
            arreglo = (char **)realloc(arreglo, maxPalabras * sizeof(char *));
            if (arreglo == NULL)
            {
                printf("Error al reasignar memoria para las palabras de Amor.\n");
                return 1;
            }
        }
        arreglo[i] = (char *)malloc((strlen(puntero)) * sizeof(char));
        if (arreglo[i] == NULL)
        {
            printf("Error al asignar memoria para la palabra.\n");
            return 1;
        }

        strcpy(arreglo[i], puntero);
        i++;
        puntero = strtok(NULL, " .,-\n");
    }
    for (int j = 0; j < i; j++)
    {
        printf("%s\n", arreglo[j]);
        free(arreglo[j]);
    }
    free(arreglo);

    return 0;
}

int main()
{
    char **arreglo = NULL;

    CargarCSV(arreglo, "amor.csv");
    return 0;
}
