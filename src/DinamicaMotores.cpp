/*

  El objetivo de este programa es simular la dinámica de un motor a través de una planta de segundo orden tipo PID.

  Las aproximaciones discretas se harán de acuerdo a la sección “8.5 Digital PID-Controllers” del libro Computer Controller Sistems Theory and Design, Karl Astrom, Ed. 3.

*/
#include "DinamicaMotores.hpp"
/*
  La dinámica de los motores será:
  y(t) = K*( x(t) + (1/Ti)*Integrate[x(t)] + Td Derivate[x(t)] )
  de ahí puede entenderse los parámetros Ti, K, Td, el último parámetro N es para la aproximación de la derivada:
  en Laplace la derivada es ´s´, se aproximará s*Td por s*Td/(1+s*Td/N) donde se espera que N se enuentre en el intervalo [3,20].

  Donde y(t) es el ángulo del motor, x(t) es el ángulo deseado. Ambos en radianes en intervalo [0-2Pi].

  h es el intervalo de tiempo entre muestras.
*/
DinamicaMotores::DinamicaMotores(double h, double initial_y,double Ti, double K, double Td, double N)
{
  printf("%lf\t%lf\t%lf\t%lf\t%lf\t%lf\n",h,initial_y,Ti,K,Td,N);
  this->Ti=Ti;
  this->K=K;
  printf("K:%lf\n",this->K);
  this->Td=Td;
  this->N=N;
  this->h=h;
  this->y=initial_y;
  this->y_prev = initial_y; // dado que no existe un y anterior se usa el inicial
  I_val=0.0;
  D_val=0.0;
  D_prev=0.0;
  y=0.0;
}
/*
La dinámica de los motores será:
y(t) = K*( x(t) + (1/Ti)*Integrate[x(t)] + Td Derivate[x(t)] )
de ahí puede entenderse los parámetros Ti, K, Td, el último parámetro N es para la aproximación de la derivada:
en Laplace la derivada es ´s´, se aproximará s*Td por s*Td/(1+s*Td/N) donde se espera que N se enuentre en el intervalo [3,20], en caso de no especificarse un N se tomará un valor en el intervalo.


Donde y(t) es el ángulo del motor, x(t) es el ángulo deseado.

h es el intervalo de tiempo entre muestras.

*/
DinamicaMotores::DinamicaMotores(double h,double initial_y, double Ti, double K, double Td)
{
  printf("%lf\t%lf\t%lf\t%lf\t%lf\n",h,initial_y,Ti,K,Td);

  this->Ti=Ti;
  this->K=K;
  this->Td=Td;
  this->N=10.0; // Se recomienda escoger uno, pero 10 es un número dentro de lo normal.
  this->h=h;
  this->y=initial_y;
  this->y_prev = initial_y; // dado que no existe un y anterior se usa el inicial.
  I_val=0.0;
  D_val=0.0;
  D_prev=0.0;
  y=0.0;
}

/*

  El estado proximo del motor real (simulado por este PID).

*/
double DinamicaMotores::calc_y(double x)
{
  printf("x:%lf\n", x);
  double y_aux = y;
  y = P(x) + I(x) + D(x);
  return y;
}


double DinamicaMotores::P(double x)
{
  double valor = K*(x-y);
  printf("P:%lf\n", valor);
  return valor;
}

double DinamicaMotores::I(double x)
{
  I_val = I_val  + (double)(K*h/(double)Ti)*(x-y);
  printf("I:%lf\n", I_val);
  return I_val;
}

double DinamicaMotores::D(double x)
{
  printf("D:%lf\ny:%lf\ny_prev%lf\n", D_val,y,y_prev);
  double D_aux = D_val;
  D_val = ( D_prev*Td  + K*Td*N*(y_prev - y) )/(double)(Td + N*h);
  D_prev=D_aux;
  y_prev=y;

  return D_val;
}

void DinamicaMotores::imprimir_PID(){
  printf("K:%lf\n",K);
  printf("Ti:%lf\n",Ti);
  printf("Td:%lf\n",Td);
  printf("N:%lf\n",N);
}
