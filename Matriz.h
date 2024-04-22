#ifndef MATRIZ_H
#define MATRIZ_H

#include <iostream>
using namespace std;

/**
* Matriz
*
* @short Crea la matriz inicial.
* Permite crear la matriz, consultar y cambiar posiciones en ella.
* @author Gustavo Adolfo Ruiz, Camilo Esteban Salazar
* @version 1.0 
*/

class Matriz
{
//Atributos
	private:
		int iColumna;
		int iContador;
		int iFigura;
		int iFila;
		int **iMatriz;
//Metodos
	public:
		Matriz ();
		virtual ~Matriz();
/**
* Cambia un elemento en la matriz.
* @param iFila esta es la fila en la matriz.
* @param iColumna esta es la columna en la matriz.
* @param iValor elemento a intrducir en la matriz.
*/
		virtual void cambiarElemento(int iFila, int iColumna,int iValor);
/**
* Mira que elemento hay en la matriz en iFila,iColumna.
* @param iFila fila de la matriz.
* @param iColumna columna de la matriz.
* @return int es la ficha que se encuentra en esa posicion en la matriz.
*/
		virtual int consultarFicha(int iFila, int iColumna);
/**
* Crea una matriz con iFilas x iColumnas
* @param iFilas cantidad de filas de la matriz.
* @param iColumnas cantidad de columnas en la matriz.
* @return int** la matriz creada.
*/
		virtual int **crearMatriz(int iFilas, int iColumnas);
/**
* Determina si esta libre esa casilla.
* @param iFila fila en la matriz.
* @param iColumna columna en la matriz.
* @return bool indica si la casilla esta libre o no.
*/
		virtual bool estaLibre(int iFila, int iColumna);
/**
* Inicializa todas las casillas de la matriz en cero.
* @param iFilas numero de filas de la matriz.
* @param iColumnas numero de columnas de la matriz.
*/
		virtual void inicializarMatriz(int iFilas, int iColumnas);
};
#endif


