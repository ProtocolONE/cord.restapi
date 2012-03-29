#ifndef _GGS_RESTAPI_TEST_SET_GNA_INSTALL_STEP_RESULT_H_
#define _GGS_RESTAPI_TEST_SET_GNA_INSTALL_STEP_RESULT_H_

#include "gtest/gtest.h"
#include "Commands\Marketing\SetGnaInstallStep.h"

class SetGnaInstallStepTest : public GGS::RestApi::Commands::Marketing::SetGnaInstallStep, public ::testing::Test
{
  Q_OBJECT

public slots:
  void SetGnaInstallStepResult( int resultCode );
  void SetGnaInstallStepResultError( int resultCode );
};

#endif