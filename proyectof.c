/*@Author: Diego Martínez Sánchez
 *@Author: Enrique Eduardo Rivera Padrón
 *@Author: Leonardo
 *@Date: 
 *@Brief: Proyecto final de fundamentos de programación, en el cual es una base
 *de datos de una biblioteca con permisos de administrador y usuario.
 */



/*Falta en la función de devolver libro que las fechas de salida y entrada se regresen a NULL de nuevo*/


#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<unistd.h>
#include<math.h>

typedef struct registros
{
  char nom[80];
  char direccion[100];
  char nacimiento[15];
  char email[90];
  int bajalt;
  int totallib;
  char contrasena[29];
  struct registros *sigu;
}usuarios;

typedef struct reglib
{
  char titulo[80];
  char autor[50];
  char categoria[80];
  int fechapub;
  char fechasalida[11];
  char fechaentrada[11];
  int pedidos;
  int paginasl;
  char usuprestamo[80];
  char isbn[100];
  struct reglib *sigl;
}libros;

void cargarlib(libros **inicioL);
void imprimirlib(libros *inicioL);
void cargarusu(usuarios **inicioU);
void imprimirusu(usuarios *inicioU);
void administrador(libros **inicioL, usuarios *inicioU);
void usuario(usuarios **inicioU, libros *inicioL);
void identificar(usuarios *inicioU, usuarios **auxusu);
usuarios *regusu(usuarios **inicioU);
void menuusu(usuarios *auxusu, libros *inicioL);
void actualizarusu(usuarios *inicioU);
void actualizarlibros(libros *inicioL);
void catalogolib(libros *inicioL);
void menucate(libros *inicioL);
int busctitulo(libros *inicioL);
int buscautor(libros *inicioL);
int busccate(libros *inicioL);
int buscfecha(libros *inicioL);
void pedirlib(char nomusu[], libros *inicioL, int *totallib);
void sacarlibro(libros *inicioL, char numusu[], int num, int *totallib);
void pedbusctitulo(libros *inicioL);
void pedbuscautor(libros *inicioL);
void pedbusccate(libros *inicioL);
void pedbuscfecha(libros *inicioL);
void devollib(char nomusu[], libros *inicioL, int *totallib);
void implib2(char nomusu[], libros *inicioL);
int validarpres(char nomusu[], libros *inicioL);
void ayudaadmon();
void infolib(libros *inicioL);
void menualtbaj(libros **inicioL);
void altalib(libros **inicioL);
void bajalib(libros **inicioL);
void bajausu(usuarios *inicioU);
void imprimirusu2(usuarios *inicioU);
void liberarmemo(usuarios *inicioU, libros *inicioL);
void sacarlibroT(libros *inicioL, char numusu[], int num, int *totallib);
int popu(libros *inicioL);
void encontrarpopu(libros *inicioL, int pop);
void *fechas1(char actual[100]);
void *fechas2(char entrega[100]);
void ayudausu();
void imprimirusuarg(usuarios *inicioU);

void main (int argc, char *argv[])
{
  int opcion;
  usuarios *inicioU;
  libros *inicioL;
  inicioU=NULL;
  inicioL=NULL;
  cargarlib(&inicioL);
  cargarusu(&inicioU);
  if(argc==1)
    {
      printf("Estás en el menú principal.\n");
      system("clear");
      do
	{
	  system("clear");
	  printf("\n\n");
	  printf("\t\t\t\t**Menú**\n");
	  printf("\t\t\t1. Administrador.\n");
	  printf("\t\t\t2. Usuario.\n");
	  printf("\t\t\t3. Salir.\n");
	  printf("\t\nElige la opción que deseas: ");
	  scanf("%i", &opcion);
	  switch(opcion)
	    {
	    case 1:
	      administrador(&inicioL, inicioU);
	      break;
	    case 2:
	      usuario(&inicioU, inicioL);
	      break;
	    case 3:
	  break;
	    default:
	      printf("Elige una opción válida.\nPresiona enter...");
	      getchar();
	      break;
	    }
	}
	while(opcion!=3);
    }
  else
    if(argc==2)
      {
	if(strcmp(argv[1], "-h")==0)
	  {
	    system("clear");
	    ayudausu();
	  }
	else
	  if(strcmp(argv[1], "-c")==0)
	    {
	      system("clear");
	      printf("Estás en la lista de libros en préstamo.\n\n\n");
	      infolib(inicioL);
	      getchar();
	      system("clear");
	    }
	  else
	    if(strcmp(argv[1], "-usu")==0)
	      {
		imprimirusuarg(inicioU);
		system("clear");
	      }
	    else
	      printf("Modo incorrecto.\n");
      }
  if(argc>2)
    printf("Ingresaste más de 1 argumento, debes poner lo que es.\n");
  actualizarusu(inicioU);
  actualizarlibros(inicioL);
}

void cargarlib(libros **inicioL)
{
  FILE *lib;
  int fecha, paginas, ped;
  libros *aux1, *aux2, *aux3;
  char linea[80];
  aux1=malloc(sizeof(libros));
  aux1->sigl=NULL;
  lib=fopen("baselibros.txt", "r");
  while(fscanf(lib,"%10[^\n]%*c\n%10[^\n]%*c\n%i\n%79[^\n]%*c\n%49[^\n]%*c\n%79[^\n]%*c\n%i\n%i\n%79[^\n]%*c%79[^\n]%*c%99[^\n]%*c", aux1->fechasalida, aux1->fechaentrada, &ped , aux1->titulo, aux1->autor, aux1->categoria,&fecha,&paginas, aux1->usuprestamo, aux1->isbn,linea)==11)
    {
      aux1->fechapub=fecha;
      aux1->paginasl=paginas;
      aux1->pedidos=ped;
      if(*inicioL==NULL)
	*inicioL=aux1;
      else
	{
	  aux2=*inicioL;
	  if(strcmp(aux1->titulo, aux2->titulo)<0)
	    {
	      aux1->sigl=*inicioL;
	      *inicioL=aux1;
	    }
	  else
	    {
	      aux2=*inicioL;
	      if(aux2->sigl==NULL)
		{
		  aux2->sigl=aux1;
		}
	      else
		{
		  aux2=*inicioL;
		  aux3=*inicioL;
		  while(strcmp(aux2->titulo, aux1->titulo)<0&&aux2->sigl!=NULL)
		    aux2=aux2->sigl;
		  if(strcmp(aux2->titulo, aux1->titulo)<0)
		    aux2->sigl=aux1;
		  else
		    {
		      aux1->sigl=aux2;
		      {
			while(aux3->sigl!=aux2)
			  aux3=aux3->sigl;
			aux3->sigl=aux1;
		      }
		    }
		}
	    }
	}
      aux1=malloc(sizeof(libros));
      aux1->sigl=NULL;
    } 
  fclose(lib);
}

void imprimirlib(libros *inicioL)
{
  libros *aux;
  int x=1;
  aux=inicioL;
  while(aux->sigl!=NULL)
    {
      printf("-------Registro %i--------\n", x);
      printf("Número de veces pedidos: %i\n", aux->pedidos);
      printf("Título: %s\n", aux->titulo);
      printf("Autor: %s\n", aux->autor);
      printf("Categoría: %s\n", aux->categoria);
      printf("Fecha de publicación: %i\n", aux->fechapub);
      printf("Número de páginas: %i\n", aux->paginasl);
      printf("Disponibilidad: %s\n", aux->usuprestamo);
      printf("ISBN: %s\n\n", aux->isbn);
      aux=aux->sigl;
      x++;
    }
  printf("-------Registro %i--------\n", x);
  printf("Número de veces pedido: %i\n", aux->pedidos);
  printf("Título: %s\n", aux->titulo);
  printf("Autor: %s\n", aux->autor);
  printf("Categoría: %s\n", aux->categoria);
  printf("Fecha de publicación: %i\n", aux->fechapub);
  printf("Número de páginas: %i\n", aux->paginasl);
  printf("Disponibilidad: %s\n", aux->usuprestamo);
  printf("ISBN: %s\n\n", aux->isbn);
  if(inicioL==NULL)
    {
      system("clear");
      printf("\n\n\t\tNo existen libros en la base, presiona enter");
      getchar();
    }
}


