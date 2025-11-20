#include <stdio.h>
#include <string.h> //Para guardar los nombres en un archivo
#include <stdlib.h> //Para malloc y system("cls")
#include "Score.h"

//Definicion de prototipos
void guardarPuntaje(char nombre[], int puntos) {
	tScore p;
	strcpy(p.nombre, nombre);
	p.puntos = puntos;
    FILE *f = fopen("scores.dat", "ab"); /*Abro/Creo un archivo.dat para guardar los puntos y nombres*/
    if (!f) return;
    fwrite(&p, sizeof(tScore), 1, f);
    fclose(f);
}

tNodoArbol* cargarArbolDesdeArchivo () { //Para guardar los datos del archivo.dat en el arbol
    FILE *f = fopen("scores.dat", "rb");
    if (!f) return NULL;

    tScore p;
    tNodoArbol *arbol = NULL;

    while (fread(&p, sizeof(tScore), 1, f) == 1) {
        arbol = insertarEnArbol(arbol, p);
    }

    fclose(f);
    return arbol;
}


tNodoArbol* insertarEnArbol (tNodoArbol *raiz, tScore x) { //Inserta en la raiz el primer jugador y luego los demas jugadores a la izquierda o derecha
	tNodoArbol *nuevo = (tNodoArbol*) malloc(sizeof(tNodoArbol)); //dependiendo si es mayor que la raiz o no
	nuevo->dato = x;
	nuevo->izq = nuevo->der = NULL;
	
	if(raiz == NULL) return nuevo;
	
	tNodoArbol *actual = raiz;
	tNodoArbol *padre = NULL;
	
	while (actual != NULL) {
		padre = actual;
		if (x.puntos < actual->dato.puntos) actual = actual->izq;
		else actual = actual->der;
	}
	
	if (x.puntos < padre->dato.puntos) padre->izq = nuevo;
	else padre->der = nuevo;
	return raiz;
}

void mostrarInOrden (tNodoArbol *raiz) {//Muestra los puntajes en In-Orden invertido (der-raiz-izq)
    tNodoArbol *lista[100];
    int top = -1;
    tNodoArbol *actual = raiz;

    while (actual != NULL || top != -1) {

        //Va todo lo posible hacia la derecha
        while (actual != NULL) {
            lista[++top] = actual;
            actual = actual->der;
        }

        // Obtener nodo del tope de la pila
        actual = lista[top--];

        // Mostrar el nodo
        printf("Jugador: %-10s | Puntos: %d\n",actual->dato.nombre, actual->dato.puntos);

        // Luego ir hacia la izquierda
        actual = actual->izq;
    }
}


