//---------------------------------------------------------------------------
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------

// LIBRERÍAS ESTÁNDAR (SIN VCL)
#include <stdio.h>    // Para E/S de archivos y consola estilo C (fopen, printf)
#include <stdlib.h>   // Para la función estándar atof()
#include <conio.h>    // Para getche() y getch()
#include <ctype.h>    // Para la función isdigit()

// Declaración de la función que procesará el archivo
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
		// --- MENÚ CORREGIDO ---
        printf("   MENU PRINCIPAL\n");
        printf("   1. Sumar numeros de 'datos.txt'\n");
        printf("   2. Analizar suma de digitos (2 archivos)\n"); // <-- Opción 2 ahora es la de dígitos
        printf("   3. Salir\n\n");                                  // <-- Opción 3 ahora es para salir
        printf("   Elija una opcion: ");

		opcion = getche();
        printf("\n\n");

        // --- LÓGICA DEL SWITCH CORREGIDA ---
        switch (opcion) {
            case '1':
				resolverDesdeArchivo();
                break;
            case '2':
                // Se llama a la función que suma dígitos y pide 2 archivos
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

    } while (opcion != '3'); // <-- CONDICIÓN DE SALIDA CORREGIDA

    return 0;
}


/**
 * @brief Lee el archivo datos.txt, extrae todos los números respetando
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

		// --- LÓGICA DE DETECCIÓN  ---
        //    maneja  los números positivos y negativos.
		bool esInicioDeNumero = false;
        // Si es un dígito, definitivamente es el inicio de un número.
		if (isdigit(caracterActual)) {
			esInicioDeNumero = true;
			ungetc(caracterActual, archivo); // Se devuelve el dígito para leerlo de forma uniforme.
		}
			if (caracterActual=='\n') {

	}
		// Si es un guion, verificamos si le sigue un dígito.
		else if (caracterActual == '-') {
			int proximoCaracter = fgetc(archivo);
			if (proximoCaracter != EOF && isdigit(proximoCaracter)) {
				esInicioDeNumero = true;
                // Devolvemos ambos caracteres en el orden correcto para leer el número completo.
				ungetc(proximoCaracter, archivo);
				ungetc(caracterActual, archivo); // El '-' se devuelve al final para que sea el primero en leerse.
            } else if (proximoCaracter != EOF) {
                // Si no le sigue un dígito, no es un número, así que devolvemos el caracter.
				ungetc(proximoCaracter, archivo);
            }
		}

        // Si se confirmó que es el inicio de un número, lo leemos completo.
		if (esInicioDeNumero) {
			indiceBuffer = 0;
            while (true) {
				caracterActual = fgetc(archivo);
                // La condición de lectura del número completo.
				if ((indiceBuffer == 0 && caracterActual == '-') || isdigit(caracterActual) || caracterActual == '.') {
					bufferNumero[indiceBuffer++] = caracterActual;
				} else {
					ungetc(caracterActual, archivo); // Se devuelve el caracter que ya no es parte del número.

					break;
                }
            }
			bufferNumero[indiceBuffer] = '\0';
			double numero = atof(bufferNumero);
			   printf("Numero encontrado: %.2f\n", numero);

			// Se suma el número (positivo o negativo) al resultado.
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
 * @brief Encuentra el segundo número más grande en un array de doubles.
 * @param numeros Array de números.
 * @param contador Cuántos números hay en el array.
 */
