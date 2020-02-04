#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "naglowkowy.h"
#include "zamykanie.h"
#include "ranking.h"
#include "logowanie.h"
#include "levele.h"

void uruchom_menu(GtkWidget *widget, gpointer data);
void uruchom_logowanie();

int main (int argc, char **argv)
{
  gtk_init(&argc, &argv);
  uruchom_logowanie();
  gtk_main();
}

void uruchom_menu(GtkWidget *widget, gpointer data)
{ 
  pakiet *Pakiet_wroc_do_login = (pakiet *) data;
  if(Pakiet_wroc_do_login == NULL)
     exit(1);
  gtk_widget_hide(Pakiet_wroc_do_login->window_prev);

  GtkWidget *window;
  GtkWidget *grid;
  GtkWidget *button;
  GtkWidget *label;
  
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window), "Pac-Man");
  gtk_window_set_default_size (GTK_WINDOW (window), 300, 500);
  
  gtk_container_set_border_width (GTK_CONTAINER (window), 10);

  Pakiet_wroc_do_login->window = window;
  pakiet *Pakiet = (pakiet *)malloc(sizeof(pakiet));
  Pakiet->window_prev = window;
  Pakiet->Gamer = Pakiet_wroc_do_login->Gamer;

  grid = gtk_grid_new();
  gtk_grid_set_row_spacing(GTK_GRID(grid), 3);
  gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
  gtk_grid_set_column_spacing(GTK_GRID(grid), 3);
  gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
  gtk_container_add(GTK_CONTAINER(window), grid);

  label = gtk_label_new("MENU");
  gtk_grid_attach (GTK_GRID (grid), label, 0, 0, 1, 1);

  button = gtk_button_new_with_label ("Levels");
  g_signal_connect (button, "clicked", G_CALLBACK (uruchom_levele), Pakiet);
  gtk_grid_attach (GTK_GRID (grid), button, 0, 2, 1, 1);

  button = gtk_button_new_with_label ("Ranking");
  g_signal_connect (button, "clicked", G_CALLBACK (uruchom_ranking), Pakiet);
  gtk_grid_attach (GTK_GRID (grid), button, 0, 3, 1, 1);

  button = gtk_button_new_with_label ("Quit");
  g_signal_connect (button, "clicked", G_CALLBACK (zamknij_okno), Pakiet_wroc_do_login);
  g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(otworz_poprzednie), Pakiet_wroc_do_login);
  gtk_grid_attach (GTK_GRID (grid), button, 0, 4, 1, 1);

  gtk_widget_show_all (window);
}

void uruchom_logowanie(GtkWidget *widget, gpointer data)
{
  przyciski *Przyciski = (przyciski *)malloc(sizeof(przyciski));

  GtkWidget *window;
  GtkWidget *grid;
  GtkWidget *label;
  GtkWidget *button;

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window), "Log in");
  gtk_window_set_default_size (GTK_WINDOW (window), 300, 500);
  g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit),NULL);
  gtk_container_set_border_width (GTK_CONTAINER (window), 10);

  pakiet *Pakiet = (pakiet *)malloc(sizeof(pakiet));
  Pakiet->window_prev = window;
  Przyciski->Pakiet = Pakiet;
  grid = gtk_grid_new();
  gtk_grid_set_row_spacing(GTK_GRID(grid), 3);
  gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
  gtk_grid_set_column_spacing(GTK_GRID(grid), 3);
  gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
  gtk_container_add(GTK_CONTAINER(window), grid);

  label = gtk_label_new("Pac-Man");
  gtk_grid_attach (GTK_GRID (grid), label, 0, 0, 1, 1);

  label = gtk_label_new("Write your login to start the game");
  gtk_grid_attach (GTK_GRID (grid), label, 0, 2, 1, 1);

  Przyciski->entry = gtk_entry_new ();
  gtk_entry_set_max_length(GTK_ENTRY(Przyciski->entry), 50);
  gtk_entry_get_alignment(GTK_ENTRY(Przyciski->entry));
  g_signal_connect(G_OBJECT(Przyciski->entry),"activate",G_CALLBACK(print_entry),(gpointer) Przyciski->entry);
  gtk_entry_set_text(GTK_ENTRY(Przyciski->entry),"");
  gtk_entry_set_placeholder_text (GTK_ENTRY(Przyciski->entry), "Write your nickname");
  gtk_grid_attach (GTK_GRID (grid), Przyciski->entry, 0, 3, 1, 1);

  button = gtk_button_new_with_label ("Log in");
  g_signal_connect (button, "clicked", G_CALLBACK (log_in), Przyciski);
  gtk_grid_attach (GTK_GRID (grid), button, 0, 4, 1, 1);

  Przyciski->empty_label = gtk_label_new("");
  gtk_grid_attach (GTK_GRID (grid), Przyciski->empty_label, 0, 5, 1, 2);

  Przyciski->return_label = gtk_label_new("");
  gtk_grid_attach (GTK_GRID (grid), Przyciski->return_label, 0, 7, 1, 1);

  Przyciski->continue_button = gtk_button_new_with_label ("Continue");
  g_signal_connect (Przyciski->continue_button, "clicked", G_CALLBACK (uruchom_menu), Pakiet);
  gtk_grid_attach (GTK_GRID (grid), Przyciski->continue_button, 0, 8, 1, 1);

  button = gtk_button_new_with_label ("Quit");
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);
  gtk_grid_attach (GTK_GRID (grid), button, 0, 9, 1, 1);

  gtk_widget_show_all (window);
  gtk_widget_hide (Przyciski->return_label);
  gtk_widget_hide(Przyciski->continue_button);
}