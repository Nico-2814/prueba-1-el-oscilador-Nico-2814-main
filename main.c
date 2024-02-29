#include "head.h"

int main() {
    int step, success, max_steps;    
    double x, v, time;
    Parameters parameters;

    // Set-up
    time = 0;
    success = loadParameters(1, &parameters);

    if(success == -1) {
        printf("Error loading the parameters");
        exit(EXIT_FAILURE);
    }

    x = parameters.x0;
    v = parameters.v0;
    max_steps = parameters.t_max / parameters.h;

    // Evolution
    resetFile();
    for(step = 0; step < max_steps; step++) {
#if defined(EULER)
        evolutionEuler(parameters, &x, &v);
#elif defined(VERLET)
        evolutionVerlet(parameters, &x, &v);
#endif
        time += parameters.h;

        if(step%1000 == 0)
            writeEvolution(parameters, x, v, time);
    }

    return 0;
}