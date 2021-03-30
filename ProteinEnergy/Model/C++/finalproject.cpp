#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <math.h>
#include "model.h"

using namespace std;

Model::Model(std::fstream& file) {
	string line, ResNametemp, AtmNametemp;
	double Xtemp, Ytemp, Ztemp, Rtemp, Epstemp, Sigmatemp, Chargetemp, ASPtemp;
	int num, ResNumtemp;
	//read in line
	getline(file, line);
	//put # of atoms for each model
	nAtoms = std::stoi(line);
	//skip the next lines
	getline(file, line);
	for(int i=0; i<nAtoms; i++) {
		//get each line and put appropiate variable in model 1
		getline(file, line);
		std::istringstream iss(line);
		//put information into appropiate temporary variables, then store in model class
		iss >> num >> Xtemp >> Ytemp >> Ztemp >> Rtemp >> Epstemp >> Sigmatemp >> Chargetemp >> ASPtemp >> AtmNametemp >> ResNametemp >> ResNumtemp;
		AtomNum.push_back(num);
		X.push_back(Xtemp);
		Y.push_back(Ytemp);
		Z.push_back(Ztemp);
		R.push_back(Rtemp);
		Epsilon.push_back(Epstemp);
		Sigma.push_back(Sigmatemp);
		Charge.push_back(Chargetemp);
		ASP.push_back(ASPtemp);
		AtmName.push_back(AtmNametemp);
		ResName.push_back(ResNametemp);
		ResNum.push_back(ResNumtemp);
		//calculate accessible surface area
		double ASAtemp = .2*4*M_PI*(pow(R[i] + 1.4,2));
		ASA.push_back(ASAtemp);
	}
	//skip the next lines
	getline(file, line);
	getline(file, line);
	//now the flag info lines
	for(int i=0; i<nAtoms; i++) {
		getline(file, line);
		istringstream iss(line);
		int Nextemp, removei, jNextemp;
		std::vector<int> jNex;
		//remove unnecessary info, and put rest into variables
		iss >> removei >> Nextemp;
		//if no flag(i,j) = 0
		if(Nextemp != 0) {
			for(int j=0; j<Nextemp; j++) {
				iss >> jNextemp;
				//store info in temporary vector
				jNex.push_back(jNextemp);
			}
		} else {
			jNex.push_back(0);
		}
		//store info in model's vectors
		Nex.push_back(Nextemp);
		NexList.push_back(jNex);

	}
}
//function that calculates the total energy
double Model::calculateU() {
	double TotEnergy = 0.0; //total energy
	double vdwE = 0.0;
	double electrostaticE = 0.0;
	double solvationE = 0.0;
	//go through i atoms
	for(int i=0; i<nAtoms; i++) {
		//(ASP(i)*ASA(i))
		TotEnergy += (ASP[i] * ASA[i]);
		solvationE += (ASP[i] * ASA[i]);
		//go through j atoms
		for(int j=i+1; j<nAtoms; j++) {
			bool skip = false;
			double e, s, q, r;
			//check which ones are flag(i,j) = 0
			for(int k=0; k<Nex[i]; k++) {
				if(j==NexList[i][k] - 1) {
				       skip = true;
				}
			}
			//skip the ones that are flag(i,j) = 0
			if(skip) {
				continue;
			} else {
				double s1, s2;
				//(sqrt(ei*ej))
				e = sqrt(Epsilon[i]*Epsilon[j]);
				//(sij/rij)^12 - 2*(sij/rij)^6
				r = sqrt(abs(pow(X[j] - X[i],2) + pow(Y[j] - Y[i],2) + pow(Z[j] - Z[i],2)));
				//makes sure we don't divide by 0
				if (r>0) {
					s1 = pow((((Sigma[i]+Sigma[j])/2)/r), 12);
					s2 = 2*pow((((Sigma[i]+Sigma[j])/2)/r), 6);
					s = s1-s2;
					vdwE += s;
					//(1/(4pie0er)) * ((qi*qj)/rij)
					q = (332/4) * ((Charge[i]*Charge[j])/r);
					electrostaticE += q;
					TotEnergy += (e*s) + q;
				}
			}
		}
		vdwEnergy = vdwE;
		electrostaticEnergy = electrostaticE;
		solvationEnergy = solvationE;
	}

	return TotEnergy;
}
