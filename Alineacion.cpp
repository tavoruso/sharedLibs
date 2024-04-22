#include "Alineacion.h"

Alineacion::Alineacion()
{
	iptrAlineacion=0;
	iptrAlineacion = new int[36];
	iContadorFichas=0;
}

Alineacion::~Alineacion()
{
	if(iptrAlineacion != 0)
	{
		delete [] iptrAlineacion;
		iptrAlineacion = 0;
	}
}

int *Alineacion::buscarAlineacion(int iPosicionInicial, int iFicha,int   **iMatrizOriginal)
{
	iPosInicial=iPosicionInicial;
	iFichaBuscada=iFicha;
	///Inicializar iptrAlineacion para introducir las nueevas posiciones de la alineacion
	for(int iCol=0;iCol < 36; iCol++)
	{
		iptrAlineacion[iCol]= -1;
	}

	iContadorFichas=0;	
	vertical(iMatrizOriginal);
	horizontal(iMatrizOriginal);
	diagonalIzqDer(iMatrizOriginal);
	diagonalDerIzq(iMatrizOriginal);
	return iptrAlineacion;
}

void Alineacion::diagonalDerIzq(int **iMatrizOriginal)
{
	int iPosInicioNuevo=iPosInicial;
	int iPosFinalNuevo=iPosInicial;
	int iColumna=0;
	int iFila=0;
	int iSeguirEn=0;
	int iFichasDiaDerIzq=0;
	bool bSeguir=true;
	
	iSeguirEn = iContadorFichas;
	
	iFila=iPosInicioNuevo/9;
	iColumna=iPosInicioNuevo%9;
	iFila--;
	iColumna++;
	
	while((iColumna >= 0) && (iFila >= 0) && bSeguir)
	{
		if(iMatrizOriginal[iFila][iColumna] == iFichaBuscada)
		{
			iPosInicioNuevo = iPosInicioNuevo - 8;
			iFichasDiaDerIzq++;
		}
		else
		{
			bSeguir=false;
		}
		iColumna++;
		iFila--;
	}
	
	bSeguir=true;
	iColumna=iPosInicial%9;
	iColumna--;
	iFila=iPosInicial/9;
	iFila++;
	while((iColumna < 9) && (iFila < 9) && bSeguir)
	{
		if(iMatrizOriginal[iFila][iColumna] == iFichaBuscada)
		{
			iPosFinalNuevo=iPosFinalNuevo+8;
			iFichasDiaDerIzq++;
		}
		else
		{
			bSeguir=false;
		}
		iColumna--;
		iFila++;
	}
	
	///Llenar el arreglo con las casillas que se van a eliminar;
	if(iFichasDiaDerIzq >= 4)
	{
		iContadorFichas += (iFichasDiaDerIzq + 1);
		iptrAlineacion[iSeguirEn]=iPosInicioNuevo;
		for(int iCol=iSeguirEn+1;iPosInicioNuevo != iPosFinalNuevo;iCol++)
		{
			iptrAlineacion[iCol]=iPosInicioNuevo+8;
			iPosInicioNuevo+=8;
		}
	}

}

void Alineacion::diagonalIzqDer(int **iMatrizOriginal)
{
	int iPosInicioNuevo=iPosInicial;
	int iPosFinalNuevo=iPosInicial;
	int iColumna=0;
	int iFila=0;
	int iSeguirEn=0;
	int iFichasDiaIzqDer=0;
	bool bSeguir=true;
	
	iSeguirEn=iContadorFichas;
	iFila=iPosInicioNuevo/9;
	iColumna=iPosInicioNuevo%9;
	iFila--;
	iColumna--;
	
	while((iColumna >= 0) && (iFila >= 0) && bSeguir)
	{
		if(iMatrizOriginal[iFila][iColumna] == iFichaBuscada)
		{
			iPosInicioNuevo=iPosInicioNuevo-10;
			iFichasDiaIzqDer++;
		}
		else
		{
			bSeguir=false;
		}
		iColumna--;
		iFila--;
	}
	
	bSeguir=true;
	iColumna=iPosInicial%9;
	iColumna++;
	iFila=iPosInicial/9;
	iFila++;
	while((iColumna < 9) && (iFila < 9) && bSeguir)
	{
		if(iMatrizOriginal[iFila][iColumna] == iFichaBuscada)
		{
			iPosFinalNuevo=iPosFinalNuevo+10;
			iFichasDiaIzqDer++;
		}
		else
		{
			bSeguir=false;
		}
		iColumna++;
		iFila++;
	}
	
	///Llenar el arreglo con las casillas que se van a eliminar;
	if(iFichasDiaIzqDer >= 4)
	{
		iContadorFichas += (iFichasDiaIzqDer + 1);
		iptrAlineacion[iSeguirEn]=iPosInicioNuevo;
		for(int iCol = iSeguirEn+1;iPosInicioNuevo != iPosFinalNuevo;iCol++)
		{
			iptrAlineacion[iCol]=iPosInicioNuevo+10;
			iPosInicioNuevo+=10;
		}
	}

}

