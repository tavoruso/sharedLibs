#include "CincoHuevitosGUI.h"

CincoHuevitosGUI::CincoHuevitosGUI(QWidget *ptr_QWidgetPadre,const char *ptr_NombreQWidget)
:QWidget(ptr_QWidgetPadre,ptr_NombreQWidget) {
	setPaletteBackgroundColor(QColor::QColor(255,128,0));
	setFixedSize(450,560);
	setCaption("Cinco o Mas");
	setIcon( QPixmap::fromMimeSource( "imagenes/icono.png" ) );
	
	inicializarControles();
	acomodarControles();
	conectarControles();
	nombrarFiguras();
	
	ptrOperaciones=0;
	ptrOperaciones = new Operaciones();
	iptrFigAleatorias=0;
	iptrFigAleatorias = new int[3];
	iptrPosAleatorias=0;
	iptrPosAleatorias = new int[3];
	iptrBorrarFiguras=0;
	iptrBorrarFiguras = new int[36];
	
	iFila=0;
	iColumna=0;
	contador=0;
	iContadorBoton=0;
	iPosInicial=0;
	iPosFinal=0;
	iPuntajeTotal=0;
	
	crearJuego();
}

CincoHuevitosGUI::~CincoHuevitosGUI()
{
	if(ptrNomFiguras!=0)
	{
		delete [] ptrNomFiguras;
		ptrNomFiguras=0;
	}
	if(ptrDirImagenes!=0)
	{
		delete [] ptrDirImagenes;
		ptrDirImagenes=0;
	}
	if(ptrOperaciones!=0)
	{
		iptrFigAleatorias=0;
		iptrBorrarFiguras=0;
		iptrPosAleatorias=0;
		ptrCaminoEncontrado=0;
		delete [] iptrFigAleatorias;
		iptrFigAleatorias=0;
		delete [] iptrBorrarFiguras;
		iptrBorrarFiguras=0;
		delete [] iptrPosAleatorias;
		iptrPosAleatorias=0;
		delete [] ptrCaminoEncontrado;
		ptrCaminoEncontrado=0;
		delete ptrOperaciones;
		ptrOperaciones=0;
	}
}

///Metodo
void CincoHuevitosGUI::acomodarControles()
{
	ptrGrilla->addMultiCellWidget(ptrEtiqTexto,4,4,1,2);
	ptrGrilla->addMultiCellWidget(etiqPuntuacion,4,4,6,7);
	ptrGrilla->addMultiCellWidget(etiqPuntaje,4,4,8,9);
	for(int iCasillaCol=0;iCasillaCol < 3; iCasillaCol++)
	{
		ptrGrilla->addWidget(etiqFichaSig[iCasillaCol],4,iCasillaCol+3);
	}
	///Se acomoda el ptrCaminoEncontrado de botones en la grilla	
	for(int iCasillaFila=0;iCasillaFila < 9; iCasillaFila++)
	{
		for(int iCasillaCol=0;iCasillaCol < 9; iCasillaCol++)
		{
			ptrGrilla->addWidget(ptrBotCasilla[iCasillaFila][iCasillaCol],iCasillaFila+6,iCasillaCol+1);
		}
	}
}

///Metodo
void CincoHuevitosGUI::borrarFiguras()
{
	int iFicha=0;
	int iDescontar=0;
	int iPuntaje=0;
	iFicha=ptrOperaciones->consultarFicha(iPosFinal/9,iPosFinal%9);
	iptrBorrarFiguras=ptrOperaciones->buscarAlineacion(iPosFinal,iFicha);

	if(iptrBorrarFiguras[0] != -1)
	{
		
		for(int iCol=0;(iCol < 36) && iptrBorrarFiguras[iCol] != -1;iCol++)
		{
			QString direccionAux("");
			direccionAux.append(ptrDirImagenes[2]);
			direccionAux.append(ptrNomFiguras[iFicha]);
			ptrOperaciones->cambiarFicha(iptrBorrarFiguras[iCol],0);
			ptrBotCasilla[iptrBorrarFiguras[iCol]/9][iptrBorrarFiguras[iCol]%9]->setPixmap(QPixmap(direccionAux));
			iCasillasOcupadas--;
			iPuntaje++;
			if(iptrBorrarFiguras[iCol] == iPosFinal)
			{
				iDescontar++;
			}
		}
		iCasillasOcupadas = (iCasillasOcupadas + iDescontar - 1);
		iPuntajeTotal +=((iPuntaje - iDescontar + 1)*5);
		etiqPuntaje->setText(QString::number(iPuntajeTotal));
		ptrTimerBorrar->start(600);
	}
	else
	{
		insertarFicha();
		iptrFigAleatorias=ptrOperaciones->aleatorioFicha();
		fichaSiguiente();
	}
}

