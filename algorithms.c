#include "head.h"

/**
 * Calculates the force on the spring at the given position
*/
double forceSpring(Parameters p, double x) {
    return -p.k*(x-p.anchor_position-p.natural_length);
}

/**
 * Calculates de potential energy of the system
*/
double potentialEnergy(Parameters p, double x) {
    return 0.5*p.k*(x-p.anchor_position-p.natural_length)*(x-p.anchor_position-p.natural_length);
}

/**
 * Calculates the kinetic energy of the system
*/
double kineticEnergy(Parameters p, double v) {
    return 0.5*p.mass*v*v; 
}

/**
 * Calculates the mechanical energy of the system
*/
double mechanicalEnergy(Parameters p, double x, double v) {
    return kineticEnergy(p, v)+potentialEnergy(p, x);
}

/**
 * Updates the value of the position and the velocity using Euler's algorithm
 */
void evolutionEuler(Parameters p, double *x, double *v) {
    double F=forceSpring(p, *x);
    *x+=p.h*(*v);
    *v+=p.h*F/p.mass; 
}

/**
 * Updates the value of the position and the velocity using Verlet's algorithm
 */
void evolutionVerlet(Parameters p, double *x, double *v) {
    *v+=forceSpring(p, *x)*p.h/2/p.mass;
    *x+=*v*p.h;
    *v+=forceSpring(p, *x)*p.h/2/p.mass;
}