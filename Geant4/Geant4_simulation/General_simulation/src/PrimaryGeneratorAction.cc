#include "PrimaryGeneratorAction.hh"
#include "ParameterContainer.hh"

#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"


PrimaryGeneratorAction::PrimaryGeneratorAction(ParameterContainer* par)
: G4VUserPrimaryGeneratorAction(),
  fParticleGun(0),
	PC(par)
{
	fParticleGun  = new G4ParticleGun();

	// default particle kinematic
	G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
	G4String particleName = PC -> GetParString("particle");
	G4ParticleDefinition* particle
		= particleTable->FindParticle(particleName);
	fParticleGun->SetParticleDefinition(particle);
	fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
	fParticleGun->SetParticleEnergy(PC->GetParDouble("energy")*MeV);
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete fParticleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
	for(G4int n=0; n<PC -> GetParInt("NperEvent"); n++)
	{
		G4double x0 = (PC->GetParDouble("x0")+PC->GetParDouble("dx")*(G4UniformRand()-0.5)) * mm;
		G4double y0 = (PC->GetParDouble("y0")+PC->GetParDouble("dy")*(G4UniformRand()-0.5)) * mm;
		G4double z0 = (PC->GetParDouble("z0")+PC->GetParDouble("dz")*(G4UniformRand()-0.5)) * mm;

		fParticleGun->SetParticlePosition(G4ThreeVector(x0,y0,z0));

		fParticleGun->GeneratePrimaryVertex(anEvent);
	}
//	G4cout << "yjkim: " << fParticleGun -> GetParticleDefinition() -> GetParticleName() << G4endl;
}
