#include "BuscarCamino.h"
#include <iostream>
using namespace std;

BuscarCamino::BuscarCamino()
{
	iptrCopiaMatriz=0;
	iptrCopiaMatriz=new int*[iTamanho];
	for (int idxFilas=0; idxFilas<iTamanho; idxFilas++)
	{
		iptrCopiaMatriz[idxFilas]=new int[iTamanho];
	}
	
	iptrNuevoCamino = 0;
	iptrNuevoCamino = new int [81];
}

BuscarCamino::~BuscarCamino()
{
	if(iptrCopiaMatriz != 0)
	{
		for (int idxFilas=0; idxFilas<iTamanho; idxFilas++)
		{
			delete []iptrCopiaMatriz[idxFilas];
		}
		delete  []iptrCopiaMatriz;
	}
	iptrCopiaMatriz=0;
	
	if(iptrNuevoCamino)
	{
		delete iptrNuevoCamino;
	}
	iptrNuevoCamino=0;
}

///Cambia el elemento en la copia de la matriz original
void BuscarCamino::cambiarElemento(int iFila, int iColumna, int iValor)
{
	iptrCopiaMatriz[iFila][iColumna]=iValor;
}

void BuscarCamino::buscarCamino()
{
	bSiHayCamino=false;
	iTamCamino=0;
	guardarElementoCamino();
	cambiarElemento(iFilaTransitoria,iColTransitoria,9);
	casillasLibres(iFilaTransitoria,iColTransitoria);
	iTamCamino++;
	
	while((bIzquierda==true || bDerecha==true || bArriba==true || bAbajo==true) && (bSiHayCamino==false))
	{
		moverUnaCasilla();
		guardarElementoCamino();
		cambiarElemento(iFilaTransitoria,iColTransitoria,9);

		if(iFilaTransitoria==iFilaFinal && iColTransitoria==iColFinal)
		{
			bSiHayCamino=true;
		}
		else
		{
			casillasLibres(iFilaTransitoria,iColTransitoria);
		}
		
		///Si esta bloqueado y no esta en la pos. inicial o en la final debe devolverse hasta hallar 1 casilla libre
		while(bIzquierda==false && bDerecha==false && bArriba==false && bAbajo==false && (iFilaTransitoria!=iFilaFinal || iColTransitoria!=iColFinal) && (iFilaTransitoria!=iFilaInicio || iColTransitoria!=iColInicio) && iTamCamino>=0)
		{
			moverReversa();
			casillasLibres(iFilaTransitoria,iColTransitoria);
		}iTamCamino++;
	}//whiles
}

///Modifica los atributos booleanos que indican si la direccion esta libre
void BuscarCamino::casillasLibres(int iFila, int iColumna)
{
	if(iFila==0 && iColumna==0)
	{
		bIzquierda=false;
		bArriba=false;
		bDerecha=estaLibre(iFila,iColumna+1);
		bAbajo=estaLibre(iFila+1,iColumna);
		return;
	}
	if(iFila==0 && iColumna==8)
	{
		bDerecha=false;
		bArriba=false;
		bIzquierda=estaLibre(iFila,iColumna-1);
		bAbajo=estaLibre(iFila+1,iColumna);
		return;
	}
	if(iFila==8 && iColumna==0)
	{
		bIzquierda=false;
		bAbajo=false;
		bDerecha=estaLibre(iFila,iColumna+1);
		bArriba=estaLibre(iFila-1,iColumna);
		return;
	}
	if(iFila==8 && iColumna==8)
	{
		bDerecha=false;
		bAbajo=false;
		bIzquierda=estaLibre(iFila,iColumna-1);
		bArriba=estaLibre(iFila-1,iColumna);
		return;
	}
	if(iFila==0)
	{
		bArriba=false;
		bAbajo=estaLibre(iFila+1,iColumna);
		bIzquierda=estaLibre(iFila,iColumna-1);
		bDerecha=estaLibre(iFila,iColumna+1);
		return;
	}
	if(iFila==8)
	{
		bAbajo=false;
		bArriba=estaLibre(iFila-1,iColumna);
		bIzquierda=estaLibre(iFila,iColumna-1);
		bDerecha=estaLibre(iFila,iColumna+1);
		return;
	}
	if(iColumna==0)
	{
		bIzquierda=false;
		bArriba=estaLibre(iFila-1,iColumna);
		bAbajo=estaLibre(iFila+1,iColumna);
		bDerecha=estaLibre(iFila,iColumna+1);
		return;
	}
	if(iColumna==8)
	{
		bDerecha=false;
		bArriba=estaLibre(iFila-1,iColumna);
		bAbajo=estaLibre(iFila+1,iColumna);
		bIzquierda=estaLibre(iFila,iColumna-1);
		return;
	}
	else
	{
		bDerecha=estaLibre(iFila,iColumna+1);
		bIzquierda=estaLibre(iFila,iColumna-1);
		bArriba=estaLibre(iFila-1,iColumna);
		bAbajo=estaLibre(iFila+1,iColumna);
		return;
	}
}

