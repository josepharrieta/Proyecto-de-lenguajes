#include <windows.h>
#include <stdio.h> // Para poder usar sprintf
#include "../core/validation/number_validator.c"
#include "../core/mcm/calculator.c"

#include "interface.h"

int WINAPI WinMain(HINSTANCE hInstanciaActual, HINSTANCE hInstanciaPrevia, LPSTR lpCmdLinea, int nCmdShow)
{
    HWND ventana;     // manejador de ventana
    MSG mensaje;      // intermediario para comunicar los mensajes de la aplicacion
    WNDCLASSEX clase; // estructura que contienen un conjunto de elementos que caracterizan a una ventana

    clase.cbSize = sizeof(WNDCLASSEX);     // tamaño de la clase es igual al tamaño de la estructura
    clase.cbClsExtra = 0;                  // El número de bytes adicionales para asignar (El sistema inicializa los bytes a cero.)
    clase.style = CS_HREDRAW | CS_VREDRAW; // se puede dibujar horizontalmente y verticalmente
    clase.lpfnWndProc = ProcediementoVentana;
    clase.hInstance = hInstanciaActual;
    clase.hIcon = LoadIcon(NULL, 0);                  // Identificador de icono
    clase.hIconSm = LoadIcon(NULL, IDI_INFORMATION);  // Elegimos que icono queremos
    clase.hCursor = LoadCursor(NULL, IDC_ARROW);      // Identificador de cursor
    clase.lpszClassName = "mcm";                      // Este es el identificador para pasarlo a CreateWindowEx();
    clase.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // Color de fondo de la ventana

    if (!RegisterClassEx(&clase))
    { // Si no está registrada la clase
        MessageBox(NULL, "No se pudo ejecutar la aplicación", "Error", MB_ICONERROR);
        return EXIT_FAILURE;
    }

    // Crear la ventana
    ventana = CreateWindowEx(0, "mcm", "mcm calculator", WS_OVERLAPPEDWINDOW | WS_SYSMENU,
                             400, 80, 500, 300, HWND_DESKTOP, NULL, hInstanciaActual, NULL);
    if (ventana == NULL)
    {
        MessageBox(NULL, "Error al crear la ventana", "Error", MB_ICONERROR);
        return EXIT_FAILURE;
    }

    ShowWindow(ventana, nCmdShow); // Mostramos la ventana
    UpdateWindow(ventana);         // Actualizamos la ventana

    // Bucle de mensajes
    while (GetMessage(&mensaje, NULL, 0, 0) > 0)
    {
        TranslateMessage(&mensaje);
        DispatchMessage(&mensaje);
    }

    return (int)mensaje.wParam;
}

LRESULT CALLBACK ProcediementoVentana(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    static HINSTANCE Instancia;
    char buffer1[256], buffer2[256], resultado[256];
    double num1, num2, res;
    HWND txtNumero1, entryNumero1, txtNumero2, entryNumero2, txtResultado, btnCalcular, btnSalir, entryResultado;

    switch (msg)
    {

    case WM_CREATE:
    {
        int centrarX = 80;
        Instancia = ((LPCREATESTRUCT)lParam)->hInstance;

        // Crear controles: campo de texto para el primer número
        txtNumero1 = CreateWindowEx(0, "STATIC", "Primer numero:", WS_CHILD | WS_VISIBLE, centrarX + 65, 30, 110, 25, hwnd, (HMENU)1, Instancia, NULL);

        // Crear campo de entrada para el primer número
        entryNumero1 = CreateWindowEx(0, "EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
                                      centrarX + 180, 30, 40, 25, hwnd, (HMENU)2, Instancia, NULL);

        // Crear controles: campo de texto para el segundo número
        txtNumero2 = CreateWindowEx(0, "STATIC", "Segundo numero:", WS_CHILD | WS_VISIBLE,
                                    centrarX + 50, 70, 130, 25, hwnd, (HMENU)3, Instancia, NULL);

        // Crear campo de entrada para el segundo número
        entryNumero2 = CreateWindowEx(0, "EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
                                      centrarX + 180, 70, 40, 25, hwnd, (HMENU)4, Instancia, NULL);

        // Crear botón de Calcular
        btnCalcular = CreateWindowEx(0, "BUTTON", "Calcular", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
                                     centrarX + 50, 110, 100, 30, hwnd, (HMENU)5, Instancia, NULL);

        // Crear botón de Salir
        btnSalir = CreateWindowEx(0, "BUTTON", "Salir", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
                                  centrarX + 160, 110, 100, 30, hwnd, (HMENU)6, Instancia, NULL);

        // Crear el campo para mostrar el resultado
        txtResultado = CreateWindowEx(0, "Static", "Resultado", WS_CHILD | WS_VISIBLE,
                                      centrarX + 50, 180, 70, 25, hwnd, (HMENU)7, Instancia, NULL);

        // Crear el campo de texto para mostrar el resultado
        entryResultado = CreateWindowEx(0, "EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_READONLY,
                                        centrarX + 50, 200, 200, 25, hwnd, (HMENU)8, Instancia, NULL);

        break;
    }

    case WM_COMMAND:
        if (LOWORD(wParam) == 5) // Botón "Calcular"
        {
            // Obtener texto de los campos de entrada
            GetWindowText(GetDlgItem(hwnd, 2), buffer1, 256);
            GetWindowText(GetDlgItem(hwnd, 4), buffer2, 256);

            if (es_numero_valido(buffer1) == 0 || es_numero_valido(buffer2) == 0)
            {
                MostrarMensaje(hwnd, "Por favor, ingrese numeros validos (mayor a 0) en el campo 1.");
                return 0; // Salir de la función si hay error
            }

            if (strlen(buffer1) == 0 || strlen(buffer2) == 0)
            {
                MostrarMensaje(hwnd, "Por favor, ingrese numeros validos (mayor a 0) en el campo 2.");
                return 0; // Salir de la función si hay error
            }

            num1 = atoi(buffer1); // Convertir el texto a número
            num2 = atoi(buffer2); // Convertir el texto a número

            // Calcular el mcm de los dos números
            res = calcular_mcm(num1, num2);

            // Mostrar el resultado en el campo de texto de resultado
            sprintf(resultado, "Resultado: %.2f", res);
            SetWindowText(GetDlgItem(hwnd, 8), resultado);
        }
        else if (LOWORD(wParam) == 6) // Botón "Salir"
        {
            PostQuitMessage(0); // Salir de la aplicación
        }
        break;

    case WM_DESTROY:
        PostQuitMessage(0); // Finaliza la aplicación
        break;

    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

void MostrarMensaje(HWND hwnd, const char *mensaje)
{
    MessageBox(hwnd, mensaje, "Error de entrada", MB_ICONEXCLAMATION | MB_OK);
}
