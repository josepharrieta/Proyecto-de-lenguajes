#include "number_validator.h"
#include <ctype.h> // Para isdigit()

int es_numero_valido(char *str)
{
    // Recorremos cada carácter de la cadena
    for (int i = 0; str[i] != '\0'; i++)
    {
        // Si el carácter es una letra (mayúscula o minúscula), devolvemos falso
        if (!isdigit(str[i]))
        {
            return 0; // Indica que hay una letra en la cadena
        }
    }
    return 1; // No hay letras, la cadena es válida
}