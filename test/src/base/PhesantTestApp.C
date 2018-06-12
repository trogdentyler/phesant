//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html
#include "PhesantTestApp.h"
#include "PhesantApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "MooseSyntax.h"
#include "ModulesApp.h"

template <>
InputParameters
validParams<PhesantTestApp>()
{
  InputParameters params = validParams<PhesantApp>();
  return params;
}

PhesantTestApp::PhesantTestApp(InputParameters parameters) : MooseApp(parameters)
{
  Moose::registerObjects(_factory);
  ModulesApp::registerObjects(_factory);
  PhesantApp::registerObjectDepends(_factory);
  PhesantApp::registerObjects(_factory);

  Moose::associateSyntax(_syntax, _action_factory);
  ModulesApp::associateSyntax(_syntax, _action_factory);
  PhesantApp::associateSyntaxDepends(_syntax, _action_factory);
  PhesantApp::associateSyntax(_syntax, _action_factory);

  Moose::registerExecFlags(_factory);
  ModulesApp::registerExecFlags(_factory);
  PhesantApp::registerExecFlags(_factory);

  bool use_test_objs = getParam<bool>("allow_test_objects");
  if (use_test_objs)
  {
    PhesantTestApp::registerObjects(_factory);
    PhesantTestApp::associateSyntax(_syntax, _action_factory);
    PhesantTestApp::registerExecFlags(_factory);
  }
}

PhesantTestApp::~PhesantTestApp() {}

void
PhesantTestApp::registerApps()
{
  registerApp(PhesantApp);
  registerApp(PhesantTestApp);
}

void
PhesantTestApp::registerObjects(Factory & /*factory*/)
{
  /* Uncomment Factory parameter and register your new test objects here! */
}

void
PhesantTestApp::associateSyntax(Syntax & /*syntax*/, ActionFactory & /*action_factory*/)
{
  /* Uncomment Syntax and ActionFactory parameters and register your new test objects here! */
}

void
PhesantTestApp::registerExecFlags(Factory & /*factory*/)
{
  /* Uncomment Factory parameter and register your new execute flags here! */
}

/***************************************************************************************************
 *********************** Dynamic Library Entry Points - DO NOT MODIFY ******************************
 **************************************************************************************************/
// External entry point for dynamic application loading
extern "C" void
PhesantTestApp__registerApps()
{
  PhesantTestApp::registerApps();
}

// External entry point for dynamic object registration
extern "C" void
PhesantTestApp__registerObjects(Factory & factory)
{
  PhesantTestApp::registerObjects(factory);
}

// External entry point for dynamic syntax association
extern "C" void
PhesantTestApp__associateSyntax(Syntax & syntax, ActionFactory & action_factory)
{
  PhesantTestApp::associateSyntax(syntax, action_factory);
}

// External entry point for dynamic execute flag loading
extern "C" void
PhesantTestApp__registerExecFlags(Factory & factory)
{
  PhesantTestApp::registerExecFlags(factory);
}
