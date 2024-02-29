#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define EULER
#define VERLET

typedef struct Parameters {
    double mass;
    double k;
    double natural_length;
    double anchor_position;
    double h;
    double t_max;
    double x0;
    double v0;
} Parameters;


// input_output.c functions
int loadParameters(int spring_id, Parameters *p);
void resetFile();
void writeEvolution(Parameters p, double x, double v, double time);

// algorithms.c functions
double forceSpring(Parameters p, double x);
double potentialEnergy(Parameters p, double x);
double kineticEnergy(Parameters p, double v);
double mechanicalEnergy(Parameters p, double x, double v);
void evolutionEuler(Parameters p, double *x, double *v);
void evolutionVerlet(Parameters p, double *x, double *v);
