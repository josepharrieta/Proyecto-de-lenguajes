#include <gtk/gtk.h>
#include "callbacks.h"

void build_interface() {
    GtkWidget *window, *grid, *entry1, *entry2, *button, *label;

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Calculadora MCM");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 150);

    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    entry1 = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry1), "Número 1");

    entry2 = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry2), "Número 2");

    button = gtk_button_new_with_label("Calcular MCM");

    label = gtk_label_new("Resultado: ");

    gtk_grid_attach(GTK_GRID(grid), entry1, 0, 0, 2, 1);
    gtk_grid_attach(GTK_GRID(grid), entry2, 0, 1, 2, 1);
    gtk_grid_attach(GTK_GRID(grid), button, 0, 2, 2, 1);
    gtk_grid_attach(GTK_GRID(grid), label, 0, 3, 2, 1);

    // Conectar el botón a la función de callback
    g_signal_connect(button, "clicked", G_CALLBACK(on_calcular_clicked), (gpointer[]) { entry1, entry2, label });

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);
}
