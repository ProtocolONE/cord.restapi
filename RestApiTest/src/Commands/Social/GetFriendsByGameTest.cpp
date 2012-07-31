#include <CommandTest.h>
#include <RestApi/Commands/Social/GetFriendsByGame.h>

using namespace GGS::RestApi::Commands::Social;

class GetFriendsByGameTest : public CommandTest
{
};

QString GetFriendsByGameTestResponse = "<response>" \
  "<friendsByGame>" \
  "<row>" \
  "<friends>" \
  "<row>" \
  "<userId>400001000001632380</userId>" \
  "</row>" \
  "</friends>" \
  "<gameId>631</gameId>" \
  "</row>" \
  "<row>" \
  "<friends>" \
  "<row>" \
  "<userId>400001000002718140</userId>" \
  "</row>" \
  "<row>" \
  "<userId>400001000003743470</userId>" \
  "</row>" \
  "<row>" \
  "<userId>400007000003028300</userId>" \
  "</row>" \
  "<row>" \
  "<userId>400007000003292660</userId>" \
  "</row>" \
  "<row>" \
  "<userId>400007000007655620</userId>" \
  "</row>" \
  "</friends>" \
  "<gameId>71</gameId>" \
  "</row>" \
  "</friendsByGame>" \
  "</response>";

TEST_F(GetFriendsByGameTest, successNetworkTest)
{
  GetFriendsByGame command;
  QStringList param;
  param << "631" << "71" << "31";
  command.setGameId(param);
  //command.appendParameter("userId", "400007000008137700");
  //command.appendParameter("appKey", "a7996b41768fb5c34c4879245f0d537ea4069338");
  command.appendParameter("userId", "400001000001634860");
  command.appendParameter("appKey", "c99ebc84714c0c316dd891602dc916d238ef73ed");
  execute(&command);

  ASSERT_FALSE(command.errorCode());
}

TEST_F(GetFriendsByGameTest, responseTest)
{
  GetFriendsByGame command;
  command.resultCallback(GGS::RestApi::CommandBase::NoError, GetFriendsByGameTestResponse);
  
  FriendsInGamesMap response = command.response();
  
  ASSERT_EQ(response.count(), 6);

  QList<UserIdWithServer> values = response.values("71");

  ASSERT_EQ(values.at(0).first, "400007000007655620");
  ASSERT_EQ(values.at(1).first, "400007000003292660");
  ASSERT_EQ(values.at(2).first, "400007000003028300");
  ASSERT_EQ(values.at(3).first, "400001000003743470");
  ASSERT_EQ(values.at(4).first, "400001000002718140");

  ASSERT_TRUE(values.at(0).second.isEmpty());
  ASSERT_TRUE(values.at(1).second.isEmpty());
  ASSERT_TRUE(values.at(2).second.isEmpty());
  ASSERT_TRUE(values.at(3).second.isEmpty());
  ASSERT_TRUE(values.at(4).second.isEmpty());
   
  for (FriendsInGamesMap::iterator it = response.begin(); it !=response.end(); ++it){
    ASSERT_FALSE((*it).first.isEmpty());
    if ( (*it).first == "631"){
      ASSERT_EQ((*it).first, "400001000001632380");
      ASSERT_TRUE((*it).second.isEmpty());
    }
  }
}
