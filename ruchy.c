#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "naglowkowy.h"
#include "zamykanie.h"
#include "wyniki.h"
#include "plansza.h"

typedef struct pakiet_zakoncz_struct
{
  Pacman *pacman;
  GtkWidget *okienko_info;
}pakiet_zakoncz;

void zamknij_okno_info(GtkWidget *widget, gpointer data)
{
  pakiet_zakoncz *Pakiet_Zakoncz = (pakiet_zakoncz *) data;
  gtk_widget_show(Pakiet_Zakoncz->pacman->Pakiet->window_prev);
  gtk_widget_set_sensitive(Pakiet_Zakoncz->pacman->Pakiet->window, true);
  gtk_widget_destroy(Pakiet_Zakoncz->pacman->Pakiet->window);
  gtk_widget_destroy(Pakiet_Zakoncz->okienko_info);
}

void zamknij_okno_info_otworz(GtkWidget *widget, gpointer data)
{
  pakiet_zakoncz *Pakiet_Zakoncz = (pakiet_zakoncz *) data;
  gtk_widget_show(Pakiet_Zakoncz->pacman->Pakiet->window_prev);
  gtk_widget_destroy(Pakiet_Zakoncz->pacman->Pakiet->window);
}

void zakoncz(Pacman *pacman, bool wynik)
{
  if(wynik)
  {
    zapisz_wynik(pacman->Pakiet->Gamer->id,pacman->pz,pacman->Level->plik);
  }

  GtkWidget *window;
  GtkWidget *grid;
  GtkWidget *button;
  GtkWidget *label;

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  
  pakiet_zakoncz *Pakiet_Zakoncz = (pakiet_zakoncz *)malloc(sizeof(pakiet_zakoncz));
  Pakiet_Zakoncz->pacman = pacman;
  Pakiet_Zakoncz->okienko_info = window;

  if(wynik)
  {
    gtk_window_set_title (GTK_WINDOW (window), "Winning");
  }
  else
  {
    gtk_window_set_title (GTK_WINDOW (window), "Failure");
  }
  
  gtk_window_set_default_size (GTK_WINDOW (window), 200, 100);
  gtk_container_set_border_width (GTK_CONTAINER (window), 15);
  g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(zamknij_okno_info_otworz), Pakiet_Zakoncz);

  gtk_widget_set_sensitive (window, true);
  gtk_widget_set_sensitive(pacman->Pakiet->window, false);
  
  grid = gtk_grid_new();
  gtk_grid_set_row_spacing(GTK_GRID(grid), 3);
  gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
  gtk_grid_set_column_spacing(GTK_GRID(grid), 3);
  gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
  gtk_container_add(GTK_CONTAINER(window), grid);

  if(wynik)
  {
    label = gtk_label_new("You have won");
  }
  else
  {
    label = gtk_label_new("You have failed");
  }
  
  gtk_grid_attach (GTK_GRID (grid), label, 0, 0, 1, 1);
  
  button = gtk_button_new_with_label ("Quit");
  g_signal_connect(button, "clicked",  G_CALLBACK (zamknij_okno_info),Pakiet_Zakoncz);
  gtk_grid_attach (GTK_GRID (grid), button, 0, 1, 1, 1);

  gtk_widget_show_all (window);
}

void quit_zakoncz(GtkWidget *widget, gpointer *data)
{
  Pacman *pacman = (Pacman *)data;
  pacman->kontynuuj = false;
  gtk_widget_show(pacman->Pakiet->window_prev);
  gtk_widget_destroy(pacman->Pakiet->window);
}

void quit_zakoncz_otworz(GtkWidget *widget, gpointer *data)
{
  Pacman *pacman = (Pacman *)data;
  pacman->kontynuuj = false;
  gtk_widget_show(pacman->Pakiet->window_prev);
}

void zdobyty_punkt(Pacman *pacman)
{
  if(pacman->table[pacman->ty][pacman->tx] == '1')
  {
    pacman->table[pacman->ty][pacman->tx] = '2';
    gtk_widget_set_name(pacman->pole_pp[pacman->ty][pacman->tx], "zdobyte_pp");
    gtk_label_set_text (GTK_LABEL(pacman->pole_pp[pacman->ty][pacman->tx]), "");
    pacman->pp--;
    gtk_label_set_text (GTK_LABEL(pacman->PP), liczba_na_slowo(pacman->pp));
    if(pacman->pp == 0)
    {
      zakoncz(pacman, true);
      pacman->kontynuuj = false;
    }
  }
}

