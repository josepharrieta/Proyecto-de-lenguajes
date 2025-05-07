#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include "calculator.h"
#include "number_validator.h"

void on_calcular_clicked(GtkButton *button, gpointer user_data) {
    gpointer *widgets = (gpointer *)user_data;
    GtkEntry *entry1 = GTK_ENTRY(widgets[0]);
    GtkEntry *entry2 = GTK_ENTRY(widgets[1]);
    GtkLabel *label = GTK_LABEL(widgets[2]);

    const char *text1 = gtk_entry_get_text(entry1);
    const char *text2 = gtk_entry_get_text(entry2);

    if (!es_entero_valido(text1) || !es_entero_valido(text2)) {
        gtk_label_set_text(label, "Por favor, ingrese números válidos.");
        return;
    }

    int num1 = atoi(text1);
    int num2 = atoi(text2);

    int resultado = calcular_mcm(num1, num2);

    char buffer[100];
    snprintf(buffer, sizeof(buffer), "Resultado: %d", resultado);
    gtk_label_set_text(label, buffer);
}