void administrador(libros **inicioL, usuarios *inicioU)
{
  char admon[15], admon2[50], contra2[8], contra[8];
  int opcion;
  strcpy(admon, "admon")==0;
  strcpy(contra, "1969052");
  system("clear");
  printf("\n\n\tIngresa el usuario de administrador: ");
  scanf("%s", admon2);
  printf("\tIngresa la contraseña: ");
  scanf("%s", &contra2);
  system("clear");
  if(strcmp(admon2, admon)==0&&strcmp(contra2, contra)==0)
    printf("\n\n\tHas ingresado con exito, bienvenido administrador.");
  else
    {
      printf("El usuario y/o la contraseña son incorrectos");
    }
  printf("\n\n\tPresiona enter...");
  getchar();
  getchar();
  if(strcmp(admon2, admon)==0&&contra2==contra)
    {
      do
	{
	  system("clear");
	  printf("\n\n");
	  printf("\t\t\t\t**Menú**\n");
	  printf("\t\t\t1. Informe de libros en préstamo.\n");
	  printf("\t\t\t2. Informes de usuarios con libros prestados.\n");
	  printf("\t\t\t3. Alta y baja de libros.\n");
	  printf("\t\t\t4. Baja de usuarios.\n");
	  printf("\t\t\t5. Ver libro más popular.\n");
	  printf("\t\t\t6. Ayuda.\n");
	  printf("\t\t\t7. Regresar.\n");
	  printf("\nIngresa la opción que deseas: ");
	  scanf("%i", &opcion);
	  switch(opcion)
	    {
	    case 1:
	      system("clear");
	      infolib(*inicioL);
	      getchar();
	      getchar();
	      break;
	    case 2:
	      imprimirusu(inicioU);
	      break;
	    case 3:
	      menualtbaj(inicioL);
	      break;
	    case 4:
	      bajausu(inicioU);
	      break;
	    case 5:
	      system("clear");
	      encontrarpopu(*inicioL, popu(*inicioL));
	      printf("\nPresiona enter...");
	      getchar();
	      getchar();
	      break;
	    case 6:
	      ayudaadmon();
	      break;
	    case 7:
	      break;
	    default:
	      printf("\n\n\tIngresa una opción válida.\n\tPresiona enter...");
	      getchar();
	      getchar();
	      break;
	    }
	}
      while(opcion!=7);
    }
}

void cargarusu(usuarios **inicioU)
{
  FILE *usu;
  usuarios *aux1, *aux2, *aux3;
  int bajaalt, libs;
  char linea[80];
  usu=fopen("regusu.txt", "r");
  aux1=malloc(sizeof(usuarios));
  aux1->sigu=NULL;
  while(fscanf(usu,"%79[^\n]%*c\n%99[^\n]%*c\n%14[^\n]%*c\n%89[^\n]%*c\n%i\n%i\n%29[^\n]%*c%79[^\n]%*c", aux1->nom, aux1->direccion, aux1->nacimiento, aux1->email, &bajaalt, &libs, aux1->contrasena, linea)==8)
    {
      aux1->bajalt=bajaalt;
      aux1->totallib=libs;
      if(*inicioU==NULL)
	*inicioU=aux1;
      else
	{
	  aux2=*inicioU;
	  if(strcmp(aux1->nom, aux2->nom)<0)
	    {
	      aux1->sigu=*inicioU;
	      *inicioU=aux1;
	    }
	  else
	    {
	      aux2=*inicioU;
	      if(aux2->sigu==NULL)
		{
		  aux2->sigu=aux1;
		}
	      else
		{
		  aux2=*inicioU;
		  aux3=*inicioU;
		  while(strcmp(aux2->nom, aux1->nom)<0&&aux2->sigu!=NULL)
		    aux2=aux2->sigu;
		  if(strcmp(aux2->nom, aux1->nom)<0)
		    aux2->sigu=aux1;
		  else
		    {
		      aux1->sigu=aux2;
		      {
			while(aux3->sigu!=aux2)
			  aux3=aux3->sigu;
			aux3->sigu=aux1;
		      }
		    }
		}
	    }
	}
      aux1=malloc(sizeof(usuarios));
      aux1->sigu=NULL;
    }
  fclose(usu);
}

void imprimirusu(usuarios *inicioU)
{
  usuarios *aux;
  int x=1;
  aux=inicioU;
  system("clear");
  while(aux->sigu!=NULL)
    {
      printf("%i Nombre: %s\n", x, aux->nom);
      printf("Dirección: %s\n", aux->direccion);
      printf("Nacimiento: %s\n", aux->nacimiento);
      printf("Correo electrónico: %s\n", aux->email);
      printf("Estado de usuario: %i\n", aux->bajalt);
      printf("Total de libros solicitados: %i\n", aux->totallib);
      printf("Contraseña: %s\n\n", aux->contrasena);
      aux=aux->sigu;
      x++;
    }
  printf("%i Nombre: %s\n", x, aux->nom);
  printf("Dirección: %s\n", aux->direccion);
  printf("Nacimiento: %s\n", aux->nacimiento);
  printf("Correo electrónico: %s\n", aux->email);
  printf("Estado de usuario: %i\n", aux->bajalt);
  printf("Total de libros solicitados: %i\n", aux->totallib);
  printf("Contraseña: %s\n", aux->contrasena);
  printf("\n\nPresiona enter...");
  getchar();
  getchar();
  if(inicioU==NULL)
    {
      system("clear");
      printf("\n\n\t\tNo existen usuarios registrados en la base, presiona enter...");
      getchar();
    }
}


void usuario(usuarios **inicioU, libros *inicioL)
{
  int eleccion;
  usuarios *auxusu;
  system("clear");
  do
    {
      printf("\n\n");
      printf("\t\tYa estás registrado? 1=si, 2=no: ");
      getchar();
      scanf("%i", &eleccion);
      if(eleccion!=1&&eleccion!=2)
	{
	  printf("Debes elegir la opción 1 o 2.\nPresiona enter...");
	  getchar();
	  getchar();
	}
    }
  while(eleccion!=1&&eleccion!=2);
  switch(eleccion)
    {
    case 1:
      auxusu=NULL;
      identificar(*inicioU, &auxusu);//checar que este dado de alta o no.
      break;
    case 2:
      auxusu=regusu(inicioU);
      break;
    default:
      break;
    }
  
  if(auxusu!=NULL)
    {
      if(auxusu->bajalt==0)
    {
      printf("\t\tEl usuario ingresado está dado de baja.\n");
      printf("\t\tPresiona enter...");
      getchar();
    }
      if(auxusu->bajalt==1)
	menuusu(auxusu,inicioL);
    }
}

void identificar(usuarios *inicioU, usuarios **auxusu)
{
  int flag=0;
  char nombre[80], contra[7];
  usuarios *aux1;
  aux1=inicioU;
  system("clear");
  printf("\n\n");
  printf("\t\tIngresa tu nombre: ");
  gets(nombre);
  scanf("%79[^\n]%*c", nombre);
  //getchar();
  //getchar();
  //printf("nombre: %s\n", nombre);
  printf("\t\tIngresa la contraseña: ");
  scanf("%s[^\n]", contra);
  //printf("contra: %s\n", contra);
  while(aux1->sigu!=NULL)
    {
      if(strcmp(nombre, aux1->nom)==0&&strcmp(contra, aux1->contrasena)==0&&aux1->bajalt==1)
	{
	  //printf("has ingresado bien.\n");
	  *auxusu=aux1;
	}
	aux1=aux1->sigu;
    }
  aux1=inicioU;
  while(strcmp(nombre, aux1->nom)!=0&&aux1->sigu!=NULL)
    {
      aux1=aux1->sigu;
    }
  if(aux1->bajalt!=1)
    {
      printf("El usuario está dado de baja.\n");
      printf("Presiona enter...");
      getchar();
    }
  else
    if(strcmp(nombre, aux1->nom)!=0)
      {
	printf("El usuario ingresado es incorrecto.\n");
	printf("Presiona enter...");
	getchar();
      }
    else
      if(strcmp(contra, aux1->contrasena)!=0)
	{
	  printf("La contraseña es incorrecta.\n");
	  printf("Presiona enter...");
	  getchar();
	}
  getchar();
}

