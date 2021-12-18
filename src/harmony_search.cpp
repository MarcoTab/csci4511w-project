#include <stdlib.h>
#include <iostream>
#include <time.h>
#include "harmony_search.h"

HarmonySearch::HarmonySearch(std::string str) {
    harmonyMemory = new int**[harmonyMemorySize];

    for (int i = 0; i < harmonyMemorySize; i++) {
        harmonyMemory[i] = new int*[9];

        for (int j = 0; j < 9; j++) {
            harmonyMemory[i][j] = new int[9];
        }
    }

    int row = 0;
	int col = 0;

	for (char const &c : str) {

		int num = -1;
		if (c >= '1' && c <= '9') {
			num = c - '1' + 1;
		}
		else if (c == '0') {
			num = 0;
		}
		else {
			std::cerr << "unexpected character '" << c << "'" << std::endl;
			return;
		}

		field[row][col] = num;

		col++;
		if (col > 8) {
			col = 0;
			row++;
		}
		if (row > 8) {
			return;
		}
	}

}

HarmonySearch::~HarmonySearch() {
    for (int i = 0; i < harmonyMemorySize; i++) {
        for (int j = 0; j < 9; j++) {
            delete[] harmonyMemory[i][j];
        }
        delete[] harmonyMemory[i];
    }
    delete[] harmonyMemory;
}


void HarmonySearch::initializeRandomly() {

    srand(time(NULL));
    
    for (int i = 0; i < harmonyMemorySize; i++) {
        int** harmony = harmonyMemory[i];
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

void HarmonySearch::copySolution(int** destination, int** source) {
    
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

void HarmonySearch::printSolution() {
    int** harmony = getBestSolution();
    
    for(int a=0; a<9; a++) {
        
        for(int b=0; b<9; b++) {
            
            printf("%d ", harmony[a][b]);
            
        }
        
        printf("\n");
        
    }
}

int** HarmonySearch::getBestSolution() {
    int bestObjectiveValue = 10000;
    int bestIndex = 0;

    for(int a=0; a<harmonyMemorySize; a++) {

        int tempObjectiveValue = getObjectiveValue(harmonyMemory[a]);

        if(tempObjectiveValue < bestObjectiveValue) {

            bestObjectiveValue = tempObjectiveValue;
            bestIndex = a;

        }

    }

    return harmonyMemory[bestIndex];
}

void HarmonySearch::solve() {

    int bestObjectiveValue = 10000;
    int* objectiveValue = new int[harmonyMemorySize];

    for(int a=0; a<harmonyMemorySize; a++) {

        initializeRandomly();
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
                    
                    if(isValid(newHarmony)) {

                    }
                    
                }

            }

        }

    }

    // cleanup

    delete[] objectiveValue;

    for(int a=0; a<9; a++) delete[] newHarmony[a];
    delete[] newHarmony;
    
    // return value return true/false?

    
    return;
    
}

