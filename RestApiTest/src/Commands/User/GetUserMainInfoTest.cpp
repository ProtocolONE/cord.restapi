#include <CommandTest.h>

#include <RestApi/CommandBase.h>
#include <RestApi/Commands/User/GetUserMainInfo.h>
#include <RestApi/Commands/User/Response/UserMainInfoResponse.h>

using GGS::RestApi::CommandBase;
using GGS::RestApi::Commands::User::GetUserMainInfo;
using GGS::RestApi::Commands::User::Response::UserMainInfoResponse;

class GetUserMainInfoTest : public CommandTest
{
public:
  QString getNormalResponse() {
   return QString("<?xml version=\"1.0\" encoding=\"utf-8\"?>" \
    "<response>                                                " \
    "	<mainInfo>                                               " \
    "		<user_master_login>gna@unit.test</user_master_login> " \
    "		<user_service_login>1000017288</user_service_login>  " \
    "		<user_question></user_question>                      " \
    "		<user_answer></user_answer>                          " \
    "		<user_registration_date>23.02.2011 10:19:51</user_registration_date>" \
    "		<reg_ip>192.168.1.104</reg_ip>                                      " \
    "		<user_status>0</user_status>                                        " \
    "		<user_rsa_close_key>-----BEGIN RSA PRIVATE KEY-----" \
    "MIIEpAIBAAKCAQEA3QgWgdF9LhLPWHHs47sUWAEdPSV4VunrdbUYnwjzLNFBHuyP" \
    "ix1Xn7HeulwJbtkcT4bj9HxzJaWl8wkErYzuVjz/gGtNB5Mtr4gJKiLbhuUHRo0O" \
    "RDC2UpIuudtNV6q74LADv7UTYNtX/lKLf//v/DVmSM5tsTxMOolkXyGZ/woXHvJE" \
    "zTa3KzQwOLVF7vEX524bvr1aufnviUbc+Saxcxh4wC9xfTMm29j5CsFDmp9e/C/U" \
    "LNjbiVw6s1tm2wdLmpFP55QFxhj/gh8jNGUxkRBUJ8gYySflpjeiSp33B4Zsfi9T" \
    "ZiMnRL3mesy3W1OOgdk4uW5E6ICIOsRDsaDPSQIDAQABAoIBAQCwA4nQ1V9HOmlt" \
    "uEN50nfP4QtErzsWk28TLCSwOLNVxEmEc8OXd8VYgY+pfjNw12oJFpUfE5+qoi/1" \
    "yv+zqN//QtIAlPIhjx25g64wpNOGp4nUr+1ldhkqxgh5rt73ahn1QpWpq2wEHIgF" \
    "GfzG8KxOfsO2RNTrZ+YYU2LfsuVsR0R9OWuZcixndNuWzwgy2+oW/RwUk58TP3WS" \
    "DHB7Mlh3w2ZPhZ6lsa83IBMW6Lir2XUwmB2sulTLSFaFLWBpKrAaNJfnr8vrGDqK" \
    "FJdARqZK1Tc4BIAoeqQkCYd1eYQyoczaVjwwLTSyUHR9KFhkRxbiV0+JPz0I0xnC" \
    "RCZmqkMBAoGBAPlWDM4MItncj2lu8WcJZJbUh9JD29r814X9JT4j095YlvoFSk7B" \
    "YpW+x5lZ37+dw7cjMrBFDwUyshdiIRz6JBc9/aE0M82fYxnFpYTEAyZrOcmSEf6L" \
    "a6Six3YWJEvpb/h22hs62Z0b94cwfGERWZ8Suah5SjfL2PagtojeE8rpAoGBAOLw" \
    "YQ6wpWipht007pNkBnQtq+KCtMjRXa7suvc5Bgeal6MQSTTx/xf0cPESoPRrCgFR" \
    "r5UBqeCDj8r3Yjgl8rGpbIr79JNa4w6SJuZrVMCf+erxPqEhc+OBmk+swIgACIPa" \
    "MIBE8dbhNOIvD6JXf2qGNhqL38JL+Y6fW02Sm2VhAoGBANuwBfhGmS58N6AeMHUo" \
    "wYhkGogZYk3BGeTk9zuZNcRjKiOBJcfefI6UWim0FoEu8JMcYD0Pm/xofqI7xBFU" \
    "FRildiPjawFxvk+m5f/k9SGUuIXyPgiZr26QPk69k52PQSkbD3GOmM7lJWPoRK8C" \
    "KoUOaqcWt14SLkifsjVF9wqBAoGAeBarxZJEdXYAH956wRQVNjVU17BC6mGgKYis" \
    "B1btkeiEhY2Ar7u/OXXoriklczGRQdFwEHGo612zIbx3BS9PliQJhCJ/8doOfQ9p" \
    "9lSlrKj7HxA6DBofsSxL9A1+dHlQCDXVpIrXTtYtneM5arbSfhQ3XSTXa4G4tXgu" \
    "YIZMJQECgYAWgrc6vjVgDH/GBCGmtdEzlFFdHCADJav9u+nzoHzo1G7PUf9e1/hA" \
    "O965vlkmf7LK9TqTcv9/9iDrk0FPKcAUfh8WI8qklCCWmufbC9XLPR+UxUDxp3DS" \
    "Kv4pY71fJE8PBjF4rUooE18+gbCJjiYdG+JK4hQFupgc0Z48CEoe6Q==" \
    "-----END RSA PRIVATE KEY-</user_rsa_close_key>                           " \
    "		<mmid>12356</mmid>                                                      " \
    "		<user_referalid></user_referalid>                                   " \
    "		<login>gna@unit.test</login>                                        " \
    "		<nickname>unittest</nickname>                                       " \
    "		<nametech>TestTechNick4101728</nametech>                            " \
    "		<userkey>d4815f11146370ac6fffee7de11f55933181e452</userkey>        " \
    "		<appkey>92da94c6a632951c8d588f596826bfd1470843f0</appkey>          " \
    "		<registerDate>23.02.2011</registerDate>                            " \
    "		<sex>2</sex>                                                       " \
    "		<id>400001000000172890</id>                                        " \
    "		<profile>http://www.gamenet.dev/users/TestTechNick4101728</profile>" \
    "		<hasAvatar></hasAvatar>                                            " \
    "		<lastOnline>1329200851</lastOnline>                                " \
    "		<avatarSmall>http://images.gamenet.dev/pics/user/avatar/small/empty2.jpg</avatarSmall>   " \
    "		<avatarMedium>http://images.gamenet.dev/pics/user/avatar/medium/empty2.jpg</avatarMedium>" \
    "		<avatarLarge>http://images.gamenet.dev/pics/user/avatar/large/empty2.jpg</avatarLarge>   " \
    "		<online>1</online>                                                                       " \
    "		<userId>400001000000172890</userId>                                                      " \
    "		<steamId>steam:0:123123</steamId>" \
    "	</mainInfo>" \
    "</response>");
  }
};

