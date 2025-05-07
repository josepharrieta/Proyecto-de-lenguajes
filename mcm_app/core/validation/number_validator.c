#include "number_validator.h"

int es_entero_valido(const char* texto) {
    if (texto == NULL || *texto == '\0') return 0;
    for (int i = 0; texto[i] != '\0'; ++i) {
        if (texto[i] < '0' || texto[i] > '9') return 0;
    }
    return 1;
}
