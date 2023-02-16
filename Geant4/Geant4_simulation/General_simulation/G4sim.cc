#include "DetectorConstruction.hh"
#include "ActionInitialization.hh"
#include "ParameterContainer.hh"

#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4PhysListFactory.hh"
#include "G4HadronicParameters.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "Randomize.hh"

#include <string>

int main(int argc,char** argv)
{
	G4UIExecutive* ui = 0;
	if ( argc == 1 ) 
		ui = new G4UIExecutive(argc, argv);

	G4RunManager* runManager = new G4RunManager;

	G4String parameters = "Parameters.conf";
//	ParameterContainer* PC = new ParameterContainer(parameters);
	ParameterContainer* PC = ParameterContainer::GetInstance();
//	PC -> PrintParameter("All");

	// initialize the physics list
	G4String physListStr = PC -> GetParString("PhysicsList");
	G4PhysListFactory* physListFac = new G4PhysListFactory();
	physListFac -> SetVerbose(PC -> GetParInt("PhysicsVerbose"));
	G4VModularPhysicsList* physicsList = physListFac ->GetReferencePhysList(physListStr.c_str());
	physicsList -> SetVerboseLevel(PC -> GetParInt("PhysicsVerbose"));
	G4HadronicParameters::Instance() -> SetVerboseLevel(PC -> GetParInt("PhysicsVerbose"));

	runManager->SetUserInitialization(physicsList);
  
	// the random seed
	G4int seed = PC -> GetParInt("RandomSeed");
	if(seed == 0)
		G4Random::setTheSeed(time(0));
	else
		G4Random::setTheSeed(seed);

	// User action initialization
	runManager->SetUserInitialization(new DetectorConstruction());
	runManager->SetUserInitialization(new ActionInitialization());

	// Initialize visualization
	//
	G4VisManager* visManager = new G4VisExecutive("0");
	visManager -> SetVerboseLevel(0);
	visManager->Initialize();

	// Get the pointer to the User Interface manager
	G4UImanager* UImanager = G4UImanager::GetUIpointer();

	// Process macro or start UI session
	if ( PC -> GetParBool("Visualisation") == false) 
	{ 
		// batch mode
		G4String command = "/control/execute ";
		if(argc ==1)
		{
			G4String fileName = PC -> GetParString("MacroFile");
			UImanager->ApplyCommand(command+fileName);
		}
		if(argc >=2)
		{
			G4String macroFile = argv[1];
			UImanager->ApplyCommand(command+macroFile);
		}
	} else { 
		// interactive mode
		UImanager->ApplyCommand("/control/execute init_vis.mac");
		ui->SessionStart();
	}

	delete ui;
	delete visManager;
	delete runManager;
	delete PC;
}