usuarios *regusu(usuarios **inicioU)
{
  FILE *usu;
  usuarios *aux1, *aux2, *aux3;
  int bajaalt, libs;
  char linea[80];
  usu=fopen("regusu.txt", "r");
  aux1=malloc(sizeof(usuarios));
  aux1->sigu=NULL;
  system("clear");
  printf("Ingresa el nombre: ");
  getchar();
  gets(aux1->nom);
  system("clear");
  printf("Ingresa la dirección: ");
  gets(aux1->direccion);
  fflush(stdin);
  system("clear");
  printf("Ingresa la fecha de nacimiento en números y con diagonales (dd/mm/yyyy): ");
  gets(aux1->nacimiento);
  fflush(stdin);
  system("clear");
  printf("Ingresa el correo electrónico: ");
  gets(aux1->email);
  fflush(stdin);
  system("clear");
  printf("Ingresa la contraseña de 7 dígitos: ");
  gets(aux1->contrasena);
  aux1->bajalt=1;
  aux1->totallib=0;
  {
    aux1->totallib=libs;
    if(*inicioU==NULL)
      *inicioU=aux1;
    else
      {
	aux2=*inicioU;
	if(strcmp(aux1->nom, aux2->nom)<0)
	  {
	    aux1->sigu=*inicioU;
	    *inicioU=aux1;
	  }
	else
	  {
	    aux2=*inicioU;
	    if(aux2->sigu==NULL)
	      {
		aux2->sigu=aux1;
	      }
	    else
	      {
		aux2=*inicioU;
		aux3=*inicioU;
		while(strcmp(aux2->nom, aux1->nom)<0&&aux2->sigu!=NULL)
		  aux2=aux2->sigu;
		if(strcmp(aux2->nom, aux1->nom)<0)
		  aux2->sigu=aux1;
		else
		  {
		    aux1->sigu=aux2;
		    {
		      while(aux3->sigu!=aux2)
			aux3=aux3->sigu;
		      aux3->sigu=aux1;
		    }
		  }
	      }
	  }
      }
  }
  return aux1;
}

void menuusu(usuarios *auxusu, libros *inicioL)
{
  int opcion;
  system("clear");
  printf("\n\n");
  printf("\t\t\tIniciaste sesión como: %s\n\t\t\tPresiona enter...", auxusu->nom);
  fflush(stdin);
  getchar();
  do
    {
      system("clear");
      printf("\n\n");
      printf("\t\t\t\t**Menú**\n");
      printf("\t\t\t1. Lista de libros prestados.\n");
      printf("\t\t\t2. Catálogo de libros.\n");
      printf("\t\t\t3. Pedir libros.\n");
      printf("\t\t\t4. Devolver libros.\n");
      printf("\t\t\t5. Regresar menú principal.\n");
      printf("\nIngresa la opción: ");
      scanf("%i", &opcion);
      switch(opcion)
	{
	case 1:
	  menucate(inicioL);
	  break;
	case 2:
	  system("clear");
	  imprimirlib(inicioL);
	  printf("Presiona enter...");
	  getchar();
	  getchar();
	  //funcion que permita el prestamo de libros al usuario
	  break;
	case 3:
	  pedirlib(auxusu->nom, inicioL, &auxusu->totallib);
	  //funcion que permita devolver los libros
	  break;
	case 4:
	  devollib(auxusu->nom, inicioL, &auxusu->totallib);
	  break;
	case 5:
	  break;
	default:
	  system("clear");
	  printf("\n\n");
	  printf("\t\t\tDebes ingresar una opción válida.\n\t\t\tPresiona enter...");
	  getchar();
	  getchar();
	  break;
	}
    }
  while(opcion!=5);
}

void actualizarusu(usuarios *inicioU)
{
  FILE *archivo;
  usuarios *aux;
  int x=1;
  archivo=fopen("regusu.txt", "wt");
  aux=inicioU;
  while(aux->sigu!=NULL)
    {
      fprintf(archivo,"%s\n", aux->nom);
      fprintf(archivo,"%s\n", aux->direccion);
      fprintf(archivo,"%s\n", aux->nacimiento);
      fprintf(archivo,"%s\n", aux->email);
      fprintf(archivo,"%i\n", aux->bajalt);
      fprintf(archivo,"%i\n", aux->totallib);
      fprintf(archivo,"%s\n", aux->contrasena);
      fprintf(archivo,"-------------------------------\n");
      aux=aux->sigu;
      x++;
    }
  fprintf(archivo,"%s\n", aux->nom);
  fprintf(archivo,"%s\n", aux->direccion);
  fprintf(archivo,"%s\n", aux->nacimiento);
  fprintf(archivo,"%s\n", aux->email);
  fprintf(archivo,"%i\n", aux->bajalt);
  fprintf(archivo,"%i\n", aux->totallib);
  fprintf(archivo,"%s\n", aux->contrasena);
  fprintf(archivo,"-------------------------------\n");
  fclose(archivo);
}

void catalogolib(libros *inicioL)
{ 
  libros *aux;
  int x=1;
  aux=inicioL;
  while(aux->sigl!=NULL)
    {
      printf("-------Registro %i--------\n", x);
      printf("Título: %s\n", aux->titulo);
      printf("Autor: %s\n", aux->autor);
      printf("Categoría: %s\n", aux->categoria);
      printf("Fecha de publicación: %i\n", aux->fechapub);
      printf("Número de páginas: %i\n", aux->paginasl);
      printf("Disponibilidad: %s\n", aux->usuprestamo);
      printf("ISBN: %s\n\n", aux->isbn);
      aux=aux->sigl;
      x++;
    }
  printf("-------Registro %i--------\n", x);
  printf("Título: %s\n", aux->titulo);
  printf("Autor: %s\n", aux->autor);
  printf("Categoría: %s\n", aux->categoria);
  printf("Fecha de publicación: %i\n", aux->fechapub);
  printf("Número de páginas: %i\n", aux->paginasl);
  printf("Disponibilidad: %s\n", aux->usuprestamo);
  printf("ISBN: %s\n\n", aux->isbn);
  if(inicioL==NULL)
    {
      system("clear");
      printf("No hay libros registrados en la base, presiona enter...");
      getchar();
    }
}

void menucate(libros *inicioL)
{
  int opcion;
  do
    {
      system("clear");
      printf("\n\n");
      printf("\t\t\t\t**Menú**\n");
      printf("\t\t\t1. Titulo.\n");
      printf("\t\t\t2. Autor.\n");
      printf("\t\t\t3. Categoría.\n");
      printf("\t\t\t4. Fecha de publicación.\n");
      printf("\t\t\t5. Regresar.\n");
      printf("\nIngresa la opción: ");
      scanf("%i", &opcion);
      switch(opcion)
	{
	case 1:
	  busctitulo(inicioL);
	  break;
	case 2:
	  buscautor(inicioL);
	  break;
	case 3:
	  busccate(inicioL);
	  break;
	case 4:
	  buscfecha(inicioL);
	  break;
	case 5:
	  break;
	default:
	  system("clear");
	  printf("\n\n");
	  printf("\t\tIngresa una opción válida.\n\t\tPresiona enter...");
	  getchar();
	  getchar();
	  break;
	}
    }
  while(opcion!=5);
}

int busctitulo(libros *inicioL)
{
  libros *aux;
  int x=1, bandera=0;
  char nombre[80];
  aux=inicioL;
  system("clear");
  printf("\n\n");
  printf("\t\t\tIngresa el título del libro: ");
  getchar();
  scanf("%79[^\n]%*c", nombre);
  if(inicioL==NULL)//condición de que no haya nada registrado.
    {
      system("clear");
      printf("\n\n\t\tNo hay usuarios registrados en la base, presiona enter...");
      getchar();
    }
  while(aux->sigl!=NULL)
    {
      if(strcmp(nombre, aux->titulo)==0)
	{
	  bandera++;
	  printf("-------Registro %i--------\n", x);
	  printf("Título: %s\n", aux->titulo);
	  printf("Autor: %s\n", aux->autor);
	  printf("Categoría: %s\n", aux->categoria);
	  printf("Fecha de publicación: %i\n", aux->fechapub);
	  printf("Número de páginas: %i\n", aux->paginasl);
	  if(strcmp(aux->usuprestamo, "NULL")==0)
	    printf("Disponibilidad: disponible\n");
	  else
	    printf("Disponibilidad: no disponible\n");
	  printf("ISBN: %s\n\n", aux->isbn);
	}
      aux=aux->sigl;
      x++;
    }
  if(strcmp(nombre, aux->titulo)==0)
    {
      bandera++;
      printf("-------Registro %i--------\n", x);
      printf("Título: %s\n", aux->titulo);
      printf("Autor: %s\n", aux->autor);
      printf("Categoría: %s\n", aux->categoria);
      printf("Fecha de publicación: %i\n", aux->fechapub);
      printf("Número de páginas: %i\n", aux->paginasl);
      if(strcmp(aux->usuprestamo, "NULL")==0)
	printf("Disponibilidad: disponible\n");
      else
	printf("Disponibilidad: no disponible\n");
      printf("ISBN: %s\n\n", aux->isbn);
    }
  if(bandera==0)
    printf("El título que ingresaste no existe.\n");
  printf("Presiona enter...");
  getchar();
  return bandera;
}

