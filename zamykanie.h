#ifndef ZAMYKANIE_H
#define ZAMYKANIE_H

#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "naglowkowy.h"

void zamknij_okno(GtkWidget *widget, gpointer data);
void otworz_poprzednie(GtkWidget *widget, gpointer data);

#endif