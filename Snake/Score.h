#ifndef Score_H
#define Score_H

//Estructura para manejar archivos
typedef struct {
    char nombre[30];
    int puntos;
} tScore;

//Estructura de arboles
typedef struct nodoArbol {
	tScore dato;
	struct nodoArbol *der;
	struct nodoArbol *izq;
}tNodoArbol;

//Prototipos
void guardarPuntaje(char[], int);
tNodoArbol* cargarArbolDesdeArchivo ();
tNodoArbol* insertarEnArbol (tNodoArbol*, tScore);
void mostrarInOrden (tNodoArbol*);

#endif