int buscautor(libros *inicioL)
{
  libros *aux;
  int x=1, bandera=0;
  char nombre[80];
  aux=inicioL;
  system("clear");
  printf("\n\n");
  printf("\t\t\tIngresa el autor del libro: ");
  getchar();
  scanf("%79[^\n]%*c", nombre);
  while(aux->sigl!=NULL)
    {
      if(strcmp(nombre, aux->autor)==0)
	{
	  bandera++;
	  printf("-------Registro %i--------\n", x);
	  printf("Título: %s\n", aux->titulo);
	  printf("Autor: %s\n", aux->autor);
	  printf("Categoría: %s\n", aux->categoria);
	  printf("Fecha de publicación: %i\n", aux->fechapub);
	  printf("Número de páginas: %i\n", aux->paginasl);
	  if(strcmp(aux->usuprestamo, "NULL")==0)
	    printf("Disponibilidad: disponible\n");
	  else
	    printf("Disponibilidad: no disponible\n");
	  printf("ISBN: %s\n\n", aux->isbn);
	}
      aux=aux->sigl;
      x++;
    }
  if(strcmp(nombre, aux->autor)==0)
    {
      bandera++;
      printf("-------Registro %i--------\n", x);
      printf("Título: %s\n", aux->titulo);
      printf("Autor: %s\n", aux->autor);
      printf("Categoría: %s\n", aux->categoria);
      printf("Fecha de publicación: %i\n", aux->fechapub);
      printf("Número de páginas: %i\n", aux->paginasl);
      if(strcmp(aux->usuprestamo, "NULL")==0)
	printf("Disponibilidad: disponible\n");
      else
	printf("Disponibilidad: no disponible\n");
      printf("ISBN: %s\n\n", aux->isbn);
    }
  if(inicioL==NULL)
    {
      system("clear");
      printf("No hay libros registrados en la base, presiona enter...");
      getchar();
    }
  if(bandera==0)
    printf("El título que ingresaste no existe.\nPresiona enter...");
  printf("Presiona enter...");
  getchar();
  return bandera;
}

int busccate(libros *inicioL)
{
  libros *aux;
  int x=1, bandera=0;
  char nombre[80];
  aux=inicioL;
  system("clear");
  printf("\n\n");
  printf("\t\t\tIngresa la categoría del libro: ");
  getchar();
  scanf("%79[^\n]%*c", nombre);
  while(aux->sigl!=NULL)
    {
      if(strcmp(nombre, aux->categoria)==0)
	{
	  bandera++;
	  printf("-------Registro %i--------\n", x);
	  printf("Título: %s\n", aux->titulo);
	  printf("Autor: %s\n", aux->autor);
	  printf("Categoría: %s\n", aux->categoria);
	  printf("Fecha de publicación: %i\n", aux->fechapub);
	  printf("Número de páginas: %i\n", aux->paginasl);
	  if(strcmp(aux->usuprestamo, "NULL")==0)
	    printf("Disponibilidad: disponible\n");
	  else
	    printf("Disponibilidad: no disponible\n");
	  printf("ISBN: %s\n\n", aux->isbn);
	}
      aux=aux->sigl;
      x++;
    }
  if(strcmp(nombre, aux->categoria)==0)
    {
      bandera++;
      printf("-------Registro %i--------\n", x);
      printf("Título: %s\n", aux->titulo);
      printf("Autor: %s\n", aux->autor);
      printf("Categoría: %s\n", aux->categoria);
      printf("Fecha de publicación: %i\n", aux->fechapub);
      printf("Número de páginas: %i\n", aux->paginasl);
      if(strcmp(aux->usuprestamo, "NULL")==0)
	printf("Disponibilidad: disponible\n");
      else
	printf("Disponibilidad: no disponible\n");
      printf("ISBN: %s\n\n", aux->isbn);
    }
  if(inicioL==NULL)//condición de que no haya nada registrado.
    {
      system("clear");
      printf("No hay libros registrados en la base, presiona enter...");
      getchar();
    }
  if(bandera==0)
    printf("El título que ingresaste no existe.\nPresiona enter...");
  printf("Presiona enter...");
  getchar();
  return bandera;
}

int buscfecha(libros *inicioL)
{
  libros *aux;
  int x=1, bandera=0, nombre;
  aux=inicioL;
  system("clear");
  printf("\n\n");
  printf("\t\t\tIngresa la fecha de publicación libro: ");
  getchar();
  scanf("%i", &nombre);
  while(aux->sigl!=NULL)
    {
      if(nombre==aux->fechapub)
	{
	  bandera++;
	  printf("-------Registro %i--------\n", x);
	  printf("Título: %s\n", aux->titulo);
	  printf("Autor: %s\n", aux->autor);
	  printf("Categoría: %s\n", aux->categoria);
	  printf("Fecha de publicación: %i\n", aux->fechapub);
	  printf("Número de páginas: %i\n", aux->paginasl);
	  if(strcmp(aux->usuprestamo, "NULL")==0)
	    printf("Disponibilidad: disponible\n");
	  else
	    printf("Disponibilidad: no disponible\n");
	  printf("ISBN: %s\n\n", aux->isbn);
	}
      aux=aux->sigl;
      x++;
    }
  if(nombre==aux->fechapub)
    {
      bandera++;
      printf("-------Registro %i--------\n", x);
      printf("Título: %s\n", aux->titulo);
      printf("Autor: %s\n", aux->autor);
      printf("Categoría: %s\n", aux->categoria);
      printf("Fecha de publicación: %i\n", aux->fechapub);
      printf("Número de páginas: %i\n", aux->paginasl);
      if(strcmp(aux->usuprestamo, "NULL")==0)
	printf("Disponibilidad: disponible\n");
      else
	printf("Disponibilidad: no disponible\n");
      printf("ISBN: %s\n\n", aux->isbn);
    }
  if(inicioL==NULL)
    {
      system("clear");
      printf("No hay libros registrados en la base, presiona enter...");
      getchar();
    }
  if(bandera==0)
    printf("El título que ingresaste no existe.\nPresiona enter...");
  printf("Presiona enter...");
  getchar();
  return bandera;
}

void pedirlib(char nomusu[], libros *inicioL, int *totallib)
{
  int opcion, numero;
  do
    {
      system("clear");
      printf("\n\n");
      printf("\t\t\t\t**Menú**\n");
      printf("\t\t\t1. Titulo.\n");
      printf("\t\t\t2. Autor.\n");
      printf("\t\t\t3. Categoría.\n");
      printf("\t\t\t4. Fecha de publicación.\n");
      printf("\t\t\t5. Regresar.\n");
      printf("\nIngresa la opción: ");
      scanf("%i", &opcion);
      switch(opcion)
	{
	case 1:
	  if(busctitulo(inicioL)>0)
	    {
	      printf("Ingresa el número de registro: ");
	      scanf("%i", &numero);
	      sacarlibroT(inicioL, nomusu, numero, totallib);
	    }
	  break;
	case 2:
	  if(buscautor(inicioL)>0)
	    {
	      printf("Ingresa el número de registro: ");
	      scanf("%i", &numero);
	      sacarlibro(inicioL, nomusu, numero, totallib);
	    }
	  break;
	case 3:
	  if(busccate(inicioL)>0)
	    {
	      printf("Ingresa el número de registro: ");
	      scanf("%i", &numero);
	      sacarlibro(inicioL, nomusu, numero, totallib);
	    }
	  break;
	case 4:
	  if(buscfecha(inicioL)>0)
	    {
	      printf("Ingresa el número de registro: ");
	      scanf("%i", &numero);
	      sacarlibro(inicioL, nomusu, numero, totallib);
	    }
	  break;
	case 5:
	  break;
	default:
	  system("clear");
	  printf("\n\n");
	  printf("\t\tIngresa una opción válida.\n\t\tPresiona enter...");
	  getchar();
	  getchar();
	  break;
	}
    }
  while(opcion!=5);
}

