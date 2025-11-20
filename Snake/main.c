#include <stdio.h>
#include <stdlib.h>
#include <windows.h> //Para sleep()
#include "TADjuego.h" //Libreria del juego
#include "Menus.h" //Libreria para mostrar menu en ascii art
#include "Score.h" //Libreria para guardar nombres y puntos en un arbol

//Programa principal
int main() {

    int opcion; //Opciones 1- nueva partida 2- mostrar puntajes 3- salir
    char nombre[30]; //Nombre de jugador
    int puntos; //Puntos del juegador

    do {
        mostrarMenu();
        printf("\nElija una opcion: ");
        scanf("%d", &opcion);

        switch(opcion) {

            case 1: {
                puntos = inicioJuego();
                mostrarGameOver();

                printf("\nIngrese su nombre: ");
                scanf("%s", nombre);

                guardarPuntaje(nombre, puntos);
                break;
            }

            case 2: {
                tNodoArbol *ranking = cargarArbolDesdeArchivo();

                if (ranking == NULL) {
                    printf("\nNo hay puntajes registrados.\n");
                } else {
                    mostrarInOrden(ranking);
                }

                Sleep(3000);
                break;
            }

            default: {
             printf("\nOpcion incorrecta.\n");
         	}
    	}

    } while(opcion != 3);

    mostrarGraciasPorJugar();
 	Sleep(4000);
    mostrarCreditos();
	Sleep(3000);

    return 0;
}