gboolean timer(gpointer *data)
{
  Pacman *pacman = (Pacman *) data;
  if(!pacman->kontynuuj)
    return false;

  pacman->time ++;
  gtk_label_set_text (GTK_LABEL(pacman->time_show), liczba_na_slowo(pacman->time));

  switch (pacman->kierunek)
  {
    case 1:
    {
      if(pacman->table[pacman->ty-1][pacman->tx])
      {
        pacman->ty--;
        pacman->y -= pacman->bottom;
        gtk_fixed_move (GTK_FIXED(pacman->pole_pacmana), pacman->pacman,pacman->x, pacman->y);
        zdobyty_punkt(pacman);
      }
      break;
    }
    case 2:
    {
      if(pacman->table[pacman->ty+1][pacman->tx])
      {
        pacman->ty++;
        pacman->y += pacman->bottom;
        gtk_fixed_move (GTK_FIXED(pacman->pole_pacmana), pacman->pacman,pacman->x, pacman->y);
        zdobyty_punkt(pacman);
      }
      break;
    }
    case 3:
    {
      if(pacman->table[pacman->ty][pacman->tx-1])
      {
        pacman->tx--;
        pacman->x -= pacman->left;
        gtk_fixed_move (GTK_FIXED(pacman->pole_pacmana), pacman->pacman,pacman->x, pacman->y);
        zdobyty_punkt(pacman);
      }
      break;
    }
    case 4:
    {
      if(pacman->table[pacman->ty][pacman->tx+1])
      {
        pacman->tx++;
        pacman->x += pacman->left;
        gtk_fixed_move (GTK_FIXED(pacman->pole_pacmana), pacman->pacman,pacman->x, pacman->y);
        zdobyty_punkt(pacman);
      }
      break;
    }
  }

  for(int i = 0 ; i < pacman->ile_duszkow ; i ++)
  {
    if(pacman->duszki[i].tx == pacman->tx && pacman->duszki[i].ty == pacman->ty)
    {
      if(pacman->duszki[i].zywy)
      {
        if(pacman->nietykalny)
        {
          pacman->duszki[i].zywy = false;
          gtk_widget_set_name(pacman->duszki[i].duszek, "nie ma etykiety"); 
          pacman->pz += pacman->czas_bonusy;
          gtk_label_set_text (GTK_LABEL(pacman->PZ), liczba_na_slowo(pacman->pz));        
        }
        else
        {
          pacman->kontynuuj = false;
          zakoncz(pacman,false);
          break;
        }
      }
    }
    if(pacman->duszki[i].zwrot == 0)
    {
      if(pacman->table[pacman->duszki[i].ty][pacman->duszki[i].tx-1])
      {
        pacman->duszki[i].tx --;
        pacman->duszki[i].x -= pacman->left;
        gtk_fixed_move (GTK_FIXED(pacman->pole_pacmana), pacman->duszki[i].duszek,pacman->duszki[i].x, pacman->duszki[i].y);
      }
      else
      {
        srand((unsigned) time(&pacman->duszki[i].zwrot));
        pacman->duszki[i].zwrot %= 4;
      }
    }
    if(pacman->duszki[i].zwrot == 1)
    {
      if(pacman->table[pacman->duszki[i].ty][pacman->duszki[i].tx+1])
      {
        pacman->duszki[i].tx ++;
        pacman->duszki[i].x += pacman->left;
        gtk_fixed_move (GTK_FIXED(pacman->pole_pacmana), pacman->duszki[i].duszek,pacman->duszki[i].x, pacman->duszki[i].y);
      }
      else
      {
        srand((unsigned) time(&pacman->duszki[i].zwrot));
        pacman->duszki[i].zwrot %= 4;
      }
    }
    if(pacman->duszki[i].zwrot == 2)
    {
      if(pacman->table[pacman->duszki[i].ty+1][pacman->duszki[i].tx])
      {
        pacman->duszki[i].ty ++;
        pacman->duszki[i].y += pacman->bottom;
        gtk_fixed_move(GTK_FIXED(pacman->pole_pacmana), pacman->duszki[i].duszek,pacman->duszki[i].x, pacman->duszki[i].y);
      }
      else
      {
        srand((unsigned) time(&pacman->duszki[i].zwrot));
        pacman->duszki[i].zwrot %= 4;
      }
    }
    if(pacman->duszki[i].zwrot == 3)
    {
      if(pacman->table[pacman->duszki[i].ty-1][pacman->duszki[i].tx])
      {
        pacman->duszki[i].ty --;
        pacman->duszki[i].y -= pacman->bottom;
        gtk_fixed_move (GTK_FIXED(pacman->pole_pacmana), pacman->duszki[i].duszek,pacman->duszki[i].x, pacman->duszki[i].y);
      }
      else
      {
        srand((unsigned) time(&pacman->duszki[i].zwrot));
        pacman->duszki[i].zwrot %= 4;
      }
    }

    if(pacman->duszki[i].tx == pacman->tx && pacman->duszki[i].ty == pacman->ty)
    {
      if(pacman->duszki[i].zywy)
      {
        if(pacman->nietykalny)
        {
          pacman->duszki[i].zywy = false;
          gtk_widget_set_name(pacman->duszki[i].duszek, "nie ma etykiety"); 
          pacman->pz += pacman->czas_bonusy;
          gtk_label_set_text (GTK_LABEL(pacman->PZ), liczba_na_slowo(pacman->pz));        
        }
        else
        {
          pacman->kontynuuj = false;
          zakoncz(pacman,false);
        }
      }
    }
  }

  if(pacman->bezpieczny != -1)
  {
    if(pacman->tx == pacman->Bonusy[pacman->bezpieczny].x && pacman->ty == pacman->Bonusy[pacman->bezpieczny].y)
    {
      pacman->pz += pacman->Bonusy[pacman->bezpieczny].ile_aktywny;
      gtk_label_set_text (GTK_LABEL(pacman->PZ), liczba_na_slowo(pacman->pz));
      pacman->Bonusy[pacman->bezpieczny].ile_aktywny = 0;
      for(int i = 0 ; i < pacman->ile_duszkow ; i++)
      {
        if(pacman->duszki[i].zywy)
          gtk_widget_set_name(pacman->duszki[i].duszek, "niektywny_duszek");
      }
    }
    else
      pacman->Bonusy[pacman->bezpieczny].ile_aktywny--;
    if(pacman->Bonusy[pacman->bezpieczny].ile_aktywny == 0)
    {
      if(pacman->table[pacman->Bonusy[pacman->bezpieczny].y][pacman->Bonusy[pacman->bezpieczny].x] == '2')
        gtk_widget_set_name(pacman->pole_pp[pacman->Bonusy[pacman->bezpieczny].y][pacman->Bonusy[pacman->bezpieczny].x], "zdobyte_pp");
      else
        gtk_widget_set_name(pacman->pole_pp[pacman->Bonusy[pacman->bezpieczny].y][pacman->Bonusy[pacman->bezpieczny].x], "pp");
      pacman->bezpieczny = -1;
      pacman->nietykalny = pacman->czas_bonusy+2;
    }
  }

  if(pacman->bezpieczny == -1)
  {
    for(int i = 0 ; i < pacman->ile_bonusow ; i ++)
    {
      if(pacman->time == pacman->Bonusy[i].czas)
      {
        pacman->bezpieczny = i;
        pacman->Bonusy[i].ile_aktywny = pacman->czas_bonusy;
        gtk_widget_set_name(pacman->pole_pp[pacman->Bonusy[i].y][pacman->Bonusy[i].x], "bonusik");
        break;
      }
    }
  }

  if(pacman->nietykalny == 1)
  {
    for(int i = 0 ; i < pacman->ile_duszkow ; i++)
        {
          if(pacman->duszki[i].zywy)
            gtk_widget_set_name(pacman->duszki[i].duszek, "duszek");
          else
          {
            gtk_widget_set_name(pacman->duszki[i].duszek, "nie ma etykiety");
          }
          
        }
  }
  if(pacman->nietykalny != 0)
  {
    pacman->nietykalny --;
  }

  return pacman->kontynuuj;
}


gboolean ruch(GtkWidget *widget, GdkEventKey *event, gpointer *data)
{
  Pacman *pacman = (Pacman *) data;
  bool ruchy = false;

  if(!pacman->kontynuuj)
    return false;

  if (event->keyval == GDK_KEY_w)
  {
    pacman->kierunek = 1;
    ruchy = TRUE;
  }
  if (event->keyval == GDK_KEY_s)
  {
    pacman->kierunek = 2;
    ruchy = TRUE;
  }
  if (event->keyval == GDK_KEY_a)
  {
    pacman->kierunek = 3;
    ruchy = TRUE;
  }
  if (event->keyval == GDK_KEY_d)
  {
    pacman->kierunek = 4;
    ruchy = TRUE;
  }

  return ruchy;
}