///Metodo
void CincoHuevitosGUI::conectarControles()
{
	///Se conectan los botones del ptrCaminoEncontrado
 	for(int iCasillaFila=0;iCasillaFila < 9; iCasillaFila++)
	{
 		for(int iCasillaCol=0;iCasillaCol < 9; iCasillaCol++)
 		{
 			connect(ptrBotCasilla[iCasillaFila][iCasillaCol],SIGNAL(pressed()),this,SLOT(botonPresionado()));
 		}
 	}
	///Se conectan las diferentes opciones del menu
	connect( nuevoJuegoAccion, SIGNAL( activated() ), this, SLOT( nuevoJuego() ) );
	connect( abrirJuegoAccion, SIGNAL( activated() ), this, SLOT( abrirJuego() ) );
	connect( guardarJuegoAccion, SIGNAL( activated() ), this, SLOT( guardarJuego() ) );
	connect( salirJuegoAccion, SIGNAL( activated() ), this, SLOT( close() ) );
	connect( comoJugarAccion, SIGNAL( activated() ), this, SLOT( comoJugar() ) );
	connect( acercaDeAccion, SIGNAL( activated() ), this, SLOT( acercaDe() ) );
	connect( ptrInternalTimer , SIGNAL(timeout()), SLOT(moverFicha()) );
	connect( ptrTimerBorrar , SIGNAL(timeout()), SLOT(borrar()));
}

///Metodo
void CincoHuevitosGUI::crearJuego()
{
	bClickInicial=false;
	ptrOperaciones->juegoNuevo();
	iptrFigAleatorias=ptrOperaciones->aleatorioFicha();
	iCasillasOcupadas=0;
	iptrPosAleatorias=ptrOperaciones->aleatorioPosicion(iCasillasOcupadas);
	insertarFicha();
	iptrFigAleatorias=ptrOperaciones->aleatorioFicha();
	fichaSiguiente();
}

///Metodo
void CincoHuevitosGUI::inicializarControles()
{
	ptrCaminoEncontrado=0;
	ptrCaminoEncontrado = new int [81];
	for(int i=0;i<81;i++)
	{
		ptrCaminoEncontrado[i]=-1;
	}
	///Llamado al metodo que crea el menu
	inicializarMenu();
	
	///Etiquetas de informacion
	ptrEtiqTexto= new QLabel("Siguiente:", this, 0);
	etiqPuntuacion = new QLabel("Puntuacion:",this);
	etiqPuntaje= new QLabel("0",this);
	///Grilla
	ptrGrilla = new QGridLayout(this,15,13,1);
	///Inicializando el label de las tres fichas Siguientes	
	for(int iCasillaCol=0;iCasillaCol < 9; iCasillaCol++)
	{
		etiqFichaSig[iCasillaCol]=new QLabel(this);
		etiqFichaSig[iCasillaCol]->setMinimumSize(QSize(50,50));
	}
	///Inicializando los botones
	for(int iCasillaFila=0;iCasillaFila < 9; iCasillaFila++)
	{
		for(int iCasillaCol=0;iCasillaCol < 9; iCasillaCol++)
		{
			ptrBotCasilla[iCasillaFila][iCasillaCol] = new QPushButton(this);
			ptrBotCasilla[iCasillaFila][iCasillaCol]->setFlat(TRUE);
			ptrBotCasilla[iCasillaFila][iCasillaCol]->setMinimumSize(QSize(50,50));
			ptrBotCasilla[iCasillaFila][iCasillaCol]->setMaximumSize(QSize(50,50));
			ptrBotCasilla[iCasillaFila][iCasillaCol]->setPaletteBackgroundColor(QColor::QColor(255,255,255));
		}
	}
	///Inicializando el qtimer
	ptrInternalTimer = new QTimer( this );
	ptrTimerBorrar= new QTimer( this );
}

