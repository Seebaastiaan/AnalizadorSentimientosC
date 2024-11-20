#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int CargarCSV(char ***arreglo, const char *NombreArchivo)
{
    FILE *apu_archivo_CSV;
    char PalabrasNOPUNTERO[10000];
    char *puntero;
    int i = 0;
    int maxPalabras = 1000;

    *arreglo = (char **)malloc(maxPalabras * sizeof(char *));
    if (*arreglo == NULL)
    {
        printf("Error al asignar memoria inicial para el array de palabras.\n");
        return 1;
    }

    apu_archivo_CSV = fopen(NombreArchivo, "r");
    if (apu_archivo_CSV == NULL)
    {
        printf("No se pudo abrir el archivo.\n");
        free(*arreglo);
        return 1;
    }

    int c;
    while ((c = fgetc(apu_archivo_CSV)) != EOF && i < sizeof(PalabrasNOPUNTERO) - 1)
    {
        PalabrasNOPUNTERO[i++] = c;
    }
    PalabrasNOPUNTERO[i] = '\0';
    fclose(apu_archivo_CSV);

    i = 0;
    puntero = strtok(PalabrasNOPUNTERO, " .,-\n");
    while (puntero != NULL)
    {

        if (i >= maxPalabras)
        {
            maxPalabras *= 2;
            char **nuevoArreglo = (char **)realloc(*arreglo, maxPalabras * sizeof(char *));
            if (nuevoArreglo == NULL)
            {
                printf("Error al reasignar memoria para las palabras.\n");
                for (int j = 0; j < i; j++)
                {
                    free((*arreglo)[j]);
                }
                free(*arreglo);
                return 1;
            }
            *arreglo = nuevoArreglo;
        }

        (*arreglo)[i] = (char *)malloc((strlen(puntero) + 1) * sizeof(char));
        if ((*arreglo)[i] == NULL)
        {
            printf("Error al asignar memoria para una palabra.\n");
            for (int j = 0; j < i; j++)
            {
                free((*arreglo)[j]);
            }
            free(*arreglo);
            return 1;
        }

        strcpy((*arreglo)[i], puntero);
        i++;
        puntero = strtok(NULL, " .,-\n");
    }

    for (int j = 0; j < i; j++)
    {
        printf("%s\n", (*arreglo)[j]);
        free((*arreglo)[j]);
    }
    free(*arreglo);

    return 0;
}

int main()
{
    char **arreglo = NULL;
    if (CargarCSV(&arreglo, "amor.csv") == 0)
    {
        printf("Archivo cargado correctamente.\n");
    }
    else
    {
        printf("Error al cargar el archivo.\n");
    }
    return 0;
}