///Copia la matriz original en una nueva matriz, para poder manipular los datos sin modificar la matriz original del juego
void BuscarCamino::copiarMatriz(int **iMatriz)
{
	for (int idxFilas=0; idxFilas<iTamanho; idxFilas++)
	{
		for (int idxColumnas=0; idxColumnas<iTamanho; idxColumnas++)
		{
			iptrCopiaMatriz[idxFilas][idxColumnas]=iMatriz[idxFilas][idxColumnas];
		}
	}
}

void BuscarCamino::crearMatriz()
{
	///Inicializar el arreglo que guarda el camino
	for (int iIndice=0;iIndice<81;iIndice++)
	{
		iptrCamino[iIndice]=-1;
	}
}

bool BuscarCamino::estaLibre(int iFila, int iColumna)
{
	if(iptrCopiaMatriz[iFila][iColumna] == 0)
	{
		return true;
	}
	return false;
}

///Guarda una posici� del camino en el arreglo
void BuscarCamino::guardarElementoCamino()
{
	int iEquivalencia=0;
	iEquivalencia=(iFilaTransitoria*9)+iColTransitoria;
	iptrCamino[iTamCamino]=iEquivalencia;
}


int *BuscarCamino::mejorarCamino()
{
	int iElemento1=0;
	int iElemento2=0;
	
	///Inicializar el iptrNuevoCamino arreglo en -1
	for(int i=0;i<81;i++)
	{
		iptrNuevoCamino[i]=-1;
	}
	
	for(int iIndiceEle2 = (iTamCamino-1);iIndiceEle2 > 0;iIndiceEle2 --)
	{
		int indiceNuevo=0;
		iElemento2 = iptrCamino[iIndiceEle2];
		
		for(int iIndiceEle1 = 0;iIndiceEle1 < (iIndiceEle2);iIndiceEle1 ++)
		{
			iElemento1=iptrCamino[iIndiceEle1];

			if((((iElemento2-1)==iElemento1) || ((iElemento2+1)==iElemento1) || ((iElemento2-9)==iElemento1) || ((iElemento2+9)==iElemento1)) && ((iElemento2/9==iElemento1/9) || (iElemento2%9 == iElemento1%9))&&(iElemento1>-1 && iElemento2>-1))
			{
				iptrNuevoCamino[indiceNuevo]=iElemento1;
				indiceNuevo++;
				
				for(int i=iIndiceEle2;i<iTamCamino;i++)
				{
					iptrNuevoCamino[indiceNuevo]=iptrCamino[i];
					indiceNuevo++;
				}
				int tam=0;
				tam=iIndiceEle1+(iTamCamino-iIndiceEle2)+1;
				iTamCamino=tam;

				for(int i=iTamCamino;i<81;i++)
				{
					iptrNuevoCamino[indiceNuevo]=-1;
					indiceNuevo++;
				}
				iIndiceEle1=81;
			}
			else
			{
				iptrNuevoCamino[indiceNuevo]=iElemento1;
				indiceNuevo++;
			}
		}
		///Pasar el camino igual o mejorado
		for(int i=0;i<81;i++)
		{
			iptrCamino[i]=iptrNuevoCamino[i];
		}
	}
	return iptrCamino;
}


