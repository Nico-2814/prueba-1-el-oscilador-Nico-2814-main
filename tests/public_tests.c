#include "../head.h"
#include <stdbool.h>
#include <math.h>
#include <string.h>

#define RUN_TEST(test_function) do { \
    n_test++; \
    printf("%d) ", n_test); \
    status = test_function(); \
    if(status) { \
        printf("OK\n"); \
        passed++; \
    } \
} while(0)

#define EPSILON 1e-3
#define APPROX_EQUAL(x, y) (fabs((x) - (y)) < EPSILON)

int countLines(FILE *f);

bool test_forceSpring() {
    Parameters p;
    double force;

    printf("Testing forceSpring...");

    p.k = 10;
    p.natural_length = p.anchor_position = 0;
    force = forceSpring(p, 0);
    if(!APPROX_EQUAL(force, 0.0)) {
        printf("\n\tERROR: Wrong force, expected 0, obtained %.1lf\n", force);
        return false;
    }

    p.k = 10;
    p.natural_length = p.anchor_position = 0;
    force = forceSpring(p, 1);
    if(!APPROX_EQUAL(force, -10.0)) {
        printf("\n\tERROR: Wrong force, expected -10, obtained %.1lf\n", force);
        return false;
    }

    p.k = 20;
    p.natural_length = 1;
    p.anchor_position = 0;
    force = forceSpring(p, 2);
    if(!APPROX_EQUAL(force, -20.0)) {
        printf("\n\tERROR: Wrong force, expected -20, obtained %.1lf\n", force);
        return false;
    }

    p.k = 5;
    p.natural_length = 0;
    p.anchor_position = 1;
    force = forceSpring(p, -3);
    if(!APPROX_EQUAL(force, 20.0)) {
        printf("\n\tERROR: Wrong force, expected 20, obtained %.1lf\n", force);
        return false;
    }

    return true;

}

bool test_evolutionEuler() {
    Parameters p;
    double x, v;

    printf("Testing evolutionEuler...");

    p.mass = 1.5;
    p.k = 1.2;
    p.natural_length = 0;
    p.anchor_position = 0;
    p.h = 1;

    x = 0;
    v = 3.2;

    evolutionEuler(p, &x, &v);
    if(!APPROX_EQUAL(x, 3.2) || !APPROX_EQUAL(v, 3.2)) {
        printf("\n\tERROR: Wrong position, expected (x,v) = (3.2, 3.2), obtained (x,v) = (%.2lf, %.2lf)\n", x, v);
        return false;
    }

    evolutionEuler(p, &x, &v);
    if(!APPROX_EQUAL(x, 6.4) || !APPROX_EQUAL(v, 0.64)) {
        printf("\n\tERROR: Wrong position, expected (x,v) = (6.4, 0.64), obtained (x,v) = (%.3lf, %.3lf)\n", x, v);
        return false;
    }

    /* Change h */
    p.h = 0.1;
    evolutionEuler(p, &x, &v);
    if(!APPROX_EQUAL(x, 6.464) || !APPROX_EQUAL(v, 0.128)) {
        printf("\n\tERROR: Wrong position, expected (x,v) = (6.464, 0.128), obtained (x,v) = (%.4lf, %.4lf)\n", x, v);
        return false;
    }

    /* Change l0, s0 */
    p.natural_length = 3.464;
    p.anchor_position = 3;
    evolutionEuler(p, &x, &v);
    if(!APPROX_EQUAL(x, 6.4768) || !APPROX_EQUAL(v, 0.128)) {
        printf("\n\tERROR: Wrong position, expected (x,v) = (6.4768, 0.128), obtained (x,v) = (%.4lf, %.4lf)\n", x, v);
        return false;
    }

    return true;
}

