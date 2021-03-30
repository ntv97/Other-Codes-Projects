#include <iostream>
#include <vector>

#ifndef MODEL_H
#define MODEL_H

//model class
class Model {
public:
        Model(std::fstream& file); //func. to put information into model class
        double calculateU(); //calculates total energy of the model
        double vdwEnergy; //total vdw energy
        double electrostaticEnergy; //total electrostatic energy
        double solvationEnergy; //total solvation energy

private:
        int nAtoms; //# of atoms
        std::vector<int> AtomNum; //atom # in list
        std::vector<double> X;//coordinates of x, y, z
        std::vector<double> Y;
        std::vector<double> Z;
        std::vector<double> R; //radius of the atom
        std::vector<double> Epsilon; //epsilon
        std::vector<double> Sigma; //sigma
        std::vector<double> Charge; //charge of atom
        std::vector<double> ASP; //atomic solvation parameter of the atom
        std::vector<std::string> AtmName; //atom name
        std::vector<std::string> ResName; //residue name
        std::vector<int> ResNum; //residue #
        std::vector<int> Nex; //# of atoms that makes flag(i,j) = 0 for the i atom
        std::vector<std::vector<int> > NexList; //for j values of flag(i,j) = 0
        std::vector<double> ASA; //accessible surface area
};
#endif
