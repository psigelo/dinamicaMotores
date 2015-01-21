#ifndef DINAMICA_MOTORES_HPP
#define DINAMICA_MOTORES_HPP

#include <stdio.h>

/*

El objetivo de este programa es simular la dinámica de un motor a través de una planta de segundo orden tipo PID.

Las aproximaciones discretas se harán de acuerdo a la sección “8.5 Digital PID-Controllers” del libro Computer Controller Sistems Theory and Design, Karl Astrom, Ed. 3.

*/
class DinamicaMotores{
  public:
    /*
    La dinámica de los motores será:
    y(t) = K*( x(t) + (1/Ti)*Integrate[x(t)] + Td Derivate[x(t)] )
    de ahí puede entenderse los parámetros Ti, K, Td, el último parámetro N es para la aproximación de la derivada:
    en Laplace la derivada es ´s´, se aproximará s*Td por s*Td/(1+s*Td/N) donde se espera que N se enuentre en el intervalo [3,20].

    Donde y(t) es el ángulo del motor, x(t) es el ángulo deseado. Ambos en radianes en intervalo [0-2Pi].

    h es el intervalo de tiempo entre muestras.
    */
    DinamicaMotores(double h, double initial_y,double Ti, double K, double Td, double N);
    /*
    La dinámica de los motores será:
    y(t) = K*( x(t) + (1/Ti)*Integrate[x(t)] + Td Derivate[x(t)] )
    de ahí puede entenderse los parámetros Ti, K, Td, el último parámetro N es para la aproximación de la derivada:
    en Laplace la derivada es ´s´, se aproximará s*Td por s*Td/(1+s*Td/N) donde se espera que N se enuentre en el intervalo [3,20], en caso de no especificarse un N se tomará un valor en el intervalo.


    Donde y(t) es el ángulo del motor, x(t) es el ángulo deseado.

    h es el intervalo de tiempo entre muestras.

    */
    DinamicaMotores(double h,double initial_y, double Ti, double K, double Td);
    /*
    Se calcula el estado próximo del motor real (simulado por este PID).
    */
    double calc_y(double x);
    void imprimir_PID();
  private:
    double P(double x);
    double I(double x);
    double D(double x);
    double Ti;
    double K;
    double Td;
    double N;
    double h;
    double y;
    double y_prev;
    double I_val;
    double D_val;
    double D_prev;
};

#endif