void sacarlibro(libros *inicioL, char numusu[], int num, int *totallib)
{
  char actual[100], entrega[100];
  int i;
  libros *aux1;
  aux1=inicioL;
  for(i=1;i<num;i++)
    {
      aux1=aux1->sigl;
    }
  if(strcmp(aux1->usuprestamo, "NULL")==0)
    {
      fechas1(actual);
      fechas2(entrega);
      strcpy(aux1->fechasalida, actual)==0;
      strcpy(aux1->fechaentrada, entrega)==0;
      strcpy(aux1->usuprestamo, numusu)==0;
      printf("titulo: %s\n", aux1->titulo);
      printf("autor: %s\n", aux1->autor);
      printf("categoria: %s\n", aux1->categoria);
      printf("fecha: %i\n", aux1->fechapub);
      printf("num paginas: %i\n", aux1->paginasl);
      printf("usuario: %s\n", aux1->usuprestamo);
      printf("isbn: %s\n", aux1->isbn);
      printf("\nHas solicitado el libro exitosamente.\nPresiona enter...");
      *totallib=*totallib+1;
      getchar();
      getchar();
    }
  else
    {
      system("clear");
      printf("\n\n\t\tEl libro solicitado ya ha sido prestado.\n\t\tIntenta con otro, presiona enter...");
      getchar();
      getchar();
    }
}

void actualizarlibros(libros *inicioL)
{
  FILE *archivo;
  libros *aux;
  int x=1;
  archivo=fopen("baselibros.txt", "wt");
  aux=inicioL;
  while(aux->sigl!=NULL)
    {
      fprintf(archivo,"%s\n", aux->fechasalida);
      fprintf(archivo,"%s\n", aux->fechaentrada);
      fprintf(archivo,"%i\n", aux->pedidos);
      fprintf(archivo,"%s\n", aux->titulo);
      fprintf(archivo,"%s\n", aux->autor);
      fprintf(archivo,"%s\n", aux->categoria);
      fprintf(archivo,"%i\n", aux->fechapub);
      fprintf(archivo,"%i\n", aux->paginasl);
      fprintf(archivo,"%s\n", aux->usuprestamo);
      fprintf(archivo,"%s\n", aux->isbn);
      fprintf(archivo,"-------------------------------\n");
      aux=aux->sigl;
      x++;
    }
  fprintf(archivo,"%s\n", aux->fechasalida);
  fprintf(archivo,"%s\n", aux->fechaentrada);
  fprintf(archivo,"%i\n", aux->pedidos);
  fprintf(archivo,"%s\n", aux->titulo);
  fprintf(archivo,"%s\n", aux->autor);
  fprintf(archivo,"%s\n", aux->categoria);
  fprintf(archivo,"%i\n", aux->fechapub);
  fprintf(archivo,"%i\n", aux->paginasl);
  fprintf(archivo,"%s\n", aux->usuprestamo);
  fprintf(archivo,"%s\n", aux->isbn);
  fprintf(archivo,"-------------------------------\n");
  fclose(archivo);
}

void pedbusctitulo(libros *inicioL)//modificar
{
   libros *aux;
  int x=1, bandera=0;
  char nombre[80];
  aux=inicioL;
  system("clear");
  printf("\n\n");
  printf("\t\t\tIngresa el título del libro: ");
  getchar();
  scanf("%79[^\n]%*c", nombre);
  while(aux->sigl!=NULL)
    {
      if(strcmp(nombre, aux->titulo)==0&&strcmp(aux->usuprestamo, "NULL")==0)//agregue lo que va después del "&&"
	{
	  bandera++;
	  printf("-------Registro %i--------\n", x);
	  printf("Título: %s\n", aux->titulo);
	  printf("Autor: %s\n", aux->autor);
	  printf("Categoría: %s\n", aux->categoria);
	  printf("Fecha de publicación: %i\n", aux->fechapub);
	  printf("Número de páginas: %i\n", aux->paginasl);
	  if(strcmp(aux->usuprestamo, "NULL")==0)
	    printf("Disponibilidad: disponible\n");
	  else
	    printf("Disponibilidad: no disponible\n");
	  printf("ISBN: %s\n\n", aux->isbn);
	}
      aux=aux->sigl;
      x++;
    }
  if(strcmp(nombre, aux->titulo)==0&&strcmp(aux->usuprestamo, "NULL")==0)//agregue lo que va después del "&&"
    {
      bandera++;
      printf("-------Registro %i--------\n", x);
      printf("Título: %s\n", aux->titulo);
      printf("Autor: %s\n", aux->autor);
      printf("Categoría: %s\n", aux->categoria);
      printf("Fecha de publicación: %i\n", aux->fechapub);
      printf("Número de páginas: %i\n", aux->paginasl);
      if(strcmp(aux->usuprestamo, "NULL")==0)
	printf("Disponibilidad: disponible\n");
      else
	printf("Disponibilidad: no disponible\n");
      printf("ISBN: %s\n\n", aux->isbn);
    }
  if(inicioL==NULL)
    {
      system("clear");
      printf("No hay libros registrados en la base, presiona enter...");
      getchar();
    }
  if(bandera==0)
    printf("El título que ingresaste no existe.\nPresiona enter...");
  printf("Presiona enter...");
  getchar();
}

void pedbuscautor(libros *inicioL)//modificar
{
   libros *aux;
  int x=1, bandera=0;
  char nombre[80];
  aux=inicioL;
  system("clear");
  printf("\n\n");
  printf("\t\t\tIngresa el título del libro: ");
  getchar();
  scanf("%79[^\n]%*c", nombre);
  while(aux->sigl!=NULL)
    {
      if(strcmp(nombre, aux->titulo)==0&&strcmp(aux->usuprestamo, "NULL")==0)//agregue lo que va después del "&&"
	{
	  bandera++;
	  printf("-------Registro %i--------\n", x);
	  printf("Título: %s\n", aux->titulo);
	  printf("Autor: %s\n", aux->autor);
	  printf("Categoría: %s\n", aux->categoria);
	  printf("Fecha de publicación: %i\n", aux->fechapub);
	  printf("Número de páginas: %i\n", aux->paginasl);
	  if(strcmp(aux->usuprestamo, "NULL")==0)
	    printf("Disponibilidad: disponible\n");
	  else
	    printf("Disponibilidad: no disponible\n");
	  printf("ISBN: %s\n\n", aux->isbn);
	}
      aux=aux->sigl;
      x++;
    }
  if(strcmp(nombre, aux->titulo)==0&&strcmp(aux->usuprestamo, "NULL")==0)//agregue lo que va después del "&&"
    {
      bandera++;
      printf("-------Registro %i--------\n", x);
      printf("Título: %s\n", aux->titulo);
      printf("Autor: %s\n", aux->autor);
      printf("Categoría: %s\n", aux->categoria);
      printf("Fecha de publicación: %i\n", aux->fechapub);
      printf("Número de páginas: %i\n", aux->paginasl);
      if(strcmp(aux->usuprestamo, "NULL")==0)
	printf("Disponibilidad: disponible\n");
      else
	printf("Disponibilidad: no disponible\n");
      printf("ISBN: %s\n\n", aux->isbn);
    }
  if(inicioL==NULL)//condición de que no haya nada registrado.
    {
      system("clear");
      printf("\n\n\t\tNo hay libros registrados en la base, presiona enter...");
      getchar();
    }
  if(bandera==0)
    printf("El título que ingresaste no existe.\nPresiona enter...");
  printf("Presiona enter...");
  getchar();
}

void pedbusccate(libros *inicioL)
{
   libros *aux;
  int x=1, bandera=0;
  char nombre[80];
  aux=inicioL;
  system("clear");
  printf("\n\n");
  printf("\t\t\tIngresa el título del libro: ");
  getchar();
  scanf("%79[^\n]%*c", nombre);
  while(aux->sigl!=NULL)
    {
      if(strcmp(nombre, aux->titulo)==0&&strcmp(aux->usuprestamo, "NULL")==0)//agregue lo que va después del "&&"
	{
	  bandera++;
	  printf("-------Registro %i--------\n", x);
	  printf("Título: %s\n", aux->titulo);
	  printf("Autor: %s\n", aux->autor);
	  printf("Categoría: %s\n", aux->categoria);
	  printf("Fecha de publicación: %i\n", aux->fechapub);
	  printf("Número de páginas: %i\n", aux->paginasl);
	  if(strcmp(aux->usuprestamo, "NULL")==0)
	    printf("Disponibilidad: disponible\n");
	  else
	    printf("Disponibilidad: no disponible\n");
	  printf("ISBN: %s\n\n", aux->isbn);
	}
      aux=aux->sigl;
      x++;
    }
  if(strcmp(nombre, aux->titulo)==0&&strcmp(aux->usuprestamo, "NULL")==0)//agregue lo que va después del "&&"
    {
      bandera++;
      printf("-------Registro %i--------\n", x);
      printf("Título: %s\n", aux->titulo);
      printf("Autor: %s\n", aux->autor);
      printf("Categoría: %s\n", aux->categoria);
      printf("Fecha de publicación: %i\n", aux->fechapub);
      printf("Número de páginas: %i\n", aux->paginasl);
      if(strcmp(aux->usuprestamo, "NULL")==0)
	printf("Disponibilidad: disponible\n");
      else
	printf("Disponibilidad: no disponible\n");
      printf("ISBN: %s\n\n", aux->isbn);
    }
  if(inicioL==NULL)
    {
      system("clear");
      printf("\n\n\t\tNo hay libros registrados en la base, presiona enter...");
      getchar();
    }
  if(bandera==0)
    printf("El título que ingresaste no existe.\nPresiona enter...");
  printf("Presiona enter...");
  getchar();
}

