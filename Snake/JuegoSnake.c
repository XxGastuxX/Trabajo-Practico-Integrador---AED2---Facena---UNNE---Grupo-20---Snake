#include <stdio.h>
#include "TADjuego.h" //Libreria del juego
#include "Score.h" //Libreria para guardar nombres y puntos en un arbol
#include "Menus.h" //Libreria para mostrar menu en ascii
#include <windows.h>

//Programa principal
int main () {
	int opcion; //Opciones 1- nueva partida 2- mostrar puntajes 3- salir
	char nombre[30]; //Nombre de jugador
	int puntos; //Puntos del juegador
	
do{
	mostrarMenu ();
	printf("\nEliga una opcion: ");
	scanf("%d", &opcion);

	switch (opcion) {
		case 1: {
			puntos = inicioJuego ();
			mostrarGameOver ();
			printf("\nEscriba un nombre: ");
			scanf("%s", &nombre);
			guardarPuntaje (nombre, puntos);
			break;
		}
		case 2: {
			tNodoArbol *ranking = cargarArbolDesdeArchivo ();
			if (ranking == NULL) {
				printf("\nNo hay puntos resitrados");
			}
			mostrarInOrden(ranking);
			sleep(3);
			break;
		}
		default: {
			printf("\nOpcion incorrecta");
			break;
		}
	}
}while (opcion != 3);

mostrarGraciasPorJugar ();
sleep(3);
mostrarCreditos ();

return 0;
}
