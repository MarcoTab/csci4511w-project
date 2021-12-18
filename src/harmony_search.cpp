#include <stdlib.h>
#include <stdio.h>
#include "harmony_search.h"

HarmonySearch::HarmonySearch(std::string str) {
    
}

void HarmonySearch::initializeRandomly(int** harmony, int** field) {
    
    for(int a=0; a<9; a++) {
        
        for(int b=0; b<9; b++) {
            
            if(field[a][b] == 0) {
            
                harmony[a][b] = rand() % 9 + 1;
                
            } else {
                
                harmony[a][b] = field[a][b];
                
            }
            
        }
        
    }
    
}

int HarmonySearch::getObjectiveValue(int** harmony) {
    
    int objectiveValue = 0;
    
    for(int a=0; a<9; a++) {
        
        int sum = 0;
        
        for(int b=0; b<9; b++) sum += harmony[a][b];
        
        objectiveValue += abs(sum - 45);
        
    }
    
    for(int a=0; a<9; a++) {
        
        int sum = 0;
        
        for(int b=0; b<9; b++) sum += harmony[b][a];
        
        objectiveValue += abs(sum - 45);
        
    }
    
    for(int a=0; a<3; a++) {
        
        for(int b=0; b<3; b++) {
            
            int sum = 0;
            
            for(int c=0; c<3; c++) {
                
                for(int d=0; d<3; d++) sum += harmony[a*3 + c][b*3 + d];
                
            }
            
            objectiveValue += abs(sum - 45);
            
        }
        
    }
    
    return objectiveValue;
    
}

void copySolution(int** destination, int** source) {
    
    for(int a=0; a<9; a++) {
        
        for(int b=0; b<9; b++) {
            
            destination[a][b] = source[a][b];
            
        }
        
    }
    
}

int HarmonySearch::isValid(int** harmony) {
    
    int* remaining = new int[9];
    
    for(int a=0; a<9; a++) {
        
        for(int z=0; z<9; z++) remaining[z] = 1;
        
        for(int b=0; b<9; b++) {
            
            remaining[harmony[a][b]]--;
            
            if(remaining[harmony[a][b]] < 0) return 0;
            
        }
        
    }
    
    for(int a=0; a<9; a++) {
        
        for(int z=0; z<9; z++) remaining[z] = 1;
        
        for(int b=0; b<9; b++) {
            
            remaining[harmony[b][a]]--;
            
            if(remaining[harmony[b][a]] < 0) return 0;
            
        }
        
    }
    
    for(int a=0; a<3; a++) {
        
        for(int b=0; b<3; b++) {
            
            for(int z=0; z<9; z++) remaining[z] = 1;
            
            for(int c=0; c<3; c++) {
                
                for(int d=0; d<3; d++) {
                    
                    remaining[harmony[a*3 + c][b*3 + d]]--;
                    
                    if(remaining[harmony[a*3 + c][b*3 + d]] < 0) return 0;
                    
                }
                
            }
            
        }
        
    }
    
    return 1;
    
}

void printSolution(int** harmony) {
    
    for(int a=0; a<9; a++) {
        
        for(int b=0; b<9; b++) {
            
            printf("%d ", harmony[a][b]);
            
        }
        
        printf("\n");
        
    }
    
}

