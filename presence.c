#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "presence.h"

void deco(int nombre)
{
	int i;
	for(i = 0; i<nombre; i++)
	{
		printf("\033[1;35m*\033[0m");
	}
	printf("\n");
}
void design()
{
	int i;
	int j;
	char* character[]={"continue the last", "open new"};
	for(i = 0; i<2; i++)
	{
		printf("   ");
		for(j = 0; j<strlen(character[i]); j++)
		{
			printf("_");
		}
		printf("\n[%d]%s\n", i+1, character[i]);
		printf("   ");
		printf("\n");
	}
}
void coding(FILE* file, student* mit)
{
	int retour;
	int i , j;
	int max = 0;
	int choice = 3;
	int numero = 1;
	char choix[MAX_SIZE];
	char line[MAX_SIZE];
	char ret[MAX_SIZE];
	char menu[MAX_SIZE];
	do
	{
		FILE* file1 = NULL;
		file1 = fopen("sauvegarde.txt", "a+");
		file = fopen("list1.html", "w");
		do
		{
			printf("type the number of the student: ");
			scanf("%d", &numero);
			if(numero<1 || numero>75)
			{
				printf("\nERROR!!!: This number don't exist...!\n");
				printf("Re");
			}
		}while(numero<1 || numero>75);
		do
		{
			printf("%d %s ", mit[numero-1].number, mit[numero-1].name);
			printf("\n\033[1m0.NON/1.OUI/2.PERSO/3.ABS:\033[0m");
			scanf("%d", &choice);
			if(choice != 0 && choice != 1 && choice != 2 && choice != 3)
			{
				printf("\nERROR!!!\n");
			}
		}while(choice != 0 && choice != 1 && choice != 2 && choice != 3);
		switch(choice)
		{
			case(NO):
				strcpy(mit[numero-1].use, "NO");
				fprintf(file1, "%d %s\n", mit[numero-1].number,mit[numero-1].use);
				break;
			case(YES):
				strcpy(mit[numero-1].use, "YES");
				fprintf(file1, "%d %s\n", mit[numero-1].number,mit[numero-1].use);
				break;
			case (PERS):
				strcpy(mit[numero-1].use, "PERS");
				fprintf(file1, "%d %s\n", mit[numero-1].number,mit[numero-1].use);
				break;
			case (ABS):
				strcpy(mit[numero-1].use, " ");
				fprintf(file1, "%d %s\n", mit[numero-1].number,mit[numero-1].use);
				break;
		}
		max = strlen(mit[0].name);
		for(i = 0; i<75; i++)
		{
			if(strcmp(mit[i].use, "NO") != 0 &&strcmp(mit[i].use, "YES") != 0 && strcmp(mit[i].use, "PERS") != 0)
			{
				strcpy(mit[i].use, " ");
			}
		}
		for(i = 1; i<75; i++)
		{
			if(max<strlen(mit[i].name))
			{
				max = strlen(mit[i].name);
			}
		}
		fprintf(file, "<HTML>\n\t<HEAD>\n\t\t<TITLE>L1</TITLE>\n</HEAD>\n\t<BODY bgcolor=\"white\" ><FONT COLOR=\"black\">");
		fprintf(file, "\n\t<TABLE border=\"2\">");
		fprintf(file,"<TR><TD>N°</TD>    <TD>Nom et Prénoms</TD> <TD>Présence</TD>");
		for(i = 0;i < 75;i++)
		{
			fprintf(file,"<TR><TD>%d</TD>    <TD>%s</TD>",mit[i].number,mit[i].name);
			for(j = 0; j<max+4-strlen(mit[i].name); j++)
			{
				fprintf(file, " ");
			}
			fprintf(file,"<TD>%s</TD></TR>\n", mit[i].use);
		}
		fprintf(file, "\n\t</TABLE>");
		fprintf(file, "</FONT>\n\t</BODY>\n</HTML>");
		fclose(file1);
		fclose(file);
		do
		{
			printf("Type \n1.Continue 2.Retour 3.Menu 4.Quit\n");
			printf("YOUR CHOICE: ");
			scanf("%d", &retour);
		}while(retour != CONTINUE && retour != RETOUR && retour != MENU && retour != QUIT);
		switch(retour)
		{
			case RETOUR:
				system("clear");
				by_number(file, mit, choix);
				break;
			case MENU:
				system("clear");
				attendance_fonction(file, line, ret,menu, mit,choix);
				break;
			case QUIT:
				printf("\nBYE BYE !!");
				sleep(2);
				exit(EXIT_SUCCESS);
				break;
		}
		if(retour == CONTINUE)
		{
			system("clear");
		}
	}while(retour == CONTINUE);
}
void restruct(FILE* file, student* mit)
{
	char line[100];
	int count;
	file = fopen("list.txt", "r");
	structuring(file,mit);
	fclose(file);
	file = fopen("sauvegarde.txt", "r");
	while(feof(file)!=1)
	{
		fscanf(file, "%[^ ]", line);
		count = atoi(line);
		fseek(file,1,SEEK_CUR);
		fscanf(file, "%[^\n]", line);
		strcpy(mit[count-1].use, line);
	}
	fclose(file);
	coding(file, mit);
}
void presence(FILE* file, student* mit, char* choice)
{
	int i;
	printf("Do a choice\n");
	design();
	printf("\033[1mYOUR CHOICE\033[0m:");
	scanf("%s", choice);
	if(strcmp(choice, "1") == 0 || strcmp(choice, "un") == 0)
	{
		restruct(file, mit);
	}
	if(strcmp(choice, "2") == 0 || strcmp(choice, "deux") == 0)
	{
		for(i = 0; i<75; i++)
		{
			strcpy(mit[i].use, " ");
		}
		remove("sauvegarde.txt");
		coding(file, mit);
	}
}
void structuring(FILE* file, student* mit)
{
	int i;
	int count = 0;
	char line[MAX_SIZE];
	//mit.number charge de stocker les numeros des étudiants
	for(i = 0; i<75; i++)
	{
		mit[i].number = i+1;
	}
	//On stocke les noms dans mit.name
	while(!feof(file))
	{
		fseek(file,4,SEEK_CUR);
		fscanf(file,"%[^\n]",line);
		strcpy(mit[count].name,line);
		count++;
	}
}
void by_number(FILE* file, student* mit, char* choice)
{
	file = fopen("list.txt", "r");
	if(file == NULL)
	{
		perror("Error opening list.txt");
		exit(EXIT_FAILURE);
	}
	else
	{
		structuring(file,mit);
		fclose(file);
		presence(file, mit, choice);
	}

}
void view_list(FILE* file,char* line, char* retour)
{
	int nombre = 8;
	file = fopen("list.txt", "r");
	while(fgets(line, sizeof(line), file))
	{
		printf("%s", line);
	}
	printf("\n");
	fclose(file);
		while(strcmp(retour, "1") != 0 && strcmp(retour, "un") != 0 && strcmp(retour, "2") != 0  && strcmp(retour, "deux") != 0)
		{
			deco(nombre);
			printf("\033[1;35m*\033[0m \033[1mType\033[0m \033[1;35m*\033[0m\n");
			deco(nombre);
			printf("\033[34m1.To return to the menu\n2.To quit\n\033[0m\033[1;36mYOUR CHOICE:\033[0m");
			scanf("%s", retour);
			if(strcmp(retour, "1") != 0 && strcmp(retour, "un") != 0 && strcmp(retour, "2") != 0  && strcmp(retour, "deux") != 0)
			{
				printf("\033[1;31mERROR!!!\n\033[0m");
				sleep(2);
				system("clear");
			}
		}
}