///Metodo
void CincoHuevitosGUI::insertarFicha()
{
	int iFila=0;
	int iCol=0;
	int iFicha=0;
	
	iptrPosAleatorias=ptrOperaciones->aleatorioPosicion(iCasillasOcupadas);
	
	for (int iVeces=0;iVeces<3 && (iptrPosAleatorias[iVeces] != -1);iVeces++)
	{
		
		QString direccionAux("imagenes/tranquilo/");
		iFicha=iptrFigAleatorias[iVeces];
		direccionAux.append(ptrNomFiguras[iFicha]);
		iFila=iptrPosAleatorias[iVeces]/9;
		iCol=iptrPosAleatorias[iVeces]%9;
		ptrBotCasilla[iFila][iCol]->setPixmap(QPixmap(direccionAux));
		ptrOperaciones->cambiarFicha(iptrPosAleatorias[iVeces],iFicha);
		iCasillasOcupadas++;
	}
	if(iCasillasOcupadas >= 81)
	{
		QMessageBox::information(this,"Fin del juego",
		"Tu puntaje es de: "+(QString::number(iPuntajeTotal)));
		
		for(int iCasillaFila=0;iCasillaFila < 9; iCasillaFila++)
		{
			for(int iCasillaCol=0;iCasillaCol < 9; iCasillaCol++)
			{
				ptrBotCasilla[iCasillaFila][iCasillaCol]->setPixmap(QPixmap(""));
			}
		}
		nuevoJuego();
	}
}

///Metodo
void CincoHuevitosGUI::inicializarMenu()
{
	///Se crea la barra del menu
	MenuBar = new QMenuBar( this, "Menu" );	

	///Creacion de las acciones del menu
	nuevoJuegoAccion = new QAction( this, "nuevoJuegoAccion" );
	abrirJuegoAccion = new QAction( this, "abrirJuegoAccion" );
	guardarJuegoAccion = new QAction( this, "guardarJuegoAccion" );
	comoJugarAccion = new QAction( this, "comoJugarAccion" );
	acercaDeAccion = new QAction( this, "acercaDeAccion" );
	salirJuegoAccion=new QAction( this, "salirJuegoAccion" );
	
	///Se crea el menu archivo 
	menuArchivo = new QPopupMenu( this );
	///Se introducen los elementos al menu archivo
    	nuevoJuegoAccion->addTo( menuArchivo );
    	abrirJuegoAccion->addTo( menuArchivo );
    	guardarJuegoAccion->addTo( menuArchivo );
	salirJuegoAccion->addTo( menuArchivo );
	///Se introduce el menu archivo a la barra del menu
	MenuBar->insertItem( "&Archivo", menuArchivo, 1 );
	///Se le pone nombre a los elementos de archivo
	nuevoJuegoAccion->setText( tr( "Nuevo Juego" ) );
   	abrirJuegoAccion->setText( tr( "Abrir" ) );
    	guardarJuegoAccion->setText( tr( "Guardar" ) );
	salirJuegoAccion->setText( tr( "Salir" ) );
	///Se crea el menu ayuda 
	menuAyuda = new QPopupMenu( this );
	///Se introducen los elementos al menu ayuda
    	comoJugarAccion->addTo( menuAyuda );
    	menuAyuda->insertSeparator();
    	acercaDeAccion->addTo( menuAyuda );
	acercaDeAccion->setIconSet( QIconSet( QPixmap::fromMimeSource( "imagenes/icono.png" ) ) );
	///Se introduce el menu ayuda a la barra del menu
    	MenuBar->insertItem( "Ayuda", menuAyuda, 2 );
	///Se le pone nombre a los elementos de ayuda
	comoJugarAccion->setText( tr( "Como Jugar" ) );
	acercaDeAccion->setText( tr( "Acerca de.." ) );
}

///Metodo
void CincoHuevitosGUI::fichaSiguiente()
{
	for(int contador=0; contador<3; contador++)
	{	
		QString direccionAux("");
		direccionAux.append(ptrDirImagenes[0]);
		direccionAux.append(ptrNomFiguras[iptrFigAleatorias[contador]]);
		etiqFichaSig[contador]->setPixmap(QPixmap(direccionAux));
	}
}

///Metodo
void CincoHuevitosGUI::nombrarFiguras()
{
	ptrNomFiguras=0;
	ptrNomFiguras = new QString [8];
	ptrDirImagenes=0;
	ptrDirImagenes = new QString [3];
	ptrNomFiguras[0]="";	
	ptrNomFiguras[1]="amarillo.jpg";
	ptrNomFiguras[2]="azul.jpg";
	ptrNomFiguras[3]="rojo.jpg";
	ptrNomFiguras[4]="verde.jpg";
	ptrNomFiguras[5]="cafe.jpg";
	ptrNomFiguras[6]="fucsia.jpg";
	ptrNomFiguras[7]="gris.jpg";
	
	ptrDirImagenes[0]="imagenes/tranquilo/";
	ptrDirImagenes[1]="imagenes/preocupado/";
	ptrDirImagenes[2]="imagenes/quebrado/";
}

