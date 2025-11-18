#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#define F 15
#define C 25

//Lista enlazada simple para implementar cola
typedef struct nodo {
	int x, y;
	struct nodo *sig;
}Nodo;

//Cola (cuerpo de la serpiente)
typedef struct {
	Nodo *primero;
	Nodo *ultimo;
	int longitud;
}tSnake;

//Estructura para manejar archivos
typedef struct {
    char nombre[30];
    int puntos;
} tScore;

//Prototipos
void iniciarSnake (tSnake*);
void agregarInicio(tSnake*, int, int);
void agregarFinal (tSnake*, int, int);
void eliminarFinal (tSnake*);
void iniciarMapa (char[F][C]);
void iniciarComida (char[F][C]);
void dibujarMapa (char[F][C], tSnake*);
void mostrarMapa (char[F][C]);
void guardarPuntaje(char[], int);
void mostrarPuntajes();
void inicioJuego();
void juego (char[F][C], tSnake*);
void leerTeclas (char*);
int movimientoJug (tSnake*, char);
int verifiEnd (int, int);
int verifiBody (tSnake*, int, int);

//Variables Globales
int comidaX, comidaY;
int hayComida;
int gameOver = 1;

void iniciarSnake (tSnake *vib) {
	vib->primero = NULL;
	vib->ultimo = NULL;
	vib->longitud = 0;
}

void agregarInicio(tSnake *vib, int x, int y) {
	Nodo *nuevo = (Nodo*) malloc(sizeof(Nodo));
	nuevo->x = x;
	nuevo->y = y;
	nuevo->sig = vib->primero;
	
	vib->primero = nuevo;
	if (vib->ultimo == NULL) vib->ultimo = nuevo;
	vib->longitud++;
}

void agregarFinal (tSnake *vib, int x, int y) {
	Nodo *nuevo = (Nodo*) malloc(sizeof(Nodo));
	nuevo->x = x;
	nuevo->y = y;
	nuevo->sig = NULL;
	
	if (vib->primero == NULL) {
		vib->primero = nuevo;
	}else{
		vib->ultimo->sig = nuevo;
	}
	vib->ultimo = nuevo;
	vib->longitud++;
}

void eliminarFinal (tSnake *vib) {
	if (vib->primero == NULL) return;
	
	if (vib->primero == vib->ultimo) {
		free(vib->primero);
		vib->primero = vib->ultimo = NULL;
		vib->longitud = 0;
		return;
	}
	
	Nodo *aux = vib->primero;
	while (aux->sig != vib->ultimo) aux = aux->sig;
	
	
	free(vib->ultimo);
	aux->sig = NULL;
	vib->ultimo = aux;
	vib->longitud--;
}

void iniciarMapa (char m[F][C]) {
	int i, j;
		for (i=0; i<F; i++){
			for (j=0; j<C; j++) {
				m[i][j] = ' ';
			}
		}

}

void iniciarComida (char m[F][C]) {
	if (!hayComida) {
		do {
		comidaX = rand() % F;
		comidaY = rand() % C;
		}while(m[comidaX][comidaY] != ' ');
		
		hayComida = 1;
	}
}

void dibujarMapa (char m[F][C], tSnake *vib) {
	int i, j;
	
	iniciarMapa (m);
	
	for (i=0; i<C; i++) {
		m[0][i] = '#';
		m[F-1][i] = '#';
	}
	for (j=0; j<F; j++) {
		m[j][0] = '#';
		m[j][C-1] = '#';
	}
	
	iniciarComida (m);
	
	Nodo *aux = vib->primero;
	int cabeza = 1;
	
    while (aux != NULL) {
        if (cabeza) m[aux->x][aux->y] = 'O';
        
        else m[aux->x][aux->y] = 'o';
        
    	cabeza = 0;
        aux = aux->sig;
    }
    
    if (hayComida) {
    m[comidaX][comidaY] = '*';
    }
}

void mostrarMapa(char m[F][C]) {
    int i, j;
	system("cls");
    for ( i=0;i<F;i++) {
        for ( j=0;j<C;j++) {
            printf("%c", m[i][j]);
        }
        printf("\n");
    }
}

void guardarPuntaje(char nombre[], int puntos) {
	tScore p;
	strcpy(p.nombre, nombre);
	p.puntos = puntos;
    FILE *f = fopen("scores.dat", "ab");
    if (!f) return;
    fwrite(&p, sizeof(tScore), 1, f);
    fclose(f);
}

void mostrarPuntajes() {
    tScore p;
    FILE *f = fopen("scores.dat", "rb");

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

void leerTeclas (char *dir){
	printf("Movimiento: w/s/a/d: ");
	scanf("%c", dir);
	fflush(stdin);
}

int movimientoJug (tSnake *vib, char dir) {
	int nX = vib->primero->x;
	int nY = vib->primero->y;
	
	if (dir == 'w' ) nX--;
	if (dir == 's' ) nX++;
	if (dir == 'a' ) nY--;
	if (dir == 'd' ) nY++;
	
	if(verifiEnd(nX, nY) == 0 || verifiBody(vib, nX, nY) == 0){
		gameOver = 0;
		return 0;
	}
	
	//Agregar Cabeza
	agregarInicio (vib, nX, nY);
	
	//¿Comio?
	if (nX == comidaX && nY == comidaY) {
		hayComida = 0;
		return 1;
	}
	
	//Eliminar Cola
	eliminarFinal (vib);
	return 0;

}

int verifiEnd (int nX, int nY) {
	if (nX < 0 || nX >= F || nY < 0 || nY >= C) return 0;
	else return 1;
}

int verifiBody (tSnake *vib, int nX, int nY) {
Nodo *aux = vib->primero;
	
	if (aux->x == nX && aux->y == nY) return 0;
}

void inicioJuego() {
    tSnake snake;
    iniciarSnake (&snake);

//Viborita inicial
    agregarFinal(&snake, 10, 10);
    agregarFinal(&snake, 10, 11);
    agregarFinal(&snake, 10, 12);

//Matriz para mapa del juego
char mapa[F][C];


    dibujarMapa(mapa, &snake);
    mostrarMapa(mapa);
    
    juego (mapa, &snake);
}

void juego (char m[F][C], tSnake *snake) {
	char nombre[30];
	char dir;
	int puntos = 0;
	
	while(!gameOver) {
		leerTeclas (&dir);
		puntos = movimientoJug (snake, dir);
		dibujarMapa (m, snake);
		mostrarMapa (m);
	}
	
	printf("****Game Over****\n");
	printf("Ingrese nombre: ");
	scanf("%s", &nombre);
	guardarPuntaje(nombre, puntos);
	
}
