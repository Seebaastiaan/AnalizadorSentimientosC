// Autores Jara Hernandez Carlos Sebastian y Mateo Medina Alexis Antonio

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
        cadena[i] = tolower((unsigned char)cadena[i]);
    }
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
        while ((c = fgetc(apu_archivo)) != EOF && i < sizeof(carta) - 1)
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

        PalabrasGuardadas[i] = (char *)malloc((strlen(puntero) + 1) * sizeof(char));
        if (PalabrasGuardadas[i] == NULL)
        {
            printf("Error al asignar memoria para la palabra.\n");
            return 1;
        }

        limpiar_palabra(puntero);
        strcpy(PalabrasGuardadas[i++], puntero);
        puntero = strtok(NULL, " .,-\n");
    }

    char *amor[] = {"amo", "afecto", "pasion", "devocion", "ternura", "romance", "adoracion", "aprecio", "cuidado", "encanto"};
    int tamano_amor = 10, puntosAmor = 0;

    char *asco[] = {"repulsion", "desagrado", "aversion", "nausea", "rechazo", "repugnancia", "asco", "horror", "desden", "incomodidad"};
    int tamano_asco = 10, puntosAsco = 0;

    char *tristeza[] = {"pena", "melancolia", "soledad", "desconsuelo", "desesperacion", "angustia", "afliccion", "lagrimas", "pesar", "lamento"};
    int tamano_tristeza = 10, puntosTristeza = 0;

    char *amistad[] = {"companerismo", "confianza", "lealtad", "apoyo", "solidaridad", "camaraderia", "comprension", "amistad", "union", "generosidad"};
    int tamano_amistad = 10, puntosAmistad = 0;

    char *felicidad[] = {"alegre", "euforia", "satisfaccion", "gozo", "entusiasmo", "regocijo", "contento", "optimismo", "plenitud", "dicha"};
    int tamano_felicidad = 10, puntosFelicidad = 0;

    int negacion = 0;
    int rango_negacion = 5;

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

            for (int k = 1; k <= rango_negacion; k++)
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
                for (int l = 0; l < tamano_asco; l++)
                {
                    if (strcmp(PalabrasGuardadas[j + k], asco[l]) == 0)
                    {
                        printf("Palabra negada: %s (no se suma a Asco)\n", PalabrasGuardadas[j + k]);
                        negada = 1;
                        break;
                    }
                }
                for (int l = 0; l < tamano_tristeza; l++)
                {
                    if (strcmp(PalabrasGuardadas[j + k], tristeza[l]) == 0)
                    {
                        printf("Palabra negada: %s (no se suma a Tristeza)\n", PalabrasGuardadas[j + k]);
                        negada = 1;
                        break;
                    }
                }
                for (int l = 0; l < tamano_amistad; l++)
                {
                    if (strcmp(PalabrasGuardadas[j + k], amistad[l]) == 0)
                    {
                        printf("Palabra negada: %s (no se suma a Amistad)\n", PalabrasGuardadas[j + k]);
                        negada = 1;
                        break;
                    }
                }
                for (int l = 0; l < tamano_felicidad; l++)
                {
                    if (strcmp(PalabrasGuardadas[j + k], felicidad[l]) == 0)
                    {
                        printf("Palabra negada: %s (no se suma a Felicidad)\n", PalabrasGuardadas[j + k]);
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

        for (int k = 0; k < tamano_asco; k++)
        {
            if (strcmp(PalabrasGuardadas[j], asco[k]) == 0)
            {
                puntosAsco++;
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

        for (int k = 0; k < tamano_amistad; k++)
        {
            if (strcmp(PalabrasGuardadas[j], amistad[k]) == 0)
            {
                puntosAmistad++;
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
