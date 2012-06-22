#include <CommandTest.h>
#include <RestApi/Commands/User/ValidateMainInfo.h>

using GGS::RestApi::Commands::User::ValidateMainInfo;

class ValidateMainInfoTest : public CommandTest
{
};

TEST_F(ValidateMainInfoTest, successNetworkTest)
{
  ValidateMainInfo command;
  command.setFieldValue("nickname", "misterion");

  executeWithAuth(&command);

  //Мы не можем сменить имя, поэтому специально проверяем что нам вернули
  //верное сообщение об ошибка
  ASSERT_EQ(119, command.errorCode());
  ASSERT_NE("", command.errorMessage());
}