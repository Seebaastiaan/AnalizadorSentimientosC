#include <stdio.h>
#include <string.h>
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

int main()
{
    char carta[10000];
    int i = 0;
    char *puntero;
    char PalabrasGuardadas[10000][20];
    int j = 0;
    FILE *apu_archivo;

    apu_archivo = fopen("carta.txt", "r");
    if (apu_archivo != NULL)
    {
        int c;

        while ((c = fgetc(apu_archivo)) != EOF && i < sizeof(carta))
        {
            carta[i++] = (char)c;
        }
        carta[i] = '\0';
        fclose(apu_archivo);
    }
    else
    {
        printf("No se pudo abrir el archivo.\n");
        return 1;
    }

    puntero = strtok(carta, " .,-");
    i = 0;
    while (puntero != NULL && i < 10000)
    {
        limpiar_palabra(puntero);
        strcpy(PalabrasGuardadas[i], puntero);
        puntero = strtok(NULL, " .,-");
        i++;
    }

    char amor[50][20] = {
        "cariño", "pasión", "ternura", "compañerismo", "afecto",
        "devocion", "amor", "atraccion", "romance", "confianza",
        "deseo", "admiracion", "cuidado", "aprecio", "dedicacion",
        "lealtad", "gratitud", "fidelidad", "encanto", "ilusion",
        "inspiracion", "entrega", "apego", "veneracion", "fascinacion",
        "conexion", "almas", "amistad", "compromiso", "ternura",
        "devocion", "delirio", "emoción", "sincero", "afecto",
        "serenidad", "cautivar", "respeto", "adulacion", "solidaridad",
        "misterio", "impulso", "unión", "belleza", "voluntad"};

    int tamano_amor = sizeof(amor) / sizeof(amor[0]);
    int puntosAmor = 0;

    char asco[50][20] = {
        "repugnancia", "desagrado", "aversion", "rechazo", "asco",
        "antipatia", "odio", "abominacion", "molestia", "irritacion",
        "desprecio", "hostilidad", "repulsion", "horror", "repelencia",
        "indiferencia", "desgusto", "disgusto", "reproche", "resistencia",
        "antipatico", "alejamiento", "distanciamiento", "critica", "rechazar",
        "odiar", "sufrimiento", "desaprobacion", "negativa", "enfermedad",
        "contaminacion", "detestar", "insolencia", "abominable", "sucio",
        "desorden", "desgano", "molesto", "sordido", "repulsivo",
        "desprecio", "desden", "desprecio", "desgarrar", "atroz"};

    int tamano_asco = sizeof(asco) / sizeof(asco[0]);
    int puntosAsco = 0;

    char tristeza[50][20] = {
        "soledad", "desesperanza", "melancolia", "dolor", "lagrimas",
        "pena", "angustia", "depresion", "tristeza", "desconsuelo",
        "desilusion", "frustracion", "amargura", "desdicha", "pesar",
        "abatimiento", "afliccion", "sufrimiento", "lamento", "nostalgia",
        "vacio", "silencio", "decepcion", "quebranto", "injusticia",
        "desgaste", "duda", "perdida", "anhelo", "doloroso",
        "melancolico", "desesperacion", "triste", "desgarrador", "fatiga",
        "congoja", "desolacion", "turbacion", "sombra", "ausencia",
        "sofrimiento", "apagado", "frustrante", "desolado", "desanimo"};

    int tamano_tristeza = sizeof(tristeza) / sizeof(tristeza[0]);
    int puntosTristeza = 0;

    char amistad[50][20] = {
        "lealtad", "compañerismo", "confianza", "solidaridad", "apoyo",
        "fraternidad", "amistad", "hermandad", "altruismo", "comunidad",
        "camaraderia", "simpatia", "respeto", "unidad", "cooperacion",
        "escucha", "consejo", "empatia", "aprecio", "alianza",
        "bondad", "entendimiento", "conexion", "presente", "mutuo",
        "valor", "afecto", "acompañamiento", "hermandad", "compromiso",
        "integridad", "fidelidad", "honestidad", "compasión", "complejidad",
        "cercania", "solidaridad", "abrazar", "apoyo", "conexión",
        "incondicional", "hermano", "consuelo", "refugio", "compañero"};

    int tamano_amistad = sizeof(amistad) / sizeof(amistad[0]);
    int puntosAmistad = 0;

    char felicidad[50][20] = {
        "alegria", "satisfaccion", "placer", "entusiasmo", "contento",
        "felicidad", "jubilo", "gozo", "gratitud", "dicha",
        "optimismo", "euforia", "bienestar", "sosiego", "serenidad",
        "sonrisa", "sueño", "celebracion", "vivir", "inspiracion",
        "sonreir", "logro", "triunfo", "victoria", "esperanza",
        "luz", "brillo", "realizacion", "bendicion", "calor",
        "vivir", "gratificante", "éxito", "luminosa", "alegría",
        "felices", "orgullo", "equilibrio", "regocijo", "deslumbrante",
        "esperanza", "paz", "aprecio", "tranquilidad", "superación"};

    int tamano_felicidad = sizeof(felicidad) / sizeof(felicidad[0]);
    int puntosFelicidad = 0;

    // arreglo amor
    for (j = 0; j < i; j++)
    {
        for (int k = 0; k < tamano_amor; k++)
        {
            if (strcmp(PalabrasGuardadas[j], amor[k]) == 0)
            {
                printf("Palabras que coinciden en amor: %s\n", PalabrasGuardadas[j]);
                puntosAmor += 1;
            }
        }
    }
    printf("Puntos amor: %d\n", puntosAmor);

    // arreglo asco
    for (j = 0; j < i; j++)
    {
        for (int k = 0; k < tamano_asco; k++)
        {
            if (strcmp(PalabrasGuardadas[j], asco[k]) == 0)
            {
                printf("Palabras que coinciden en Asco: %s\n", PalabrasGuardadas[j]);
                puntosAsco += 1;
            }
        }
    }
    printf("Puntos Asco: %d\n", puntosAsco);

    // Arreglo tristeza
    for (j = 0; j < i; j++)
    {
        for (int k = 0; k < tamano_tristeza; k++)
        {
            if (strcmp(PalabrasGuardadas[j], tristeza[k]) == 0)
            {
                printf("Palabras que coinciden en tristeza: %s\n", PalabrasGuardadas[j]);
                puntosTristeza += 1;
            }
        }
    }
    printf("Puntos Tristeza: %d\n", puntosTristeza);

    // arreglo amistad
    for (j = 0; j < i; j++)
    {
        for (int k = 0; k < tamano_amistad; k++)
        {
            if (strcmp(PalabrasGuardadas[j], amistad[k]) == 0)
            {
                printf("Palabras que coinciden en amistad: %s\n", PalabrasGuardadas[j]);
                puntosAmistad += 1;
            }
        }
    }
    printf("Puntos Amistad: %d\n", puntosAmistad);

    // Arreglo felicidad
    for (j = 0; j < i; j++)
    {
        for (int k = 0; k < tamano_felicidad; k++)
        {
            if (strcmp(PalabrasGuardadas[j], felicidad[k]) == 0)
            {
                printf("Palabras que coinciden en felicidad: %s\n", PalabrasGuardadas[j]);
                puntosFelicidad += 1;
            }
        }
    }
    printf("Puntos felicidad: %d\n", puntosFelicidad);

    return 0;
}
