#include "ParameterContainer.hh"

#include <sstream>

ParameterContainer::ParameterContainer()
{
    par_Name = "Parameters.conf";
    ReadParameters();
    PrintParameter("yjkim");
}

ParameterContainer::ParameterContainer(G4String fileName)
{
    par_Name = fileName;
    ReadParameters();
    PrintParameter("yjkim");
}

ParameterContainer::~ParameterContainer()
{}

void ParameterContainer::ReadParameters()
{
    ifstream par_file(par_Name);
    string line;
    while(getline(par_file,line))
    {
        G4String val_name, val_type;
        istringstream ss(line);
        ss >> val_name >> val_type;

        if(val_name[0] == '#') continue;

        if(val_type.contains("b") || val_type.contains("bool"))
        {
            G4bool val = 0;
            ss >> val;
            par_bool.insert(make_pair(val_name,val));
        }
        if(val_type.contains("i") || val_type.contains("int"))
        {
            G4int val = -1;
            ss >> val;
            par_int.insert(make_pair(val_name,val));
		}
        if(val_type.contains("d") || val_type.contains("double"))
        {
            G4double val = 0;
            ss >> val;
            par_double.insert(make_pair(val_name,val));
        }
        if(val_type.contains("s") || val_type.contains("string"))
        {
            G4String val;
            ss >> val;
            par_string.insert(make_pair(val_name,val));
        }
    }
}

const ParameterContainer& ParameterContainer::operator=(const ParameterContainer& right)
{
    par_bool = right.par_bool;
    par_int = right.par_int;
    par_double = right.par_double;
    par_string = right.par_string;
    return *this;
}

void ParameterContainer::PrintParameter(G4String par)
{
	G4bool parb = par_bool[par];
	G4int pari = par_int[par];
	G4double pard = par_double[par];
	G4String pars = par_string[par];
	if(parb)
		G4cout << par << " " << parb << G4endl;
	else if(pari)
		G4cout << par << " " << pari << G4endl;
	else if(pard)
		G4cout << par << " " << pard << G4endl;
	else if(pars)
		G4cout << par << " " << pars << G4endl;
	else
    G4cout << "yjkim in Parameter Container" << G4endl;
}