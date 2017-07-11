#include <CommandTest.h>
#include <RestApi/Auth/GetRedirectToken.h>

using namespace GGS::RestApi::Auth;

class GetRedirectTokenTest : public CommandTest
{
};

TEST_F(GetRedirectTokenTest, Test)
{
  GetRedirectToken command;
  executeWithAuth(&command);
  const QString& token = command.token();

  ASSERT_EQ(false, token.isEmpty());
  ASSERT_EQ(0, command.errorCode());
}
