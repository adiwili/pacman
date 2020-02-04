#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "naglowkowy.h"
#include "zamykanie.h"
#include "plansza.h"

void uruchom_levele(GtkWidget *widget, gpointer data)
{ 
  pakiet *Pakiet_wroc_do_menu = (pakiet *) data;
  if(Pakiet_wroc_do_menu == NULL)
     exit(1);
  gtk_widget_hide(Pakiet_wroc_do_menu->window_prev);

  GtkWidget *window;
  GtkWidget *grid;
  GtkWidget *button;
  GtkWidget *label;
  
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window), "Pac-Man");
  gtk_window_set_default_size (GTK_WINDOW (window), 300, 500);
  gtk_container_set_border_width (GTK_CONTAINER (window), 10);

  Pakiet_wroc_do_menu->window = window;
  pakiet *Pakiet = (pakiet *)malloc(sizeof(pakiet));
  Pakiet->window_prev = window;
  Pakiet->Gamer = Pakiet_wroc_do_menu->Gamer;

  grid = gtk_grid_new();
  gtk_grid_set_row_spacing(GTK_GRID(grid), 3);
  gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
  gtk_grid_set_column_spacing(GTK_GRID(grid), 3);
  gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
  gtk_container_add(GTK_CONTAINER(window), grid);

  label = gtk_label_new("LEVELS");
  gtk_grid_attach (GTK_GRID (grid), label, 0, 0, 1, 1);

  char znak;

  do_level *Do_Poziomu = (do_level *)malloc(sizeof(do_level));
  Do_Poziomu->Pakiet = Pakiet;
  Do_Poziomu->Levele = (levele *)malloc(sizeof(levele));

  FILE *plik = fopen( "levele.txt", "r" );
  Do_Poziomu->Levele->ile = 0;
  while((znak = getc(plik)) && znak != '\n')
  {
    Do_Poziomu->Levele->ile *= 10;
    Do_Poziomu->Levele->ile += znak - '0';
  }

  Do_Poziomu->Levele->Poziomy = (level *)malloc(sizeof(level)*Do_Poziomu->Levele->ile);

  for(int i = 0 ; i < Do_Poziomu->Levele->ile ; i++)
  { 
    Do_Poziomu->Levele->Poziomy[i].name = (char *)malloc(sizeof(char)*51);
    Do_Poziomu->Levele->Poziomy[i].plik = (char *)malloc(sizeof(char)*51);
    Do_Poziomu->Levele->Poziomy[i].id = 0;
    while((znak = getc(plik)) && znak != ';')
    {
          Do_Poziomu->Levele->Poziomy[i].id *= 10;
          Do_Poziomu->Levele->Poziomy[i].id += znak - '0';
    }
    int m = 0;
    Do_Poziomu->Levele->Poziomy[i].name[m] = '\0';
    while((znak = getc(plik)) && znak != ';')
    {
          Do_Poziomu->Levele->Poziomy[i].name[m] = znak;
          m++;
    }
    Do_Poziomu->Levele->Poziomy[i].name[m] = '\0';
    m = 0;
    Do_Poziomu->Levele->Poziomy[i].plik[m] = '\0';
    while((znak = getc(plik)) && znak != '\n')
    {
          Do_Poziomu->Levele->Poziomy[i].plik[m] = znak;
          m++;
    }
    Do_Poziomu->Levele->Poziomy[i].plik[m] = '\0';
    Do_Poziomu->Levele->Poziomy[i].button_wywolujacy = gtk_button_new_with_label (Do_Poziomu->Levele->Poziomy[i].name);
    g_signal_connect (Do_Poziomu->Levele->Poziomy[i].button_wywolujacy, "clicked", G_CALLBACK (uruchom_plansze), Do_Poziomu);
    gtk_grid_attach (GTK_GRID (grid), Do_Poziomu->Levele->Poziomy[i].button_wywolujacy, 0, Do_Poziomu->Levele->Poziomy[i].id+1, 1, 1);
  }
  fclose( plik );

  button = gtk_button_new_with_label ("Quit");
  g_signal_connect(button, "clicked", G_CALLBACK (zamknij_okno), Pakiet_wroc_do_menu);
  g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(otworz_poprzednie), Pakiet_wroc_do_menu);
  gtk_grid_attach (GTK_GRID (grid), button, 0, 5, 1, 1);
  
  gtk_widget_show_all (window);
}