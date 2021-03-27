package Model;

import java.io.File;
import java.util.Scanner;
import java.util.Vector;

public class Main {
    public static class Model {
        public double vdwEnergy;
        public double electrostaticEnergy;
        public double solvationEnergy;
        private int nAtoms;
        private int[] AtomNum;
        private double[] X;
        private double[] Y;
        private double[] Z;
        private double[] R;
        private double[] Epsilon;
        private double[] Sigma;
        private double[] Charge;
        private double[] ASP;
        private String[] AtmName;
        private String[] ResName;
        private int[] ResNum;
        private int[] Nex;
        private int[][] NexList;
        private double[] ASA;


        public Model(String file) {
            try {
                File model = new File(file);
                String line, ResNameTemp, AtmNameTemp;
                double Xtemp, Ytemp, Ztemp, Rtemp, Epstemp, Sigmatemp, Chargetemp, ASPtemp;
                int num, ResNumtemp;

                Scanner nextline = new Scanner(model);
                line = nextline.nextLine();
                String nospace = line.replaceAll("\\s+", "");
                nAtoms = Integer.parseInt(nospace);
                line = nextline.nextLine();

               for (int i=0; i<nAtoms; i++) {
                    line = nextline.nextLine();
                    // num-int >> Xtemp-d >> Ytemp-d >> Ztemp-d >> Rtemp-d >> Epstemp-d >> Sigmatemp-d >> Chargetemp-d >> ASPtemp-d >> AtmNametemp-str >> ResNametemp-str >> ResNumtemp-int;
                    String[] arr = line.trim().split(" +");
                    //num = nospace.nextInt();
                    num = Integer.parseInt(arr[0]); Xtemp = Double.parseDouble(arr[1]); Ytemp = Double.parseDouble(arr[2]); Ztemp = Double.parseDouble(arr[3]); Rtemp = Double.parseDouble(arr[4]); Epstemp = Double.parseDouble(arr[5]); Sigmatemp = Double.parseDouble(arr[6]);
                    Chargetemp = Double.parseDouble(arr[7]); ASPtemp = Double.parseDouble(arr[8]); AtmNameTemp = arr[9]; ResNameTemp = arr[10]; ResNumtemp = Integer.parseInt(arr[11]);
                    AtomNum = new int[nAtoms]; X = new double[nAtoms]; Y = new double[nAtoms]; Z = new double[nAtoms];
                    R = new double[nAtoms]; Epsilon = new double[nAtoms]; Sigma = new double[nAtoms]; Charge = new double[nAtoms];
                    ASP = new double[nAtoms]; AtmName = new String[nAtoms]; ResName = new String[nAtoms]; ResNum = new int[nAtoms];
                    AtomNum[i] = num;
                    X[i] = Xtemp;
                    Y[i] = Ytemp;
                    Z[i] = Ztemp;
                    R[i] = Rtemp;
                    Epsilon[i] = Epstemp;
                    Sigma[i] = Sigmatemp;
                    Charge[i] = Chargetemp;
                    ASP[i] = ASPtemp;
                    AtmName[i] = AtmNameTemp;
                    ResName[i] = ResNameTemp;
                    ResNum[i] = ResNumtemp;

                   ASA = new double[nAtoms];
                    double ASAtemp = .2*4*Math.PI*(Math.pow(Rtemp + 1.4,2));
                   ASA[i] = ASAtemp;
                }

                line = nextline.nextLine();
                line = nextline.nextLine();

                for (int i=0; i<nAtoms; i++) {
                    int Nextemp, jNextemp;
                    int[] jNex = new int[nAtoms];
                    line = nextline.nextLine();
                    String[] arr = line.trim().split(" +");
                    Nextemp = Integer.parseInt(arr[1]);
                    if (Nextemp != 0) {
                        for(int j=0; j<Nextemp; j++) {
                            jNex[i] = Integer.parseInt(arr[2]);
                        }
                    }  else {
                        jNex[i] = 0;
                    }
                    Nex = new int[nAtoms];
                    Nex[i] = Nextemp;
                    NexList = new int[nAtoms][nAtoms];
                    NexList[i] = jNex;
                }

            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    public double calculateU() {
            double TotEnergy = 0.0, vdwE = 0.0, electrostaticE = 0.0, solvationE = 0.0;
            for (int i=0; i<nAtoms; i++) {
                TotEnergy += (ASP[i] * ASA[i]);
                solvationE += (ASP[i] * ASA[i]);
                for (int j=i+1; j<nAtoms; j++) {
                    boolean skip = false;
                    double e, s, q, r;
                    for (int k=0; k<Nex[i]; k++) {
                        if (j == NexList[i][k] - 1)
                            skip = true;
                    }

                    if (skip) {
                        continue;
                    } else {
                        double s1, s2;
                        e = Math.sqrt(Epsilon[i]*Epsilon[j]);
                        r = Math.sqrt(Math.abs(Math.pow(X[j] - X[i],2) + Math.pow(Y[j] - Y[i],2) + Math.pow(Z[j] - Z[i],2)));
                        if (r>0) {
                            s1 = Math.pow((((Sigma[i]+Sigma[j])/2)/r), 12);
                            s2 = 2*Math.pow((((Sigma[i]+Sigma[j])/2)/r), 6);
                            s = s1-s2;
                            vdwE += s;
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

    }


    public static void main(String[] args) {
        Model model1 = new Model(args[0]);
        Model model2 = new Model(args[1]);
        if (args.length < 2)
            System.exit(1);

        double TotEnergy1 = model1.calculateU();
        double TotEnergy2 = model2.calculateU();

        System.out.println("Model 1's vdw Energy: "  + model1.vdwEnergy + ".");
        System.out.println("Model 1's electrostatic Energy: " + model1.electrostaticEnergy + ".");
        System.out.println("Model 1's solvation Energy: " + model1.solvationEnergy + ".");

        System.out.println("Model 2's vdw Energy: " + model2.vdwEnergy + ".");
        System.out.println("Model 2's electrostatic Energy: " + model2.electrostaticEnergy + ".");
        System.out.println("Model 2's solvation Energy: " + model2.solvationEnergy + ".");

        //print out model's energies
        System.out.println("Total energy of Model 1: " + TotEnergy1);
        System.out.println("Total energy of Model 2: " + TotEnergy2);

        //find out which has the global minimum energy
        if (TotEnergy1 < TotEnergy2) {
            System.out.println("Model 1 has the lowest energy, therefore this model is better than the other.");
        }
        else if (TotEnergy1 > TotEnergy2) {
            System.out.println("Model 2 has the lowest energy, therefore this model is better than the other.");
        }
        else {
            System.out.println("Both models have the same energy. It is hard to determine which model is better.");
        }



    }
}