///******************SLOTS***********************///
///Slot publico
void CincoHuevitosGUI::abrirJuego()
{
	int iCargarFicha=0;
	iPuntajeTotal=ptrOperaciones->cargarJuego();
	iCasillasOcupadas=0;
	for(int iCasillaFila=0;iCasillaFila < 9; iCasillaFila++)
	{
		for(int iCasillaCol=0;iCasillaCol < 9; iCasillaCol++)
		{
			QString direccionAux("");
			direccionAux.append("imagenes/tranquilo/");
			iCargarFicha=ptrOperaciones->consultarFicha(iCasillaFila,iCasillaCol);
			direccionAux.append(ptrNomFiguras[iCargarFicha]);
			ptrBotCasilla[iCasillaFila][iCasillaCol]->setPixmap(QPixmap(direccionAux));
			if(iCargarFicha != 0)
			{
				iCasillasOcupadas++;
			}
		}
	}
	etiqPuntaje->setText(QString::number(iPuntajeTotal));
}

///Slot publico
void CincoHuevitosGUI::acercaDe()
{
	QMessageBox::information(this, "Acerca de...", "Cinco o Mas v1.0\nAutores:\nGustavo Adolfo Ruiz Soto\nCamilo Esteban Salazar Soto");
}

///Slot publico
void CincoHuevitosGUI::borrar()
{
	//QSound::play("glass.wav");
	for(int iCol=0;(iCol < 36) && iptrBorrarFiguras[iCol] != -1;iCol++)
	{
		ptrOperaciones->cambiarFicha(iptrBorrarFiguras[iCol],0);
		ptrBotCasilla[iptrBorrarFiguras[iCol]/9][iptrBorrarFiguras[iCol]%9]->setPixmap(QPixmap(""));
	}
	ptrTimerBorrar->stop();
	if(iCasillasOcupadas == 0)
	{
		insertarFicha();
		iptrFigAleatorias=ptrOperaciones->aleatorioFicha();
		fichaSiguiente();
	}
}

///Slot publico
void CincoHuevitosGUI::comoJugar()
{
	QMessageBox::information(this, "Como jugar...",
	 "Intentar hacer alineaciones verticales, horizontales o\ndiagonales de 5 o mas figuras. Haz click en una\nfigura y otro en una casilla que este desocupada.\nNo se aceptan desplazamientos diagonales.");
}

///Slot publico
void CincoHuevitosGUI::guardarJuego()
{
	QMessageBox mensajeGuardar( "Guardar el juego actual",
	"Guardar el juego actual sobrescribira el anterior..."
	"\nDesea guardar?",
	QMessageBox::Information,
	QMessageBox::Yes | QMessageBox::Default,
	QMessageBox::No | QMessageBox::Escape ,
	QMessageBox::NoButton);
	mensajeGuardar.setButtonText( QMessageBox::Yes, "Guardar" );
	mensajeGuardar.setButtonText( QMessageBox::No, "No gurdar" );
	
	switch(mensajeGuardar.exec())
	{
		case QMessageBox::Yes:
			ptrOperaciones->salvarJuego(iPuntajeTotal);
			QMessageBox::information(this, "Guardar", "El juego ha sido guardado");
		break;
		case QMessageBox::No:
			QMessageBox::information(this, "Guardar", "El juego NO se ha guardado");
		break;
	}
}

///hay que arreglar
void CincoHuevitosGUI::moverFicha()
{
	int iFicha=0;
	QString direccionFinal("");
	QString direccionInicial("");
	ptrInternalTimer->start(70);
	
	iFicha=ptrOperaciones->consultarFicha(iPosInicial/9,iPosInicial%9);
	direccionFinal.append(ptrDirImagenes[1]);
	direccionFinal.append(ptrNomFiguras[iFicha]);
	if(ptrCaminoEncontrado[contador]!= -1)
	{
		ptrBotCasilla[iFila][iColumna]->setPixmap(QPixmap());
		iFila=ptrCaminoEncontrado[contador]/9;
		iColumna=ptrCaminoEncontrado[contador]%9;
		ptrBotCasilla[iFila][iColumna]->setPixmap(QPixmap(direccionFinal));
		contador++;
	}
	else
	{
		ptrInternalTimer->stop();
		direccionInicial.append(ptrDirImagenes[0]);
		direccionInicial.append(ptrNomFiguras[iFicha]);
		ptrBotCasilla[iFila][iColumna]->setPixmap(QPixmap(direccionInicial));
		
		ptrOperaciones->cambiarFicha(iPosInicial,0);
		ptrOperaciones->cambiarFicha(iPosFinal,iFicha);
		contador=0;
		borrarFiguras();
	}
}

