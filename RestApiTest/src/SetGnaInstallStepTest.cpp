#include "gtest/gtest.h"
#include "MemoryLeaksChecker.h"

#include <RestApi/Commands/Marketing/SetGnaInstallStep.h>
#include "SetGnaInstallStepTest.h"
#include <RestApi/GameNetCredential.h>

#include <QtCore/QWaitCondition>

#include <QtCore/QDebug>

QString okResponse = "<response><status>ok</status></response>";
QString errorResponse = "<respsegsegesgnse>";
QString errorMessageResponce = "<response><error><message>Неверно указан логин или пароль</message><code>100</code></error></response>";

void SetGnaInstallStepTest::SetGnaInstallStepResult( GGS::RestApi::CommandBaseInterface::CommandResults resultCode ) 
{
    ASSERT_TRUE(resultCode == GGS::RestApi::CommandBaseInterface::NoError);
}

void SetGnaInstallStepTest::SetGnaInstallStepResultError( GGS::RestApi::CommandBaseInterface::CommandResults resultCode ) 
{
    ASSERT_TRUE(resultCode != GGS::RestApi::CommandBaseInterface::NoError);
}

TEST_F(SetGnaInstallStepTest, setGnaInstallTest)
{
  GGS::RestApi::Commands::Marketing::SetGnaInstallStep gnaInstallStep;
  ASSERT_TRUE( QObject::connect(&gnaInstallStep, SIGNAL(result(GGS::RestApi::CommandBaseInterface::CommandResults)), 
      this, SLOT(SetGnaInstallStepResult(GGS::RestApi::CommandBaseInterface::CommandResults))) );

  gnaInstallStep.resultCallback(CommandBaseInterface::NoError, okResponse);

  GGS::RestApi::Commands::Marketing::SetGnaInstallStep gnaInstallStepError;

  if (gnaInstallStepError.resultCallback(CommandBaseInterface::NoError, errorMessageResponce)){
	  ASSERT_TRUE(gnaInstallStepError.getGenericErrorMessage().size());
  }
}