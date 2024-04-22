#ifndef CINCOHUEVITOSGUI_H
#define CINCOHUEVITOSGUI_H

#include <qframe.h>
#include <qapplication.h>
#include <qpushbutton.h>
#include <qfont.h>
#include <qwidget.h>
#include <qlayout.h>
#include <qlabel.h>
#include <qstring.h>
#include <qcolor.h>
#include <qmenubar.h>
#include <qpopupmenu.h>
#include <qaction.h>
#include <qmessagebox.h>
#include <qtimer.h>


#include "Operaciones.h"


/**
* CincoHuevitosGUI
*
* @short Crea la interfaz grafica.
* Permite crear la ventana e interactuar con la clase Operaciones.
* @author Gustavo Adolfo Ruiz, Camilo Esteban Salazar
* @version 1.0 
*/

class CincoHuevitosGUI : public QWidget {
	Q_OBJECT
	private:
		///puntero 
		Operaciones *ptrOperaciones;
		///Grilla
		QGridLayout *ptrGrilla;
		///Menu
		QMenuBar *MenuBar;
		QPopupMenu *menuArchivo;
		QPopupMenu *menuAyuda;
		///Elementos del Menu
		QAction *nuevoJuegoAccion;
   		QAction *abrirJuegoAccion;
   		QAction *guardarJuegoAccion;
		QAction *salirJuegoAccion;
		QAction *comoJugarAccion;
   		QAction *acercaDeAccion;
		///Botones casillas
		QPushButton *ptrBotCasilla[9][9];
		///Etiquetas de informacion al usuario
		QLabel *ptrEtiqTexto;
		QLabel *etiqPuntuacion;
		QLabel *etiqPuntaje;
		QLabel *etiqFichaSig[3];
		///Contador de tiempo
		QTimer*  ptrInternalTimer ;
		QTimer*  ptrTimerBorrar ;
		///Filas y columnas
		int iFila;
		int iColumna;
		int contador;
		int iPosInicial;
		int iPosFinal;
		int iContadorBoton;
		int iPuntajeTotal;
		int *ptrCaminoEncontrado;
		bool bClickInicial;
		bool bClickFinal;
		///Arreglo nombre de Figuras
		QString *ptrNomFiguras;
		QString *ptrDirImagenes;
		
		int *iptrFigAleatorias;
		int *iptrPosAleatorias;
		int iCasillasOcupadas;
		int *iptrBorrarFiguras;

	public:
		CincoHuevitosGUI(QWidget *ptr_QWidgetPadre=0,const char *ptr_NombreQWidget=0);
		virtual ~CincoHuevitosGUI();
		
		virtual void acomodarControles();
		virtual void borrarFiguras();
		virtual void conectarControles();
		virtual void crearJuego();
		virtual void inicializarControles();
		virtual void insertarFicha();
		virtual void inicializarMenu();
		virtual void fichaSiguiente();
		virtual void nombrarFiguras();
		
	public slots:
		virtual void abrirJuego();
		virtual void acercaDe();
		virtual void botonPresionado();
		virtual void borrar();
		virtual void comoJugar();
		virtual void guardarJuego();
		virtual void moverFicha();
		virtual void nuevoJuego();
};
#endif
