#include <stdio.h>
#include <stdlib.h>
#include "Menus.h"

//Definicion de prototipos
void mostrarMenu () {
	FILE *f = fopen ("Menu.txt", "r");
	
	char linea[200]; //Variable del tipo char para leer toda la linea de texto e imprimirlo
	
	system("cls"); //Para limpiar la pantalla
	while (fgets(linea, sizeof(linea), f) != NULL) {
		printf ("%s", linea);
	}
	
	fclose(f);
}

void mostrarGameOver () {
	FILE *f = fopen ("Game over.txt", "r");
	
	char linea[200];
	
	system("cls");
	while (fgets(linea, sizeof(linea), f) != NULL) {
		printf("%s", linea);
	}
	
	fclose(f);
}

void mostrarGraciasPorJugar () {
	FILE *f = fopen ("Gracias por Jugar.txt", "r");
	
	char linea[200];
	
	system("cls");
	while (fgets(linea, sizeof(linea), f) != NULL) {
		printf("%s", linea);
	}
	
	fclose(f);
}

void mostrarCreditos () {
	FILE *f = fopen ("Creditos.txt", "r");
	
	char linea[200];
	
	system("cls");
	while (fgets(linea, sizeof(linea), f) != NULL) {
		printf("%s", linea);
	}
	
	fclose(f);
}
