#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "naglowkowy.h"

void dopisz(gamer *Gamer)
{
  FILE *fp;
  if ((fp = fopen("gamers.txt", "a"))==NULL)
  {
        printf ("File error\n");
        exit(1);
  }
  fprintf (fp, ":%d;%s~0|\n", Gamer->id, Gamer->nick);
  fclose (fp);
}

void log_in (GtkWidget *widget, gpointer data)
{
  przyciski *Przyciski = (przyciski *) data;
  const gchar *entry_text = gtk_entry_get_text (GTK_ENTRY(Przyciski->entry));
  const gchar *beginning_text = "Continue as ";
  gchar *beg_text;
  beg_text = (char *)malloc(sizeof(char)*63);

  Przyciski->Gamer = (gamer *)malloc(sizeof(gamer));
  Przyciski->Gamer->nick = (char *)malloc(sizeof(char)*51);

  char x;
  bool nowy = true;
  int id = 0;

  FILE *gamers;
  if ((gamers = fopen("gamers.txt", "r"))==NULL)
  {
    printf ("File error\n");
    exit(1);
  }
    while((x = getc(gamers)) && x != EOF)
    {
      if(x == ':')
      {
        id = 0;
        while((x = getc(gamers)) && x != ';')
        {
          id *= 10;
          id += x - '0';
        }
        int i = 0;
        nowy = true;
        while((x = getc(gamers)) && x == entry_text[i])
        {
          i++;
        }

        if(x == '~' && entry_text[i] == '\0')
        {
          nowy = false;
          break;
        }
      }
    } 
    fclose(gamers);

    if(nowy)
    {
      Przyciski->Gamer->id = id+1;
      Przyciski->Gamer->nick = entry_text;
      dopisz(Przyciski->Gamer);
    }
    else
    {
      Przyciski->Gamer->id = id;
      Przyciski->Gamer->nick = entry_text;
    }
    

  int i;
  for(i = 0 ; beginning_text[i]!= '\0' ; i ++)
  {
    beg_text[i] = beginning_text[i];
  }
  beg_text[i] = ' ';
  for(int j = 0 ; beg_text[j+i-1] != '\0' ; j ++)
  {
    beg_text[j+i] = entry_text[j];
  }
  gchar * text = beg_text;
  
  gtk_label_set_text(GTK_LABEL(Przyciski->return_label), text);
  gtk_widget_show (Przyciski->return_label);
  gtk_widget_show (Przyciski->continue_button);
  gtk_widget_hide (Przyciski->empty_label);
  Przyciski->Pakiet->Gamer = Przyciski->Gamer;
}