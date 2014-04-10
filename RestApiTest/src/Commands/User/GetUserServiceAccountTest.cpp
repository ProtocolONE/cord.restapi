#include <CommandTest.h>
#include <RestApi/Commands/User/GetUserServiceAccount.h>
#include <RestApi/Commands/User/Response/UserServiceAccountResponse.h>

using GGS::RestApi::Commands::User::GetUserServiceAccount;
using GGS::RestApi::Commands::User::Response::UserServiceAccountResponse;

class GetUserServiceAccountTest : public CommandTest
{
};

TEST_F(GetUserServiceAccountTest, failedNetworkTest)
{
  GetUserServiceAccount command;
  command.setServiceId("300002010000000000");
  command.appendParameter("appKey", "someBadKey");
  command.appendParameter("userId", "someBadId");

  execute(&command);

  ASSERT_NE(0, command.errorCode());
}

TEST_F(GetUserServiceAccountTest, successNetworkSaltTest)
{
  GetUserServiceAccount command;
  QString salt("WjjRnOuelLO/D7Ys+rIVelaGCIiuStBxr2yL4Ut9TFk=");

  command.setServiceId("300002010000000000");
  command.setVersion("2");
  command.appendParameter("salt", salt);

  executeWithAuth(&command);

  UserServiceAccountResponse *response = command.response();
  ASSERT_EQ(0, command.errorCode());
  ASSERT_TRUE(response->getLogin().size());
  ASSERT_TRUE(response->getToken().size());
  ASSERT_TRUE(response->getStatus().size());
  ASSERT_TRUE(response->getPassword().size());
}