void menu_fonction(char* menu)
{
	//Title
	int number = 29;
	int i;
	printf("    \033[1;33m-----This application manages the presence of students at MIT-----\033[0m\n");
	printf("   ");
	for(i = 0; i<67; i++)
	{
		printf("\033[1;33m_\033[0m");
	}
	printf("\n\n");
	//Menu
	deco(number);
	printf("\033[35m*\033[0m\033[1m1.View student list\033[0m        \033[35m*\033[0m\n");
	deco(number);
	printf("\033[35m*\033[0m\033[1m2.Search by name\033[0m           \033[35m*\033[0m\n");
	deco(number);
	printf("\033[35m*\033[0m\033[1m3.Search by number\033[0m         \033[35m*\033[0m\n");
	deco(number);
	printf("\033[35m*\033[0m\033[1m4.Search by number and name\033[0m\033[35m*\033[0m\n");
	deco(number);
	printf("\033[35m*\033[0m\033[1m5.Quit\033[0m                     \033[35m*\033[0m\n");
	deco(number);
	printf("\n\033[1;32mChoose from these five options\033[0m: ");
	scanf("%s",menu);
}

void attendance_fonction(FILE* file, char* line, char* ret, char* menu, student* mit, char* choice)
{
	system("clear");
	do
	{
		menu_fonction(menu);
		strcat(ret, "a");
		//Instruction for each choice
		if(strcmp(menu, "1") == 0 ||strcmp(menu, "un") == 0 )
		{
			view_list(file,line, ret);
			if(strcmp(ret, "1") == 0 || strcmp(ret, "un") == 0)
			{
				system("clear");
			}
			else if(strcmp(ret, "2") == 0 || strcmp(ret, "deux") == 0)
			{
				exit(EXIT_SUCCESS);
			}
		}
		if(strcmp(menu, "3") == 0 || strcmp(menu, "trois") == 0)
		{
			by_number(file,mit, choice);
		}
	}while(strcmp(ret, "1") == 0 || strcmp(ret, "un") == 0);
}
