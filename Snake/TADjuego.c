#include "TADjuego.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Variables globales
int comidaX, comidaY;
int hayComida;
bool gameOver;

//Definicion de prototipos
void iniciarSnake (tSnake *vib) {
	vib->primero = NULL; //Inicio la cola
	vib->ultimo = NULL; 
	vib->longitud = 0;
}

void agregarInicio(tSnake *vib, int x, int y) { //Asigno memorio dinamica a los campos de la lista y la cola al principio
	Nodo *nuevo = (Nodo*) malloc(sizeof(Nodo));
	nuevo->x = x;
	nuevo->y = y;
	nuevo->sig = vib->primero;
	
	vib->primero = nuevo;
	if (vib->ultimo == NULL) vib->ultimo = nuevo;
	vib->longitud++;
}

void agregarFinal (tSnake *vib, int x, int y) { //Asigno memoria dinamica al final de  la cola y la lista
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

void eliminarFinal (tSnake *vib) { //Elimino un nodo al final de la cola
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

void iniciarMapa (char m[F][C]) { //Inicio el mapa poniendolo en "blanco"
	int i, j;
		for (i=0; i<F; i++){
			for (j=0; j<C; j++) {
				m[i][j] = ' ';
			}
		}

}

void iniciarComida (char m[F][C]) { //verifico y agrego comida al mapa si no hay
	if (!hayComida) {
		do {
		comidaX = rand() % F;
		comidaY = rand() % C;
		}while(m[comidaX][comidaY] != ' ');
		
		hayComida = 1;
	}
}

void dibujarMapa (char m[F][C], tSnake *vib) { //Dibujo el mapa con bordes de "#" y agrego la comida y tambien dibujo la serpiente
	int i, j;
	
	iniciarMapa (m);
	
	for (i=0; i<C; i++) {//El primer borde iria en la fila 0 y el otro en F-1 (14)
		m[0][i] = '#';
		m[F-1][i] = '#';
	}
	for (j=0; j<F; j++) {//El tercer borde iria en la columna 0 y el otro en C-1 (24)
		m[j][0] = '#';
		m[j][C-1] = '#';
	}
	
	iniciarComida (m);
	
	Nodo *aux = vib->primero;
	int cabeza = 1; //Condicional para detectar la cabeza de la serpiente
	
    while (aux != NULL) { //El cuerpo serpiente aparce en la fila 10, columna 10 y termina en la fila 10, columna 12
        if (cabeza) m[aux->x][aux->y] = 'O';
        
        else m[aux->x][aux->y] = 'o';
        
    	cabeza = 0;
        aux = aux->sig;
    }
    
    if (hayComida) {//Se agrega la comida si no hay
    m[comidaX][comidaY] = '*';
    }
}

void mostrarMapa(char m[F][C]) {//Muestro el mapa ya dibujado con la comida, los bordes y la serpiente
    int i, j;
	system("cls"); //Cls para limpiar la pantalla y solo aparezca el mapa
    for ( i=0;i<F;i++) {
        for ( j=0;j<C;j++) {
            printf("%c", m[i][j]);
        }
        printf("\n");
    }
}

void leerTeclas(char *dir) { //Leo teclas con getchar () para el movimiento de la serpiente
    printf("Movimiento: w/s/a/d: ");
    do {
        *dir = getchar();
    } while(*dir == '\n');  //salta ENTER
}


int movimientoJug (tSnake *vib, char dir) { //Cambio las coordenadas de la serpiente para que se pueda mover en el mapa y
	int nX = vib->primero->x;               //agrego una cabeza y elimino la cola para el movimiento, si la serpiente come
	int nY = vib->primero->y;               //solo agrego un nodo al principio sin eliminar al final
	
	if (dir == 'w' ) nX--;
	if (dir == 's' ) nX++;
	if (dir == 'a' ) nY--;
	if (dir == 'd' ) nY++;
	
	if(verifiEnd(nX, nY) == 0 || verifiBody(vib, nX, nY) == 0){ //Verifico la colision, si choca con los bordes del mapa
		gameOver = 1;                                           //o se choca a si misma es game over
		return 0;
	}
	
	//Agregar Cabeza
	agregarInicio (vib, nX, nY);
	
	//¿Comio?
	if (nX == comidaX && nY == comidaY) {
		hayComida = 0;
		return 5;
	}
	
	//Eliminar Cola
	eliminarFinal (vib);
	return 0;

}

int verifiEnd (int nX, int nY) {//Verificacion de colision con bordes del mapa
	if (nX == 0 || nX >= F-1 || nY == 0 || nY >= C-1) return 0;
	else return 1;
}

int verifiBody (tSnake *vib, int nX, int nY) {//Verificacion de colision con cuerpo de serpiente
Nodo *aux = vib->primero->sig;
	while (aux != NULL){
	if (aux->x == nX && aux->y == nY) return 0;
	aux = aux->sig;
	}
return 1;
}

int inicioJuego() { //Inicio el juego mostrando un mapa y una serpiente inicializada con la comida
	gameOver = 0;   //Esta funcion retornara los puntos de los jugadores
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
    
   return juego (mapa, &snake); //Esa misma serpiente, comida y mapa le mando a otra funcion donde se dará el juego
}

int juego (char m[F][C], tSnake *snake) { //En esta funcion se da el juego, retorna los puntos de los jugadores
	char dir;
	int puntos = 0;
	
	while(!gameOver) {
		leerTeclas (&dir);
		puntos += movimientoJug (snake, dir);
		dibujarMapa (m, snake);
		mostrarMapa (m);
	}

return puntos;
}

