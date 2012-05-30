#include "gtest/gtest.h"

#include <RestApi/Commands/Service/Response/DetailedServiceInfo.h>

#include <QtXml/QDomDocument>
#include <QtXml/QDomElement>

class DetailedServiceInfoTest : public ::testing::Test
{
public:
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
      "			<servinfo_value>http://files.gamenet.ru/update/aika/</servinfo_value>                                   " \
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
};

TEST_F(DetailedServiceInfoTest, deserializeMainInfoTest)
{
  using GGS::RestApi::Commands::Service::Response::DetailedServiceInfo;

  QDomDocument doc;
  doc.setContent(this->getNormalServiceInfoExample());

  QDomElement responseElement = doc.documentElement();
  QString rootName = responseElement.tagName();

  QDomElement firstServiceInfoElement = responseElement.firstChildElement("serviceList").firstChildElement("row");
  QString rootName1 = firstServiceInfoElement.tagName();

  DetailedServiceInfo info;

  info.deserializeMainInfo(firstServiceInfoElement);

  ASSERT_EQ(300002010000000000, info.id());
  ASSERT_EQ(0, QString("Aika").compare(info.name()) );
  ASSERT_EQ(0, QString("http://gamenet.ru/games/aika").compare(info.serviceUrl()) );

}