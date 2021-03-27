package Model;

import java.io.File;
import java.util.*;

public class Model {
    /*
    private int nAtoms;
    private Vector AtomNum = new Vector(nAtoms);
    private Vector X = new Vector(nAtoms);
    private Vector Y = new Vector(nAtoms);
    private Vector Z = new Vector(nAtoms);
    private Vector R = new Vector(nAtoms);
    private Vector Epsilon = new Vector(nAtoms);
    private Vector Sigma = new Vector(nAtoms);
    private Vector Charge = new Vector(nAtoms);
    private Vector ASP = new Vector(nAtoms);
    private Vector AtmName = new Vector(nAtoms);
    private Vector ResName = new Vector(nAtoms);
    private Vector ResNum = new Vector(nAtoms);
    private Vector Nex = new Vector(nAtoms);
    private Vector NexList = new Vector(nAtoms);
    private Vector ASA = new Vector(nAtoms);

    public Model(String file) {
        try {
            File model = new File(file);
        } catch(Exception e) {
            e.printStackTrace();
        }

        String line, ResNameTemp, AtmNameTemp;
        double Xtemp, Ytemp, Ztemp, Rtemp, Epstemp, Sigmatemp, Chargetemp, ASPtemp;
        int num, ResNumtemp;

        Scanner nextline = new Scanner(file);
        line = nextline.nextLine();
        String nospace = line.replaceAll("\\s+","");
        nAtoms = Integer.parseInt(nospace);
   //     nAtoms = Integer.parseInt(nextline.nextLine());
        System.out.println("nAtoms = " + nAtoms);
    }
/*    public double calculateU() {}
    public double vdwEnergy() {}
    public double electrosaticEnergy() {}
    public double solvationEnergy() {}
 */
    */
}
