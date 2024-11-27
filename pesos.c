#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Función para leer palabras de un archivo CSV
int LeerCSV(const char *archivo, char palabras[][50], int maxPalabras)
{
    FILE *f = fopen(archivo, "r");
    if (!f)
    {
        printf("No se pudo abrir el archivo: %s\n", archivo);
        return 0;
    }

    char buffer[1000];
    int i = 0;
    while (fgets(buffer, sizeof(buffer), f) && i < maxPalabras)
    {
        char *token = strtok(buffer, ",\n");
        while (token != NULL && i < maxPalabras)
        {
            strcpy(palabras[i++], token);
            token = strtok(NULL, ",\n");
        }
    }

    fclose(f);
    return i; // Retorna la cantidad de palabras leídas
}

// Función para generar el archivo de pesos iniciales
void GenerarPesos(char palabrasAmor[][50], int tamAmor,
                  char palabrasFelicidad[][50], int tamFelicidad,
                  char palabrasAmistad[][50], int tamAmistad,
                  char palabrasAsco[][50], int tamAsco,
                  char palabrasTristeza[][50], int tamTristeza,
                  const char *archivoPesos)
{
    FILE *f = fopen(archivoPesos, "w");
    if (!f)
    {
        printf("Error al crear el archivo de pesos: %s\n", archivoPesos);
        return;
    }

    fprintf(f, "palabra,amor,amistad,asco,tristeza,felicidad\n");

    // Función para escribir palabras con pesos iniciales
    void EscribirPesos(FILE * f, char palabras[][50], int tam, float amor, float amistad, float asco, float tristeza, float felicidad)
    {
        for (int i = 0; i < tam; i++)
        {
            fprintf(f, "%s,%.1f,%.1f,%.1f,%.1f,%.1f\n", palabras[i], amor, amistad, asco, tristeza, felicidad);
        }
    }

    EscribirPesos(f, palabrasAmor, tamAmor, 1.0, 0.1, 0.0, 0.0, 0.1);
    EscribirPesos(f, palabrasFelicidad, tamFelicidad, 0.1, 0.1, 0.0, 0.0, 1.0);
    EscribirPesos(f, palabrasAmistad, tamAmistad, 0.1, 1.0, 0.0, 0.1, 0.1);
    EscribirPesos(f, palabrasAsco, tamAsco, 0.0, 0.0, 1.0, 0.1, 0.0);
    EscribirPesos(f, palabrasTristeza, tamTristeza, 0.0, 0.1, 0.0, 1.0, 0.0);

    fclose(f);
    printf("Archivo de pesos iniciales generado en: %s\n", archivoPesos);
}

int main()
{
    // Máximo de palabras por sentimiento
    const int maxPalabras = 100;

    // Arreglos para almacenar las palabras
    char palabrasAmor[maxPalabras][50];
    char palabrasFelicidad[maxPalabras][50];
    char palabrasAmistad[maxPalabras][50];
    char palabrasAsco[maxPalabras][50];
    char palabrasTristeza[maxPalabras][50];

    // Leer palabras de los archivos
    int tamAmor = LeerCSV("amor.csv", palabrasAmor, maxPalabras);
    int tamFelicidad = LeerCSV("felicidad.csv", palabrasFelicidad, maxPalabras);
    int tamAmistad = LeerCSV("amistad.csv", palabrasAmistad, maxPalabras);
    int tamAsco = LeerCSV("asco.csv", palabrasAsco, maxPalabras);
    int tamTristeza = LeerCSV("tristeza.csv", palabrasTristeza, maxPalabras);

    // Generar el archivo de pesos iniciales
    GenerarPesos(palabrasAmor, tamAmor, palabrasFelicidad, tamFelicidad,
                 palabrasAmistad, tamAmistad, palabrasAsco, tamAsco,
                 palabrasTristeza, tamTristeza, "pesos.csv");

    return 0;
}
