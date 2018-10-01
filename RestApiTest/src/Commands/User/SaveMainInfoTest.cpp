#include <CommandTest.h>
#include <RestApi/Commands/User/SaveMainInfo.h>

using GGS::RestApi::Commands::User::SaveMainInfo;

class SaveMainInfoTest : public CommandTest
{
};

TEST_F(SaveMainInfoTest, successNetworkTest)
{
  SaveMainInfo command;
  command.setFieldValue("nickname", "misterion");

  executeWithAuth(&command);

  //�� �� ����� ������� ���, ������� ���������� ��������� ��� ��� �������
  //������ ��������� �� ������
  ASSERT_EQ(119, command.errorCode());
  ASSERT_NE("", command.errorMessage());
}