void pedbuscfecha(libros *inicioL)
{
   libros *aux;
  int x=1, bandera=0;
  char nombre[80];
  aux=inicioL;
  system("clear");
  printf("\n\n");
  printf("\t\t\tIngresa el título del libro: ");
  getchar();
  scanf("%79[^\n]%*c", nombre);
  while(aux->sigl!=NULL)
    {
      if(strcmp(nombre, aux->titulo)==0&&strcmp(aux->usuprestamo, "NULL")==0)//agregue lo que va después del "&&"
	{
	  bandera++;
	  printf("-------Registro %i--------\n", x);
	  printf("Título: %s\n", aux->titulo);
	  printf("Autor: %s\n", aux->autor);
	  printf("Categoría: %s\n", aux->categoria);
	  printf("Fecha de publicación: %i\n", aux->fechapub);
	  printf("Número de páginas: %i\n", aux->paginasl);
	  if(strcmp(aux->usuprestamo, "NULL")==0)
	    printf("Disponibilidad: disponible\n");
	  else
	    printf("Disponibilidad: no disponible\n");
	  printf("ISBN: %s\n\n", aux->isbn);
	}
      aux=aux->sigl;
      x++;
    }
  if(strcmp(nombre, aux->titulo)==0&&strcmp(aux->usuprestamo, "NULL")==0)//agregue lo que va después del "&&"
    {
      bandera++;
      printf("-------Registro %i--------\n", x);
      printf("Título: %s\n", aux->titulo);
      printf("Autor: %s\n", aux->autor);
      printf("Categoría: %s\n", aux->categoria);
      printf("Fecha de publicación: %i\n", aux->fechapub);
      printf("Número de páginas: %i\n", aux->paginasl);
      if(strcmp(aux->usuprestamo, "NULL")==0)
	printf("Disponibilidad: disponible\n");
      else
	printf("Disponibilidad: no disponible\n");
      printf("ISBN: %s\n\n", aux->isbn);
    }
  if(inicioL==NULL)
    {
      system("clear");
      printf("\n\n\t\tNo hay libros registrados en la base, presiona enter...");
      getchar();
    }
  if(bandera==0)
    printf("El título que ingresaste no existe.\nPresiona enter...");
  printf("Presiona enter...");
  getchar();
}

void devollib(char nomusu[], libros *inicioL, int *totallib)//agregue esta función
{
  int opcion, i;
  libros *aux1;
  aux1=inicioL;
  system("clear");
  if(validarpres(nomusu, inicioL)==1)
    {
      printf("Estos son los libros que tienes solicitados, selecciona el libro\nque deseas devolver.\n");
      implib2(nomusu, inicioL);
      printf("Ingresa el número de registro del libro que deseas devolver: ");
      scanf("%i", &opcion);
      for(i=1;i<opcion;i++)
	{
	  aux1=aux1->sigl;
	}
      printf("prestamo: %s\n", aux1->usuprestamo);
      getchar();
      strcpy(aux1->fechasalida, "NULL")==0;
      strcpy(aux1->fechaentrada, "NULL")==0;
      strcpy(aux1->usuprestamo, "NULL")==0;
      *totallib=*totallib-1;
      printf("El libro ha sido devuelto con exito.\nPresiona enter...");
    }
  else
    {
      printf("No tienes libros pedidos.\n");
      printf("Presiona enter...");
      getchar();
    }
  getchar();
}

void implib2(char nomusu[], libros *inicioL)//agregue esta función
{
  libros *aux;
  int x=1;
  aux=inicioL;
  //printf("nom usu: %s\n", nomusu);
  //getchar();
  while(aux->sigl!=NULL)
    {
      if(strcmp(aux->usuprestamo, nomusu)==0)
	{
	  printf("-------Registro %i--------\n", x);
	  printf("Título: %s\n", aux->titulo);
	  printf("Autor: %s\n", aux->autor);
	  printf("Categoría: %s\n", aux->categoria);
	  printf("Fecha de publicación: %i\n", aux->fechapub);
	  printf("Número de páginas: %i\n", aux->paginasl);
	  printf("Usuario prestado: %s\n", aux->usuprestamo);
	  printf("ISBN: %s\n\n", aux->isbn);
	}
      aux=aux->sigl;
      x++;
    }
  if(strcmp(aux->usuprestamo, nomusu)==0)
    {
      printf("-------Registro %i--------\n", x);
      printf("Título: %s\n", aux->titulo);
      printf("Autor: %s\n", aux->autor);      printf("Categoría: %s\n", aux->categoria);
      printf("Fecha de publicación: %i\n", aux->fechapub);
      printf("Número de páginas: %i\n", aux->paginasl);
      printf("Usuario prestado: %s\n", aux->usuprestamo);
      printf("ISBN: %s\n\n", aux->isbn);
    }
  if(inicioL==NULL)
    {
      system("clear");
      printf("\n\n\t\tNo hay libros registrados en la base, presiona enter...");
      getchar();
    }
}

int validarpres(char nomusu[], libros *inicioL)//checar después
{
  int bandera=0;
  libros *aux1;
  aux1=inicioL;
  while(aux1->sigl!=NULL)
    {
      if(strcmp(aux1->usuprestamo, nomusu)==0)
	bandera=1;
      aux1=aux1->sigl;
    }
  if(strcmp(aux1->usuprestamo, nomusu)==0)
    bandera=1;
  return bandera;
}

void ayudaadmon()
{
  system("clear");
  printf("\n\n");
  printf("\t\tBienvenido administrador, a continuación se te explicarán las funciones de lo\n\t\tque hay en el menú.\n");
  printf("\n\n\t\tEn la 1ra opción se mostrará en pantalla los libros en prestamo y la fecha de expiración para el mismo.\n");
  printf("\t\tEn la 2da opción se mostrará los usuarios que están dados de alta como los libros que tienen.\n");
  printf("\t\tEn la 3ra opción se mostrará los libros que están dados de alta y que se dierón de baja.\n");
  printf("\t\tEn la 4ta opción se podrá dar de baja a los usuarios que se desee y obviamente que esten registrados.\n");
  printf("\t\tEn la 5ta opción se mostrará en pantalla el/los libros más populares solicitados.\n");
  printf("\t\tEn la 6ta opción se mostrará la ayuda en la que acabas de ingresar para ver la información de lo demás.\n");
  printf("\t\tPresiona enter para regresar al menú del administrador.\n");
  getchar();
  getchar();
}

void infolib(libros *inicioL)//falta poner fechas de prestamo y cuando se termina el préstamo
{
  libros *aux;
  int x=1;
  aux=inicioL;
  while(aux->sigl!=NULL)
    {
      if(strcmp(aux->usuprestamo, "NULL")!=0)
	{
	  printf("-------Registro %i--------\n", x);
	  printf("Título: %s\n", aux->titulo);
	  printf("Autor: %s\n", aux->autor);
	  printf("Categoría: %s\n", aux->categoria);
	  printf("Fecha de publicación: %i\n", aux->fechapub);
	  printf("Número de páginas: %i\n", aux->paginasl);
	  printf("Disponibilidad: %s\n", aux->usuprestamo);
	  printf("Fecha de salida: %s\n", aux->fechasalida);
	  printf("Fecha de expiración préstamo: %s\n", aux->fechaentrada);
	  printf("ISBN: %s\n\n", aux->isbn); 
	}
      aux=aux->sigl;
      x++;
    }
  if(strcmp(aux->usuprestamo, "NULL")!=0)
    {
      //strcpy(aux->usuprestamo, numusu)==0;
      printf("-------Registro %i--------\n", x);
      printf("Título: %s\n", aux->titulo);
      printf("Autor: %s\n", aux->autor);
      printf("Categoría: %s\n", aux->categoria);
      printf("Fecha de publicación: %i\n", aux->fechapub);
      printf("Número de páginas: %i\n", aux->paginasl);
      printf("Disponibilidad: %s\n", aux->usuprestamo);
      printf("Fecha de salida: %s\n", aux->fechasalida);
      printf("Fecha de expiración préstamo: %s", aux->fechaentrada);
      printf("ISBN: %s\n\n", aux->isbn);
    }
  printf("Presiona enter...");
}

