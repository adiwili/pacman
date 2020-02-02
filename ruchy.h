#ifndef RUCH_H
#define RUCH_H

#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "naglowkowy.h"
#include "zamykanie.h"
#include "plansza.h"

void zdobyty_punkt(Pacman *pacman);
void zakoncz(Pacman *pacman, bool wynik);
void quit_zakoncz(GtkWidget *widget, gpointer *data);
gboolean timer(gpointer *data);
gboolean ruch(GtkWidget *widget, GdkEventKey *event, gpointer *data);

#endif