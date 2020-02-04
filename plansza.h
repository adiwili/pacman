#ifndef PLANSZA_H
#define PLANSZA_H

#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "naglowkowy.h"
#include "levele.h"

void uruchom_plansze(GtkWidget *widget, gpointer data);

typedef struct punkty_zwiciestwa
{
  GtkWidget *bonusik;
  int czas;
  int x;
  int y;
  int ile_aktywny;
}bonus;

typedef struct monster
{
  GtkWidget *duszek;
  int x,y;
  int tx,ty;
  time_t zwrot;
  int cykl;
  int i_droga;
  char *droga;
  bool zywy;
}duszek;

typedef struct pacman_wskazniki
{
  level *Level;
  pakiet *Pakiet;
  gamer *Gamer;
  GtkWidget *PZ;
  GtkWidget *PP;
  GtkWidget *pole_pacmana;
  GtkWidget *pacman;
  GtkWidget ***pole_pp;
  GtkWidget *time_show;
  int x,y;
  int width,height;
  int left,bottom;
  int tx,ty;
  int pp, pz;
  char **table;
  int ile_duszkow;
  duszek *duszki;
  int time;
  int czas_bonusy;
  int ile_bonusow;
  bonus *Bonusy;
  int bezpieczny;
  int nietykalny;
  bool kontynuuj;
  int kierunek;
}Pacman;

#endif