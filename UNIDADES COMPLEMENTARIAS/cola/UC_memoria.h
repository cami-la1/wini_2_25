//---------------------------------------------------------------------------
	#include "Umemoria.h"
#ifndef UC_memoriaH
#define UC_memoriaH
//---------------------------------------------------------------------------

typedef int direccion;
 //	const string datoNL = "elemento,sig";
 //	const string elementNL = "->elemento";
  ///	const string sigNL = "->sig";
  	//static const int MAX= 20;
   //	static const int NULO = -1;
class colaM{
	private:



	direccion ini,fin;

	CSmemoria* Cm;
	public: 	int longitud;
colaM();
	colaM(CSmemoria* m);
	 bool vacia();
	 void Meter(int e);

    int colaprimero();
  void Sacar(int &e);
  int cima();
  int ultimoElemento() ;
  void SacarUltimo(int &e) ;
  void MeterAlPrincipio(int e) ;
 void imprimir(TColor FormColor, TCanvas *Canvas);

};
#endif
