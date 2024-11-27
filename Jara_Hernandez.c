// Autores: Carlos Sebastian Jara Hernandez y Alexis Antonio Mateo Medina

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void limpiar_palabra(char *palabra)
{
    int i = 0, j = 0;
    while (palabra[i] != '\0')
    {
        if (isalpha(palabra[i]) || palabra[i] == '-')
        {
            palabra[j++] = palabra[i];
        }
        i++;
    }
    palabra[j] = '\0';
}

void minusculas(char *cadena)
{
    for (int i = 0; cadena[i] != '\0'; i++)
    {
        cadena[i] = tolower(cadena[i]);
    }
}

int CargarCSV(char ***arreglo, const char *NombreArchivo)
{
    FILE *apu_archivo_CSV;
    char buffer[10000];
    char *puntero;
    int i = 0, maxPalabras = 1000;

    *arreglo = (char **)malloc(maxPalabras * sizeof(char *));
    if (*arreglo == NULL)
    {
        printf("Error al asignar memoria inicial para el array de palabras.\n");
        return 1;
    }

    apu_archivo_CSV = fopen(NombreArchivo, "r");
    if (apu_archivo_CSV == NULL)
    {
        printf("No se pudo abrir el archivo: %s\n", NombreArchivo);
        free(*arreglo);
        return 1;
    }

    int c, pos = 0;
    while ((c = fgetc(apu_archivo_CSV)) != EOF && pos < sizeof(buffer) - 1)
    {
        buffer[pos++] = c;
    }
    buffer[pos] = '\0';
    fclose(apu_archivo_CSV);

    puntero = strtok(buffer, " .,-\n");
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

        (*arreglo)[i] = (char *)malloc((strlen(puntero)) * sizeof(char));
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

        limpiar_palabra(puntero);
        strcpy((*arreglo)[i++], puntero);
        puntero = strtok(NULL, " .,-\n");
    }

    return i;
}

