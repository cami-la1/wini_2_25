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
void imprimir2dos();
void calcularPromedioDeVariosArchivos();
void encontrarSegundoMayor(double numeros[], int contador);
void calcularPromedioSumaDeDigitos();


int sumarDigitosDeNumero(const char* bufferNumero);
bool leerSiguienteEntero(FILE* archivo, char* buffer, int tamanoBuffer);


#pragma argsused
int _tmain(int argc, _TCHAR* argv[])
{
	char opcion;

	do {
		system("cls");
		printf("=============================================\n");
		printf("     ANALIZADOR DE ARCHIVOS DE TEXTO       \n");
		printf("=============================================\n\n");
		// --- MEN� CORREGIDO ---
        printf("   MENU PRINCIPAL\n");
        printf("   1. Sumar numeros de 'datos.txt'\n");
        printf("   2. Analizar suma de digitos (2 archivos)\n"); // <-- Opci�n 2 ahora es la de d�gitos
        printf("   3. Salir\n\n");                                  // <-- Opci�n 3 ahora es para salir
        printf("   Elija una opcion: ");

		opcion = getche();
        printf("\n\n");

        // --- L�GICA DEL SWITCH CORREGIDA ---
        switch (opcion) {
            case '1':
				resolverDesdeArchivo();
                break;
            case '2':
                // Se llama a la funci�n que suma d�gitos y pide 2 archivos
				calcularPromedioSumaDeDigitos();
                break;
            case '3':
				printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opcion no valida. Presione cualquier tecla para continuar.\n");
                getch();
                break;
		}

    } while (opcion != '3'); // <-- CONDICI�N DE SALIDA CORREGIDA

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
/**
 * @brief Encuentra el segundo n�mero m�s grande en un array de doubles.
 * @param numeros Array de n�meros.
 * @param contador Cu�ntos n�meros hay en el array.
 */
void encontrarSegundoMayor(double numeros[], int contador) {
    if (contador < 2) {
        printf("No hay suficientes numeros para encontrar un segundo mayor.\n");
        return;
    }
    double mayor = -1e300; // Un n�mero muy peque�o
    double segundoMayor = -1e300;
    for (int i = 0; i < contador; i++) {
        if (numeros[i] > mayor) {
            segundoMayor = mayor; // El antiguo mayor ahora es el segundo
            mayor = numeros[i];
        } else if (numeros[i] > segundoMayor && numeros[i] < mayor) {
            segundoMayor = numeros[i];
        }
    }
    printf("El segundo numero mas grande es: %.2f\n", segundoMayor);
}

/**
 * @brief Lee el archivo l�nea por l�nea y para cada una, imprime el segundo
 * n�mero m�s grande que encuentre.
 */
void imprimir2dos() {
	FILE* archivo = fopen("datos.txt", "r");
    if (archivo == NULL) {
        printf("Error: No se pudo encontrar o abrir el archivo 'datos.txt'.\n");
        system("pause");
        return;
	}
    printf("--- Buscando el segundo numero mas grande por fila ---\n\n");
    int caracterActual;
    int numeroDeFila = 1;
    // Bucle principal que se ejecuta hasta el fin del archivo
    while ((caracterActual = fgetc(archivo)) != EOF) {
        ungetc(caracterActual, archivo); // Devolvemos el caracter para empezar a procesar la l�nea
        // Array para guardar los n�meros de la l�nea actual
        double numerosEnLaFila[256];
        int contadorDeNumeros = 0;
        bool finDeLinea = false;
        // Bucle para procesar una sola l�nea
        while (!finDeLinea) {
            caracterActual = fgetc(archivo);
            if (caracterActual == EOF || caracterActual == '\n') {
                finDeLinea = true;
            } else {
                 // L�gica para extraer un n�mero (similar a la funci�n anterior)
                bool esInicioDeNumero = false;
                if (isdigit(caracterActual)) {
                    esInicioDeNumero = true;
                    ungetc(caracterActual, archivo);
                } else if (caracterActual == '-') {
                    int proximo = fgetc(archivo);
                    if (proximo != EOF && isdigit(proximo)) {
                        esInicioDeNumero = true;
                        ungetc(proximo, archivo);
                        ungetc(caracterActual, archivo);
                    } else if (proximo != EOF) {
						ungetc(proximo, archivo);
                    }
                }
                if (esInicioDeNumero) {
                    char buffer[64];
                    int i = 0;
                    while(true) {
                        caracterActual = fgetc(archivo);
                        if((i == 0 && caracterActual == '-') || isdigit(caracterActual) || caracterActual == '.') {
                            buffer[i++] = caracterActual;
                        } else {
                            ungetc(caracterActual, archivo);
                            break;
                        }
                    }
                    buffer[i] = '\0';
                    // Guardamos el n�mero encontrado en nuestro array temporal
                    if (contadorDeNumeros < 256) {
                        numerosEnLaFila[contadorDeNumeros++] = atof(buffer);
                    }
                }
            }
        }
        // Al final de la l�nea, procesamos los n�meros encontrados
        printf("Fila %d: ", numeroDeFila++);
        encontrarSegundoMayor(numerosEnLaFila, contadorDeNumeros);
    }
    fclose(archivo);
    printf("\n-----------------------------------------------------\n");
    system("pause");
}

/**
 * @brief Procesa un �nico archivo para obtener la suma y cantidad de n�meros.
 * @param rutaArchivo La ruta completa al archivo de texto.
 * @param sumaTotal Referencia donde se guardar� la suma de los n�meros.
 * @param cantidadNumeros Referencia donde se guardar� la cantidad de n�meros.
 */
void procesarArchivoParaPromedio(const char* rutaArchivo, double &sumaTotal, int &cantidadNumeros) {
    // Inicializamos los valores de salida
    sumaTotal = 0.0;
    cantidadNumeros = 0;

    FILE* archivo = fopen(rutaArchivo, "r");
    if (archivo == NULL) {
        printf(" -> Error: No se pudo abrir el archivo '%s'.\n", rutaArchivo);
        return; // Salimos de la funci�n si el archivo no existe
    }

	// La l�gica para encontrar n�meros
    int caracterActual;
    while ((caracterActual = fgetc(archivo)) != EOF) {
        bool esInicioDeNumero = false;
        if (isdigit(caracterActual)) {
            esInicioDeNumero = true;
            ungetc(caracterActual, archivo);
        } else if (caracterActual == '-') {
            int proximo = fgetc(archivo);
            if (proximo != EOF && isdigit(proximo)) {
                esInicioDeNumero = true;
                ungetc(proximo, archivo);
                ungetc(caracterActual, archivo);
            } else if (proximo != EOF) {
                ungetc(proximo, archivo);
            }
        }

        if (esInicioDeNumero) {
            char buffer[64];
            int i = 0;
            while(true) {
                caracterActual = fgetc(archivo);
                if((i == 0 && caracterActual == '-') || isdigit(caracterActual) || caracterActual == '.') {
                    buffer[i++] = caracterActual;
                } else {
                    ungetc(caracterActual, archivo);
                    break;
                }
            }
            buffer[i] = '\0';
            double numero = atof(buffer);


            sumaTotal += numero;
            cantidadNumeros++; // Aumentamos el contador por cada n�mero encontrado
        }
    }
    fclose(archivo);
}

/**
 * @brief Pide al usuario N rutas de archivos, las procesa y calcula el promedio total.
 */
void calcularPromedioDeVariosArchivos() {
	int cantidadArchivos = 0;
	/*printf("�Cuantos archivos desea promediar? ");
	scanf("%d", &cantidadArchivos);
	  */
   cantidadArchivos=2;
    // Limpiamos el buffer de entrada despu�s de leer un n�mero
    while (getchar() != '\n');

	if (cantidadArchivos <= 0) {
		printf("Cantidad no valida.\n");
        system("pause");
        return;
    }

    // Creamos un arreglo para guardar hasta 50 rutas de 256 caracteres cada una
    char rutas[50][256];

	// Pedimos al usuario cada una de las rutas
    printf("\nIngrese las rutas de los archivos (sin comillas):\n");
    for (int i = 0; i < cantidadArchivos; i++) {
        printf(" Ruta del archivo #%d: ", i + 1);

        // fgets lee la l�nea completa, incluyendo espacios, hasta presionar Enter.
        fgets(rutas[i], 256, stdin);

        // IMPORTANTE: fgets guarda el salto de l�nea ('\n') al final. Debemos eliminarlo.
        // Esta l�nea busca el primer '\n' y lo reemplaza con el terminador nulo '\0'.
        rutas[i][strcspn(rutas[i], "\n")] = 0;
	}

    printf("\n--- Procesando Archivos ---\n");

    double sumaGlobal = 0.0;
    int cantidadGlobal = 0;

    // Recorremos las rutas guardadas y procesamos cada archivo
    for (int i = 0; i < cantidadArchivos; i++) {
        double sumaArchivo;
        int cantidadArchivo;

        procesarArchivoParaPromedio(rutas[i], sumaArchivo, cantidadArchivo);

        if (cantidadArchivo > 0) {
            printf(" -> Archivo '%s': Suma=%.2f, Numeros=%d\n", rutas[i], sumaArchivo, cantidadArchivo);
            sumaGlobal += sumaArchivo;
            cantidadGlobal += cantidadArchivo;
        }
    }

    // Calculamos y mostramos el resultado final
    printf("\n---------------------------------------------\n");
    if (cantidadGlobal > 0) {
        double promedioFinal = sumaGlobal / cantidadGlobal;
        printf("Resultados Globales:\n");
        printf(" - Suma Total: %.2f\n", sumaGlobal);
        printf(" - Cantidad Total de Numeros: %d\n", cantidadGlobal);
        printf(" - Promedio Final: %.2f\n", promedioFinal);
    } else {
        printf("No se encontraron numeros en los archivos procesados.\n");
    }
    printf("---------------------------------------------\n");
    system("pause");
}


/**
 * @brief Recibe un n�mero como texto y devuelve la suma de sus d�gitos.
 * @param bufferNumero El n�mero en formato de cadena de caracteres.
 * @return La suma entera de los d�gitos.
 */
int sumarDigitosDeNumero(const char* bufferNumero) {
	int suma = 0;
	for (int i = 0; bufferNumero[i] != '\0'; i++) {
		// Nos aseguramos de sumar solo los caracteres que son d�gitos
		if (isdigit(bufferNumero[i])) {
			// Convertimos el caracter ('5') a su valor num�rico (5)
			suma += bufferNumero[i] - '0';
		}
	}
    return suma;
}
/**
 * @brief Lee un stream de archivo y extrae el siguiente N�MERO ENTERO que encuentra.
 * @return true si se encontr� un n�mero, false si se lleg� al final del archivo.
 */
bool leerSiguienteEntero(FILE* archivo, char* buffer, int tamanoBuffer) {
    int caracterActual;
    while ((caracterActual = fgetc(archivo)) != EOF) {
		bool esInicioDeNumero = false;
        if (isdigit(caracterActual)) {
            esInicioDeNumero = true;
            ungetc(caracterActual, archivo);
        } else if (caracterActual == '-') {
            int proximo = fgetc(archivo);
            if (proximo != EOF && isdigit(proximo)) {
                esInicioDeNumero = true;
                ungetc(proximo, archivo);
                ungetc(caracterActual, archivo);
            } else if (proximo != EOF) {
                ungetc(proximo, archivo);
            }
		}

        if (esInicioDeNumero) {
            int i = 0;
            while (i < tamanoBuffer - 1) {
                caracterActual = fgetc(archivo);
                // La condici�n ahora solo acepta d�gitos y el signo al inicio
                if ((i == 0 && caracterActual == '-') || isdigit(caracterActual)) {
                    buffer[i++] = caracterActual;
                } else {
                    ungetc(caracterActual, archivo);
                    break;
                }
			}
            buffer[i] = '\0';
            return true;
        }
    }
    return false;
}

void calcularPromedioSumaDeDigitos() {

    int cantidadArchivos = 2;
    /*
    printf("�Cuantos archivos desea procesar? ");
	scanf("%d", &cantidadArchivos);
    while (getchar() != '\n'); // Ya no es necesario
    */

    char rutas[50][256];
    printf("\nIngrese las 2 rutas de los archivos (sin comillas):\n");
    for (int i = 0; i < cantidadArchivos; i++) {
        printf(" Ruta del archivo #%d: ", i + 1);
        fgets(rutas[i], 256, stdin);
        rutas[i][strcspn(rutas[i], "\n")] = 0;
    }

    // --- FASE 1: Recolectar todas las sumas de d�gitos de todos los archivos ---
	int todasLasSumas[1024];
    int contadorDeSumas = 0;
    printf("\n--- Procesando Archivos ---\n");

    for (int i = 0; i < cantidadArchivos; i++) {
        FILE* archivo = fopen(rutas[i], "r");
        if (archivo == NULL) {
            printf(" -> Error al abrir '%s'.\n", rutas[i]);
            continue;
        }

        char buffer[64];
        // Se usa la funci�n auxiliar 'leerSiguienteEntero' que definimos antes
		while (leerSiguienteEntero(archivo, buffer, 64)) {
            if (contadorDeSumas < 1024) {
                // Se usa la funci�n auxiliar 'sumarDigitosDeNumero' que definimos antes
                todasLasSumas[contadorDeSumas++] = sumarDigitosDeNumero(buffer);
            }
        }
        fclose(archivo);
    }

    // --- FASE 2: Calcular y mostrar los resultados (sin cambios) ---
    printf("\n---------------------------------------------\n");
    if (contadorDeSumas > 0) {
        double sumaTotalDeDigitos = 0;
		for(int i = 0; i < contadorDeSumas; i++) {
            sumaTotalDeDigitos += todasLasSumas[i];
        }
        double promedio = sumaTotalDeDigitos / contadorDeSumas;

        int menorCercano = -1, mayorCercano = -1;
        double diffMenor = 1e9, diffMayor = 1e9;

        for (int i = 0; i < contadorDeSumas; i++) {
            int sumaActual = todasLasSumas[i];
            if (sumaActual < promedio) {
                if ((promedio - sumaActual) < diffMenor) {
                    diffMenor = promedio - sumaActual;
					menorCercano = sumaActual;
                }
            } else if (sumaActual > promedio) {
                if ((sumaActual - promedio) < diffMayor) {
                    diffMayor = sumaActual - promedio;
                    mayorCercano = sumaActual;
                }
            }
        }

        printf("Resultados del Analisis de Digitos:\n");
        printf(" - Promedio de la suma de digitos: %.2f\n", promedio);

		if (menorCercano != -1) {
            printf(" - Suma de digitos menor mas cercana al promedio: %d\n", menorCercano);
        } else {
            printf(" - No se encontraron sumas menores al promedio.\n");
        }

        if (mayorCercano != -1) {
            printf(" - Suma de digitos mayor mas cercana al promedio: %d\n", mayorCercano);
        } else {
            printf(" - No se encontraron sumas mayores al promedio.\n");
        }

    } else {
		printf("No se encontraron numeros en los archivos procesados.\n");
    }
    printf("---------------------------------------------\n");
    system("pause");
}
