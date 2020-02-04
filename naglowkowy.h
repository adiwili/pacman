#ifndef NAGLOWKOWY_H
#define NAGLOWKOWY_H

#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

void print_hello (GtkWidget *widget, gpointer data);
void print_entry (GtkWidget *widget, gpointer data);
char *liczba_na_slowo(int a);
char *sklej(char *nazwa,char *doklej);

typedef struct user
{
  int id;
  const gchar *nick;
}gamer;

typedef struct pakiet_do_zamkniecia
{
    GtkWidget *window;
    GtkWidget *window_prev;
    gamer *Gamer;
}pakiet;

typedef struct pakiet_przyciskow
{
  GtkWidget *continue_button;
  GtkWidget *return_label;
  GtkWidget *empty_label;
  GtkWidget *entry;
  pakiet *Pakiet;
  gamer *Gamer;
}przyciski;

typedef struct poziom
{
  int id;
  char *name;
  char *plik;
  GtkWidget *button_wywolujacy;
}level;

typedef struct poziomy
{
  int ile;
  level *Poziomy;
}levele;

typedef struct do_poziomu
{
  levele *Levele;
  pakiet *Pakiet;
}do_level;

#endif