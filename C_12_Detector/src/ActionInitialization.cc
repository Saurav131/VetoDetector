
#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"
// #include "RunAction.hh"
// #include "EventAction.hh"
// #include "SteppingAction.hh"
// namespace B1
// {
ActionInitialization::ActionInitialization()
{}
ActionInitialization::~ActionInitialization()
{}
// //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void ActionInitialization::Build() const
{
  PrimaryGeneratorAction* generate = new PrimaryGeneratorAction();
  SetUserAction(generate);

   MyRunAction *runaction = new MyRunAction();
  SetUserAction(runaction);
}



























// void ActionInitialization::BuildForMaster() const
// {
//   RunAction* runAction = new RunAction;
//   SetUserAction(runAction);
// }

// //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// void ActionInitialization::Build() const
// {
//   SetUserAction(new PrimaryGeneratorAction);

//   RunAction* runAction = new RunAction;
//   SetUserAction(runAction);

//   EventAction* eventAction = new EventAction(runAction);
//   SetUserAction(eventAction);

//   SetUserAction(new SteppingAction(eventAction));
// }

// //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// }
