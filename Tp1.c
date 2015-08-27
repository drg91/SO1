#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define BUFFSIZE 256

void main(int argc, char **argv)
{
    Infocpu();
    KernelC();
    Tiempoactivo();
    Memoria();
    NombrePC();
    TiempoInicio();
    PromedioCarga();
    FechaHora();
    CambiosDeContexto();
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
void Infocpu(){
	char cadena[BUFFSIZE];
	char tipo[50];
	char modelo[100];
	CopiarCadena("/proc/cpuinfo", cadena,"vendor_id");
	sscanf(cadena,"vendor_id : %s",tipo);
	CopiarCadena("/proc/cpuinfo",cadena,"model name");
	sscanf(cadena, "model name : %[^\n]c", modelo);

	printf ("\nTipo de procesador: %s \nModelo: %s\n", tipo,modelo);

	}

void KernelC(){
	FILE *fd;
	char kernelc[60];
	fd = fopen("/proc/version","r");
	fscanf(fd, "%[^(]s", kernelc);
	printf("Version del Kernel: %s \n", kernelc);
	fclose(fd);
    }

void ConversorTiempo (float secs, char* buf){
	unsigned int d, h, m;
	float s;

    d = (int) (secs / 86400);
    secs = secs - (long) (d * 86400);
    h = (int) (secs / 3600);
    secs = secs - (long) (h * 3600);
    m = (int) (secs / 60);
    secs = secs - (long) (m * 60);
    s = secs;
    if (d > 0)
		sprintf (buf, "%3ud %2u:%02u:%02.2f\n", d, h, m, secs);
    else
		sprintf (buf, "%2u:%02u:%02.2f\n", h, m, s);
	return;
}

void Tiempoactivo(){
	FILE *fd;
	float time;
	char hms[18];
	fd = fopen("/proc/uptime","r");
	fscanf(fd, "%f", &time);
	ConversorTiempo(time, hms);
	printf("Tiempo transcurrido desde que se inicio: %s \n", hms);
	fclose(fd);

}

void Memoria(){
	char cadena[BUFFSIZE];
	unsigned int total;
	unsigned int libre;

	CopiarCadena("/proc/meminfo", cadena, "MemTotal");
	sscanf(cadena, "MemTotal: %u", &total);
	CopiarCadena("/proc/meminfo", cadena, "MemFree");
	sscanf(cadena, "MemFree: %u", &libre);

	total = total/1024;
	libre = libre/1024;
	printf("Memoria total: %u MB\n", total);
	printf("Memoria disponible: %u MB\n", libre);

}

void NombrePC(){
	FILE *fd;
	char nombre[30];

	fd = fopen("/proc/sys/kernel/hostname","r");
	fscanf(fd, "%[^\n]s", nombre);

	printf("Nombre PC: %s \n", nombre);
	fclose(fd);

}

void TiempoInicio(){
	char cadena [BUFFSIZE];
	time_t btime;
	unsigned int aux;
	char inicio[40];

	CopiarCadena("/proc/stat", cadena, "btime");
	sscanf(cadena, "btime %u", &aux);
	btime= (time_t)aux;

	strftime(inicio,sizeof(inicio),"%c", localtime(&btime));
	printf("Horario Inicio: %s \n", inicio);

}

void PromedioCarga(){
	FILE *fd;
	float carga;

	fd = fopen("/proc/loadavg","r");
	fscanf(fd,"%f", &carga);

	printf("Promedio carga en un minuto: %f\n", carga);
	fclose(fd);

}

void CambiosDeContexto(){
	char cadena[BUFFSIZE];
	unsigned int cambios;

	CopiarCadena("/proc/stat", cadena, "ctxt");
	sscanf(cadena, "ctxt %u", &cambios);

	printf("Cambios de contexto: %u \n", cambios);
}

void FechaHora(){
	char fecha[12];
	char hora[13];
	char cadena[BUFFSIZE];

	CopiarCadena("/proc/driver/rtc", cadena, "rtc_date");
	sscanf(cadena, "rtc_date : %s", fecha);

	CopiarCadena("/proc/driver/rtc", cadena, "rtc_time");
	sscanf(cadena, "rtc_time : %s", hora);

	printf("Fecha: %s \nHora: %s \n", fecha, hora);

}

