/*
 ============================================================================
 Name        : Aufgabe 6.8.9
 Author      : Markus Vogel
 Version     : V1.0
 Copyright   : free sample
 Description : erweiterte Personenverwaltung mit Datei
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

//Erfassen der Daten einer Person
void erfassePerson(struct Person *pPerson);

//Ausgeben der Daten einer Person
void zeigePerson(struct Person person);

//zeigt alle erfassten Personen
void zeigeAllePersonen(struct Person personen[], int anzPersonen);

//schreibt erfasste Personendaten in File
void speicherePersonenDatei(char dateiName[], struct Person personen[], int anzPersonen);

//liest Personendaten aus File
int liesPersonenDatei(char dateiName[], struct Person personen[]);

//schreibt enzelne Person in File
void schreibePerson(FILE *pFile, struct Person person);

//liest einzelne Person aus File
int liesPerson(FILE *pFile, struct Person *person);

//zeigt Menu an und gibt Auswahl zurueck
int liesMenuAuswahl();

//sucht Person in Personendaten, gibt Index zurueck, bei nicht gefunden -1
int suchePerson(struct Person personen[], char name[], char vorname[], int anzPersonen);

//aendert Personendaten einer Person
void aenderePerson(struct Person *person);

//loesche Person an Stelle index aus Personendaten
void loeschePerson(struct Person personen[], int index, int *anzPersonen);



int main( int argc, char *argv[])
{
  struct Person person;
  struct Person personen[100];  //Personenarray
  int anzPersonen = 0;          //Anzahl Personen in Array
  int currPersIdx = -1;         //Indes der selektierten Person, -1 wenn keine selektiert
  char dateiName[256] = "Personen.dat";

  if (argc == 2)
  {
    strcpy(dateiName, argv[1]);  //Dateiname als Aufrufparameter
  }

  char name[64];
  char vorname[64];
  int menuAuswahl = 0;

  while ((menuAuswahl = liesMenuAuswahl()) != 9)
  {
    switch (menuAuswahl)
    {
      case 0:
        anzPersonen = liesPersonenDatei(dateiName, personen);
        break;
      case 1:
        zeigeAllePersonen(personen, anzPersonen);
        break;
      case 2:
        erfassePerson(&person);
        personen[anzPersonen++] = person;
        break;
      case 3:
        printf("suche Vorname Name :");
        scanf("%s %s", vorname, name);
        currPersIdx = suchePerson(personen, name, vorname, anzPersonen);
        if (currPersIdx >= 0)
          zeigePerson(personen[currPersIdx]);
        else
          printf("%s %s nicht gefunden\n", vorname, name);
        break;
      case 4:
        printf("aendere Vorname Name :");
        scanf("%s %s", vorname, name);
        currPersIdx = suchePerson(personen, name, vorname, anzPersonen);
        if (currPersIdx >= 0)
          aenderePerson(&(personen[currPersIdx]));
        else
          printf("%s %s nicht gefunden\n", vorname, name);
        break;
      case 5:
        printf("loesche Vorname Name :");
        scanf("%s %s", vorname, name);
        currPersIdx = suchePerson(personen, name, vorname, anzPersonen);
        if (currPersIdx >= 0)
          loeschePerson(personen, currPersIdx, &anzPersonen);
        else
          printf("%s %s nicht gefunden\n", vorname, name);
        break;
      case 8:
        speicherePersonenDatei(dateiName, personen, anzPersonen);
        break;
      default:
        printf("ungueltige Auswahl\n");
        break;
    }
  }
  return 0;
}

//Erfassen der Daten einer Person
void erfassePerson(struct Person *pPerson)
{
  fflush(stdin);
  printf("Vorname:  ");
  scanf("%s", pPerson->vorname);
  printf("Nachname: ");
  scanf("%s", pPerson->nachname);
  printf("Alter:    ");
  scanf("%d", &(pPerson->alter));
}

//Ausgeben der Daten einer Person
void zeigePerson(struct Person person)
{
  printf("Vorname:  %s\n", person.vorname);
  printf("Nachname: %s\n", person.nachname);
  printf("Alter:    %d\n", person.alter);
}

//zeigt alle Personen
void zeigeAllePersonen( struct Person personen[], int anzPersonen)
{
  int i;
  for (i = 0; i < anzPersonen; i++)
    zeigePerson(personen[i]);
}

//schreibt Personendaten in File
void speicherePersonenDatei(char dateiName[], struct Person personen[], int anzPersonen)
{
  FILE *pFile;
  pFile = fopen(dateiName, "w");
  int i;
  if (pFile != NULL)
  {
    for (i = 0; i < anzPersonen; i++)
      schreibePerson(pFile, personen[i]);

    fclose(pFile);
  }
}

//liest Personendaten  aus File
int liesPersonenDatei(char dateiName[], struct Person personen[])
{
  FILE *pFile;
  pFile = fopen(dateiName, "r");
  int i = 0;
  if (pFile != NULL)
  {
    while ( liesPerson(pFile, &(personen[i])) == 1)
      i++;

    fclose(pFile);
  }

  return i;
}

//zeigt Menu an und gibt Auswahl zurueck
int liesMenuAuswahl()
{
  int auswahl;
  printf("\nPersonenverwaltung:\n");
  printf("0: Personen aus Datei laden\n");
  printf("1: Alle Personen anzeigen\n");
  printf("2: Neue Person eingeben\n");
  printf("3: Person suchen\n");
  printf("4: Person aendern\n");
  printf("5: Person loeschen\n");
  printf("8: Personen speichern\n");
  printf("9: Programm beenden\n");
  printf("Ihre Auswahl: ");
  scanf("%d", &auswahl);
  return auswahl;
}

//sucht Person in Personendaten, gibt Index zurueck, bei nicht gefunden -1
int suchePerson(struct Person personen[], char nachname[], char vorname[], int anzPersonen)
{
  int i = 0;
  int found = -1;
  while (found == -1 && i < anzPersonen)
  {
    if (strcmp(personen[i].vorname, vorname) == 0)
    {
      if (strcmp(personen[i].nachname, nachname) == 0)
      {
        found = i;
      }
    }
    i++;
  }
  return found;
}

//aendert Personendaten einer Person
void aenderePerson(struct Person *person)
{
  zeigePerson(*person);
  erfassePerson(person);
}

//loesche Person an Stelle index aus Personendaten
void loeschePerson(struct Person personen[], int index, int *anzPersonen)
{
  int i;
  for (i = index; i < *anzPersonen; i++)
    personen[i] = personen[i+1];

  (*anzPersonen)--;
}

//schreibt enzelne Person in File
void schreibePerson(FILE *pFile, struct Person person)
{
  fprintf(pFile, "%s\n", person.vorname);
  fprintf(pFile, "%s\n", person.nachname);
  fprintf(pFile, "%d\n", person.alter);
}

//liest einzelne Person aus File
int liesPerson(FILE *pFile, struct Person *person)
{
  int ret = 0;
  char zeile[64];
  if (fgets(zeile, 64, pFile) != NULL)
  {
    zeile[strlen(zeile)-1] = 0x00;   //Zeilenumbruch entfernen
    strcpy(person->vorname, zeile);

    if (fgets(zeile, 64, pFile) != NULL)
    {
      zeile[strlen(zeile)-1] = 0x00;   //Zeilenumbruch entfernen
      strcpy(person->nachname, zeile);
      if (fgets(zeile, 64, pFile) != NULL)
      {
        person->alter = atoi(zeile);     //String auf int wandeln
        ret = 1;
      }
    }
  }

  return ret;
}

