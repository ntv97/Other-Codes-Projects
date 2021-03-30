#include<iostream>
#include <fstream>
#include "model.h"

using namespace std;

int main(int argc, char* argv[]) {
        if(argc<=1) {
          exit(0);
        }
        //get files
        std::fstream file1(argv[1]);
        std::fstream file2(argv[2]);

        //initialize models w/ appropiate model's information
        Model model1(file1);
        Model model2(file2);

        //get total energy of both models
        double TotEnergy1 = model1.calculateU();
        double TotEnergy2 = model2.calculateU();

        //print out separate energies
        std::cout << "Model 1's vdw Energy: " << model1.vdwEnergy << "." << endl;
        std::cout << "Model 1's electrostatic Energy: " << model1.electrostaticEnergy << "." << endl;
        std::cout << "Model 1's solvation Energy: " << model1.solvationEnergy << "." << endl;

        std::cout << "Model 2's vdw Energy: " << model2.vdwEnergy << "." << endl;
        std::cout << "Model 2's electrostatic Energy: " << model2.electrostaticEnergy << "." << endl;
        std::cout << "Model 2's solvation Energy: " << model2.solvationEnergy << "." << endl;

        //print out model's energies
        std::cout << "Total energy of Model 1: " << TotEnergy1 << std::endl;
        std::cout << "Total energy of Model 2: " << TotEnergy2 << std::endl;

        //find out which has the global minimum energy
        if (TotEnergy1 < TotEnergy2) {
          std::cout << "Model 1 has the lowest energy, therefore this model is better than the other." << endl;
        }
        else if (TotEnergy1 > TotEnergy2) {
          std::cout << "Model 2 has the lowest energy, therefore this model is better than the other." << endl;
        }
        else {
          std::cout << "Both models have the same energy. It is hard to determine which model is better." << endl;
        }

        return 0;
}
