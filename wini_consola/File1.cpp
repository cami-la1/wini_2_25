//---------------------------------------------------------------------------
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------

// LIBRER�AS EST�NDAR (SIN VCL)
#include <stdio.h>    // Para E/S de archivos y consola estilo C (fopen, printf)
#include <stdlib.h>   // Para la funci�n est�ndar atof()
#include <conio.h>    // Para getche() y getch()
#include <ctype.h>    // Para la funci�n isdigit()

// Declaraci�n de la funci�n que procesar� el archivo
void resolverDesdeArchivo();

#pragma argsused
int _tmain(int argc, _TCHAR* argv[])
{
    char opcion;

    do {
		system("cls");
		printf("=============================================\n");
		printf("     CALCULADORA DE ARCHIVOS DE TEXTO      \n");
		printf("=============================================\n\n");
		printf("   MENU PRINCIPAL\n");
		printf("   1. Resolver del archivo (datos.txt)\n");
		printf("   2. Salir\n\n");
		printf("   Elija una opcion: ");

        opcion = getche();
        printf("\n\n");

        switch (opcion) {
			case '1':
				resolverDesdeArchivo();
                break;
            case '2':
				printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opcion no valida. Presione cualquier tecla para continuar.\n");
                getch();
                break;
        }

    } while (opcion != '2');

    return 0;
}


/**
 * @brief Lee el archivo datos.txt, extrae todos los n�meros respetando
 * su signo (+ o -) y calcula la suma total.
 */
void resolverDesdeArchivo() {

	FILE* archivo = fopen("datos.txt", "r");
	if (archivo == NULL) {
		printf("Error: No se pudo encontrar o abrir el archivo 'datos.txt'.\n");
		system("pause");
        return;
	}
	double resultado = 0.0;
	char bufferNumero[64];
	int indiceBuffer = 0;
	int caracterActual;
	printf("Procesando 'datos.txt'...\n\n");

	while ((caracterActual = fgetc(archivo)) != EOF) {

		// --- L�GICA DE DETECCI�N  ---
        //    maneja  los n�meros positivos y negativos.
		bool esInicioDeNumero = false;
        // Si es un d�gito, definitivamente es el inicio de un n�mero.
		if (isdigit(caracterActual)) {
			esInicioDeNumero = true;
			ungetc(caracterActual, archivo); // Se devuelve el d�gito para leerlo de forma uniforme.
		}
			if (caracterActual=='\n') {

	}
		// Si es un guion, verificamos si le sigue un d�gito.
		else if (caracterActual == '-') {
			int proximoCaracter = fgetc(archivo);
			if (proximoCaracter != EOF && isdigit(proximoCaracter)) {
				esInicioDeNumero = true;
                // Devolvemos ambos caracteres en el orden correcto para leer el n�mero completo.
				ungetc(proximoCaracter, archivo);
				ungetc(caracterActual, archivo); // El '-' se devuelve al final para que sea el primero en leerse.
            } else if (proximoCaracter != EOF) {
                // Si no le sigue un d�gito, no es un n�mero, as� que devolvemos el caracter.
				ungetc(proximoCaracter, archivo);
            }
		}

        // Si se confirm� que es el inicio de un n�mero, lo leemos completo.
		if (esInicioDeNumero) {
			indiceBuffer = 0;
            while (true) {
				caracterActual = fgetc(archivo);
                // La condici�n de lectura del n�mero completo.
				if ((indiceBuffer == 0 && caracterActual == '-') || isdigit(caracterActual) || caracterActual == '.') {
					bufferNumero[indiceBuffer++] = caracterActual;
				} else {
					ungetc(caracterActual, archivo); // Se devuelve el caracter que ya no es parte del n�mero.

					break;
                }
            }
			bufferNumero[indiceBuffer] = '\0';
			double numero = atof(bufferNumero);
			   printf("Numero encontrado: %.2f\n", numero);

			// Se suma el n�mero (positivo o negativo) al resultado.
		  resultado += numero;
		}
	}
	fclose(archivo);
	printf("\n---------------------------------------------\n");
	printf("El resultado final de las operaciones es: %.2f\n", resultado);
	printf("---------------------------------------------\n");
	system("pause");
}
