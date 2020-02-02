#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "naglowkowy.h"
#include "levele.h"
#include "zamykanie.h"
#include "plansza.h"
#include "ruchy.h"

void uruchom_plansze(GtkWidget *widget, gpointer data)
{ 
  do_level *Do_Poziomu = (do_level *) data;
  pakiet *Pakiet_wroc_do_levele = Do_Poziomu->Pakiet;
  if(Pakiet_wroc_do_levele == NULL)
     exit(1);
  gtk_widget_hide(Pakiet_wroc_do_levele->window_prev);

  level *Level = (level *)malloc(sizeof(level));
  Level->id = -1;
  Level->button_wywolujacy = widget;

  Pacman *pacman = (Pacman *)malloc(sizeof(Pacman));
  pacman->kontynuuj = true;
  pacman->time = 0;
  pacman->pp = 0;
  pacman->pz = 0;

  GtkCssProvider *css_provider=css_provider = gtk_css_provider_new();
  gtk_css_provider_load_from_path(css_provider, "style.css", NULL);
  gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(css_provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

  for(int i = 0 ; i < Do_Poziomu->Levele->ile ; i++)
  {
    if(Do_Poziomu->Levele->Poziomy[i].button_wywolujacy == Level->button_wywolujacy)
    {
      Level->id = Do_Poziomu->Levele->Poziomy[i].id;
      Level->name = Do_Poziomu->Levele->Poziomy[i].name;
      Level->plik = Do_Poziomu->Levele->Poziomy[i].plik;
    }
  }

  if(Level->id == -1)
  {
    printf("Level Error\n");
    exit(1);
  }
  pacman->Level = Level;

//tutaj cialo planszy----------------------------------------------------------
  
  GtkWidget *window;
  GtkWidget *grid;
  GtkWidget *button;
  GtkWidget *label;
  GtkWidget *overlay;

//operacja na pliku--------------------------------------------------------------

  int width, height,cykl_czas;
  char znak;
  char *nazwa_pliku = sklej(pacman->Level->plik, ".txt");

  FILE *plik = fopen(nazwa_pliku, "r" );

  width = 0;
  while((znak = getc(plik)) && znak != ';')//szerokosc planszy;
  {
    width *= 10;
    width += znak - '0';
  }

  height = 0;
  while((znak = getc(plik)) && znak != '\n')// wysokosc planszy;
  {
    height *= 10;
    height += znak - '0';
  }

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);//gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Pac-Man");
  gtk_window_set_default_size (GTK_WINDOW (window), width, height);
  gtk_window_set_resizable (GTK_WINDOW(window), FALSE);
  gtk_container_set_border_width (GTK_CONTAINER (window), 15);
  g_signal_connect(G_OBJECT(window), "key_press_event", G_CALLBACK(ruch), pacman);

  gtk_widget_add_events(window, GDK_KEY_PRESS_MASK);

  Pakiet_wroc_do_levele->window = window;
  pacman->Pakiet = Pakiet_wroc_do_levele;

  grid = gtk_grid_new();
  gtk_grid_set_row_spacing(GTK_GRID(grid), 3);
  gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
  gtk_grid_set_column_spacing(GTK_GRID(grid), 3);
  gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
  gtk_container_add(GTK_CONTAINER(window), grid);

  width = 0;
  while((znak = getc(plik)) && znak != ';')//szerokosc planszy;
  {
    width *= 10;
    width += znak - '0';
  }

  height = 0;
  while((znak = getc(plik)) && znak != '\n')// wysokosc planszy;
  {
    height *= 10;
    height += znak - '0';
  }

  char **tbl;
  tbl = malloc(height * sizeof(char *));//tworzenie tablicy tablic dla pp
  for(int i = 0 ; i < height; i++)
  {
    tbl[i] = malloc(width * sizeof(char));
  }
  
  GtkWidget ***pola;
  pola = malloc(height * sizeof(GtkWidget *));//tworzenie tablicy tablic dla labeli
  for(int i = 0 ; i < height; i++)
  {
    pola[i] = malloc(width * sizeof(GtkWidget*));
  }

  label = gtk_label_new(Level->name);
  gtk_widget_set_name (label, "title");//tutaj bedzie char * z ktorym wgl uruchomimy ten program
  gtk_grid_attach (GTK_GRID (grid), label, 0, 0, width, 1);
  
  for(int i = 0 ; i < height ; i ++)
  {
    for(int j = 0 ; j < width ; j ++)
    {
      znak = getc(plik);
      if(znak == '1')
      {
        pola[i][j] = gtk_label_new("o");
        gtk_widget_set_name (pola[i][j], "pp");
        gtk_grid_attach (GTK_GRID (grid), pola[i][j], j, i+1, 1, 1);
        tbl[i][j] = '1';
        pacman->pp++;
      }
      else if(znak == '0')
      {
        pola[i][j] = gtk_label_new("");
        gtk_widget_set_name (pola[i][j], "scianka");
        gtk_grid_attach (GTK_GRID (grid), pola[i][j], j, i+1, 1, 1);
        tbl[i][j] = 0;
      }
      else
      {
        pola[i][j] = gtk_label_new("");
        gtk_widget_set_name (pola[i][j], "zdobyte_pp");
      }
    }
    znak = getc(plik);//'\n'
  }
  
  pacman->width = 0;
  while((znak = getc(plik)) && znak != ';')
  {
    pacman->width *= 10;
    pacman->width += znak - '0';
  }
  pacman->height = 0;
  while((znak = getc(plik)) && znak != '\n')
  {
    pacman->height *= 10;
    pacman->height += znak - '0';
  }

  pacman->x = 0;
  while((znak = getc(plik)) && znak != ';')
  {
    pacman->x *= 10;
    pacman->x += znak - '0';
  }

  pacman->y = 0;
  while((znak = getc(plik)) && znak != '\n')
  {
    pacman->y *= 10;
    pacman->y += znak - '0';
  }

  pacman->left = 0;
  while((znak = getc(plik)) && znak != ';')
  {
    pacman->left *= 10;
    pacman->left += znak - '0';
  }
  pacman->bottom = 0;
  while((znak = getc(plik)) && znak != '\n')
  {
    pacman->bottom *= 10;
    pacman->bottom += znak - '0';
  }

  cykl_czas = 0;
  while((znak = getc(plik)) && znak != '\n')
  {
    cykl_czas *= 10;
    cykl_czas += znak - '0';
  }

  pacman->ile_duszkow = 0;
  while((znak = getc(plik)) && znak != '\n')
  {
    pacman->ile_duszkow *= 10;
    pacman->ile_duszkow += znak - '0';
  }
  pacman->duszki = (duszek *)malloc(sizeof(duszek)*pacman->ile_duszkow);
  //g_print("%d\n", pacman->ile_duszkow);
  for(int i = 0 ; i < pacman->ile_duszkow ; i++)
  {
    pacman->duszki[i].duszek = gtk_label_new("");
    gtk_widget_set_name (pacman->duszki[i].duszek, "duszek");
    gtk_widget_set_size_request (pacman->duszki[i].duszek, pacman->width,pacman->height);
    pacman->duszki[i].zywy = true;
    srand((unsigned) time(&pacman->duszki[i].zwrot));
    pacman->duszki[i].zwrot %= 4;

    pacman->duszki[i].tx = 0;
    while((znak = getc(plik)) && znak != ';')
    {
      pacman->duszki[i].tx *= 10;
      pacman->duszki[i].tx += znak - '0';
    }
    //g_print("%d ", pacman->duszki[i].tx);
    pacman->duszki[i].ty = 0;
    while((znak = getc(plik)) && znak != '\n')
    {
      pacman->duszki[i].ty *= 10;
      pacman->duszki[i].ty += znak - '0';
    }
    //g_print("%d\n", pacman->duszki[i].ty);
    pacman->duszki[i].i_droga = 1;
    //znak = getc(plik);
    //g_print("* koniec %c*", znak);
   // g_print("%s;%d", pacman->duszki[i].droga, pacman->duszki[i].ty);
  }
    
  pacman->ile_bonusow = 0;
  while((znak = getc(plik)) && znak != ';')
  {
    pacman->ile_bonusow *= 10;
    pacman->ile_bonusow += znak - '0';
  }
  
  pacman->czas_bonusy = 0;
  while((znak = getc(plik)) && znak != '\n' && znak != EOF)
  {
    pacman->czas_bonusy *= 10;
    pacman->czas_bonusy += znak - '0';
  }

  pacman->Bonusy = (bonus *)malloc(sizeof(bonus)*pacman->ile_bonusow);
  pacman->bezpieczny = -1;
  pacman->nietykalny = 0;
  for(int i = 0 ; i < pacman->ile_bonusow ; i ++)
  {
    pacman->Bonusy[i].czas = 0;
    while((znak = getc(plik)) && znak != ';')
    {
          pacman->Bonusy[i].czas *= 10;
          pacman->Bonusy[i].czas += znak - '0';
    }
    pacman->Bonusy[i].x = 0;
    while((znak = getc(plik)) && znak != ';')
    {
          pacman->Bonusy[i].x *= 10;
          pacman->Bonusy[i].x += znak - '0';
    }
    pacman->Bonusy[i].y = 0;
    while((znak = getc(plik)) && znak != '\n' && znak != EOF)
    {
          pacman->Bonusy[i].y *= 10;
          pacman->Bonusy[i].y += znak - '0';
    }
    pacman->Bonusy[i].ile_aktywny = 0;
    //g_print("tutaj bonus %d %d %d %d %d\n", pacman->ile_bonusow, pacman->czas_bonusy, pacman->Bonusy[i].czas, pacman->Bonusy[i].x, pacman->Bonusy[i].y);
    //g_print("tutaj bonus %d %d\n", pacman->Bonusy[i].x, pacman->Bonusy[i].y);
  }

  fclose( plik );
  g_timeout_add(cykl_czas*100, (gpointer)(timer), pacman);//dodac czas do wczytania

 //-------------------------------------------------------------

  label = gtk_label_new("PZ:");
  gtk_grid_attach (GTK_GRID (grid), label, width-4, height+3, 1, 1);
  label = gtk_label_new("0");
  pacman->PZ = label;
  gtk_grid_attach (GTK_GRID (grid), label, width-3, height+3, 1, 1);
  label = gtk_label_new("PP:");
  gtk_grid_attach (GTK_GRID (grid), label, width-2, height+3, 1, 1);
  label = gtk_label_new(liczba_na_slowo(pacman->pp));
  pacman->PP = label;
  gtk_grid_attach (GTK_GRID (grid), label, width-1, height+3, 1, 1);
  
  label = gtk_label_new("Time:");
  gtk_grid_attach (GTK_GRID (grid), label, 0, height+3, 1, 1);
  label = gtk_label_new("0");

  gtk_grid_attach (GTK_GRID (grid), label, 1, height+3, 1, 1);
  pacman->time_show = label;

  //-------------------------------------------------------------
  
  overlay = gtk_overlay_new();
  gtk_widget_set_name (overlay, "pacman_pole");
  gtk_grid_attach (GTK_GRID (grid), overlay, 0, 0, width, height);
  
  pacman->tx = 1;
  pacman->ty = 1;
  pacman->table = tbl;
  pacman->pole_pp = pola;
  pacman->pole_pacmana = gtk_fixed_new();
  gtk_overlay_add_overlay(GTK_OVERLAY(overlay), pacman->pole_pacmana);

  gtk_widget_show_all (window);
  pacman->pacman = gtk_label_new("");
  gtk_widget_set_name (pacman->pacman, "pacman");


  //koordynacja Pac-Man
  /*int wx,wy;
  int wx1, wy1;
  gtk_widget_translate_coordinates(pola[0][1], gtk_widget_get_toplevel(grid), 0, 0, &wx1, &wy1);
  gtk_widget_translate_coordinates(pola[1][0], gtk_widget_get_toplevel(grid), 0, 0, &wx, &wy);

  //pozycje startowe
  pacman->x = wx1-11;
  pacman->y = wy-11;
  pacman->width = wx1-wx-10;
  pacman->height = wy-wy1-10;
  
  //odległości 
  pacman->left = pacman->width+10;
  pacman->bottom = pacman->height+10;
  g_print("%d %d", pacman->left, pacman->bottom);*/

  gtk_fixed_put (GTK_FIXED(pacman->pole_pacmana), pacman->pacman,pacman->x,pacman->y);
  gtk_widget_set_size_request (pacman->pacman, pacman->width,pacman->height);
  g_signal_connect(G_OBJECT(window), "key_press_event", G_CALLBACK(ruch), pacman);

  for(int i = 0 ; i < pacman->ile_duszkow ; i++)
  {
    pacman->duszki[i].x =  pacman->x+pacman->left*(pacman->duszki[i].tx-1);
    pacman->duszki[i].y = pacman->y+pacman->bottom*(pacman->duszki[i].ty-1);
    //gtk_fixed_put (GTK_FIXED(pacman->pole_pacmana), pacman->duszki[i].duszek, pacman->x+pacman->width*pacman->duszki[i].tx, pacman->y+pacman->height*pacman->duszki[i].ty);
    gtk_fixed_put (GTK_FIXED(pacman->pole_pacmana), pacman->duszki[i].duszek, pacman->duszki[i].x, pacman->duszki[i].y);
    gtk_widget_set_size_request (pacman->duszki[i].duszek, pacman->width,pacman->height);
  }

  button = gtk_button_new_with_label ("Quit");
  g_signal_connect (button, "clicked", G_CALLBACK (quit_zakoncz), pacman);
  gtk_grid_attach (GTK_GRID (grid), button, 0, height+4, width, 1);

  gtk_widget_show_all (window);  
}