void menualtbaj(libros **inicioL)
{
  int opcion;
  do
    {
      system("clear");
      printf("\n\n");
      printf("\t\t\t\t**Menú**\n");
      printf("\t\t\t1. Alta de libros.\n");
      printf("\t\t\t2. Baja de libros.\n");
      printf("\t\t\t3. Regresar.\n");
      printf("Ingresa la opción: ");
      scanf("%i", &opcion);
      switch(opcion)
	{
	case 1:
	  altalib(inicioL);
	  break;
	case 2:
	  bajalib(inicioL);
	  break;
	case 3:
	  break;
	default:
	  printf("Debes ingresar una opción válida.\n");
	  printf("Presiona enter...");
	  getchar();
	  getchar();
	  break;
	}
    }
  while(opcion!=3);
}

void bajalib(libros **inicioL)
{
  libros *aux, *aux1, *aux2;
  int x=1, registro, i;
  aux=*inicioL;
  system("clear");
  printf("Estos son los libros que están en la base:\n");
  while(aux->sigl!=NULL)
    {
      printf("-------Registro %i--------\n", x);
      printf("Título: %s\n", aux->titulo);
      printf("Autor: %s\n", aux->autor);
      printf("Categoría: %s\n", aux->categoria);
      printf("Fecha de publicación: %i\n", aux->fechapub);
      printf("Número de páginas: %i\n", aux->paginasl);
      printf("Disponibilidad: %s\n", aux->usuprestamo);
      printf("ISBN: %s\n\n", aux->isbn);
      aux=aux->sigl;
      x++;
    }
  printf("-------Registro %i--------\n", x);
  printf("Título: %s\n", aux->titulo);
  printf("Autor: %s\n", aux->autor);
  printf("Categoría: %s\n", aux->categoria);
  printf("Fecha de publicación: %i\n", aux->fechapub);
  printf("Número de páginas: %i\n", aux->paginasl);
  printf("Disponibilidad: %s\n", aux->usuprestamo);
  printf("ISBN: %s\n\n", aux->isbn);
  printf("\nIngresa el número de registro del libro que deseas dar de baja: ");
  scanf("%i", &registro);
  system("clear");
  aux=*inicioL;
  for(i=1;i<registro;i++)
    aux=aux->sigl;
  printf("-------Registro %i--------\n", registro);
  printf("titulo: %s\n", aux->titulo);
  printf("autor: %s\n", aux->autor);
  printf("categoria: %s\n", aux->categoria);
  printf("fecha: %i\n", aux->fechapub);
  printf("num paginas: %i\n", aux->paginasl);
  printf("usuario: %s\n", aux->usuprestamo);
  printf("isbn: %s\n", aux->isbn);
  printf("Has eliminado el libro exitosamente.\nPresiona enter...");
  if(aux==*inicioL)
    *inicioL=(aux->sigl);
  else
    {
      aux2=*inicioL;
      while(aux2->sigl!=aux)
	aux2=aux2->sigl;
      aux2->sigl=aux->sigl;
    }
  getchar();
  getchar();
}


void altalib(libros **inicioL)
{
  
  libros *aux1, *aux2, *aux3;
  int fechaaux, paginasaux;
  aux1=malloc(sizeof(libros));
  system("clear");
  strcpy(aux1->fechasalida, "NULL")==0;
  strcpy(aux1->fechaentrada, "NULL")==0;
  printf("Ingresa el título del libro: ");
  __fpurge(stdin);
  gets(aux1->titulo);
  getchar();
  printf("\nIngresa el autor del libro: ");
  __fpurge(stdin);
  scanf("%s[^\n]", aux1->autor);
  getchar();
  printf("\nIngresa la categoria del libro: ");
  __fpurge(stdin);
  scanf("%s[^\n]c", aux1->categoria);
  getchar();
  printf("\nIngresa la fecha de publicación: ");
  __fpurge(stdin);
  scanf("%i", &fechaaux);
  getchar();
  //getchar();
  printf("\nIngresa el número total de páginas: ");
  __fpurge(stdin);
  scanf("%i", &paginasaux);
  getchar();
  strcpy(aux1->usuprestamo, "NULL")==0;
  // getchar();
  //getchar();
  printf("\nIngresa el ISBN del libro: ");
  //__fpurge(stdin);
  scanf("%s[^\n]c", aux1->isbn);
  aux1->fechapub=fechaaux;
  aux1->paginasl=paginasaux;
  getchar();
  system("clear");
  printf("titulo: %s\n", aux1->titulo);
  printf("autor: %s\n", aux1->autor);
  printf("categoria: %s\n", aux1->categoria);
  printf("fecha de publicacion: %i\n", fechaaux);
  printf("total de paginas: %i\n", paginasaux);
  printf("ISBN: %s\n", aux1->isbn);
  printf("\n\nPresiona enter...");
  getchar();
  /* aux1->fechapub=fechaaux; */
  /* aux1->paginasl=paginasaux; */
  /* aux1->fechapub=fecha; */
  /* aux1->paginasl=paginas; */
  aux1->pedidos=0;
  if(*inicioL==NULL)
    *inicioL=aux1;
  else
    {
      aux2=*inicioL;
      if(strcmp(aux1->titulo, aux2->titulo)<0)
	{
	  aux1->sigl=*inicioL;
	  *inicioL=aux1;
	}
      else
	{
	  aux2=*inicioL;
	  if(aux2->sigl==NULL)
	    {
	      aux2->sigl=aux1;
	    }
	  else
	    {
	      aux2=*inicioL;
	      aux3=*inicioL;
	      while(strcmp(aux2->titulo, aux1->titulo)<0&&aux2->sigl!=NULL)
		aux2=aux2->sigl;
	      if(strcmp(aux2->titulo, aux1->titulo)<0)
		aux2->sigl=aux1;
	      else
		{
		  aux1->sigl=aux2;
		  {
		    while(aux3->sigl!=aux2)
		      aux3=aux3->sigl;
		    aux3->sigl=aux1;
		  }
		}
	    }
	}
    }
}


void bajausu(usuarios *inicioU)
{
  usuarios *aux;
  char selecusu[80];
  aux=inicioU;
  printf("Estos son los usuarios activos: \n");
  imprimirusu2(inicioU);
  printf("Ingresa el nombre completo del usuario que deseas dar de baja: ");
  gets(selecusu);
  while(strcmp(selecusu, aux->nom)!=0&&aux->sigu!=NULL)
    aux=aux->sigu;
  printf("%s", aux->nom);
  getchar();
  if(strcmp(selecusu, aux->nom)==0)
    aux->bajalt=0;
  else
    {
      printf("No se encontro al usuario.\n");
      printf("Presiona enter...");
      getchar();
    }
}

void imprimirusu2(usuarios *inicioU)
{
  usuarios *aux;
  int x=1;
  aux=inicioU;
  system("clear");
  while(aux->sigu!=NULL)
    {
      if(aux->bajalt==1)
	{
	  printf("%i Nombre: %s\n", x, aux->nom);
	  printf("Dirección: %s\n", aux->direccion);
	  printf("Nacimiento: %s\n", aux->nacimiento);
	  printf("Correo electrónico: %s\n", aux->email);
	  printf("Estado de usuario: %i\n", aux->bajalt);
	  printf("Total de libros solicitados: %i\n", aux->totallib);
	  printf("Contraseña: %s\n\n", aux->contrasena);
	}
      aux=aux->sigu;
      x++;
    }
  if(aux->bajalt==1)
    {
      printf("%i Nombre: %s\n", x, aux->nom);
      printf("Dirección: %s\n", aux->direccion);
      printf("Nacimiento: %s\n", aux->nacimiento);
      printf("Correo electrónico: %s\n", aux->email);
      printf("Estado de usuario: %i\n", aux->bajalt);
      printf("Total de libros solicitados: %i\n", aux->totallib);
      printf("Contraseña: %s\n", aux->contrasena);
      printf("\n\nPresiona enter...");
    }
  getchar();
  getchar();
  if(inicioU==NULL)
    {
      system("clear");
      printf("\n\n\t\tNo existen usuarios registrados en la base, presiona enter...");
      getchar();
    }
}

