#include <CommandTest.h>

#include <RestApi/Commands/Games/GetMw2ServerList.h>
#include <RestApi/Commands/Games/Response/Mw2ServerListResponse.h>

#include <QtCore/QList>

class Mw2ServerListTest : public CommandTest
{
};

using namespace GGS::RestApi::Commands::Games;

TEST_F(Mw2ServerListTest, successNetworkTest) 
{
  GetMw2ServerList serverList;
  executeWithAuth(&serverList);
  
  ASSERT_EQ(0, serverList.errorCode());
  ASSERT_TRUE(serverList.getServers().size());
}

TEST_F(Mw2ServerListTest, successLocalTest) 
{
   QString testResponse(
     "<response>"
      "<serverList>"
        "<row>"
          "<id>2</id>"
          "<position>2</position>"
          "<name>Gloria</name>"
          "<address>31.25.225.134:3724</address>"
          "<pin>1</pin>"
          "<status>2</status>"
        "</row>"
        "<row>"
          "<id>1</id>"
          "<position>1</position>"
          "<name>Animus</name>"
          "<address>31.25.225.130:3724</address>"
          "<pin>0</pin>"
          "<status>0</status>"
        "</row>"
      "</serverList>"
      "<charList>"
        "<row>"
          "<server>Gloria</server>"
          "<count>33</count>"
        "</row>"
        "</charList>"
    "</response>");

  QDomDocument xmlResponse;
  xmlResponse.setContent(testResponse);

  GetMw2ServerList serverList;
  serverList.callMethod(xmlResponse);

  QList<Response::Mw2ServerInfo> servers = serverList.getServers();
  ASSERT_EQ(2, servers.size());
  
  ASSERT_EQ(2, servers[0].id());
  ASSERT_EQ(2, servers[0].position());
  ASSERT_EQ("Gloria", servers[0].name());
  ASSERT_EQ("31.25.225.134:3724", servers[0].address());
  ASSERT_EQ(true, servers[0].isPinned());
  ASSERT_EQ(2, servers[0].status());
  ASSERT_EQ(33, servers[0].charCount());

  ASSERT_EQ(1, servers[1].id());
  ASSERT_EQ(1, servers[1].position());
  ASSERT_EQ("Animus", servers[1].name());
  ASSERT_EQ("31.25.225.130:3724", servers[1].address());
  ASSERT_EQ(false, servers[1].isPinned());
  ASSERT_EQ(0, servers[1].status());
  ASSERT_EQ(0, servers[1].charCount());
}