bool test_evolutionVerlet() {
    Parameters p;
    double x, v;

    printf("Testing evolutionVerlet...");
   
    p.mass = 1.5;
    p.k = 1.2;
    p.natural_length = 0;
    p.anchor_position = 0;
    p.h = 1;

    x = 0;
    v = 3.2;

    evolutionVerlet(p, &x, &v);
    if(!APPROX_EQUAL(x, 3.2) || !APPROX_EQUAL(v, 1.92)) {
        printf("\n\tERROR: Wrong position, expected (x,v) = (3.2, 1.92), obtained (x,v) = (%.2lf, %.3lf)\n", x, v);
        return false;
    }

    evolutionVerlet(p, &x, &v);
    if(!APPROX_EQUAL(x, 3.840) || !APPROX_EQUAL(v, -0.8960)) {
        printf("\n\tERROR: Wrong position, expected (x,v) = (3.840, -0.8960), obtained (x,v) = (%.4lf, %.4lf)\n", x, v);
        return false;
    }

    /* Change h */
    p.h = 0.1;
    evolutionVerlet(p, &x, &v);
    if(!APPROX_EQUAL(x, 3.735) || !APPROX_EQUAL(v, -1.199)) {
        printf("\n\tERROR: Wrong position, expected (x,v) = (3.735, -1.199), obtained (x,v) = (%.4lf, %.4lf)\n", x, v);
        return false;
    }

    /* Change l0, s0 */
    p.natural_length = 3.464;
    p.anchor_position = 3;
    evolutionVerlet(p, &x, &v);
    if(!APPROX_EQUAL(x, 3.6261) || !APPROX_EQUAL(v, -0.9763)) {
        printf("\n\tERROR: Wrong position, expected (x,v) = (3.6261, -0.9763), obtained (x,v) = (%.4lf, %.4lf)\n", x, v);
        return false;
    }

    return true;
}

bool test_potentialEnergy() {
    Parameters p;
    double energy;

    printf("Testing potentialEnergy...");

    p.k = 10;
    p.natural_length = p.anchor_position = 0;
    energy = potentialEnergy(p, 0);
    if(!APPROX_EQUAL(energy, 0.0)) {
        printf("\n\tERROR: Wrong energy, expected 0, obtained %.1lf\n", energy);
        return false;
    }

    p.k = 10;
    energy = potentialEnergy(p, 1);
    if(!APPROX_EQUAL(energy, 5)) {
        printf("\n\tERROR: Wrong energy, expected 5, obtained %.1lf\n", energy);
        return false;
    }

    p.k = 20;
    p.natural_length = 1;
    energy = potentialEnergy(p, 3);
    if(!APPROX_EQUAL(energy, 40.0)) {
        printf("\n\tERROR: Wrong energy, expected 40, obtained %.1lf\n", energy);
        return false;
    }

    p.k = 6;
    p.natural_length = 0;
    p.anchor_position = 1;
    energy = potentialEnergy(p, -3);
    if(!APPROX_EQUAL(energy, 48.0)) {
        printf("\n\tERROR: Wrong energy, expected 48, obtained %.1lf\n", energy);
        return false;
    }

    return true;

}

bool test_kineticEnergy() {
    Parameters p;
    double energy;

    printf("Testing kineticEnergy...");

    p.mass = 10;
    energy = kineticEnergy(p, 0);
    if(!APPROX_EQUAL(energy, 0.0)) {
        printf("\n\tERROR: Wrong energy, expected 0, obtained %.1lf\n", energy);
        return false;
    }

    p.mass = 0;
    energy = kineticEnergy(p, 10);
    if(!APPROX_EQUAL(energy, 0)) {
        printf("\n\tERROR: Wrong energy, expected 0, obtained %.1lf\n", energy);
        return false;
    }

    p.mass = 3;
    energy = kineticEnergy(p, 2);
    if(!APPROX_EQUAL(energy, 6)) {
        printf("\n\tERROR: Wrong energy, expected 6, obtained %.1lf\n", energy);
        return false;
    }

    p.mass = 4.5;
    energy = kineticEnergy(p, 2.5);
    if(!APPROX_EQUAL(energy, 14.0625)) {
        printf("\n\tERROR: Wrong energy, expected 14.0625, obtained %.4lf\n", energy);
        return false;
    }

    return true;

}

