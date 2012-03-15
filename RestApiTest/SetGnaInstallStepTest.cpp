#include "gtest/gtest.h"
#include "MemoryLeaksChecker.h"

#include "Commands\Marketing\SetGnaInstallStep.h"
#include "SetGnaInstallStepTest.h"
#include "GameNetCredential.h"

#include <QtCore/QWaitCondition>

#include <qdebug>

QString okResponse = "<response><status>ok</status></response>";
QString errorResponse = "<respsegsegesgnse>";
QString errorMessageResponce = "<response><error><message>Неверно указан логин или пароль</message><code>100</code></error></response>";

void SetGnaInstallStepTest::SetGnaInstallStepResult( int resultCode ) 
{
  ASSERT_TRUE(resultCode);
}

void SetGnaInstallStepTest::SetGnaInstallStepResultError( int resultCode ) 
{
  ASSERT_TRUE(resultCode);
}

TEST_F(SetGnaInstallStepTest, setGnaInstallTest)
{
  GGS::RestApi::Commands::Marketing::SetGnaInstallStep gnaInstallStep;
  ASSERT_TRUE( QObject::connect(&gnaInstallStep, SIGNAL(result(int)), this, SLOT(SetGnaInstallStepResult(int))) );

  gnaInstallStep.resultCallback(CommandBaseInterface::NoError, okResponse);

  GGS::RestApi::Commands::Marketing::SetGnaInstallStep gnaInstallStepError;

  if (gnaInstallStepError.resultCallback(CommandBaseInterface::NoError, errorMessageResponce)){
	  ASSERT_TRUE(gnaInstallStepError.getGenericErrorMessage().size());
  }
}