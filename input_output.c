#include "head.h"


/**
 * Loads the parameters of the requested spring contained in
 * 
 * data/spring_X.txt
 * 
 * where X is the number of the spring (spring_id). If the file 
 * does not exist, the function should return -1. Otherwise, it
 * should return 0.
*/ 
int loadParameters(int spring_id, Parameters *parameters) {
    char id[100];
    sprintf(id, "%d", spring_id);
    FILE *f;
    char nom[17]="data/spring_";
    f=fopen(strcat(strcat(nom,id), ".txt"), "r");
    if (f==NULL){
        return -1;
    }
    else{

        char palabra[100];
        double numero;

        do{
        fscanf(f, "%s %lf", palabra, &numero);

        if(strcmp(palabra, "mass")==0)
            parameters->mass=numero;

        if(strcmp(palabra, "k")==0)
            parameters->k=numero;

        if(strcmp(palabra, "natural_length")==0)
            parameters->natural_length=numero;

        if(strcmp(palabra, "anchor_position")==0)
            parameters->anchor_position=numero;

        if(strcmp(palabra, "h")==0)
            parameters->h=numero;

        if(strcmp(palabra, "t_max")==0)
            parameters->t_max=numero;

        if(strcmp(palabra, "x0")==0)
            parameters->x0=numero;

        if(strcmp(palabra, "v0")==0)
            parameters->v0=numero;
        }while(!feof(f));
        fclose(f);
        return 0;
    }
}

/**
 * Creates a file in the results folder with the name
 * 
 * results/evolution_ALGORITHM.txt
 * 
 * where ALGORITHM should be EULER or VERLET depending on the algorithm used. Note
 * that you can get this information using #ifdef.
 * 
 * It also writes in text format a single line that will act as header:
 * #t Ec Ep Em x v
*/
void resetFile() {
    #ifdef EULER
    FILE *f=fopen("results/evolution_EULER.txt", "w");
    #endif

    #ifdef VERLET
    FILE *f=fopen("results/evolution_VERLET.txt", "w");
    #endif

    fprintf(f, "#t Ec Ep Em x v\n");
    fclose(f);
}

/**
 * Appends the state of the system into the file created with resetFile(). There
 * should be 6 values separated by a single whitespace in each line: time, 
 * kinetic energy, potential energy, mechanical energy, position, velocity. 
*/
void writeEvolution(Parameters p, double x, double v, double time) {
    #ifdef EULER
    FILE *f=fopen("results/evolution_EULER.txt", "a");
    #endif

    #ifdef VERLET
    FILE *f=fopen("results/evolution_VERLET.txt", "a");
    #endif

    fprintf(f, "%f %f %f %f %f %f\n", time, kineticEnergy(p, v), potentialEnergy(p, x), mechanicalEnergy(p, x, v), x, v);
    fclose(f);
}