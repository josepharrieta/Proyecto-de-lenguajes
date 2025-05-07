#include <windows.h>
#include <stdio.h> // Para poder usar sprintf

LRESULT CALLBACK ProcediementoVentana(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
void MostrarMensaje(HWND hwnd, const char *mensaje); // Función para mostrar mensajes

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
    clase.lpszClassName = "Calculadora";              // Este es el identificador para pasarlo a CreateWindowEx();
    clase.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // Color de fondo de la ventana

    if (!RegisterClassEx(&clase))
    { // Si no está registrada la clase
        MessageBox(NULL, "No se pudo ejecutar la aplicación", "Error", MB_ICONERROR);
        return EXIT_FAILURE;
    }

    // Crear la ventana
    ventana = CreateWindowEx(0, "Calculadora", "Calculadora Simple", WS_OVERLAPPEDWINDOW | WS_SYSMENU,
                             400, 80, 300, 250, HWND_DESKTOP, NULL, hInstanciaActual, NULL);

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
    HWND txtNumero1, txtNumero2, txtResultado, btnCalcular, btnCerrar;
    char buffer1[256], buffer2[256], resultado[256];
    double num1, num2, res;

    switch (msg)
    {
    case WM_CREATE:
    {
        Instancia = ((LPCREATESTRUCT)lParam)->hInstance;

        // Crear controles: campo de texto para el primer número
        txtNumero1 = CreateWindowEx(0, "EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER,
                                    50, 30, 100, 25, hwnd, (HMENU)1, Instancia, NULL);

        // Crear controles: campo de texto para el segundo número
        txtNumero2 = CreateWindowEx(0, "EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER,
                                    50, 70, 100, 25, hwnd, (HMENU)2, Instancia, NULL);

        // Crear botón de Calcular
        btnCalcular = CreateWindowEx(0, "BUTTON", "Calcular", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
                                     50, 110, 100, 30, hwnd, (HMENU)3, Instancia, NULL);

        // Crear botón de Cerrar
        btnCerrar = CreateWindowEx(0, "BUTTON", "Cerrar", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
                                   160, 110, 100, 30, hwnd, (HMENU)4, Instancia, NULL);

        // Crear el campo para mostrar el resultado
        txtResultado = CreateWindowEx(0, "EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_READONLY,
                                      50, 150, 200, 25, hwnd, (HMENU)5, Instancia, NULL);

        break;
    }

    case WM_COMMAND:
        if (LOWORD(wParam) == 3) // Botón "Calcular"
        {
            // Obtener texto de los campos de entrada
            GetWindowText(GetDlgItem(hwnd, 1), buffer1, 256);
            GetWindowText(GetDlgItem(hwnd, 2), buffer2, 256);

            // Validar que no sean letras y que sean mayores a cero
            if (sscanf(buffer1, "%lf", &num1) != 1 || num1 <= 0)
            {
                MostrarMensaje(hwnd, "Por favor ingresa un número válido mayor a cero en el primer campo.");
                return 0;
            }

            if (sscanf(buffer2, "%lf", &num2) != 1 || num2 <= 0)
            {
                MostrarMensaje(hwnd, "Por favor ingresa un número válido mayor a cero en el segundo campo.");
                return 0;
            }

            // Calcular la suma de los dos números
            res = num1 + num2;

            // Mostrar el resultado en el campo de texto de resultado
            sprintf(resultado, "Resultado: %.2f", res);
            SetWindowText(GetDlgItem(hwnd, 5), resultado);
        }
        else if (LOWORD(wParam) == 4) // Botón "Cerrar"
        {
            PostQuitMessage(0); // Cerrar la aplicación
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