///Slot publico
void CincoHuevitosGUI::nuevoJuego()
{
	ptrOperaciones->juegoNuevo();
	iPuntajeTotal=0;
	
	for(int iCasillaFila=0;iCasillaFila < 9; iCasillaFila++)
	{
		for(int iCasillaCol=0;iCasillaCol < 9; iCasillaCol++)
		{
			QString direccionAux("imagenes/tranquilo/");
			ptrBotCasilla[iCasillaFila][iCasillaCol]->setPixmap(QPixmap(direccionAux));
		}
	}
	etiqPuntaje->setText(QString::number(iPuntajeTotal));
	iptrFigAleatorias=ptrOperaciones->aleatorioFicha();
	
	iCasillasOcupadas=0;
	iptrPosAleatorias=ptrOperaciones->aleatorioPosicion(iCasillasOcupadas);
	insertarFicha();
	iptrFigAleatorias=ptrOperaciones->aleatorioFicha();
	fichaSiguiente();
}

///Slot publico
void CincoHuevitosGUI::botonPresionado()
{
	QString direccionInicial("");
	QString direccionFinal("");
	
	if(! (ptrInternalTimer->isActive()))
	{
		for(int iCasillaFila=0;iCasillaFila < 9; iCasillaFila++)
		{
			for(int iCasillaCol=0;iCasillaCol < 9; iCasillaCol++)
			{
				if (ptrBotCasilla[iCasillaFila][iCasillaCol]->isDown())
				{
					iFila=iCasillaFila;
					iColumna=iCasillaCol;
				}
			}
		}
		
		if (bClickInicial==false && (! ptrOperaciones->estaLibre(iFila,iColumna)))
		{
			direccionInicial.append(ptrDirImagenes[1]);
			int iFicha=(-1);
			
			iFicha=ptrOperaciones->consultarFicha(iFila, iColumna);
			direccionInicial.append(ptrNomFiguras[iFicha]);
			ptrBotCasilla[iFila][iColumna]->setPixmap(QPixmap(direccionInicial));
			bClickInicial=true;
			iPosInicial=iFila*9+iColumna;
			return;
		}
		
		if (bClickInicial==true && !(ptrOperaciones->estaLibre(iFila,iColumna)))
		{
			int iFicha=-1;
			direccionFinal.append(ptrDirImagenes[0]);
			iFicha=ptrOperaciones->consultarFicha(iPosInicial/9,iPosInicial%9);
			direccionFinal.append(ptrNomFiguras[iFicha]);
			ptrBotCasilla[iPosInicial/9][iPosInicial%9]->setPixmap(QPixmap(direccionFinal));
			
			direccionInicial.append(ptrDirImagenes[1]);
			iFicha=ptrOperaciones->consultarFicha(iFila, iColumna);
			direccionInicial.append(ptrNomFiguras[iFicha]);
			
			ptrBotCasilla[iFila][iColumna]->setPixmap(QPixmap(direccionInicial));
			iPosInicial=iFila*9+iColumna;
			bClickInicial=true;
			return;
		}
		
		if(bClickInicial==true && (ptrOperaciones->estaLibre(iFila,iColumna)))
		{
			iPosFinal=(iFila*9)+iColumna;
			if(ptrOperaciones->buscarCamino(iPosInicial,iPosFinal)==true)
			{
				ptrCaminoEncontrado=ptrOperaciones->devolverCamino();
				ptrBotCasilla[iFila][iColumna]->setPixmap(QPixmap());
				moverFicha();
				bClickInicial=false;
				///ptrOperaciones->aleatorioPosicion();//insertarFicha();//ptrOperaciones->aleatorioPosicion();
			}
			
		}
	}
}


int main(int argc, char **argv) {
	QApplication aplicacion(argc,argv);
	QApplication ::setFont(QFont( "Times", 12, QFont::Bold ), true);
	CincoHuevitosGUI miGui(0,"CincoHuevitosGUI");
	aplicacion.setMainWidget(&miGui);
	miGui.show();
	return aplicacion.exec();
}