void encontrarSegundoMayor(double numeros[], int contador) {
    if (contador < 2) {
        printf("No hay suficientes numeros para encontrar un segundo mayor.\n");
        return;
    }
    double mayor = -1e300; // Un número muy pequeño
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
 * @brief Lee el archivo línea por línea y para cada una, imprime el segundo
 * número más grande que encuentre.
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
        ungetc(caracterActual, archivo); // Devolvemos el caracter para empezar a procesar la línea
        // Array para guardar los números de la línea actual
        double numerosEnLaFila[256];
        int contadorDeNumeros = 0;
        bool finDeLinea = false;
        // Bucle para procesar una sola línea
        while (!finDeLinea) {
            caracterActual = fgetc(archivo);
            if (caracterActual == EOF || caracterActual == '\n') {
                finDeLinea = true;
            } else {
                 // Lógica para extraer un número (similar a la función anterior)
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
                    // Guardamos el número encontrado en nuestro array temporal
                    if (contadorDeNumeros < 256) {
                        numerosEnLaFila[contadorDeNumeros++] = atof(buffer);
                    }
                }
            }
        }
        // Al final de la línea, procesamos los números encontrados
        printf("Fila %d: ", numeroDeFila++);
        encontrarSegundoMayor(numerosEnLaFila, contadorDeNumeros);
    }
    fclose(archivo);
    printf("\n-----------------------------------------------------\n");
    system("pause");
}

/**
 * @brief Procesa un único archivo para obtener la suma y cantidad de números.
 * @param rutaArchivo La ruta completa al archivo de texto.
 * @param sumaTotal Referencia donde se guardará la suma de los números.
 * @param cantidadNumeros Referencia donde se guardará la cantidad de números.
 */
void procesarArchivoParaPromedio(const char* rutaArchivo, double &sumaTotal, int &cantidadNumeros) {
    // Inicializamos los valores de salida
    sumaTotal = 0.0;
    cantidadNumeros = 0;

    FILE* archivo = fopen(rutaArchivo, "r");
    if (archivo == NULL) {
        printf(" -> Error: No se pudo abrir el archivo '%s'.\n", rutaArchivo);
        return; // Salimos de la función si el archivo no existe
    }

	// La lógica para encontrar números
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
            cantidadNumeros++; // Aumentamos el contador por cada número encontrado
        }
    }
    fclose(archivo);
}

/**
 * @brief Pide al usuario N rutas de archivos, las procesa y calcula el promedio total.
 */
void calcularPromedioDeVariosArchivos() {
	int cantidadArchivos = 0;
	/*printf("¿Cuantos archivos desea promediar? ");
	scanf("%d", &cantidadArchivos);
	  */
   cantidadArchivos=2;
    // Limpiamos el buffer de entrada después de leer un número
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

        // fgets lee la línea completa, incluyendo espacios, hasta presionar Enter.
        fgets(rutas[i], 256, stdin);

        // IMPORTANTE: fgets guarda el salto de línea ('\n') al final. Debemos eliminarlo.
        // Esta línea busca el primer '\n' y lo reemplaza con el terminador nulo '\0'.
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
 * @brief Recibe un número como texto y devuelve la suma de sus dígitos.
 * @param bufferNumero El número en formato de cadena de caracteres.
 * @return La suma entera de los dígitos.
 */
int sumarDigitosDeNumero(const char* bufferNumero) {
	int suma = 0;
	for (int i = 0; bufferNumero[i] != '\0'; i++) {
		// Nos aseguramos de sumar solo los caracteres que son dígitos
		if (isdigit(bufferNumero[i])) {
			// Convertimos el caracter ('5') a su valor numérico (5)
			suma += bufferNumero[i] - '0';
		}
	}
    return suma;
}
/**
 * @brief Lee un stream de archivo y extrae el siguiente NÚMERO ENTERO que encuentra.
 * @return true si se encontró un número, false si se llegó al final del archivo.
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
                // La condición ahora solo acepta dígitos y el signo al inicio
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
    printf("¿Cuantos archivos desea procesar? ");
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

    // --- FASE 1: Recolectar todas las sumas de dígitos de todos los archivos ---
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
        // Se usa la función auxiliar 'leerSiguienteEntero' que definimos antes
		while (leerSiguienteEntero(archivo, buffer, 64)) {
            if (contadorDeSumas < 1024) {
                // Se usa la función auxiliar 'sumarDigitosDeNumero' que definimos antes
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