void Alineacion::horizontal(int **iMatrizOriginal)
{
	int iPosInicioNuevo=iPosInicial;
	int iPosFinalNuevo=iPosInicial;
	int iColumna=0;
	int iSeguirEn=0;
	int iFichasHorizontales=0;
	bool bSeguir=true;

	iSeguirEn = iContadorFichas;
	iColumna = iPosInicioNuevo%9;
	iColumna --;
	
	while((iColumna >= 0) && bSeguir)
	{
		if(iMatrizOriginal[iPosInicioNuevo/9][iColumna] == iFichaBuscada)
		{
			iPosInicioNuevo=iPosInicioNuevo - 1;
			iFichasHorizontales ++;
		}
		else
		{
			bSeguir=false;
		}
		iColumna --;
	}

	iColumna = iPosInicial%9;
	bSeguir = true;
	iColumna ++;
	while((iColumna < 9) && bSeguir)
	{
		if(iMatrizOriginal[iPosInicioNuevo/9][iColumna] == iFichaBuscada)
		{
			iPosFinalNuevo=iPosFinalNuevo+1;
			iFichasHorizontales++;
		}
		else
		{
			bSeguir=false;
		}
		iColumna ++;
	}
	
	if(iFichasHorizontales >= 4)
	{
		iContadorFichas += (iFichasHorizontales+1);
		iptrAlineacion[iSeguirEn] = iPosInicioNuevo;
		for(int iCol=(iSeguirEn+1);iPosInicioNuevo != iPosFinalNuevo;iCol++)
		{
			iptrAlineacion[iCol] = iPosInicioNuevo+1;
			iPosInicioNuevo ++;
		}
	}
}

void Alineacion::vertical(int **iMatrizOriginal)
{
	int iPosInicioNuevo = iPosInicial;
	int iPosFinalNuevo = iPosInicial;
	int iFila=0;
	int iFichasVerticales=0;
	bool bSeguir=true;
	

	iFila = iPosInicioNuevo/9;
	iFila--;
	
	while((iFila >= 0) && bSeguir)
	{
		if(iMatrizOriginal[iFila][iPosInicioNuevo%9] == iFichaBuscada)
		{
			iPosInicioNuevo -= 9;
			iFichasVerticales ++;
		}
		else
		{
			bSeguir=false;
		}
		iFila --;
	}

	iFila = iPosInicial/9;
	bSeguir = true;
	iFila ++;
	while((iFila < 9) && bSeguir)
	{
		if(iMatrizOriginal[iFila][iPosFinalNuevo%9] == iFichaBuscada)
		{
			iPosFinalNuevo=iPosFinalNuevo+9;
			iFichasVerticales++;
		}
		else
		{
			bSeguir=false;
		}
		iFila++;
	}
	
	
	if(iFichasVerticales >= 4)
	{
		iContadorFichas += (iFichasVerticales + 1);
		///Se encarga de llenar el iptrAlineacion si hay una alineacion de 5 o mas fichas iguales
		iptrAlineacion[0]= iPosInicioNuevo;
		for(int iCol=1;iPosInicioNuevo != iPosFinalNuevo;iCol++)
		{
			iptrAlineacion[iCol]=iPosInicioNuevo+9;
			iPosInicioNuevo+=9;
		}
	}
}