void HarmonySearch::solve() {

    // parameters
    
    // long randomSeed = atol(argv[1]);

    // int harmonyMemorySize = atoi(argv[2]);

    // double harmonyMemoryConsiderationRate = atof(argv[3]);
    
    // double pitchAdjustmentRate = atof(argv[4]);
    
    // int maximumImprovisations = 1000000;
    
    // int runs = atoi(argv[5]);
    
    // printf("********* parameters ********\n");
    
    // printf("random seed: %ld\n", randomSeed);
    
    // printf("harmony memory size: %d\n", harmonyMemorySize);
    
    // printf("harmony memory conisderation rate: %.2lf\n", harmonyMemoryConsiderationRate);
    
    // printf("pitch adjustment rate: %.2lf\n", pitchAdjustmentRate);
    
    // printf("maximum improvisations: %d\n", maximumImprovisations);
    
    // printf("runs: %d\n\n", runs);
    
    srand(randomSeed);
    
    // int averageIterations = 0;
    
    // int terminatedWithin10k = 0;
    // int terminatedWithin100k = 0;
    // int terminatedWithin1000k = 0;

    // int feasibleWithin10k = 0;
    // int feasibleWithin100k = 0;
    // int feasibleWithin1000k = 0;

    // double time10k = 0.0;
    // double time100k = 0.0;
    // double time1000k = 0.0;
    
    for(int u=0; u<runs; u++) {
    
        // initialization
        
        // Timer* timer = new Timer();
        
        // timer->startTimer();

        int** field = new int*[9];    

        for(int a=0; a<9; a++) {

            field[a] = new int[9];

            for(int b=0; b<9; b++) field[a][b] = 0;

        }

        field[0][1] = 5;
        field[0][3] = 3;
        field[0][5] = 6;
        field[0][8] = 7;
        field[1][4] = 8;
        field[1][5] = 5;
        field[1][7] = 2;
        field[1][8] = 4;    
        field[2][1] = 9;
        field[2][2] = 8;
        field[2][3] = 4;
        field[2][4] = 2;
        field[2][6] = 6;
        field[2][8] = 3;
        field[3][0] = 9;
        field[3][2] = 1;
        field[3][5] = 3;
        field[3][6] = 2;
        field[3][8] = 6;
        field[4][1] = 3;
        field[4][7] = 1;
        field[5][0] = 5;
        field[5][2] = 7;
        field[5][3] = 2;
        field[5][4] = 6;
        field[5][6] = 9;
        field[5][8] = 8;
        field[6][0] = 4;
        field[6][2] = 5;
        field[6][4] = 9;
        field[6][6] = 3;
        field[6][7] = 8;
        field[7][1] = 1;
        field[7][3] = 5;
        field[7][4] = 7;
        field[7][8] = 2;
        field[8][0] = 8;
        field[8][3] = 1;
        field[8][5] = 4;
        field[8][7] = 7;

        int*** harmonyMemory = new int**[harmonyMemorySize];
        for(int a=0; a<harmonyMemorySize; a++) {
            harmonyMemory[a] = new int*[9];
            for(int b=0; b<9; b++) harmonyMemory[a][b] = new int[9];
        }

        int bestObjectiveValue = 10000;
        int* objectiveValue = new int[harmonyMemorySize];

        for(int a=0; a<harmonyMemorySize; a++) {

            initializeRandomly(harmonyMemory[a], field);
            objectiveValue[a] = getObjectiveValue(harmonyMemory[a]);

            if(objectiveValue[a] < bestObjectiveValue) {

                bestObjectiveValue = objectiveValue[a];

            }

        }

        int** newHarmony = new int*[9];    
        for(int a=0; a<9; a++) newHarmony[a] = new int[9];

        // algorithm

        for(int a=0; a<maximumImprovisations; a++) {
            
            for(int b=0; b<9; b++) {

                for(int c=0; c<9; c++) {

                    if(field[b][c] == 0) {

                        if((double)rand() / (double)RAND_MAX < harmonyMemoryConsiderationRate) {

                            newHarmony[b][c] = harmonyMemory[rand() % harmonyMemorySize][b][c];

                            if((double)rand() / (double)RAND_MAX < pitchAdjustmentRate) {

                                if(rand() % 2 == 0) {

                                    if(newHarmony[b][c] != 9) newHarmony[b][c]++;

                                } else {

                                    if(newHarmony[b][c] != 1) newHarmony[b][c]--;

                                }

                            }

                        } else {

                            newHarmony[b][c] = rand() % 9 + 1;

                        }

                    } else {

                        newHarmony[b][c] = field[b][c];

                    }

                }

            }

            int newObjectiveValue = getObjectiveValue(newHarmony);

            int worstObjectiveValue = objectiveValue[0];
            int worstIndex = 0;

            for(int b=1; b<harmonyMemorySize; b++) {

                if(objectiveValue[b] > worstObjectiveValue) {

                    worstObjectiveValue = objectiveValue[b];
                    worstIndex = b;

                }

            }

            if(worstObjectiveValue > newObjectiveValue) {

                copySolution(harmonyMemory[worstIndex], newHarmony);

                objectiveValue[worstIndex] = newObjectiveValue;

                if(newObjectiveValue < bestObjectiveValue) {

                    bestObjectiveValue = newObjectiveValue;

                    if(newObjectiveValue == 0) {

                        if(a < 10000) terminatedWithin10k++;
                        if(a < 100000) terminatedWithin100k++;
                        if(a < 1000000) terminatedWithin1000k++;
                        
                        averageIterations += a + 1;
                        
                        if(isValid(newHarmony)) {

                            if(a < 10000) feasibleWithin10k++;
                            if(a < 100000) feasibleWithin100k++;
                            if(a < 1000000) feasibleWithin1000k++;

                        }
                        
                    }

                }

            }
            
            if(a == 9999) time10k += timer->getElapsedTime();
            if(a == 99999) time100k += timer->getElapsedTime();
            if(a == 999999) time1000k += timer->getElapsedTime();

        }

        // cleanup

        for(int a=0; a<9; a++) delete[] field[a];   
        delete[] field;

        for(int a=0; a<harmonyMemorySize; a++) {

            for(int b=0; b<9; b++) delete[] harmonyMemory[a][b];        
            delete[] harmonyMemory[a];

        }

        delete[] harmonyMemory;

        delete[] objectiveValue;

        for(int a=0; a<9; a++) delete[] newHarmony[a];
        delete[] newHarmony;

        delete timer;
        
    }
    
    // summary
    
    printf("********** results **********\n\n");
    
    printf("terminated within 10000 iterations: %d / %d\n", terminatedWithin10k, runs);
    printf("feasible within 10000 iterations: %d / %d\n", feasibleWithin10k, runs);
    printf("average time for 10000 iterations: %.2lf\n\n", time10k / runs);
    
    printf("terminated within 100000 iterations: %d / %d\n", terminatedWithin100k, runs);
    printf("feasible within 100000 iterations: %d / %d\n", feasibleWithin100k, runs);
    printf("average time for 100000 iterations: %.2lf\n\n", time100k / runs);
    
    printf("terminated within 1000000 iterations: %d / %d\n", terminatedWithin1000k, runs);
    printf("feasible within 1000000 iterations: %d / %d\n", feasibleWithin1000k, runs);
    printf("average time for 1000000 iterations: %.2lf\n\n", time1000k / runs);
    
    if(terminatedWithin1000k == 0) printf("average iterations until termination: ---\n");
    else printf("average iterations until termination: %d\n", averageIterations / terminatedWithin1000k);
    
    printf("\n\n\n");
    
    return 0;
    
}

