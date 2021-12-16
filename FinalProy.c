#include <stdio.h>
#include <stdlib.h>
#include <locale.h> //Poner acentos y la tilde de la ñ en C
#include <windows.h>
typedef struct { //estructura: una estructura es un tipo de dato compuesto que permite almacenar un conjunto de datos de diferente tipo.
  int *vector;//Vector o arreglo dinámico
  size_t utilizados;//espacios utilizados del vector
  size_t tamano;//tamaño del vector
  //size_t es un tipo entero sin signo devuelto por el operador sizeof y es usado para representar el tamaño de construcciones en bytes.
  //Este tipo está definido de manera tal de garantizar que siempre va a poder almacenar el tamaño del tipo más grande posible, por lo que también garantiza que va a poder almacenar cualquier índice de cualquier arreglo.
} Vector; //Nombre del la estructura declarada

void inicilizarVector(Vector *a, size_t tamanoInicial);
void insertarElementoEnVector(Vector *a, int elemento);
void liberarVector(Vector *a);
void cls(HANDLE hConsole);

int main(void)
{
    setlocale(LC_ALL,"");//Poner acentos y la tilde de la ñ en C
    HANDLE hStdout; //Variable que se utiliza para el método CLS
    hStdout = GetStdHandle(STD_OUTPUT_HANDLE);//Se inicializa con estos valores para que puedan utilizarce en el metodo CLS.

    printf("PROYECTO FINAL\n\n");

    printf("Integrantes:\n");
    printf("1. Paola Knausel    CiP.: 20-70-6086\n");
    printf("2. José Rivas Díaz  CiP.: 6-725-626\n");
    printf("3. Virgilio Saldaña CiP.: 4-817-2011\n");
    printf("4. José Pérez       CiP.: 8-993-595\n\n");

    printf("ASIGNATURA: Herramientas de Programación Aplicada I\n\n");

    printf("BIENVENIDO\n");
    printf("------------------------------------\n\n");
    int opc = 0; //variable para el manejo del menu principal.
    char continuar = 'N'; //variable para el manejo del ingreso de valores.

    Vector vectorDinamico;//declarar vector
    int valorNumerico;//declarar variable para el valorNumérico
    inicilizarVector(&vectorDinamico, 1);  // vector a declarado con un tamaño 1, el cual se incrementa.

    do{
        cls(hStdout);//cls limpia la pantalla

        printf("MENU DE OPCIONES\n\n");
        printf("1. Ingresar valores\n");
        printf("2. Imprimir valores \n");
        printf("3. Total de elementos en el vector \n");
        printf("4. Salir \n\n");

        printf("Ingrese una opción: ");
        scanf("%d", &opc);

        switch(opc){
        case 1:
            cls(hStdout);
            printf("Has seleccionado la opción %d\n\n",opc);
            do{
                printf("Ingrese un valor numérico: ");
                scanf("%d", &valorNumerico);
                insertarElementoEnVector(&vectorDinamico, valorNumerico);  // Este método se encarga de aumentar el tamaño del vector automáticamente.
                printf("¿Desea ingresar otro valor numérico? (Y/N): ");
                scanf(" %c",&continuar);

            }while((continuar == 'Y') || (continuar == 'y'));
            break;
        case 2:
            cls(hStdout);
            printf("Has seleccionado la opción %d\n\n",opc);
            printf("Imprimiendo valores del vector\n\n");

            int cont;
            for(cont = 0; cont < vectorDinamico.tamano; cont++)
                printf("Posición: %d, Dirección: %p, Valor: %d\n", cont, vectorDinamico.vector[cont], vectorDinamico.vector[cont]);
            printf("\n\n\nPresiona cualquier tecla para regresar al menú principal.\n");
            getch();
            break;
        case 3:
            cls(hStdout);
            printf("Has seleccionado la opción %d\n\n",opc);
            printf("Total de elementos del Vector: %d",vectorDinamico.tamano);
            printf("\n\n\nPresiona cualquier tecla para regresar al menú principal.\n");
            getch();
            break;
        case 4:
            cls(hStdout);
            liberarVector(&vectorDinamico);
            printf("Usted ha seleccionado la opción de salir. \nHasta la próxima!\n\n");
            break;
        default:
            cls(hStdout);
            printf("La opción que ingresó es incorrecta, vuelva a intentarlo.");
            getch();
            break;

        }
    }while(opc != 4);



    return 0; //No es necesario colocarlo ya que por defecto retorna 0
}

