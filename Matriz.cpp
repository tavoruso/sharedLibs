#include "Matriz.h"

Matriz::Matriz ()
{
	iFila=0;
	iColumna=0;
	iFigura=0;
}

Matriz::~Matriz()
{
	if (iMatriz != 0)
	{
		for (int idxFilas=0; idxFilas<iFila; idxFilas++)
		{
			delete []iMatriz[idxFilas];
		}
		delete  []iMatriz;
	}
	iMatriz=0;
}

void Matriz::cambiarElemento(int iFila, int iColumna,int iValor)
{
	iMatriz[iFila][iColumna]=iValor;
}

int Matriz::consultarFicha(int iFila, int iColumna)
{
	return iMatriz[iFila][iColumna];
}

int **Matriz::crearMatriz(int iFilas, int iColumnas)
{
	iFila=iFilas;
	iColumna=iColumnas;
	iMatriz=new int*[iFilas];
	
	for (int idxFilas=0; idxFilas<iFilas; idxFilas++)
	{
		iMatriz[idxFilas]=new int[iColumnas];
	}
	return iMatriz;
}

bool Matriz::estaLibre(int iFila, int iColumna)
{
	if(iMatriz[iFila][iColumna] == 0)
	{
		return true;
	}
	return false;
}

void Matriz::inicializarMatriz(int iFilas, int iColumnas)
{
	for (int idxFilas=0; idxFilas<iFilas; idxFilas++)
	{
		for (int idxColumnas=0; idxColumnas<iColumnas; idxColumnas++)
		{
			iMatriz[idxFilas][idxColumnas]=0;
		}
	}
}
