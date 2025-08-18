//---------------------------------------------------------------------------

#pragma hdrstop

#include "ColasDV.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
 colaDV1::  colaDV1(){
	ini=0; fin=-1;
	// Constructor


	}

		bool colaDV1:: vacia() {
            return (ini > fin);
        }

		void colaDV1:: Meter(int e) {
            if (fin < maxx - 1) {
                fin++;
                V[fin] = e;
            }
            // Aqu� puedes manejar el caso cuando la cola est� llena
        }

		void colaDV1:: Sacar(int &e) {
            if (!vacia()) {
                e = V[ini];
                ini++;
            }
            // Aqu� puedes manejar el caso cuando la cola est� vac�a
        }

		int colaDV1:: primero() {
            if (!vacia()) {
                return V[ini];
            }
            // Aqu� puedes manejar el caso cuando la cola est� vac�a
		}

void colaDV1::imprimir(TColor FormColor, TCanvas *Canvas) {
	int posX = 700;
    int posY = 100;
    int TamanoCeldaX = 80;
    int TamanoCeldaY = 35;
    if (!vacia()) {
        // Dibujar el encabezado de la cola
        TRect rect(posX, posY, posX + TamanoCeldaX, posY + TamanoCeldaY);
        Canvas->Brush->Color = FormColor;
        Canvas->FillRect(rect);
        Canvas->TextOutW(posX, posY, "Cola");
        posY += TamanoCeldaY;
        // Iterar sobre los elementos de la cola y mostrarlos
        for (int i = ini; i <= fin; i++) {
            TRect rect(posX, posY, posX + TamanoCeldaX, posY + TamanoCeldaY);
            Canvas->Brush->Color = clWhite;  // Color de fondo de las celdas
			Canvas->FillRect(rect);
			// Convierte el n�mero a string y lo muestra
			Canvas->TextOutW(posX, posY, IntToStr(V[i]));
			posY += TamanoCeldaY;  // Mueve la posici�n verticalmente para el siguiente elemento
		}
	} else {
		// Si la cola est� vac�a
		Canvas->TextOutW(posX, posY, "Cola vac�a");
	}
}


int colaDV1::ultimoElemento() {
	if (!vacia()) {
		return V[fin]; // Devuelve el �ltimo elemento de la cola
	}
	// Manejo del caso en que la cola est� vac�a
	return -1; // Valor de error o bandera
}

void colaDV1::SacarUltimo(int &e) {
	if (!vacia()) {
		e = V[fin]; // Obtiene el �ltimo elemento
		fin--;      // Reduce el �ndice de fin para eliminar el �ltimo elemento
	}
	// Puedes manejar aqu� el caso en que la cola est� vac�a
}

void colaDV1::MeterAlPrincipio(int e) {
	if (ini > 0) {
		ini--;       // Ajusta el �ndice inicial hacia atr�s
		V[ini] = e;  // Inserta el elemento en la nueva posici�n inicial
	} else if (fin < maxx - 1) {
        // Si no hay espacio para mover ini, desplaza todos los elementos hacia adelante
		for (int i = fin; i >= ini; i--) {
			V[i + 1] = V[i];
		}
		V[ini] = e; // Inserta el nuevo elemento en el inicio
		fin++;      // Ajusta el �ndice de fin
	}
	// Manejo del caso en que la cola est� llena (opcional)
}

