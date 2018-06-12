#include "PhesantApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ModulesApp.h"
#include "MooseSyntax.h"

template <>
InputParameters
validParams<PhesantApp>()
{
  InputParameters params = validParams<MooseApp>();
  return params;
}

PhesantApp::PhesantApp(InputParameters parameters) : MooseApp(parameters)
{
  Moose::registerObjects(_factory);
  ModulesApp::registerObjects(_factory);
  PhesantApp::registerObjects(_factory);

  Moose::associateSyntax(_syntax, _action_factory);
  ModulesApp::associateSyntax(_syntax, _action_factory);
  PhesantApp::associateSyntax(_syntax, _action_factory);

  Moose::registerExecFlags(_factory);
  ModulesApp::registerExecFlags(_factory);
  PhesantApp::registerExecFlags(_factory);
}

PhesantApp::~PhesantApp() {}

void
PhesantApp::registerApps()
{
  registerApp(PhesantApp);
}

void
PhesantApp::registerObjects(Factory & factory)
{
    Registry::registerObjectsTo(factory, {"PhesantApp"});
}

void
PhesantApp::associateSyntax(Syntax & /*syntax*/, ActionFactory & action_factory)
{
  Registry::registerActionsTo(action_factory, {"PhesantApp"});

  /* Uncomment Syntax parameter and register your new production objects here! */
}

void
PhesantApp::registerObjectDepends(Factory & /*factory*/)
{
}

void
PhesantApp::associateSyntaxDepends(Syntax & /*syntax*/, ActionFactory & /*action_factory*/)
{
}

void
PhesantApp::registerExecFlags(Factory & /*factory*/)
{
  /* Uncomment Factory parameter and register your new execution flags here! */
}

/***************************************************************************************************
 *********************** Dynamic Library Entry Points - DO NOT MODIFY ******************************
 **************************************************************************************************/
extern "C" void
PhesantApp__registerApps()
{
  PhesantApp::registerApps();
}

extern "C" void
PhesantApp__registerObjects(Factory & factory)
{
  PhesantApp::registerObjects(factory);
}

extern "C" void
PhesantApp__associateSyntax(Syntax & syntax, ActionFactory & action_factory)
{
  PhesantApp::associateSyntax(syntax, action_factory);
}

extern "C" void
PhesantApp__registerExecFlags(Factory & factory)
{
  PhesantApp::registerExecFlags(factory);
}
