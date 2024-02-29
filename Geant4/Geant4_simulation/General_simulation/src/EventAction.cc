#include "EventAction.hh"
#include "ParameterContainer.hh"
#include "RunAction.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"

EventAction::EventAction(RunAction* runAction)
: G4UserEventAction(),
  fRunAction(runAction)
{
	if(ParameterContainer::GetInstance() -> GetParInt("UserVerbose") > 0)
		G4cout << "Constructor of EventAction" << G4endl;
} 

EventAction::~EventAction()
{
	if(ParameterContainer::GetInstance() -> GetParInt("UserVerbose") > 0)
		G4cout << "Destructor of EventAction" << G4endl;
}

void EventAction::BeginOfEventAction(const G4Event* anEvent)
{
	if(ParameterContainer::GetInstance() -> GetParInt("UserVerbose") > 0)
		G4cout << "Begin of Event Action" << G4endl;
	fRunAction -> clear_data();
}

void EventAction::EndOfEventAction(const G4Event* anEvent)
{  
	if(ParameterContainer::GetInstance() -> GetParInt("UserVerbose") > 0)
		G4cout << "End of Event Action" << G4endl;
	fRunAction -> update_Tree();
}

