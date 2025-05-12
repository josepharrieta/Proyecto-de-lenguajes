#ifndef INTERFACE_H
#define INTERFACE_H

#include <windows.h>

LRESULT CALLBACK ProcediementoVentana(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

void MostrarMensaje(HWND hwnd, const char *mensaje); // Función para mostrar mensajes

#endif // INTERFACE_H