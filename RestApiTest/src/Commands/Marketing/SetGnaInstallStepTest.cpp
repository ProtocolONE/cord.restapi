#include <CommandTest.h>

#include <RestApi/CommandBase.h>
#include <RestApi/Commands/Marketing/SetGnaInstallStep.h>

using P1::RestApi::CommandBase;
using P1::RestApi::Commands::Marketing::SetGnaInstallStep;

class SetGnaInstallStepTest : public CommandTest
{
};

TEST_F(SetGnaInstallStepTest, successParseTest)
{
  QString okResponse = 
    "<response>"
      "<status>ok</status>"
    "</response>";

  SetGnaInstallStep gnaInstallStep;
  gnaInstallStep.resultCallback(CommandBase::NoError, okResponse);

  ASSERT_EQ(0, gnaInstallStep.errorCode());
}

TEST_F(SetGnaInstallStepTest, errorParseTest) 
{
  QString errorMessageResponce = 
    "<response>"
      "<error>"
        "<message>Неверно указан логин или пароль</message>"
        "<code>100</code>"
      "</error>"
    "</response>";

  SetGnaInstallStep gnaInstallStepError;
  gnaInstallStepError.resultCallback(CommandBase::NoError, errorMessageResponce);

  ASSERT_NE(0, gnaInstallStepError.errorCode());
}