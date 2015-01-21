/*
  Se simulará como se mueve un motor (angular), la entrada de datos serán las posiciones angulares deseadas y la salida serán las posiciones logradas.

  El formato de ejecución es:
    ./executuble  h  initial_y Ti  K  Td  <N> ruta_datos

    donde:
    h: tiempo entre muestras
    initial_y: Angulo inicial del motor.
    Ti: Parámetro del PID de la parte integrativa.
    K: Parámetro del PID de la parte Proporcional
    Td: Parámetro del PID de la parte derivativa.
    <N>: Parametro util para mejorar la derivación discreta usar valores en el intervalo [3 20], es opcional.
    ruta_datos: Ruta a los datos de entrada, o sea a las posiciones que se desea mover el motor cada tiempo de muestra.

*/
#include "DinamicaMotores.hpp"
#include <stdio.h> // printf, fseek, rewind, ftell
#include <stdlib.h> // atof
#include <string.h> // strtok

DinamicaMotores * inicializacionMotorSimulado(int argc, char ** argv);
int obtencionDatos(int argc,char ** argv);
void calculoPosicionesSimuladas(DinamicaMotores * motor, int cantidad_posiciones,double * datos_simulados);
double * datos;

int main(int argc, char ** argv)
{
  /*
    Orden de la función:
      1) A través de la entrada por consola se ontienen los parámetros del motor.
      2) Se obtienen los datos desde la entrada de datos del usuario y son guardados en un arreglo del tamaño exacto.
      3) Se calculan las posiciones que el motor debería lograr.
      4) Se grafican ambos casos usando octave.
  */
  DinamicaMotores * motor;
  motor=inicializacionMotorSimulado(argc, argv);
  motor->imprimir_PID();
  int cantidad_posiciones = obtencionDatos(argc, argv);
  double * datos_simulados = (double *)malloc(sizeof(double)*cantidad_posiciones);
  calculoPosicionesSimuladas(motor,cantidad_posiciones,datos_simulados);
  return EXIT_SUCCESS;
}

DinamicaMotores * inicializacionMotorSimulado(int argc, char ** argv)
{
  DinamicaMotores * motor;
  if( argc == 7){ // Entonces la N no fue especificada.
    printf("%lf\t%lf\t%lf\t%lf\t%lf\n",atof(argv[1]),atof(argv[2]),atof(argv[3]),atof(argv[4]),atof(argv[5]) );
    motor = new DinamicaMotores( atof(argv[1]),atof(argv[2]),atof(argv[3]),atof(argv[4]),atof(argv[5]) );
  }
  else if( argc == 8){ // Todos los datos fueron introducidos.
    printf("%lf\t%lf\t%lf\t%lf\t%lf\t%lfok\n",atof(argv[1]),atof(argv[2]),atof(argv[3]),atof(argv[4]),atof(argv[5]),atof(argv[6]) );
    motor = new DinamicaMotores( atof(argv[1]),atof(argv[2]),atof(argv[3]),atof(argv[4]),atof(argv[5]), atof(argv[6]) );
  }
  else{ // El usuario no introdujo correctamente los valores.
    printf("Error, la ejecucion del programa requiere la siguiente estructura:\n %s h  initial_y Ti  K  Td  <N> ruta_datos\ndonde:\n    h: tiempo entre muestras\n    initial_y: Angulo inicial del motor.\n    Ti: Parámetro del PID de la parte integrativa.\n    K: Parámetro del PID de la parte Proporcional\n    Td: Parámetro del PID de la parte derivativa.\n    <N>: Parametro util para mejorar la derivación discreta usar valores en el intervalo [3 20], es opcional.\n    ruta_datos: Ruta a los datos de entrada, o sea a las posiciones que se desea mover el motor cada tiempo de muestra.\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  return motor;
}
/*
  Se retorna la cantidad de datos obtenidos.
*/
int obtencionDatos(int argc,char ** argv)
{
  FILE * archivo_entrada;
  int largo_archivo;
  archivo_entrada = fopen(argv[argc-1],"r"); // Se guarda el archivo en memoria
  if( archivo_entrada == NULL )
  {
    perror ("Error al abrir el archivo\n");
    exit (EXIT_FAILURE);
  }
  fseek(archivo_entrada, 0, SEEK_END);
  largo_archivo = ftell(archivo_entrada); // Se obtiene el largo del archivo en carácteres.
  fseek(archivo_entrada, 0, SEEK_SET);
  char * string_archivo  = (char *)malloc(sizeof(char)*largo_archivo);
  datos  = (double *)malloc(sizeof(double)*largo_archivo/17); // en realidad son menos pero es una aproximación y así se usa arreglos que son la estructura más eficiente para este problema.
  if (string_archivo)
  {
    fread (string_archivo, 1, largo_archivo, archivo_entrada); // Se copia a string el archivo
  }
  fclose (archivo_entrada);

  const char delimiters[] = "\n \t";
  char * string_dato_obtenido;
  string_dato_obtenido = strtok ( string_archivo,  delimiters);
  int contador=0;
  while (string_dato_obtenido != NULL)
  {
    datos[contador++] =  atof(string_dato_obtenido);
    string_dato_obtenido = strtok (NULL, delimiters);
  }
  return contador;
}


void calculoPosicionesSimuladas(DinamicaMotores * motor, int cantidad_posiciones,double * datos_simulados)
{
  for(int i=0; i < cantidad_posiciones ; i++){
    printf("dato:%lf\n",datos[i]);
    datos_simulados[i] = motor->calc_y(datos[i]);
  }
}
