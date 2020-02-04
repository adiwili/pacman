#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "zamykanie.h"

typedef struct user_score
{
      int id;
      int score;
      char *nick;
}score;

void przepisz(score *Rank)
{
      FILE *fp;
      if ((fp=fopen("ranking.txt", "w"))==NULL)
        {
          printf ("File error\n");
          exit(1);
        }
      for(int i = 0 ; i < 5 ; i ++)
      {
        fprintf (fp, "%s;%d\n", Rank[i].nick, Rank[i].score);
      }
      fclose (fp);
}

void znajdz_gamer_na_pozycje(int n, score *Rank)
{
    int id,user_score,max_score = -1;
    char znak;
    char *nick = (char *)malloc(sizeof(char)*51);
    Rank[n].nick = (char *)malloc(sizeof(char)*51);
    FILE *plik = fopen( "gamers.txt", "r" );
    
    while((znak = getc(plik)) && znak != EOF)
    {
      if(znak == ':')
      {
        id = 0;
        while((znak = getc(plik)) && znak != ';')
        {
          id *= 10;
          id += znak - '0';
        }
        int m = 0;
        nick[m] = '\0';
        while((znak = getc(plik)) && znak != '~')
        {
          nick[m] = znak;
          m++;
        }
        nick[m] = '\0';
        user_score = 0;
        while((znak = getc(plik)) && znak != '|')
        {
          user_score *= 10;
          user_score += znak - '0';
        }
        bool nowy = true;
        if(user_score > max_score)
        {
          for(int j = 0 ; j < n ; j ++)
          {
            if(Rank[j].id == id)
              nowy = false;
          }
          if(nowy)
          {
            Rank[n].id = id;
            Rank[n].score = user_score;
            strcpy(Rank[n].nick, nick);
            max_score = user_score;
          }
        }
      }
    }
    fclose( plik );
  free(nick);
}

void przygotowanie_rankingu()
{
    // moj_typ *m;

    // m = inicjalizuj();

    // operacja1(m);

    // zwolnij(m);
    
      score *Rank;
      Rank = (score *)malloc(sizeof(score)*5);
      for(int i = 0 ; i < 5 ; i ++)
      {
        Rank[i].id = -1;
        Rank[i].score = -1;
        Rank[i].nick = (char *)malloc(sizeof(char)*51);
        Rank[i].nick[0] = '\0';
        znajdz_gamer_na_pozycje(i,Rank);
        if(Rank[i].id == -1)
        {
          Rank[i].nick[0] = '\0';
          Rank[i].score = 0;
        }
      }
      for(int i = 0 ; i < 5 ; i ++)
        przepisz(Rank);
}

void uruchom_ranking(GtkWidget *widget, gpointer data)
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
  gtk_window_set_title (GTK_WINDOW (window), "RANK");
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

  label = gtk_label_new("Ranking");
  gtk_grid_attach (GTK_GRID (grid), label, 0, 0, 3, 1);

  int m;
  char x;
  
  char *number;
  number = (char *)malloc(sizeof(char)*3);
  number[0] = 1 + '0';
  number[1] = '.';
  number[2] = '\0';
  
  char *nick;
  nick = (char *)malloc(sizeof(char)*51);

  char *score;
  score = (char *)malloc(sizeof(char)*10);
  score[9] = '\0';

  przygotowanie_rankingu();

  FILE *plik = fopen( "ranking.txt", "r" );  

   for(int i = 0 ; i < 5 ; i ++)
   {
      number[0] = i + 1 + '0';
      label = gtk_label_new(number);
      gtk_grid_attach (GTK_GRID (grid), label, 0, i+1, 1, 1);
      m = 0;
      while((x = getc(plik)) && x != ';')
      {
        nick[m] = x;
        m++;
      }
      nick[m] = '\0';

     label = gtk_label_new(nick);
     gtk_grid_attach (GTK_GRID (grid), label, 1, i+1, 1, 1);

      m = 0;
      while((x = getc(plik)) && x != '\n' && x != EOF)
      {
        score[m] = x;
        m++;
      }
      score[m] = '\0';

      label = gtk_label_new(score);
      gtk_grid_attach (GTK_GRID (grid), label, 2, i+1, 1, 1);
      if(x == EOF)
        break;
   }
   fclose( plik );

  button = gtk_button_new_with_label ("Quit");
  g_signal_connect (button, "clicked", G_CALLBACK (zamknij_okno), Pakiet_wroc_do_menu);
  g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(otworz_poprzednie), Pakiet_wroc_do_menu);
  gtk_grid_attach (GTK_GRID (grid), button, 0, 6, 3, 1);
  gtk_widget_show_all (window);
}