/*
 ============================================================================
 Name        : Aufgabe 6.8.8
 Author      : Markus Vogel
 Version     : V1.0
 Copyright   : free sample
 Description : Personenverwaltung mit Datei
               Personendatei ist wie folgt zeilenweise aufgebaut:
               Hans
               Meier
               12
               Fritz
               Hauser
               20
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Person
{
  char vorname[64];
  char nachname[64];
  int alter;
};

//Erfassen der Daten für eine Person
void erfassePerson(struct Person *pPerson); //Call by Reference

//Ausgeben der Daten einer Person
void ausgabePerson(struct Person person);   //Call by Value

//schreibt Personendaten einer Person in File
void schreibePerson(FILE *pFile, struct Person person);

//liest Personendaten einer Person aus File
int liesPerson(FILE *pFile, struct Person *person);


int main()
{
  FILE *pFile;
  struct Person personen[10];
  int i;

  printf("\n3 Personen erfassen: \n");
  for (i = 0; i < 3; i++)
  {
    erfassePerson(&(personen[i]));
  }

  printf("\n3 Personen ausgeben:\n");
  for (i = 0; i < 3; i++)
  {
    ausgabePerson(personen[i]);
  }

  printf("\n3 Personen auf File schreiben\n");
  pFile = fopen("Personen.dat", "w");
  if (pFile != NULL)
  {
    for (i = 0; i < 3; i++)
    {
     schreibePerson(pFile, personen[i]);
    }
  }
  fclose(pFile);

  printf("\n3 Personen aus File lesen\n");
  pFile = fopen("Personen.dat", "r");
  if (pFile != NULL)
  {
    for (i = 0; i < 3; i++)
    {
     liesPerson(pFile, &(personen[i]));
    }
  }
  fclose(pFile);

  printf("\n3 Personen ausgeben:\n");
  for (i = 0; i < 3; i++)
  {
    ausgabePerson(personen[i]);
  }

  return 0;
}

void erfassePerson(struct Person *pPerson)
{
  printf("Vorname:  ");
  scanf("%s", pPerson->vorname);
  printf("Nachname: ");
  scanf("%s", pPerson->nachname);
  printf("Alter:    ");
  scanf("%d", &(pPerson->alter));
}

void ausgabePerson(struct Person person)
{
  printf("Vorname:  %s\n", person.vorname);
  printf("Nachname: %s\n", person.nachname);
  printf("Alter:    %d\n", person.alter);
}

void schreibePerson(FILE *pFile, struct Person person)
{
  fprintf(pFile, "%s\n", person.vorname);
  fprintf(pFile, "%s\n", person.nachname);
  fprintf(pFile, "%d\n", person.alter);
}
/*
int liesPerson(FILE *pFile, struct Person *person)
{
  fscanf(pFile, "%s", person->vorname);
  fscanf(pFile, "%s", person->nachname);
  fscanf(pFile, "%d", &person->alter);
  return 1;
}
*/


int liesPerson1(FILE *pFile, struct Person *person)
{
  char zeile[64];
  fgets(zeile, 64, pFile);
  zeile[strlen(zeile)-1] = 0x00;   //Zeilenumbruch entfernen
  strcpy(person->vorname, zeile);

  fgets(zeile, 64, pFile);
  zeile[strlen(zeile)-1] = 0x00;   //Zeilenumbruch entfernen
  strcpy(person->nachname, zeile);

  fgets(zeile, 64, pFile);
  person->alter = atoi(zeile);     //String auf int wandeln
  return 1;
}

