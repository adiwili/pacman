#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "naglowkowy.h"

void przepisz_plik(char *dest, char *source)
{
  FILE *plik = fopen(dest, "w");
  FILE *pom = fopen(source, "r");
  char znak;
  while((znak = getc(pom)) && znak != EOF)//szerokosc planszy;
    fputc(znak,plik);

  fclose(plik);
  fclose(pom);
}

void zmiana_w_punkty(int id, int wynik, int odjac)
{
  //printf("%d, %d\n", id, wynik);

  FILE *plik = fopen("gamers.txt", "r" );
  FILE *pom = fopen("pomocniczy.txt", "w" );
  int id_temp, wynik_temp;
  char znak;
  while((znak = getc(plik)) && znak != EOF)
  {
    if(znak == ':')
    {
      putc(znak, pom);//dwukropek
      id_temp = 0;
      while((znak = getc(plik)) && znak != ';')
      {
        putc(znak, pom);//przepisz id
        id_temp *= 10;
        id_temp += znak -'0';
      }
      putc(znak, pom);//srednik
      while((znak = getc(plik)) && znak != '~')
      {
        fputc(znak, pom);//przepisz nick
      }
      putc(znak, pom);//~
      //printf("%d\n", id_temp);
      if(id == id_temp)
      {
        wynik_temp = 0;//pobierz wynik
        while((znak = getc(plik)) && znak != '|')
        {
          wynik_temp *= 10;
          wynik_temp += znak -'0';
        }
        fprintf(pom, "%d|\n", wynik_temp-odjac+wynik);
      }
      else
      {
        while((znak = getc(plik)) && znak != '|')
        {
          putc(znak, pom);//przepisz wynik
        }
        putc(znak, pom);//'|'
        putc('\n', pom);//'\n'
      }
    }
  }
  fclose(plik);
  fclose(pom);

  przepisz_plik("gamers.txt","pomocniczy.txt");
}

void zapisz_wynik(int id, int wynik, char *nazwa)
{
  //printf("wyniki %d %d\n", id, wynik);
  char *doklej = "_wyniki.txt";
  char *nazwa_pliku = sklej(nazwa, doklej);
  //printf("wyniki %s\n", nazwa_pliku);
  //nazwa = (char *)realloc(nazwa,sizeof(char)*(x+y));
 // nazwa = strcat(nazwa, doklej);
  //printf("%s", nazwa_pliku);
  int id_temp, wynik_temp;
  int odjac = 0;
  char znak;
  bool nowy = true;
  bool dopisz = false;

  FILE *plik = fopen(nazwa_pliku, "r" );
  FILE *pom = fopen("pomocniczy.txt", "w" );
  
  while((znak = getc(plik)) && znak != EOF)//szerokosc planszy;
  {
    if(znak == ':')
    {
      id_temp = 0;
      while((znak = getc(plik)) && znak != ';')
      {
        id_temp *= 10;
        id_temp += znak -'0';
      }
      wynik_temp = 0;
      while((znak = getc(plik)) && znak != '\n')
      {
        wynik_temp *= 10;
        wynik_temp += znak -'0';
      }
      if(id_temp == id)
      {
        nowy = false;
        if(wynik > wynik_temp)
        {
          odjac = wynik_temp;
          wynik_temp = wynik;
          dopisz = true;
        }
      }
      fprintf(pom, ":%d;%d\n", id_temp, wynik_temp);
      //printf(":%d;%d\n", id_temp, wynik_temp);
    }
  }
  if(nowy)
  {
    fprintf(pom, ":%d;%d\n", id, wynik);
    dopisz = true;
    //printf(":%d;%d\n", id, wynik);
  }
  fclose(plik);
  fclose(pom);
  
  przepisz_plik(nazwa_pliku,"pomocniczy.txt");

  if(dopisz)
    zmiana_w_punkty(id,wynik,odjac);
}