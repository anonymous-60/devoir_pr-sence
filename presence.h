#include <string.h>
#include <stdio.h>
#define USE 10
#define MAX_SIZE 100
#define MAX_NAME_LENGTH 50
typedef enum option
{
    CONTINUE=1, RETOUR=2, MENU=3, QUIT=4
}option;
typedef enum choice
{
    NO, YES, PERS, ABS
}choice;
//Les structures
typedef struct eleve
{
    char name[MAX_NAME_LENGTH];
    int number;
    char use[USE];
}student;

int effectif_eleve(FILE*fichier);
//Design
void deco(int nombre);
void menu_fonction(char* menu);
void design();
//Print the list of student
void view_list(FILE* file,char* line, char* retour);
//PRESENCE
///Stores student name and number in a array
void structuring(FILE* file, student* mit);
void presence(FILE* file, student* mit, char* choice);
///Stocke les choix lors de l'utilisation dans mit.use
void restruct(FILE* file, student* mit);
///Fais le sauvegarde du fichier contenant la presence
void coding(FILE* file, student* mit);
//Make the presence by searching from the student number
void by_number(FILE* file, student* mit, char* choice);
void attendance_fonction(FILE* file, char* line, char* ret,char* menu, student* mit, char* choice);
void search();
void recherche(FILE*fichier,int nombre_eleve);
int effectif_eleve(FILE*fichier);
