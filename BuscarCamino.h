#ifndef BUSCARCAMINO_H
#define BUSCARCAMINO_H

/**
* BuscarCamino
*
* @short Busca un camino libre.
* Permite determinar si hay algun camino libre para llegar a la nueva posicion y   * devolverlo.
* @author Gustavo Adolfo Ruiz, Camilo Esteban Salazar
* @version 1.0 
*/

class BuscarCamino
{
//Atributos
	private:
		static int const iTamanho=9;
		bool bAbajo;
		bool bArriba;
		bool bDerecha;
		bool bIzquierda;
		bool bSiHayCamino;
		
		int iFilaFinal;
		int iFilaInicio;
		int iFilaTransitoria;
		int iColFinal;
		int iColInicio;
		int iColTransitoria;
		
		int iptrCamino[81];
		int **iptrCopiaMatriz;
		int iTamCamino;
		int *iptrNuevoCamino;
//Metodos
	public:
		BuscarCamino();
		virtual ~BuscarCamino();
/**
* Busca un un camino libre para llegar a su destino.
*/
		virtual void buscarCamino();
/**
* Cambia un elemento de la matriz copia.
*/
		virtual void cambiarElemento(int iFila, int iColumna,int iValor);
/**
* Determina que casillas estan libres alrededor de la posicion en que se encuentre.
* @param iFila esta es la fila en la copia matriz. 
* @param iColumna esta es la columna en la copia matriz. 
*/
		virtual void casillasLibres(int iFila, int iColumna);
/**
* Le hace una copia a la matriz original.
* @param iMatriz es la direccion de la matriz.
*/
		virtual void copiarMatriz(int **iMatriz);
/**
* Crea la matriz
*/
		virtual void crearMatriz();
/**
* Determina si la posicion [iFila][iColumna] en la copia matriz esta libre.
* @param iFila esta es la fila en la copia matriz. 
* @param iColumna esta es la columna en la copia matriz. 
* @return bool que dice si esta libre o no.
*/
		virtual bool estaLibre(int iFila, int iColumna);
/**
* Guarda un elemento en el arreglo iptrNuevoCamino.
*/
		virtual void guardarElementoCamino();
/**
* Determina si la posicion [iFila][iColumna] en la copia matriz esta libre.
* @param iPosInicial esta es la posicion de donde empieza a buscar el camino. 
* @param iPosFinal esta es la posicion final del camino. 
* @param iMatriz la direccion de la matriz.
* @return bool que dice si hay camino o no.
*/
		virtual bool interactuar(int iPosInicial, int iPosFinal, int **iMatriz);
/**
* Mejora el camino ya calculado anteriormente.
* @return int* es el arreglo con el camino mejorado.
*/
		virtual int *mejorarCamino();
/**
* Decide hacia donde debe moverse.
*/
		virtual void mover(bool bPaso1,bool bPaso2,bool bPaso3,bool bPaso4,char iPaso1,char iPaso2,char iPaso3,char iPaso4,char cPaso1,char cPaso2,char cPaso3,char cPaso4);
/**
* Se devuelve en caso de no encontrar camino por esa ruta.
*/
		virtual void moverReversa();
/**
* Se mueve una sola casilla.
*/
		virtual void moverUnaCasilla();
};
#endif