bool test_mechanicalEnergy() {
    Parameters p;
    double energy;

    printf("Testing mechanicalEnergy...");

    p.mass = 10;
    p.k = 0;
    p.natural_length = 0;
    p.anchor_position = 0;
    energy = mechanicalEnergy(p, 0, 1);
    if(!APPROX_EQUAL(energy, 5)) {
        printf("\n\tERROR: Wrong energy, expected 5, obtained %.1lf\n", energy);
        return false;
    }

    p.k = 3;
    energy = mechanicalEnergy(p, 2, 1);
    if(!APPROX_EQUAL(energy, 11)) {
        printf("\n\tERROR: Wrong energy, expected 11, obtained %.1lf\n", energy);
        return false;
    }

    p.natural_length = 1;
    energy = mechanicalEnergy(p, 2, 1);
    if(!APPROX_EQUAL(energy, 6.5)) {
        printf("\n\tERROR: Wrong energy, expected 6.5, obtained %.1lf\n", energy);
        return false;
    }

    return true;

}

bool test_resetFile() {
    FILE *f;
    int n_lines;
    char header[] = "#t Ec Ep Em x v\n";
    char line[256];

/* Using the preprocessor this way is not the best... */
#if defined(EULER)
    char filename[] = "results/evolution_EULER.txt";
#elif defined(VERLET)
    char filename[] = "results/evolution_VERLET.txt";
#endif

    printf("Testing resetFile...");

    resetFile();

    f = fopen(filename, "rt");
    if(f == NULL) {
        printf("\n\tERROR: the file %s does not exist\n", filename);
        return false;
    }
    fclose(f);

    f = fopen(filename, "rt");
    n_lines = countLines(f);
    if(n_lines != 1) {
        printf("\n\tERROR: the file should only contain the header but there are %d lines\n", n_lines);
        return false;
    }
    fclose(f);

    f = fopen(filename, "rt");
    fgets(line, sizeof(line), f);
    if(strcmp(line, header) != 0) {
        printf("\n\tERROR: the header should be %s but is %s\n", header, line);
        return false;
    }

    return true;
}

bool test_writeEvolution() {
    FILE *f;
    int n_lines;
    Parameters p;

/* Using the preprocessor this way is not the best... */
#if defined(EULER)
    char filename[] = "results/evolution_EULER.txt";
#elif defined(VERLET)
    char filename[] = "results/evolution_VERLET.txt";
#endif

    printf("Testing writeEvolution...");

    p.mass = p.k = p.natural_length = p.anchor_position = p.h = 0;

    resetFile();
    for(int i = 0; i < 10; i++) {
        writeEvolution(p, 0, 0, 0);
    }

    f = fopen(filename, "rt");
    if(f == NULL) {
        printf("\n\tERROR: the file %s does not exist\n", filename);
        return false;
    }
    fclose(f);

    f = fopen(filename, "rt");
    n_lines = countLines(f);
    if(n_lines != 11) {
        printf("\n\tERROR: the file should contain 11 lines but there are %d lines\n", n_lines);
        return false;
    }
    fclose(f);

    return true;
}

