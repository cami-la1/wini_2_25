//---------------------------------------------------------------------------

#pragma hdrstop

#include "UC_vectores.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
   colaV1::  colaV1(){
	ini=0; fin=-1;
	// Constructor


	}

		bool colaV1:: vacia() {
            return (ini > fin);
        }

		void colaV1:: Meter(int e) {
            if (fin < maxx - 1) {
                fin++;
                V[fin] = e;
            }
            // Aqu� puedes manejar el caso cuando la cola est� llena
        }

		void colaV1:: Sacar(int &e) {
            if (!vacia()) {
                e = V[ini];
				ini++;
            }
            // Aqu� puedes manejar el caso cuando la cola est� vac�a
        }

		int colaV1:: primero() {
			if (!vacia()) {
                return V[ini];
            }
            // Aqu� puedes manejar el caso cuando la cola est� vac�a
		}

void colaV1::imprimir(TColor FormColor, TCanvas *Canvas) {
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






