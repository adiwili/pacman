#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

//functions-------------------------------------------

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

//typedef-------------------------------------------

typedef struct user
{
  int id;
  const gchar *nick;
}gamer;

gamer* malloc_gamer(int x)
{
  return (gamer *)malloc(sizeof(gamer)*x);
}

void free_gamer(gamer *x)
{
  free(x);
}

//--------------------------------------------------------

typedef struct poziom
{
  int id;
  char *name;
  char *plik;
  GtkWidget *button_wywolujacy;
}level;

level* malloc_level(int x)
{
  return (level *)malloc(sizeof(level)*x);
}

void free_level(level *x)
{
  free(x);
}

//--------------------------------------------------------

typedef struct poziomy
{
  int ile;
  level *Poziomy;
}levele;

levele* malloc_levele(int x)
{
  return (levele *)malloc(sizeof(levele)*x);
}

void free_levele(levele *x)
{
  free(x);
}

//--------------------------------------------------------

typedef struct pakiet_do_zamkniecia
{
    GtkWidget *window;
    GtkWidget *window_prev;
    gamer *Gamer;
}pakiet;

pakiet* malloc_pakiet(int x)
{
  return (pakiet *)malloc(sizeof(pakiet)*x);
}

void free_pakiet(pakiet *x)
{
  free(x);
}

//--------------------------------------------------------

typedef struct pakiet_przyciskow
{
  GtkWidget *continue_button;
  GtkWidget *return_label;
  GtkWidget *empty_label;
  GtkWidget *entry;
  pakiet *Pakiet;
  gamer *Gamer;
}przyciski;

przyciski* malloc_przyciski(int x)
{
  return (przyciski *)malloc(sizeof(przyciski)*x);
}

void free_przyciski(przyciski *x)
{
  free(x);
}

//--------------------------------------------------------

typedef struct do_poziomu
{
  levele *Levele;
  pakiet *Pakiet;
}do_level;

do_level* malloc_do_level(int x)
{
  return (do_level *)malloc(sizeof(do_level)*x);
}

void free_do_level(do_level *x)
{
  free(x);
}

//--------------------------------------------------------

// struct m_typ 
// {
//   int pole;
// };
// typedef struct m_typ moj_typ;

// moj_typ* inicjalizuj(void)
// { 
//   moj_typ *tmp = malloc(sizeof(moj_typ));
//   tmp -> pole = 0;
//   return tmp;
// }

// void operacja1(moj_typ *m)
// {

//   m->pole = 7;
// }
// void operacja2(moj_typ *m)
// {

//   m->pole = 77;
// }


// void skasuj(moj_typ *m) {

//   free(m);
// }