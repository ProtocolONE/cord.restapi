#include <CommandTest.h>
#include <RestApi/Commands/User/SaveMainInfo.h>

using P1::RestApi::Commands::User::SaveMainInfo;

class SaveMainInfoTest : public CommandTest
{
};

TEST_F(SaveMainInfoTest, successNetworkTest)
{
  SaveMainInfo command;
  command.setFieldValue("nickname", "misterion");

  executeWithAuth(&command);

  //Мы не можем сменить имя, поэтому специально проверяем что нам вернули
  //верное сообщение об ошибка
  ASSERT_EQ(115, command.errorCode());
  ASSERT_NE("", command.errorMessage());
}