TEST_F(GetUserMainInfoTest, normalParseTest)
{
  GetUserMainInfo command;

  command.resultCallback(CommandBase::NoError, this->getNormalResponse());
  UserMainInfoResponse *answer = command.response();
  ASSERT_EQ("12356", answer->marketingId());
  ASSERT_EQ("unittest", answer->nickname());
  ASSERT_EQ("TestTechNick4101728", answer->nametech());
  ASSERT_EQ("http://www.gamenet.dev/users/TestTechNick4101728", answer->profileUrl());
  ASSERT_EQ("http://images.gamenet.dev/pics/user/avatar/small/empty2.jpg", answer->smallAvatarUrl());
  ASSERT_EQ("http://images.gamenet.dev/pics/user/avatar/medium/empty2.jpg", answer->mediumAvatarUrl());
  ASSERT_EQ("http://images.gamenet.dev/pics/user/avatar/large/empty2.jpg", answer->largeAvatarUrl());
  ASSERT_EQ("steam:0:123123", answer->steamId());
  ASSERT_EQ(2, answer->sex());
}

TEST_F(GetUserMainInfoTest, successNetworkTest)
{
  GetUserMainInfo command;
  
  executeWithAuth(&command);

  UserMainInfoResponse *response = command.response();
  ASSERT_EQ("0", response->marketingId());
  ASSERT_EQ("gnaunittest", response->nickname());
  ASSERT_EQ("gnaunittest", response->nametech());
  ASSERT_EQ("http://www.gamenet.ru/users/gnaunittest", response->profileUrl());
  ASSERT_EQ("http://images.gamenet.ru/pics/user/avatar/small/60/48/63/400001000001634860.jpg", response->smallAvatarUrl());
  ASSERT_EQ("http://images.gamenet.ru/pics/user/avatar/medium/60/48/63/400001000001634860.jpg", response->mediumAvatarUrl());
  ASSERT_EQ("http://images.gamenet.ru/pics/user/avatar/large/60/48/63/400001000001634860.jpg", response->largeAvatarUrl());
  ASSERT_EQ(2, response->sex());
}