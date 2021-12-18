#ifndef HARMONY_SEARCH_H
#define HARMONY_SEARCH_H

#include <string>

class HarmonySearch {
    private:
        int harmonyMemorySize = 10;
        double harmonyMemoryConsiderationRate = 0.5;
        double pitchAdjustmentRate = 0.1;
        int maximumImprovisations = 1000000;
        int*** harmonyMemory;
        int** field;

    public:
        HarmonySearch(std::string str);
        void initializeRandomly();
        int getObjectiveValue(int** harmony);
        int isValid(int** harmony);
        void solve();
};

#endif