void liberarmemo(usuarios *inicioU, libros *inicioL)
{
  usuarios *aux1, *aux3;
  libros *aux2, *aux4;
  aux1=inicioU;
  aux2=inicioL;
  while(aux1->sigu!=NULL)
    {
      aux3=aux1;
      aux1=aux1->sigu;
      free(aux3);
    }
  free(aux1);
  while(aux2->sigl!=NULL)
    {
      aux4=aux2;
      aux2=aux2->sigl;
      free(aux4);
    }
  free(aux2);
}

void sacarlibroT(libros *inicioL, char numusu[], int num, int *totallib)
{
  int i;
  libros *aux1;
  char actual[100], entrega[100];
  aux1=inicioL;
  for(i=1;i<num;i++)
    {
      aux1=aux1->sigl;
    }
  if(strcmp(aux1->usuprestamo, "NULL")==0)
    {
      aux1->pedidos=aux1->pedidos+1;
      fechas1(actual);
      fechas2(entrega);
      strcpy(aux1->fechasalida, actual)==0;
      strcpy(aux1->fechaentrada, entrega)==0;
      strcpy(aux1->usuprestamo, numusu)==0;
      printf("titulo: %s\n", aux1->titulo);
      printf("autor: %s\n", aux1->autor);
      printf("categoria: %s\n", aux1->categoria);
      printf("fecha: %i\n", aux1->fechapub);
      printf("num paginas: %i\n", aux1->paginasl);
      printf("usuario: %s\n", aux1->usuprestamo);
      printf("isbn: %s\n", aux1->isbn);
      *totallib=*totallib+1;
      printf("total de libros pedidos: %i\n", *totallib);
      printf("\nHas solicitado el libro exitosamente.\nPresiona enter...");
      getchar();
      getchar();
    }
  else
    {
      system("clear");
      printf("\n\n\t\tEl libro solicitado ya ha sido prestado.\n\t\tIntenta con otro, presiona enter...");
      getchar();
      getchar();
    }
}

int popu(libros *inicioL)
{
  int mayor=0;
  libros *aux;
  aux=inicioL;
  while(aux->sigl!=NULL)
    {
      aux=aux->sigl;
      if(aux->pedidos>mayor)
	mayor=aux->pedidos;
    }
  return mayor;
}

void encontrarpopu(libros *inicioL, int pop)
{
  int x=1;
  libros *aux;
  aux=inicioL;
  if(pop==0)
    {
      system("clear");
      printf("\n\n");
      printf("\t\tNo hay libros populares aún.\n");
      printf("\t\tPresiona enter...");
      getchar();
    }
  printf("Estos son el/los libros más populares por título:\n\n");
  while(aux->sigl!=NULL)
    {
      aux=aux->sigl;
      if(pop==aux->pedidos)
	{
	  printf("-------Registro %i--------\n", x);
	  printf("Título: %s\n", aux->titulo);
	  printf("Autor: %s\n", aux->autor);
	  printf("Categoría: %s\n", aux->categoria);
	  printf("Fecha de publicación: %i\n", aux->fechapub);
	  printf("Número de páginas: %i\n", aux->paginasl);
	  printf("Disponibilidad: %s\n", aux->usuprestamo);
	  printf("ISBN: %s\n\n", aux->isbn);
	  aux=aux->sigl;
	  x++;
	}
    }
  if(pop==aux->pedidos)
    {
      printf("-------Registro %i--------\n", x);
      printf("Título: %s\n", aux->titulo);
      printf("Autor: %s\n", aux->autor);
      printf("Categoría: %s\n", aux->categoria);
      printf("Fecha de publicación: %i\n", aux->fechapub);
      printf("Número de páginas: %i\n", aux->paginasl);
      printf("Disponibilidad: %s\n", aux->usuprestamo);
      printf("ISBN: %s\n\n", aux->isbn);
    }
}

void *fechas1(char actual[100])
{
  int mes,ano, dia;
  time_t t;
  struct tm *tm;
  char fechayhora[100];
  t=time(NULL);
  tm=localtime(&t);
  strftime(actual, 100, "%d/%m/%y", tm);
}

void *fechas2(char entrega[100])
{
  int mes,ano, dia;
  time_t t;
  struct tm *tm;
  char fechayhora[100], nuefecha[15];
  t=time(NULL);
  tm=localtime(&t);
  strftime(nuefecha, 100, "%d/%m/%y", tm);
  sscanf(nuefecha,"%d/%d/%d", &dia, &mes, &ano);
  if((mes==4||mes==6||mes==9||mes==11)&&dia+15>30)
    {
      mes=mes+1;
      dia=dia+15-30;
    }
  else
    if((mes==1||mes==3||mes==5||mes==7||mes==8||mes==10||mes==12)&&dia+15>31)
      {
	mes++;
	dia=dia+15-31;
      }
    else
      if(mes==2&&ano%4==0&&dia+15>29)
	{
	  mes++;
	  dia=dia+15-29;
	}
      else
	if(mes==2&&ano%4!=0&&dia+15>28)
	  {
	    
	    mes++;
	    dia=dia+15-28;
	  }
	else
	  if(mes==13)
	    {
	      //printf("dia: %i", dia);
	      mes=1;
	      ano=ano+1;
	    }
	  else
	    dia=dia+15;
  //printf("%i/%i/%i\n", dia, mes, ano);
  //getchar();
  //sscanf(entrega,"%d/%d/%d", &dia, &mes, &ano);
  sprintf(entrega,"%i/%i/%i", dia, mes, ano);
}

void ayudausu()
{
  printf("\n\n\n");
  printf("\t\t\tEsta es la guía del usuario y a continuación se te presentará los pasos\n");
  printf("\t\t\ta seguir para moverte a través del menú del usuario.\n\t\tPresiona enter...");
  getchar();
  system("clear");
  printf("\n\n\n");
  printf("\t\tPrimero aparecerá unmenú en el cual tu decidirás si entrar como administrador o como usuario.\n");
  printf("\t\tDeberás seleccionar para entrar como usuario y posteriormente aparecerá una pregunta\n");
  printf("\t\tque dirá si ya estás registrado o no en la base de datos, a continuación se desgolzará\n");
  printf("\t\tel qué hacer en cada opción.\n\t\tPresiona enter...");
  getchar();
  system("clear");
  printf("\t\tEn caso de que sea la opción 1 se te pedirá que ingreses tu nombre de usuario y la contraseña.\n");
  printf("\t\tUna vez que estén correctas ambas ingresarás al sistema para poder hacer las actividades que están\n");
  printf("\t\tpermitidas para el usuario.\n\n");
  printf("\t\tEn caso de que sea la opción 2 tendrás que registrarte en el sistema y una vez que ya estés\n");
  printf("\t\tregistrado podrás acceder al sistema para poder hacer las actividades permitidas para usuario.\n");
  printf("\t\tPresiona enter...");
  getchar();
  system("clear");
}


void imprimirusuarg(usuarios *inicioU)
{
  usuarios *aux;
  int x=1;
  aux=inicioU;
  system("clear");
  while(aux->sigu!=NULL)
    {
      printf("%i Nombre: %s\n", x, aux->nom);
      printf("Dirección: %s\n", aux->direccion);
      printf("Nacimiento: %s\n", aux->nacimiento);
      printf("Correo electrónico: %s\n", aux->email);
      printf("Estado de usuario: %i\n", aux->bajalt);
      printf("Total de libros solicitados: %i\n", aux->totallib);
      printf("Contraseña: %s\n\n", aux->contrasena);
      aux=aux->sigu;
      x++;
    }
  printf("%i Nombre: %s\n", x, aux->nom);
  printf("Dirección: %s\n", aux->direccion);
  printf("Nacimiento: %s\n", aux->nacimiento);
  printf("Correo electrónico: %s\n", aux->email);
  printf("Estado de usuario: %i\n", aux->bajalt);
  printf("Total de libros solicitados: %i\n", aux->totallib);
  printf("Contraseña: %s\n", aux->contrasena);
  printf("\n\nPresiona enter...");
  getchar();
  if(inicioU==NULL)
    {
      system("clear");
      printf("\n\n\t\tNo existen usuarios registrados en la base, presiona enter...");
      getchar();
    }
}
