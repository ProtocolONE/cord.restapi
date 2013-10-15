#include <CommandTest.h>

#include <RestApi/Commands/Games/GetCSServerList.h>

#include <QtCore/QString>
#include <QtXml/QDomDocument>

class CSServerListTest : public CommandTest
{
};

//TEST_F(CSServerListTest, successNetworkTest) 
//{
//  GGS::RestApi::Commands::Games::GetCSServerList serverList;
//  execute(&serverList);
//
//  ASSERT_EQ(0, serverList.errorCode());
//  ASSERT_TRUE(serverList.getServers().size());
//}

TEST_F(CSServerListTest, successLocalTest) 
{
  QString testResponse("<response>"
                          "<result>" 
                            "<row>"
                              "<server>195.239.171.195:27015</server>"
                              "<usage>9</usage>"
                            "</row>"
                            "<row>"
                              "<server>195.239.171.194:27015</server>"
                              "<usage>11</usage>"
                            "</row>"
                          "</result>" 
                        "</response>");

  QDomDocument xmlResponse;
  xmlResponse.setContent(testResponse);
                          
  GGS::RestApi::Commands::Games::GetCSServerList serverList;
  serverList.callMethod(xmlResponse);

  ASSERT_TRUE(serverList.getServers().size());
}