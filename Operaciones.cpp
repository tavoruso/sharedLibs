#include "Operaciones.h"

Operaciones::Operaciones()
{
	srand(time(0));
	ptrObjMatrizPrincipal=0;
	ptrObjMatrizPrincipal=new Matriz();
	iDirMatriz=0;

	iptrCamino=0;
	iptrCamino=new int [81];
	iptrFicha=0;
	iptrFicha=new int [3];
	iptrPosAleatoria=0;
	iptrPosAleatoria=new int [3];
	ptrObjBuscarCamino=0;
	ptrObjBuscarCamino=new BuscarCamino();
	ptrObjAlineacion=0;
	ptrObjAlineacion = new Alineacion();
	iptrAlineacion=0;
	iptrAlineacion = new int [36];
	ptrObjArchivoJuego=0;
	ptrObjArchivoJuego= new ArchivoJuego;
	iDirMatriz=ptrObjMatrizPrincipal->crearMatriz(iTamano,iTamano);
}

Operaciones::~Operaciones()
{
	if (ptrObjArchivoJuego != 0)
	{
		delete ptrObjArchivoJuego;
		ptrObjArchivoJuego=0;
	}
	if (ptrObjBuscarCamino != 0)
	{
		delete ptrObjBuscarCamino;
		ptrObjBuscarCamino=0;
	}
	if (iptrFicha != 0)
	{
		delete [] iptrFicha;
		iptrFicha=0;
	}
	if (iptrPosAleatoria != 0)
	{
		delete [] iptrPosAleatoria;
		iptrPosAleatoria=0;
	}
	if (ptrObjAlineacion != 0)
	{
		iptrAlineacion=0;
		iptrCamino=0;
		delete [] iptrCamino;
		iptrCamino=0;
		delete [] iptrAlineacion;
		iptrAlineacion=0;
		delete ptrObjAlineacion;
		ptrObjAlineacion=0;
	}
	if (ptrObjMatrizPrincipal != 0)
	{
		delete ptrObjMatrizPrincipal;
		ptrObjMatrizPrincipal=0;
	}
}

int *Operaciones::aleatorioFicha()
{
	int iFigura=0;

	for (int idxColumnas=0; idxColumnas<3; idxColumnas++)
	{
		iptrFicha[idxColumnas]=0;
	}
	
	for(int iVeces=0;iVeces<3;iVeces++)
	{
		iFigura=generarValorAleatorio(iNumFichas)+1;
		iptrFicha[iVeces] = iFigura;
	}
	return iptrFicha;
}

int *Operaciones::aleatorioPosicion(int iCasillasOcupadas)
{
	int iVeces=0;
	int iFilaAleatoria=0;
	int iColAleatoria=0;

	for (int idxColumnas=0; idxColumnas<3; idxColumnas++)
	{
		iptrPosAleatoria[idxColumnas]=-1;
	}
	
	while (iVeces<3 && ( iCasillasOcupadas < (iTamano*iTamano)))
	{
		int iPosAleatoria=0;
		iFilaAleatoria=generarValorAleatorio(iTamano);
		iColAleatoria=generarValorAleatorio(iTamano);
		iPosAleatoria=(iFilaAleatoria*iTamano)+iColAleatoria;
		
		if(iVeces==0 && (ptrObjMatrizPrincipal->estaLibre(iFilaAleatoria,iColAleatoria)))
		{
			iptrPosAleatoria[iVeces] =iPosAleatoria;
			iVeces++;
			iCasillasOcupadas++;
		}
		else
		{
		
			if((ptrObjMatrizPrincipal->estaLibre(iFilaAleatoria,iColAleatoria)) && (iptrPosAleatoria[0] != iPosAleatoria)&&(iptrPosAleatoria[1] != iPosAleatoria))
			{
				iptrPosAleatoria[iVeces] =iPosAleatoria;
				iVeces++;
				iCasillasOcupadas++;
			}
		}
	}
	return iptrPosAleatoria;
}

int *Operaciones::buscarAlineacion(int iPosFinal,int iFicha)
{
	iptrAlineacion=ptrObjAlineacion->buscarAlineacion(iPosFinal,iFicha, iDirMatriz);
	return iptrAlineacion;
}

bool Operaciones::buscarCamino(int iPosInicial,int iPosFinal)
{
	bool bSiHayCamino=false;
	iPosInicio=iPosInicial;
	iPosFin=iPosFinal;
	bSiHayCamino=ptrObjBuscarCamino->interactuar(iPosInicio,iPosFin,iDirMatriz);
	return bSiHayCamino;
}

void Operaciones::cambiarFicha(int iPosicion,int iValor)
{
	int iFila=0;
	int iColumna=0;
	iFila=iPosicion/9;
	iColumna=iPosicion%9;
	ptrObjMatrizPrincipal->cambiarElemento(iFila, iColumna, iValor);
}

int Operaciones::cargarJuego()
{
	return ptrObjArchivoJuego->leerArchivo(iDirMatriz);
}

int Operaciones::consultarFicha(int iFila, int iColumna)
{
	return ptrObjMatrizPrincipal->consultarFicha(iFila, iColumna);
}

// void Operaciones::crearJuego()
// {
// // 	iDirMatriz=ptrObjMatrizPrincipal->crearMatriz(iTamano,iTamano);
// 	ptrObjMatrizPrincipal->inicializarMatriz(iTamano,iTamano);
// }

int *Operaciones::devolverCamino()
{
	iptrCamino=ptrObjBuscarCamino->mejorarCamino();
	return iptrCamino;
}

bool Operaciones::estaLibre(int iFila, int iColumna)
{
	return ptrObjMatrizPrincipal->estaLibre(iFila,iColumna);
}

int Operaciones::generarValorAleatorio(int iUmbral)
{
	return rand()%(iUmbral);
}

void Operaciones::juegoNuevo()
{
	ptrObjMatrizPrincipal->inicializarMatriz(iTamano,iTamano);
}

void Operaciones::salvarJuego(int iPuntaje)
{
	ptrObjArchivoJuego->crearArchivo(iPuntaje,iTamano,iTamano,iDirMatriz);
}
