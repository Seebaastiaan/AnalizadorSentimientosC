#include <stdio.h>
#include <string.h>

int main(void)
{
    int i = 0;
    char Palabras[10][10];
    char cad[] = "- esta es, una.cadena simple.";
    char *puntero;
    int cont = 1;

    puntero = strtok(cad, " .,-");
    while (puntero != NULL && i < 10)
    {
        printf("%d \t%s\n", cont, puntero);
        strcpy(Palabras[i], puntero);
        puntero = strtok(NULL, " .,-");
        cont++;
        i++;
    }

    printf("\nPalabras almacenadas:\n");
    for (int j = 0; j < i; j++)
    {
        puts(Palabras[j]);
    }

    return 0;
}
