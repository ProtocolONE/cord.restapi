#include <CommandTest.h>
#include <RestApi/Commands/User/SetUserActivity.h>

using GGS::RestApi::Commands::User::SetUserActivity;

class SetUserActivityTest : public CommandTest
{
};

TEST_F(SetUserActivityTest, setUserActivityTestTest)
{
  SetUserActivity command;
  command.setGameId(71);

  executeWithAuth(&command);

  ASSERT_TRUE(command.getTimeout() > 0);
}