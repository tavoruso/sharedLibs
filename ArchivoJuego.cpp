#include "ArchivoJuego.h"

ArchivoJuego::ArchivoJuego()
{
	ptrNombreArchivo = "UltimoJuego.txt";
}

ArchivoJuego::~ArchivoJuego()
{
	
}

///Crea el archivo con el nombre
void ArchivoJuego::crearArchivo(int iPuntaje,int iFilas,int iColumnas,int **iMatrizOriginal)
{
	int iEspacio=5;
	ofstream archivoOut;
	archivoOut.open(ptrNombreArchivo, ios::out);
	
	///Crea el archivo primero con el tamano de la matriz, luego el puntaje y posteriormente los elementos de la matriz principal
	archivoOut<<setw(iEspacio)<<iPuntaje<<endl;
	archivoOut<<setw(iEspacio)<<iFilas<<setw(iEspacio)<<iColumnas<<endl;
	
	for(int idxFilas=0; idxFilas<iFilas; idxFilas++)
	{
		for(int idxColumnas=0; idxColumnas<iColumnas; idxColumnas++)
		{
			archivoOut<<setw(iEspacio)<<iMatrizOriginal[idxFilas][idxColumnas];
		}
		archivoOut<<endl;
	}
	archivoOut.close();
}

int ArchivoJuego::leerArchivo(int **iMatrizOriginal)
{
	int iPuntaje=0;
	int iFilas=0;
	int iColumnas=0;
	
	ifstream archivoIn;
	archivoIn.open(ptrNombreArchivo,ios::in);
	
	archivoIn>>iPuntaje;
	archivoIn>>iFilas;
	archivoIn>>iColumnas;

	for(int idxFilas=0; idxFilas<iFilas; idxFilas++)
	{
		for(int idxColumnas=0; idxColumnas<iColumnas; idxColumnas++)
		{
			archivoIn>>iMatrizOriginal[idxFilas][idxColumnas];
		}
	}
	archivoIn.close();
	return iPuntaje;
}
