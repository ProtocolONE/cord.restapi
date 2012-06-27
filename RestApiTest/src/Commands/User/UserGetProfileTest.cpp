#include <CommandTest.h>
#include <RestApi/Commands/User/Response/UserGetProfileResponse.h>
#include <RestApi/Commands/User/GetProfile.h>

using GGS::RestApi::Commands::User::GetProfile;
using GGS::RestApi::Commands::User::Response::UserGetProfileResponse;

class UserGetProfileTest : public CommandTest
{
};

QString userGetProfileTestQueryResponse = "<response>" \
  "<userInfo>" \
  "<row>" \
  "<userId>400007000003292660</userId>" \
  "<shortInfo>" \
  "<nickname>LJUVILLA</nickname>" \
  "<nametech>ljuvilla</nametech>" \
  "<registerDate>19.07.2011</registerDate>" \
  "<sex>2</sex>" \
  "<online>1</online>"
  "<id>400007000003292660</id>" \
  "<profile>http://www.gamenet.ru/users/ljuvilla</profile>" \
  "<hasAvatar>1</hasAvatar>" \
  "<lastOnline>1340782715</lastOnline>" \
  "<avatarSmall>" \
  "http://images.gamenet.ru/pics/user/avatar/small/60/26/29/400007000003292660/1316772590.jpg" \
  "</avatarSmall>" \
  "<avatarMedium>" \
  "http://images.gamenet.ru/pics/user/avatar/medium/60/26/29/400007000003292660/1316772590.jpg" \
  "</avatarMedium>" \
  "<avatarLarge>" \
  "http://images.gamenet.ru/pics/user/avatar/large/60/26/29/400007000003292660/1316772590.jpg" \
  "</avatarLarge>" \
  "<isFriend>1</isFriend>" \
  "</shortInfo>" \
  "</row>" \
  "<row>" \
  "<userId>400007000007655620</userId>" \
  "<shortInfo>" \
  "<nickname>фывафйцуеа</nickname>" \
  "<nametech>fyvafitsuea</nametech>" \
  "<registerDate>26.09.2011</registerDate>" \
  "<sex>1</sex>" \
  "<online>1</online>" \
  "<id>400007000007655620</id>" \
  "<profile>http://www.gamenet.ru/users/fyvafitsuea</profile>" \
  "<hasAvatar>1</hasAvatar>" \
  "<lastOnline>1340782728</lastOnline>" \
  "<avatarSmall>" \
  "http://images.gamenet.ru/pics/user/avatar/small/20/56/65/400007000007655620/1317044121.jpg" \
  "</avatarSmall>" \
  "<avatarMedium>" \
  "http://images.gamenet.ru/pics/user/avatar/medium/20/56/65/400007000007655620/1317044121.jpg" \
  "</avatarMedium>" \
  "<avatarLarge>" \
  "http://images.gamenet.ru/pics/user/avatar/large/20/56/65/400007000007655620/1317044121.jpg" \
  "</avatarLarge>" \
  "<isFriend>1</isFriend>" \
  "</shortInfo>" \
  "</row>" \
  "</userInfo>" \
  "</response>";
  
TEST_F(UserGetProfileTest, successNetworkTest)
{
  GetProfile command;
  command.appendParameter("userId", "400007000008137700");
  command.appendParameter("appKey", "a7996b41768fb5c34c4879245f0d537ea4069338");
  QStringList param;
  param << "400007000003292660" << "400007000007655620";
  command.setProfileId(param);

  execute(&command);

  ASSERT_FALSE(command.errorCode());
}

TEST_F(UserGetProfileTest, responseTest)
{
  GetProfile command;
  command.resultCallback(GGS::RestApi::CommandBase::NoError, userGetProfileTestQueryResponse);
  
  QMap<QString, UserGetProfileResponse> response = command.response();
  ASSERT_EQ(response.count(), 2);
  
  Q_FOREACH(UserGetProfileResponse userProfile, response.values()){
    ASSERT_FALSE(userProfile.userId().isEmpty());
    if (userProfile.userId() == "400007000003292660"){
      ASSERT_EQ(userProfile.nickname(), "LJUVILLA");
      ASSERT_EQ(userProfile.nametech(), "ljuvilla");
      ASSERT_EQ(userProfile.registerDate(), "19.07.2011");
      ASSERT_EQ(userProfile.sex(), 2);
      ASSERT_EQ(userProfile.online(), true);
      ASSERT_EQ(userProfile.profileLink(), "http://www.gamenet.ru/users/ljuvilla");
      ASSERT_EQ(userProfile.hasAvatar(), true);
      ASSERT_EQ(userProfile.lastOnline(), 1340782715);
      ASSERT_EQ(userProfile.avatarSmall(), "http://images.gamenet.ru/pics/user/avatar/small/60/26/29/400007000003292660/1316772590.jpg");
      ASSERT_EQ(userProfile.avatarMedium(), "http://images.gamenet.ru/pics/user/avatar/medium/60/26/29/400007000003292660/1316772590.jpg");
      ASSERT_EQ(userProfile.avatarLarge(), "http://images.gamenet.ru/pics/user/avatar/large/60/26/29/400007000003292660/1316772590.jpg");
    } 
    else if (userProfile.userId() == "400007000007655620"){
      ASSERT_EQ(userProfile.nickname(), "фывафйцуеа");
      ASSERT_EQ(userProfile.nametech(), "fyvafitsuea");
      ASSERT_EQ(userProfile.registerDate(), "26.09.2011");
      ASSERT_EQ(userProfile.sex(), 1);
      ASSERT_EQ(userProfile.online(), true);
      ASSERT_EQ(userProfile.profileLink(), "http://www.gamenet.ru/users/fyvafitsuea");
      ASSERT_EQ(userProfile.hasAvatar(), true);
      ASSERT_EQ(userProfile.lastOnline(), 1340782728);
      ASSERT_EQ(userProfile.avatarSmall(), "http://images.gamenet.ru/pics/user/avatar/small/20/56/65/400007000007655620/1317044121.jpg");
      ASSERT_EQ(userProfile.avatarMedium(), "http://images.gamenet.ru/pics/user/avatar/medium/20/56/65/400007000007655620/1317044121.jpg");
      ASSERT_EQ(userProfile.avatarLarge(), "http://images.gamenet.ru/pics/user/avatar/large/20/56/65/400007000007655620/1317044121.jpg");
    }
  }
}
