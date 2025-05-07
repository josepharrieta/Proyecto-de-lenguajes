#include <gtk/gtk.h>
#include "interface.h"

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    build_interface();
    gtk_main();
    return 0;
}
