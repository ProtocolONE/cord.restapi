#ifndef _GGS_RESTAPI_TEST_SET_GNA_INSTALL_STEP_RESULT_H_
#define _GGS_RESTAPI_TEST_SET_GNA_INSTALL_STEP_RESULT_H_

#include "gtest/gtest.h"
#include <RestApi/Commands/Marketing/SetGnaInstallStep.h>

class SetGnaInstallStepTest : public GGS::RestApi::Commands::Marketing::SetGnaInstallStep, public ::testing::Test
{
  Q_OBJECT

public slots:
  void SetGnaInstallStepResult( GGS::RestApi::CommandBaseInterface::CommandResults resultCode );
  void SetGnaInstallStepResultError( GGS::RestApi::CommandBaseInterface::CommandResults resultCode );
};

#endif