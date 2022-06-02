#include <iostream>
#include <fstream>

using namespace std;

class Atom{
private:
    int m_id;
    double m_coord [3];
    double m_vel [3];
    double m_acc [3];
    int m_type;
public:
    Atom(): m_id(0), m_coord{0, 0, 0}, m_vel{0, 0, 0}, m_acc{0, 0, 0}, m_type(0)
    {}
    Atom(const double* coord, const double* vel, int id = 1, int type = 0): m_id(id), m_coord {coord[0], coord[1], coord[2]}, m_vel {vel[0], vel[1], vel[2]}, m_acc{0, 0, 0}
    {}
    int getId() { return m_id; }
    friend ostream& operator<<(ostream& out, const Atom& atom);
};



class AtomSystem
{
private:
    int m_nAtoms;
    Atom* atoms;
    double m_eFull;
    double m_ePot;
    double m_eKin;
public:
    AtomSystem(int nAtoms){
        m_nAtoms = nAtoms;
        atoms = new Atom[nAtoms];
    }
    AtomSystem(string fName){
        ifstream in(fName);
        if (in.is_open())
        {
            in >> m_nAtoms;
            atoms = new Atom[m_nAtoms];
            int i, id;
            double coordAtom[3], vel[3];
            for (i = 0; i < m_nAtoms; i++ ){
                in >> id >> coordAtom[0] >> coordAtom[1] >> coordAtom[2] >> vel[0] >> vel[1] >> vel[2];
                Atom atom(coordAtom, vel, id);
                atoms[i] = atom;
            } 
        }
        in.close();
    }
    ~AtomSystem(){
        delete[] atoms;
    }
    int addAtom(Atom& atom){
        int i;
        for (i = 0; i < m_nAtoms; i++ ){
            if (atoms[i].getId() == 0){
                atoms[i] = atom;
                break;
            }
        }
    return i;
    };
    friend ostream& operator<<(ostream& out, const AtomSystem& system);
    int calcF();
    int calcCoordNew();
};

ostream& operator<<(ostream& out, const AtomSystem& system) {
out << system.m_nAtoms << endl;
int i;
for (i = 0; i < system.m_nAtoms; i++){
    out << system.atoms[i] << endl;
}
return out;
}

ostream& operator<<(ostream& out, const Atom& atom) {
out << atom.m_id << " " << atom.m_coord[0] << " " << atom.m_coord[1] << " " << atom.m_coord[2] << " " << atom.m_vel[0] << " " << atom.m_vel[1] << " " << atom.m_vel[2];
return out;
}

int main (){
    double coord1Atom[] = {1,1,1};
    double coord2Atom[] = {2,1,1};
    double vel[] = {0,0,0};
    Atom atom1(coord1Atom, vel);
    Atom atom2(coord2Atom, vel, 2);
    AtomSystem system1(2);
    system1.addAtom(atom1);
    system1.addAtom(atom2);
    //cout << system1;
    AtomSystem system2("system2.txt");
    cout << system2;
    return 0;
}