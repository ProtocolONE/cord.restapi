#include "gtest/gtest.h"
#include "MemoryLeaksChecker.h"

#include "CommandBaseInterface.h"
#include "Commands/Service/GetDetailedServices.h"

class GetDetailedServicesTest : public ::testing::Test{
public:
  GetDetailedServicesTest() {
    this->leakChecker.start();
  }

  ~GetDetailedServicesTest() {
    this->leakChecker.finish();
    if(this->leakChecker.isMemoryLeaks())
      failTest("Memory leak detected!"); 
  }

  QString getNormalServiceInfoExample() 
  {
    return QString::fromLocal8Bit("<?xml version=\"1.0\" encoding=\"utf-8\"?>																				" \
      "<response>                                                                                                         " \
      "	<serviceList>                                                                                                   " \
      "		<row>                                                                                                       " \
      "			<serv_id>300002010000000000</serv_id>                                                                   " \
      "			<serv_name>Aika</serv_name>                                                                             " \
      "			<serv_url>http://gamenet.ru/games/aika</serv_url>                                                       " \
      "			<serv_desc>Aika</serv_desc>                                                                             " \
      "			<serv_sub_status>free</serv_sub_status>                                                                 " \
      "			<serv_authtypeid>token</serv_authtypeid>                                                                " \
      "		</row>                                                                                                      " \
      "		<row>                                                                                                       " \
      "			<serv_id>300003010000000000</serv_id>                                                                   " \
      "			<serv_name>BS</serv_name>                                                                               " \
      "			<serv_url>http://gamenet.ru/games/bs</serv_url>                                                         " \
      "			<serv_desc></serv_desc>                                                                                 " \
      "			<serv_sub_status>free</serv_sub_status>                                                                 " \
      "			<serv_authtypeid>token</serv_authtypeid>                                                                " \
      "                                                                                                                   " \
      "		</row>                                                                                                      " \
      "	</serviceList>                                                                                                  " \
      "	<serviceDetail>                                                                                                 " \
      "		<row>                                                                                                       " \
      "			<servinfo_serv_id>300002010000000000</servinfo_serv_id>                                                 " \
      "			<servinfo_value>aikalauncher.exe</servinfo_value>                                                       " \
      "			<ref_name>Приложение для запуска сервиса</ref_name>                                                     " \
      "			<ref_code>launcher</ref_code>																			" \
      "                                                                                                                   " \
      "		</row>                                                                                                      " \
      "		<row>                                                                                                       " \
      "			<servinfo_serv_id>300002010000000000</servinfo_serv_id>                                                 " \
      "			<servinfo_value>631</servinfo_value>                                                                    " \
      "			<ref_name>GameID</ref_name>                                                                             " \
      "			<ref_code>gameid</ref_code>                                                                             " \
      "                                                                                                                   " \
      "		</row>                                                                                                      " \
      "		<row>                                                                                                       " \
      "			<servinfo_serv_id>300002010000000000</servinfo_serv_id>                                                 " \
      "			<servinfo_value>http://fs0.gamenet.ru/update/aika/</servinfo_value>                                     " \
      "			<ref_name>Ссылка на обновление клиента (http)</ref_name>                                                " \
      "			<ref_code>update_http</ref_code>                                                                        " \
      "                                                                                                                   " \
      "		</row>                                                                                                      " \
      "		<row>                                                                                                       " \
      "			<servinfo_serv_id>300002010000000000</servinfo_serv_id>                                                 " \
      "			<servinfo_value>http://fs0.gamenet.ru/update/aika/</servinfo_value>                                     " \
      "			<ref_name>Ссылка на клиент (http)</ref_name>                                                            " \
      "			<ref_code>client_http</ref_code>                                                                        " \
      "                                                                                                                   " \
      "		</row>                                                                                                      " \
      "		<row>                                                                                                       " \
      "			<servinfo_serv_id>300002010000000000</servinfo_serv_id>                                                 " \
      "			<servinfo_value>http://fs0.gamenet.ru/update/aika/</servinfo_value>                                     " \
      "			<ref_name>Ссылка на клиент (torrent)</ref_name>                                                         " \
      "			<ref_code>client_torrent</ref_code>                                                                     " \
      "                                                                                                                   " \
      "		</row>                                                                                                      " \
      "		<row>                                                                                                       " \
      "			<servinfo_serv_id>300002010000000000</servinfo_serv_id>                                                 " \
      "			<servinfo_value>http://www.gamenet.ru/register/launcher/aika/</servinfo_value>                          " \
      "			<ref_name>Cсылка для незарегистрированных пользователей</ref_name>                                      " \
      "			<ref_code>noreg_url</ref_code>                                                                          " \
      "                                                                                                                   " \
      "		</row>                                                                                                      " \
      "		<row>                                                                                                       " \
      "			<servinfo_serv_id>300002010000000000</servinfo_serv_id>                                                 " \
      "			<servinfo_value>AIKA</servinfo_value>                                                                   " \
      "			<ref_name></ref_name>                                                                                   " \
      "			<ref_code>shortcutname</ref_code>                                                                       " \
      "                                                                                                                   " \
      "		</row>                                                                                                      " \
      "		<row>                                                                                                       " \
      "			<servinfo_serv_id>300002010000000000</servinfo_serv_id>                                                 " \
      "			<servinfo_value>http://www.gamenet.ru/games/aika/screenshots</servinfo_value>                           " \
      "			<ref_name>Сраница для пользователя не играющего в данную игру</ref_name>                                " \
      "			<ref_code>AuthUserSite1</ref_code>                                                                      " \
      "                                                                                                                   " \
      "		</row>                                                                                                      " \
      "		<row>                                                                                                       " \
      "			<servinfo_serv_id>300002010000000000</servinfo_serv_id>                                                 " \
      "			<servinfo_value>5</servinfo_value>                                                                      " \
      "			<ref_name>ServiceIndex</ref_name>                                                                       " \
      "			<ref_code>ServiceIndex</ref_code>                                                                       " \
      "                                                                                                                   " \
      "		</row>                                                                                                      " \
      "		<row>                                                                                                       " \
      "			<servinfo_serv_id>300002010000000000</servinfo_serv_id>                                                 " \
      "			<servinfo_value>http://www.gamenet.ru/games/aika</servinfo_value>                                       " \
      "			<ref_name>Сраница для пользователя играющего в данную игру</ref_name>                                   " \
      "			<ref_code>AuthUserSite2</ref_code>                                                                      " \
      "                                                                                                                   " \
      "		</row>                                                                                                      " \
      "		<row>                                                                                                       " \
      "			<servinfo_serv_id>300002010000000000</servinfo_serv_id>                                                 " \
      "			<servinfo_value>Aika Online</servinfo_value>                                                            " \
      "			<ref_name>DisplayName</ref_name>                                                                        " \
      "			<ref_code>DisplayName</ref_code>                                                                        " \
      "                                                                                                                   " \
      "		</row>                                                                                                      " \
      "		<row>                                                                                                       " \
      "			<servinfo_serv_id>300003010000000000</servinfo_serv_id>                                                 " \
      "			<servinfo_value>http://www.gamenet.ru/games/bs</servinfo_value>                                         " \
      "			<ref_name>Сраница для пользователя играющего в данную игру</ref_name>                                   " \
      "			<ref_code>AuthUserSite2</ref_code>                                                                      " \
      "                                                                                                                   " \
      "		</row>                                                                                                      " \
      "		<row>                                                                                                       " \
      "			<servinfo_serv_id>300003010000000000</servinfo_serv_id>                                                 " \
      "			<servinfo_value>BS.ru</servinfo_value>                                                                  " \
      "			<ref_name>DisplayName</ref_name>                                                                        " \
      "			<ref_code>DisplayName</ref_code>                                                                        " \
      "                                                                                                                   " \
      "		</row>                                                                                                      " \
      "		<row>                                                                                                       " \
      "			<servinfo_serv_id>300003010000000000</servinfo_serv_id>                                                 " \
      "			<servinfo_value>100</servinfo_value>                                                                    " \
      "			<ref_name>ServiceIndex</ref_name>                                                                       " \
      "			<ref_code>ServiceIndex</ref_code>                                                                       " \
      "                                                                                                                   " \
      "		</row>                                                                                                      " \
      "		<row>                                                                                                       " \
      "			<servinfo_serv_id>300003010000000000</servinfo_serv_id>                                                 " \
      "			<servinfo_value>http://www.gamenet.ru/games/bs/screenshots</servinfo_value>                             " \
      "			<ref_name>Сраница для пользователя не играющего в данную игру</ref_name>                                " \
      "			<ref_code>AuthUserSite1</ref_code>                                                                      " \
      "                                                                                                                   " \
      "		</row>                                                                                                      " \
      "		<row>                                                                                                       " \
      "			<servinfo_serv_id>300003010000000000</servinfo_serv_id>                                                 " \
      "			<servinfo_value>BS.ru</servinfo_value>                                                                  " \
      "			<ref_name></ref_name>                                                                                   " \
      "			<ref_code>shortcutname</ref_code>                                                                       " \
      "                                                                                                                   " \
      "		</row>                                                                                                      " \
      "		<row>                                                                                                       " \
      "			<servinfo_serv_id>300003010000000000</servinfo_serv_id>                                                 " \
      "			<servinfo_value>bslauncher.exe</servinfo_value>                                                         " \
      "			<ref_name>Приложение для запуска сервиса</ref_name>                                                     " \
      "			<ref_code>launcher</ref_code>                                                                           " \
      "																													" \
      "		</row>                                                                                                      " \
      "		<row>                                                                                                       " \
      "			<servinfo_serv_id>300003010000000000</servinfo_serv_id>                                                 " \
      "			<servinfo_value>71</servinfo_value>                                                                     " \
      "			<ref_name>GameID</ref_name>                                                                             " \
      "			<ref_code>gameid</ref_code>                                                                             " \
      "                                                                                                                   " \
      "		</row>                                                                                                      " \
      "		<row>                                                                                                       " \
      "			<servinfo_serv_id>300003010000000000</servinfo_serv_id>                                                 " \
      "			<servinfo_value>http://fs0.gamenet.ru/update/bs/</servinfo_value>                                       " \
      "			<ref_name>Ссылка на обновление клиента (http)</ref_name>                                                " \
      "			<ref_code>update_http</ref_code>                                                                        " \
      "                                                                                                                   " \
      "		</row>                                                                                                      " \
      "		<row>                                                                                                       " \
      "			<servinfo_serv_id>300003010000000000</servinfo_serv_id>                                                 " \
      "			<servinfo_value>http://fs0.gamenet.ru/update/bs/</servinfo_value>                                       " \
      "			<ref_name>Ссылка на клиент (http)</ref_name>                                                            " \
      "			<ref_code>client_http</ref_code>                                                                        " \
      "                                                                                                                   " \
      "		</row>                                                                                                      " \
      "		<row>                                                                                                       " \
      "			<servinfo_serv_id>300003010000000000</servinfo_serv_id>                                                 " \
      "			<servinfo_value>http://fs0.gamenet.ru/update/bs/</servinfo_value>                                       " \
      "			<ref_name>Ссылка на клиент (torrent)</ref_name>                                                         " \
      "			<ref_code>client_torrent</ref_code>                                                                     " \
      "                                                                                                                   " \
      "		</row>                                                                                                      " \
      "		<row>                                                                                                       " \
      "			<servinfo_serv_id>300003010000000000</servinfo_serv_id>                                                 " \
      "			<servinfo_value>http://www.gamenet.ru/register/launcher/bs/</servinfo_value>                            " \
      "			<ref_name>Cсылка для незарегистрированных пользователей</ref_name>                                      " \
      "			<ref_code>noreg_url</ref_code>                                                                          " \
      "                                                                                                                   " \
      "		</row>                                                                                                      " \
      "	</serviceDetail>                                                                                                " \
      "</response>                                                                                                        ");

  }

private:
  void failTest(const char* message) 
  { 
    FAIL() << message; 
  }

