#include <CommandTest.h>
#include <RestApi/Commands/Service/GetLicense.h>

using P1::RestApi::Commands::Service::GetLicense;

class GetLicenseTest : public CommandTest
{
};

TEST_F(GetLicenseTest, successNetworkTest)
{
  GetLicense command("300002010000000000");
  command.setHash("fakeHash");
   
  execute(&command);
  ASSERT_TRUE(command.isLicenseNew());

  QString responseHash = command.responseHash();

  P1::RestApi::Commands::Service::GetLicense command2("300002010000000000");
  command2.setHash(responseHash);

  execute(&command2);
  ASSERT_FALSE(command2.isLicenseNew());
  ASSERT_EQ(command.responseHash(), command2.responseHash());
}