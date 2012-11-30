#include <CommandTest.h>

#include <RestApi/Commands/Games/GetCAInGameBanner.h>

#include <QtCore/QString>
#include <QtXml/QDomDocument>

class GetCAInGameBannerTest : public CommandTest
{
};

TEST_F(GetCAInGameBannerTest, successNetworkTest) 
{
  GGS::RestApi::Commands::Games::GetCAInGameBanner cmd;
  execute(&cmd);
  ASSERT_EQ(0, cmd.errorCode());
}
