#ifndef ALINEACION_H
#define ALINEACION_H

/**
* Alineacion
*
* @short Clase que determina si hay alguna alineacion.
* <ul> 
* <li> Esta clase contiene cinco metodos que permiten:
* <li> Devolver la alineacion a eliminar.
* <li> Determinar si hay alineacion vertical.
* <li> Determinar si hay alineacion horizontal.
* <li> Dos metodos que determinan si hay alineacion diagonal.
* </ul>
* @author Gustavo Adolfo Ruiz, Camilo Esteban Salazar
* @version 1.0 
*/

class Alineacion
{
//Atributos
	private:
		int iContadorFichas;
		int iFichaBuscada;
		int iPosInicial;
		int *iptrAlineacion;
//Metodos		
	public:
		Alineacion();
		virtual ~Alineacion();
/**
* Devuelve el atributo iptrAlineacion (arreglo unidimensional con 36 posiciones)
* @return  int* cuyo valor corresponde al arreglo de las posiciones que se van a eliminar.. 
*/
		virtual int *buscarAlineacion(int iPosicionInicial, int iFicha, int  **iMatrizOriginal);
/**
* Modifica el atributo iptrAlineacion en caso de que encuentre alineacion diagonal de derecha a izquierda.
* @param iMatrizOriginal es la direccion de la matriz original. 
*/
		virtual void diagonalDerIzq(int **iMatrizOriginal);
/**
* Modifica el atributo iptrAlineacion en caso de que encuentre alineacion diagonal de izquierda a derecha.
* @param iMatrizOriginal es la direccion de la matriz original. 
*/
		virtual void diagonalIzqDer(int **iMatrizOriginal);
/**
* Modifica el atributo iptrAlineacion en caso de que encuentre alineacion horizontal.
* @param iMatrizOriginal es la direccion de la matriz original. 
*/
		virtual void horizontal(int **iMatrizOriginal);
/**
* Modifica el atributo iptrAlineacion en caso de que encuentre alineacion vertical.
* @param iMatrizOriginal es la direccion de la matriz original. 
*/
		virtual void vertical(int **iMatrizOriginal);
};
#endif