bool test_loadParameters() {
    Parameters p;
    int success, spring_id;

    printf("Testing loadParameters...");

    p.mass = p.k = p.natural_length = p.anchor_position = p.h = 0;
    p.t_max = p.x0 = p.v0 = 0;

    spring_id = 0;
    success = loadParameters(spring_id, &p);
    if(success != -1) {
        printf("\n\tERROR: the spring %d does not exist. Expected -1\n", spring_id);
        return false;
    }

    spring_id = 1;
    success = loadParameters(spring_id, &p);
    if (success != 0) {
        printf("\n\tERROR: the spring %d exists. Expected 0\n", spring_id);
        return false;
    }

    if(!APPROX_EQUAL(p.mass, 10)) {
        printf("\n\tERROR: Wrong mass in spring %d, expected 10.0, obtained %.1lf\n", spring_id, p.mass);
        return false;
    }

    if(!APPROX_EQUAL(p.k, 20)) {
        printf("\n\tERROR: Wrong k in spring %d, expected 20.0, obtained %.1lf\n", spring_id, p.k);
        return false;
    }

    if(!APPROX_EQUAL(p.natural_length, 160)) {
        printf("\n\tERROR: Wrong natural_length in spring %d, expected 160.0, obtained %.1lf\n", spring_id, p.natural_length);
        return false;
    }   

    if(!APPROX_EQUAL(p.anchor_position, 640)) {
        printf("\n\tERROR: Wrong anchor_position in spring %d, expected 640.0, obtained %.1lf\n", spring_id, p.anchor_position);
        return false;
    }   

    if(!APPROX_EQUAL(p.h, 0.0001)) {
        printf("\n\tERROR: Wrong h in spring %d, expected 0.0, obtained %.1lf\n", spring_id, p.h);
        return false;
    }   

    if(!APPROX_EQUAL(p.t_max, 50)) {
        printf("\n\tERROR: Wrong t_max in spring %d, expected 50.0, obtained %.1lf\n", spring_id, p.t_max);
        return false;
    }   

    if(!APPROX_EQUAL(p.x0, 840)) {
        printf("\n\tERROR: Wrong x0 in spring %d, expected 840.0, obtained %.1lf\n", spring_id, p.x0);
        return false;
    }   

    if(!APPROX_EQUAL(p.v0, 0)) {
        printf("\n\tERROR: Wrong v0 in spring %d, expected 0.0, obtained %.1lf\n", spring_id, p.v0);
        return false;
    }   

    p.mass = p.k = p.natural_length = p.anchor_position = p.h = 0;
    p.t_max = p.x0 = p.v0 = 0;

    spring_id = 2;
    success = loadParameters(spring_id, &p);
    if (success != 0) {
        printf("\n\tERROR: the spring %d exists. Expected 0\n", spring_id);
        return false;
    }

    if(!APPROX_EQUAL(p.mass, 10)) {
        printf("\n\tERROR: Wrong mass in spring %d, expected 10.0, obtained %.1lf\n", spring_id, p.mass);
        return false;
    }

    if(!APPROX_EQUAL(p.k, 10)) {
        printf("\n\tERROR: Wrong k in spring %d, expected 10.0, obtained %.1lf\n", spring_id, p.k);
        return false;
    }

    if(!APPROX_EQUAL(p.natural_length, 160)) {
        printf("\n\tERROR: Wrong natural_length in spring %d, expected 160.0, obtained %.1lf\n", spring_id, p.natural_length);
        return false;
    }   

    if(!APPROX_EQUAL(p.anchor_position, 640)) {
        printf("\n\tERROR: Wrong anchor_position in spring %d, expected 640.0, obtained %.1lf\n", spring_id, p.anchor_position);
        return false;
    }   

    if(!APPROX_EQUAL(p.h, 0.0001)) {
        printf("\n\tERROR: Wrong h in spring %d, expected 0.0, obtained %.1lf\n", spring_id, p.h);
        return false;
    }   

    if(!APPROX_EQUAL(p.t_max, 50)) {
        printf("\n\tERROR: Wrong t_max in spring %d, expected 50.0, obtained %.1lf\n", spring_id, p.t_max);
        return false;
    }   

    if(!APPROX_EQUAL(p.x0, 800)) {
        printf("\n\tERROR: Wrong x0 in spring %d, expected 800.0, obtained %.1lf\n", spring_id, p.x0);
        return false;
    }   

    if(!APPROX_EQUAL(p.v0, 0)) {
        printf("\n\tERROR: Wrong v0 in spring %d, expected 0.0, obtained %.1lf\n", spring_id, p.v0);
        return false;
    }   

    return true;
}

int main() {
    int passed = 0, n_test = 0;
    bool status = true;

    printf("************************************\n* TESTING HARMONIC OSCILLATOR CODE *\n************************************\n\n");
    RUN_TEST(test_forceSpring);
    RUN_TEST(test_evolutionEuler);
    RUN_TEST(test_evolutionVerlet);
    RUN_TEST(test_potentialEnergy);
    RUN_TEST(test_kineticEnergy);
    RUN_TEST(test_mechanicalEnergy);
    RUN_TEST(test_resetFile);
    RUN_TEST(test_writeEvolution);
    RUN_TEST(test_loadParameters);

    printf("\nTests succesfully completed: %d/%d\n", passed, n_test);

    return n_test - passed;
}