///Busca el camino partiendo de las casillas libres halladas en casillasLibres
void BuscarCamino::mover(bool bPaso1,bool bPaso2,bool bPaso3,bool bPaso4,
			char cOpPaso1,char cOpPaso2,char cOpPaso3,char cOpPaso4,
			char cPaso1,char cPaso2,char cPaso3,char cPaso4)
{
	if(bPaso1==true)
	{
		if (cOpPaso1=='+')
		{
			if(cPaso1=='F')
			{
				iFilaTransitoria++;
			}
			else
			{
				iColTransitoria++;
			}
		}
		else
		{
			if(cPaso1=='F')
			{
				iFilaTransitoria--;
			}
			else
			{
				iColTransitoria--;
			}
		}
		return;
	}
	
	if(bPaso2==true)
	{
		if (cOpPaso2=='+')
		{
			if(cPaso2=='F')
			{
				iFilaTransitoria++;
			}
			else
			{
				iColTransitoria++;
			}
		}
		else
		{
			if(cPaso2=='F')
			{
				iFilaTransitoria--;
			}
			else
			{
				iColTransitoria--;
			}
		}
		return;
	}
	if(bPaso3==true)
	{
		if (cOpPaso3=='+')
		{
			if(cPaso3=='F')
			{
				iFilaTransitoria++;
			}
			else
			{
				iColTransitoria++;
			}
		}
		else
		{
			if(cPaso3=='F')
			{
				iFilaTransitoria--;
			}
			else
			{
				iColTransitoria--;
			}
		}
		return;
	}
	if(bPaso4==true)
	{
		if (cOpPaso4=='+')
		{
			if(cPaso4=='F')
			{
				iFilaTransitoria++;
			}
			else
			{
				iColTransitoria++;
			}
		}
		else
		{
			if(cPaso4=='F')
			{
				iFilaTransitoria--;
			}
			else
			{
				iColTransitoria--;
			}
		}
		return;
	}
}

///Devuelve a una posicion anterior
void BuscarCamino::moverReversa()
{
	cambiarElemento(iFilaTransitoria,iColTransitoria,5);
	iTamCamino--;
	iFilaTransitoria=(iptrCamino[iTamCamino])/9;
	iColTransitoria=(iptrCamino[iTamCamino])%9;
}

///Da las pautas para hacer la movida
void BuscarCamino::moverUnaCasilla()
{
	bool bHecho=false;
	
	if (iFilaTransitoria==iFilaFinal)
	{
		if(iColTransitoria<iColFinal)
		{
			mover(bDerecha,bArriba,bAbajo,bIzquierda,'+','-','+','-','C','F','F','C');
		}
		else
		{
			mover(bIzquierda,bArriba,bAbajo,bDerecha,'-','-','+','+','C','F','F','C');
		}
		bHecho=true;
	}
	if(iColTransitoria==iColFinal && bHecho==false)
	{
		if(iFilaTransitoria<iFilaFinal)
		{
			mover(bAbajo,bDerecha,bIzquierda,bArriba,'+','+','-','-','F','C','C','F');
		}
		else
		{
			mover(bArriba,bIzquierda,bDerecha,bAbajo,'-','-','+','+','F','C','C','F');
		}
		bHecho=true;
	}
	if(iFilaTransitoria<iFilaFinal && bHecho==false)
	{
		if(iColTransitoria<iColFinal)
		{
			mover(bAbajo,bDerecha,bIzquierda,bArriba,'+','+','-','-','F','C','C','F');
		}
		else
		{
			mover(bAbajo,bIzquierda,bDerecha,bArriba,'+','-','+','-','F','C','C','F');
		}
		bHecho=true;
	}
	if(iFilaTransitoria>iFilaFinal && bHecho==false)
	{
		if(iColTransitoria<iColFinal)
		{
			mover(bArriba,bDerecha,bIzquierda,bAbajo,'-','+','-','+','F','C','C','F');
		}
		else
		{
			mover(bArriba,bIzquierda,bDerecha,bAbajo,'-','-','+','+','F','C','C','F');
		}
	}
}

bool BuscarCamino::interactuar(int iPosInicial, int iPosFinal, int **iMatriz)
{
	bool hayCamino=false;
	iFilaInicio=iPosInicial/9;
	iColInicio=iPosInicial%9;
	iFilaFinal=iPosFinal/9;
	iColFinal=iPosFinal%9;
	iFilaTransitoria=iFilaInicio;
	iColTransitoria=iColInicio;
	copiarMatriz(iMatriz);
	buscarCamino();
	hayCamino=bSiHayCamino;
	return hayCamino;
}
