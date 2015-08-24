#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

void main(int argc, char **argv)
{
    CpuInfo();


}


void CopiarCadena(char* filename, char* cadena, char* comienzo){
	FILE* fd;
	char *leer=NULL;
	char buffer[500];
	fd=fopen(filename,"r");

	while(feof(fd)==0){
		fgets(buffer,500,fd);
		leer=strstr(buffer,comienzo);
		if(leer!=NULL)
		break;
	}
	fclose (fd);
	strcpy (cadena,leer);
}
void CpuInfo(){
	char cadena[256];
	char tipocpu[50];
	char modelocpu[100];
	CopiarCadena("/proc/cpuinfo", cadena,"vendor_id");
	sscanf(cadena,"vendor_id : %s",tipocpu);
	CopiarCadena("/proc/cpuinfo",cadena,"model name");
	sscanf(cadena, "model name : %[^\n]c", modelocpu);
	printf ("\nTipo de procesador: %s \nModelo: %s\n", tipocpu,modelocpu);
	}

