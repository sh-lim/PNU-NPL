#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "SteppingAction.hh"
#include "TrackingAction.hh"

#include "ParameterContainer.hh"

ActionInitialization::ActionInitialization()
 : G4VUserActionInitialization()
{
	PC = ParameterContainer::GetInstance();
	if(PC -> GetParInt("UserVerbose") > 0)
		G4cout << "Constructor of ActionInitialization" << G4endl;
}

ActionInitialization::~ActionInitialization()
{
	if(PC -> GetParInt("UserVerbose") > 0)
		G4cout << "Destructor of ActionInitialization" << G4endl;
}

void ActionInitialization::BuildForMaster() const
{
  RunAction* runAction = new RunAction();
  SetUserAction(runAction);
  
}

void ActionInitialization::Build() const
{
  SetUserAction(new PrimaryGeneratorAction());

  RunAction* runAction = new RunAction();
  SetUserAction(runAction);
  
  EventAction* eventAction = new EventAction(runAction);
  SetUserAction(eventAction);
  
  SetUserAction(new TrackingAction(runAction));
  SetUserAction(new SteppingAction(runAction));
}  
