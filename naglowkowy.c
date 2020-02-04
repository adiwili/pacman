#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

void print_hello (GtkWidget *widget, gpointer data)
{
    g_print ("Hello_1 World\n");
}

void print_entry (GtkWidget *widget, gpointer data)
{
  gchar nick[52];
  g_print("%s", nick);
}

char *liczba_na_slowo(int a)
{
  char *slowo;
  if(a == 0)
  {
    slowo = (char *)malloc(sizeof(char)*2);
    slowo[0] = '0';
    slowo[1] = '\0';
  }
  else
  {
    int i = 0;
    int j = a;
    while(j>0)
    {
      i++;
      j /= 10;
    }
    slowo = (char *)malloc(sizeof(char)*(i+1));
    slowo[i] = '\0';
    while(i>0)
    {
      i--;
      slowo[i] = a%10 + '0';
      a /= 10;
    }
  }
  return slowo;
}

char *sklej(char *nazwa,char *doklej)
{
  int x = strlen(nazwa);
  int y = strlen(doklej);
  char *nowa_nazwa = (char *)malloc(sizeof(char)*(x+y+1));
  for(int i = 0 ; nazwa[i]!= '\0' ; i++)
    nowa_nazwa[i] = nazwa[i];
  for(int i = 0 ; doklej[i]!='\0' ; i++)
    nowa_nazwa[i+x] = doklej[i];
  nowa_nazwa[x+y] = '\0';
  return nowa_nazwa;
}

typedef struct user
{
  int id;
  const gchar *nick;
}gamer;

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

typedef struct do_poziomu
{
  levele *Levele;
  pakiet *Pakiet;
}do_level;