#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "naglowkowy.h"

void zamknij_okno(GtkWidget *widget, gpointer data)
{
    pakiet *Pakiet = (pakiet *) data;
    gtk_widget_show(Pakiet->window_prev);
    gtk_widget_destroy(Pakiet->window);
}

void otworz_poprzednie(GtkWidget *widget, gpointer data)
{
    pakiet *Pakiet = (pakiet *) data;
    gtk_widget_show(Pakiet->window_prev);
}