void inicilizarVector(Vector *a, size_t tamanoInicial) {
  a->vector = (int*) malloc(tamanoInicial * sizeof(int));//asignación dinámica del tamaño inicial del vector tipo entero.
  a->utilizados = 0;// espacios utilizados 0 ya que se inicializa por primera vez el vector.
  a->tamano = tamanoInicial;//Tamaño inicial del vector, se le colocó 1.

  if (a->vector == NULL) {
        printf("Error: Espacio en memoria no asignado.\nEl programa ha finalizado.\n");
        exit(0);
    }
}

void insertarElementoEnVector(Vector *a, int elemento) {

  if (a->utilizados == a->tamano) {//Se valida que tenga espacios disponibles, si es igual al tamaño quiere decir que no hay espacios disponibles, se debe incrementar el tamaño del vector.
    a->tamano += 1;//el tamaño se incrementa en 1.
    a->vector = (int*) realloc(a->vector, a->tamano * sizeof(int));

    if (a->vector == NULL) {
        printf("Error: Espacio en memoria no asignado.\nEl programa ha finalizado.\n");
        exit(0);
    }
  }
  a->vector[a->utilizados++] = elemento;

  //-----------------------

  if(a->tamano > 1){
        int i,j,aux;

        for(i=0;i<a->tamano;i++)
        {
            aux = a->vector[i];//
            j = i-1;//
            while((j>=0) && (a->vector[j]>aux)){
                a->vector[j+1] = a->vector[j];//
                j = j-1;//
            }

            a->vector[j+1] = aux;//

        }
    }
    int i;
    for(i=0;i<a->tamano;i++)
        {
            if(a->vector[i] == elemento){
                if(i==0){ printf("Elemento colocado al inicio del vector.\n\n");}
                  else if(i==(a->tamano)-1){ printf("Elemento colocado al final del vector.\n\n");}
                     else{  printf("El elemento fue colocado en la posición: %d\n\n",i);}
            }
        }
}

void liberarVector(Vector *a) { //Se usa para desasignar dinámicamente la memoria
  free(a->vector);
  a->vector = NULL;
  a->utilizados = a->tamano = 0;
}

//Método para limpiar la pantalla especificando las coordenadas.
void cls(HANDLE hConsole)
{
    //https://docs.microsoft.com/en-us/windows/console/clearing-the-screen?redirectedfrom=MSDN
    COORD coordScreen = { 0, 13 };    // home for the cursor
    DWORD cCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD dwConSize;

    // Get the number of character cells in the current buffer.
    if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
    {
        return;
    }

    dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

    // Fill the entire screen with blanks.
    if (!FillConsoleOutputCharacter(hConsole,        // Handle to console screen buffer
                                    (TCHAR)' ',      // Character to write to the buffer
                                    dwConSize,       // Number of cells to write
                                    coordScreen,     // Coordinates of first cell
                                    &cCharsWritten)) // Receive number of characters written
    {
        return;
    }

    // Get the current text attribute.
    if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
    {
        return;
    }

    // Set the buffer's attributes accordingly.
    if (!FillConsoleOutputAttribute(hConsole,         // Handle to console screen buffer
                                    csbi.wAttributes, // Character attributes to use
                                    dwConSize,        // Number of cells to set attribute
                                    coordScreen,      // Coordinates of first cell
                                    &cCharsWritten))  // Receive number of characters written
    {
        return;
    }


    // Put the cursor at its home coordinates.
    SetConsoleCursorPosition(hConsole, coordScreen);
}

