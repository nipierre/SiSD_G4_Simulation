#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"
#include "EventAction.hh"
#include "RunAction.hh"

ActionInitialization::ActionInitialization()
 : G4VUserActionInitialization()
{}

ActionInitialization::~ActionInitialization()
{}

void ActionInitialization::BuildForMaster() const
{
  EventAction* event_action = new EventAction();
  SetUserAction(new RunAction(event_action));
}

void ActionInitialization::Build() const
{
  SetUserAction(new PrimaryGeneratorAction);
  EventAction* event_action = new EventAction();
  SetUserAction(event_action);
  SetUserAction(new RunAction(event_action));
}
