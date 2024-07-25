#include "presence.h"
int main()
{
	char menu[MAX_SIZE];
	FILE* file;
	student mit[76];
	char line[MAX_SIZE];
	char retour[MAX_SIZE];
	char choice[MAX_SIZE];
	char ret[MAX_SIZE];
	attendance_fonction(file,line,retour,menu,mit,choice);
	return 0;
}
