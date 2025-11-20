#ifndef TADJUEGO_H
#define TADJUEGO_H

#include <stdbool.h>

#define F 15
#define C 25

typedef struct nodo {
    int x, y;
    struct nodo *sig;
} Nodo;

typedef struct {
    Nodo *primero;
    Nodo *ultimo;
    int longitud;
} tSnake;

void iniciarSnake(tSnake*);
void agregarInicio(tSnake*, int, int);
void agregarFinal(tSnake*, int, int);
void eliminarFinal(tSnake*);
void iniciarMapa(char[F][C]);
void iniciarComida(char[F][C]);
void dibujarMapa(char[F][C], tSnake*);
void mostrarMapa(char[F][C]);
void leerTeclas(char*);
int movimientoJug(tSnake*, char);
int verifiEnd(int, int);
int verifiBody(tSnake*, int, int);
int inicioJuego();
int juego(char[F][C], tSnake*);

// Variables externas:
extern int comidaX, comidaY;
extern int hayComida;
extern bool gameOver;

#endif

