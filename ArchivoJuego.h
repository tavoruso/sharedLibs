#ifndef ARCHIVOJUEGO_H
#define ARCHIVOJUEGO_H

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using std::endl;
using std::string;
using std::ofstream;
using std::ifstream;
using std::setw;
using std::ios;
/**
* ArchivoJuego
*
* @short Crea o lee un archivo.
* Permite crear un archivo *.txt y despues leerlo.
* @author Gustavo Adolfo Ruiz, Camilo Esteban Salazar
* @version 1.0 
*/
class ArchivoJuego
{
//Atributos
	private:
		char *ptrNombreArchivo;
//Metodos
	public:
		ArchivoJuego();
		virtual ~ArchivoJuego();
/**
* Este metodo guarda el juego en un archivo.txt 
* @param iFilas estas son las filas de la matriz
* @param iColumnas estas son las columnas de la matriz.
* @param iMatrizOriginal esta es la direccion de la matriz original.
*/
		virtual void crearArchivo(int iPuntaje,int iFilas,int iColumnas,int **iMatrizOriginal);
/**
* Lee un archivo *.txt previamente guardado.
* @param iMatrizOriginal es la direccion de la matriz original. 
*/
		virtual int leerArchivo(int **iMatrizOriginal);
};
#endif