int main()
{
    char carta[10000];
    char *puntero;
    char **PalabrasGuardadas = NULL;
    int i = 0, j = 0, maxPalabras = 1000;
    FILE *apu_archivo;

    PalabrasGuardadas = (char **)malloc(maxPalabras * sizeof(char *));
    if (PalabrasGuardadas == NULL)
    {
        printf("Error al asignar memoria para las palabras.\n");
        return 1;
    }

    apu_archivo = fopen("carta.txt", "r");
    if (apu_archivo != NULL)
    {
        int c;
        while ((c = fgetc(apu_archivo)) != EOF && i < sizeof(carta))
        {
            carta[i++] = c;
        }
        carta[i] = '\0';
        fclose(apu_archivo);

        minusculas(carta);
    }
    else
    {
        printf("No se pudo abrir el archivo.\n");
        return 1;
    }

    puntero = strtok(carta, " .,-\n");
    i = 0;
    while (puntero != NULL)
    {
        if (i >= maxPalabras)
        {
            maxPalabras *= 2;
            PalabrasGuardadas = (char **)realloc(PalabrasGuardadas, maxPalabras * sizeof(char *));
            if (PalabrasGuardadas == NULL)
            {
                printf("Error al reasignar memoria para las palabras.\n");
                return 1;
            }
        }

        PalabrasGuardadas[i] = (char *)malloc((strlen(puntero)) * sizeof(char));
        if (PalabrasGuardadas[i] == NULL)
        {
            printf("Error al asignar memoria para la palabra.\n");
            return 1;
        }

        limpiar_palabra(puntero);
        strcpy(PalabrasGuardadas[i++], puntero);
        puntero = strtok(NULL, " .,-\n");
    }

    char **amor = NULL, **asco = NULL, **tristeza = NULL, **amistad = NULL, **felicidad = NULL;
    int tamano_amor = CargarCSV(&amor, "amor.csv");
    int tamano_asco = CargarCSV(&asco, "asco.csv");
    int tamano_tristeza = CargarCSV(&tristeza, "tristeza.csv");
    int tamano_amistad = CargarCSV(&amistad, "amistad.csv");
    int tamano_felicidad = CargarCSV(&felicidad, "felicidad.csv");

    int puntosAmor = 0, puntosAsco = 0, puntosTristeza = 0, puntosAmistad = 0, puntosFelicidad = 0;
    int negacion = 0;

    for (j = 0; j < i; j++)
    {
        if (strcmp(PalabrasGuardadas[j], "no") == 0)
        {
            negacion = 1;
            continue;
        }

        if (negacion)
        {
            int negada = 0;

            for (int k = 1; k <= 5 && j + k < i; k++)
            {
                for (int l = 0; l < tamano_amor; l++)
                {
                    if (strcmp(PalabrasGuardadas[j + k], amor[l]) == 0)
                    {
                        printf("Palabra negada: %s (no se suma a Amor)\n", PalabrasGuardadas[j + k]);
                        negada = 1;
                        break;
                    }
                }

                for (int l = 0; l < tamano_amistad; l++)
                {
                    if (strcmp(PalabrasGuardadas[j + k], amistad[l]) == 0)
                    {
                        printf("Palabra negada: %s (no se suma a amistad)\n", PalabrasGuardadas[j + k]);
                        negada = 1;
                        break;
                    }
                }

                for (int l = 0; l < tamano_asco; l++)
                {
                    if (strcmp(PalabrasGuardadas[j + k], asco[l]) == 0)
                    {
                        printf("Palabra negada: %s (no se suma a asco)\n", PalabrasGuardadas[j + k]);
                        negada = 1;
                        break;
                    }
                }

                for (int l = 0; l < tamano_felicidad; l++)
                {
                    if (strcmp(PalabrasGuardadas[j + k], felicidad[l]) == 0)
                    {
                        printf("Palabra negada: %s (no se suma a felicidad)\n", PalabrasGuardadas[j + k]);
                        negada = 1;
                        break;
                    }
                }

                for (int l = 0; l < tamano_tristeza; l++)
                {
                    if (strcmp(PalabrasGuardadas[j + k], tristeza[l]) == 0)
                    {
                        printf("Palabra negada: %s (no se suma a tristeza)\n", PalabrasGuardadas[j + k]);
                        negada = 1;
                        break;
                    }
                }

                if (negada)
                    break;
            }

            if (!negada)
                negacion = 0;

            continue;
        }

        for (int k = 0; k < tamano_amor; k++)
        {
            if (strcmp(PalabrasGuardadas[j], amor[k]) == 0)
            {
                puntosAmor++;
                break;
            }
        }

        for (int k = 0; k < tamano_amistad; k++)
        {
            if (strcmp(PalabrasGuardadas[j], amistad[k]) == 0)
            {
                puntosAmistad++;
                break;
            }
        }

        for (int k = 0; k < tamano_asco; k++)
        {
            if (strcmp(PalabrasGuardadas[j], asco[k]) == 0)
            {
                puntosAsco++;
                break;
            }
        }

        for (int k = 0; k < tamano_felicidad; k++)
        {
            if (strcmp(PalabrasGuardadas[j], felicidad[k]) == 0)
            {
                puntosFelicidad++;
                break;
            }
        }

        for (int k = 0; k < tamano_tristeza; k++)
        {
            if (strcmp(PalabrasGuardadas[j], tristeza[k]) == 0)
            {
                puntosTristeza++;
                break;
            }
        }
    }

    int PuntosTotales = puntosAmor + puntosAsco + puntosTristeza + puntosAmistad + puntosFelicidad;
    if (PuntosTotales > 0)
    {
        printf("Porcentaje de Amor en la carta: %.2f %%\n", (puntosAmor * 100.0) / PuntosTotales);
        printf("Porcentaje de Asco en la carta: %.2f %%\n", (puntosAsco * 100.0) / PuntosTotales);
        printf("Porcentaje de Tristeza en la carta: %.2f %%\n", (puntosTristeza * 100.0) / PuntosTotales);
        printf("Porcentaje de Amistad en la carta: %.2f %%\n", (puntosAmistad * 100.0) / PuntosTotales);
        printf("Porcentaje de Felicidad en la carta: %.2f %%\n", (puntosFelicidad * 100.0) / PuntosTotales);
    }
    else
    {
        printf("No se encontraron palabras relevantes en la carta.\n");
    }

    for (int k = 0; k < i; k++)
    {
        free(PalabrasGuardadas[k]);
    }
    free(PalabrasGuardadas);

    return 0;
}