  MemoryLeaksChecker leakChecker;
};

TEST_F(GetDetailedServicesTest, ParserTest)
{
  using GGS::RestApi::Commands::Service::GetDetailedServices;
  using GGS::RestApi::CommandBaseInterface;
  using GGS::RestApi::Commands::Service::Response::DetailedServicesResponse;
  using GGS::RestApi::Commands::Service::Response::DetailedServiceInfo;

  GetDetailedServices *cmd = new GetDetailedServices();

  cmd->resultCallback(CommandBaseInterface::CommandResults::NoError, this->getNormalServiceInfoExample());
  
  DetailedServicesResponse* response = cmd->response();
  QMap<quint64, DetailedServiceInfo *> serviceList = response->serviceList();
  DetailedServiceInfo *aikaInfo = serviceList[300002010000000000];
  ASSERT_EQ(300002010000000000, aikaInfo->id());
  ASSERT_EQ(0, QString("Aika").compare(aikaInfo->name()) );
  ASSERT_EQ(0, QString("http://gamenet.ru/games/aika").compare(aikaInfo->serviceUrl()) );
  
  QString tmp;
  ASSERT_TRUE(aikaInfo->detailedInfo(QString("launcher"), tmp));
  ASSERT_EQ(0, QString("aikalauncher.exe").compare(tmp) );

  ASSERT_TRUE(aikaInfo->detailedInfo(QString("gameid"), tmp));
  ASSERT_EQ(0, QString("631").compare(tmp) );

  ASSERT_TRUE(aikaInfo->detailedInfo(QString("update_http"), tmp));
  ASSERT_EQ(0, QString("http://fs0.gamenet.ru/update/aika/").compare(tmp) );

  ASSERT_TRUE(aikaInfo->detailedInfo(QString("client_http"), tmp));
  ASSERT_EQ(0, QString("http://fs0.gamenet.ru/update/aika/").compare(tmp) );

  ASSERT_TRUE(aikaInfo->detailedInfo(QString("client_torrent"), tmp));
  ASSERT_EQ(0, QString("http://fs0.gamenet.ru/update/aika/").compare(tmp) );

  ASSERT_TRUE(aikaInfo->detailedInfo(QString("noreg_url"), tmp));
  ASSERT_EQ(0, QString("http://www.gamenet.ru/register/launcher/aika/").compare(tmp) );

  ASSERT_TRUE(aikaInfo->detailedInfo(QString("shortcutname"), tmp));
  ASSERT_EQ(0, QString("AIKA").compare(tmp) );

  ASSERT_TRUE(aikaInfo->detailedInfo(QString("AuthUserSite1"), tmp));
  ASSERT_EQ(0, QString("http://www.gamenet.ru/games/aika/screenshots").compare(tmp) );

  ASSERT_TRUE(aikaInfo->detailedInfo(QString("ServiceIndex"), tmp));
  ASSERT_EQ(0, QString("5").compare(tmp) );

  ASSERT_TRUE(aikaInfo->detailedInfo(QString("AuthUserSite2"), tmp));
  ASSERT_EQ(0, QString("http://www.gamenet.ru/games/aika").compare(tmp) );

  ASSERT_TRUE(aikaInfo->detailedInfo(QString("DisplayName"), tmp));
  ASSERT_EQ(0, QString("Aika Online").compare(tmp) );


  aikaInfo = serviceList[300003010000000000];
  ASSERT_EQ(300003010000000000, aikaInfo->id());
  ASSERT_EQ(0, QString("BS").compare(aikaInfo->name()) );
  ASSERT_EQ(0, QString("http://gamenet.ru/games/bs").compare(aikaInfo->serviceUrl()) );

  ASSERT_TRUE(aikaInfo->detailedInfo(QString("launcher"), tmp));
  ASSERT_EQ(0, QString("bslauncher.exe").compare(tmp) );

  ASSERT_TRUE(aikaInfo->detailedInfo(QString("gameid"), tmp));
  ASSERT_EQ(0, QString("71").compare(tmp) );

  ASSERT_TRUE(aikaInfo->detailedInfo(QString("update_http"), tmp));
  ASSERT_EQ(0, QString("http://fs0.gamenet.ru/update/bs/").compare(tmp) );

  ASSERT_TRUE(aikaInfo->detailedInfo(QString("client_http"), tmp));
  ASSERT_EQ(0, QString("http://fs0.gamenet.ru/update/bs/").compare(tmp) );

  ASSERT_TRUE(aikaInfo->detailedInfo(QString("client_torrent"), tmp));
  ASSERT_EQ(0, QString("http://fs0.gamenet.ru/update/bs/").compare(tmp) );

  ASSERT_TRUE(aikaInfo->detailedInfo(QString("noreg_url"), tmp));
  ASSERT_EQ(0, QString("http://www.gamenet.ru/register/launcher/bs/").compare(tmp) );

  ASSERT_TRUE(aikaInfo->detailedInfo(QString("shortcutname"), tmp));
  ASSERT_EQ(0, QString("BS.ru").compare(tmp) );

  ASSERT_TRUE(aikaInfo->detailedInfo(QString("AuthUserSite1"), tmp));
  ASSERT_EQ(0, QString("http://www.gamenet.ru/games/bs/screenshots").compare(tmp) );

  ASSERT_TRUE(aikaInfo->detailedInfo(QString("ServiceIndex"), tmp));
  ASSERT_EQ(0, QString("100").compare(tmp) );

  ASSERT_TRUE(aikaInfo->detailedInfo(QString("AuthUserSite2"), tmp));
  ASSERT_EQ(0, QString("http://www.gamenet.ru/games/bs").compare(tmp) );

  delete cmd;
  // UNDONE check parsed object
}