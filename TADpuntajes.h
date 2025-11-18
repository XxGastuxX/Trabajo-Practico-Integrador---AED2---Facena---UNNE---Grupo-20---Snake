#include <stdio.h>
#include <string.h>

//Estructura para manejar archivos
typedef struct {
    char nombre[30];
    int puntos;
} tScore;

//Prototipos
void guardarPuntaje(char[], int);
void mostrarPuntajes();


void guardarPuntaje(char nombre[], int puntos) {
	tScore p;
	strcpy(p.nombre, nombre);
	p.puntos = puntos;
    FILE *f = fopen("scores.txt", "a");
    if (!f) return;
    fprintf(f, "%d - %s", p.puntos, p.nombre);
    fclose(f);
}

void mostrarPuntajes() {
    tScore p;
    FILE *f = fopen("scores.txt", "r");

    if (!f) {
        printf("No hay puntajes registrados.\n");
        return;
    }

    printf("\n***LISTA DE PUNTAJES***\n\n");

    while (fread(&p, sizeof(tScore), 1, f) == 1) {
        printf("Jugador: %s\n", p.nombre);
        printf("Puntos : %d\n\n", p.puntos);
    }

    fclose(f);
}

