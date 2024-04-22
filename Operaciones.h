#ifndef OPERACIONES_H
#define OPERACIONES_H

#include "Matriz.h"
#include "BuscarCamino.h"
#include "Alineacion.h"
#include "ArchivoJuego.h"

/**
* Operaciones
*
* @short Se comunica con varias clases para permitir el correcto     	       funcionamiento de la aplicacion.
* Esta clase se encarga de pasar los parametros a otras clases y             * devolverselos a la ventana.
* @author Gustavo Adolfo Ruiz, Camilo Esteban Salazar
* @version 1.0 
*/

class Operaciones
{
//Atributos
	private:
		Alineacion *ptrObjAlineacion;
		ArchivoJuego *ptrObjArchivoJuego;
		BuscarCamino *ptrObjBuscarCamino;
		Matriz *ptrObjMatrizPrincipal;
		
		static int const iTamano=9;
		static int const iNumFichas=7;
		
		int iPosInicio;
		int iPosFin;
		
		int **iDirMatriz;
		int *iptrAlineacion;
		int *iptrCamino;
		int *iptrFicha;
		int *iptrPosAleatoria;
//Metodos
	public:
		Operaciones();
		virtual ~Operaciones();
/**
* Genera tres fichas aleatorias y las introduce en un arreglo.
* @return int* arreglo con las tres fichas aleatorias.
*/
		virtual int *aleatorioFicha();
/**
* Genera tres posiciones aleatorias y las introduce en un arreglo.
* @param iCasillasOcupadas el numero de casillas ocupadas en la matriz.
* @return int* arreglo con las tres posiciones aleatorios.
*/
		virtual int *aleatorioPosicion(int iCasillasOcupadas);
/**
* Busca alineacion.
* @param iPosFinal esta es la fila en la matriz.
* @param iFicha esta es la columna en la matriz.
* @return int* devuelve las casillas a eliminar dentro de un arreglo.
*/
		virtual int *buscarAlineacion(int iPosFinal,int iFicha);
/**
* Busca el camino desde la posicion inicila hasta la final.
* @param iPosIncial primera posicion en el camino.
* @param iPosFinal ultima posicion en el camino.
* @return bool indica si hay camino o no.
*/
		virtual bool buscarCamino(int iPosIncial, int iPosFinal);
/**
* Cambia un elemento en la matriz.
* @param iPosIncial primera posicion.
* @param iPosFinal ultima posicion.
*/
		virtual void cambiarFicha(int iPosicion, int iValor);
/**
* Carga un juego previamente guardado.
* @return int este es el puntaje de la partida guardada.
*/
		virtual int cargarJuego();
/**
* Consulta un elemento en la matriz.
* @param iFila primera posicion.
* @param iColumna ultima posicion.
* @return int este es el valor de la ficha consultada.
*/
		virtual int consultarFicha(int iFila, int iColumna);
/**
* Calcula el camino de la posicion inicial a la final.
* @return int* arreglo con el camino libre de la posicion inicial a la final.
*/
		virtual int *devolverCamino();
/**
* Determina si una casilla esta libre.
* @param iFila fila en la matriz.
* @param iColumna columna en la matriz.
* @return bool indica si la casilla esta libre.
*/
		virtual bool estaLibre(int iFila, int iColumna);
/**
* Genera un valor aleatorio entre 1 y 7.
* @param iUmbral el valor para generar el aleatorio.
* @return int es el valor aleatorio generado.
*/
		virtual int generarValorAleatorio(int iUmbral);
/**
* Crea un juego nuevo
*/
		virtual void juegoNuevo();
/**
* Guarda el juego actual.
* @param iPuntaje puntaje actual.
*/
		virtual void salvarJuego(int iPuntaje);
};
#endif

