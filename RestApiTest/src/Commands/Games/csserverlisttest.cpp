#include "gtest/gtest.h"

#include "csserverlisttest.h"
#include <RestApi/Commands/Games/GetCSServerList.h>
#include <RestApi/HttpCommandRequest.h>

#include <QDomDocument>

CSServerListTest::CSServerListTest(QObject *parent)
    : QObject(parent)
{

}

CSServerListTest::~CSServerListTest()
{

}

const QString testResponse = "<response><result><row><server>195.239.171.195:27015</server><usage>9</usage></row><row><server>195.239.171.194:27015</server><usage>11</usage></row>";
/*		
<row>
			<server>77.220.187.58:27508</server>
			<usage>181</usage>

		</row>
		<row>
			<server>77.220.187.58:27506</server>
			<usage>190</usage>

		</row>
		<row>
			<server>77.220.187.58:27509</server>
			<usage>198</usage>

		</row>
		<row>
			<server>77.220.187.58:27505</server>
			<usage>254</usage>

		</row>
		<row>
			<server>77.220.187.58:27507</server>
			<usage>254</usage>

		</row>
		<row>
			<server>77.220.187.58:27504</server>
			<usage>300</usage>

		</row>
		<row>
			<server>77.220.187.58:27503</server>
			<usage>349</usage>

		</row>
		<row>
			<server>77.220.187.58:27502</server>
			<usage>354</usage>

		</row>
		<row>
			<server>212.76.139.141:27015</server>
			<usage>641</usage>

		</row>
		<row>
			<server>77.220.187.58:27501</server>
			<usage>714</usage>

		</row>";
        */
TEST(GetCSServerListTest, GetCSServerListTest1) 
{
  using GGS::RestApi::HttpRequest;
  using GGS::RestApi::HttpRequestInterface;
  HttpRequest http;
  HttpRequestInterface::ResultCodes resultCode;
  QString response = http.execute(QString("https://api.gamenet.ru/restapi"), QString("method=games.getCSServerList"), resultCode);

  GGS::RestApi::Commands::Games::GetCSServerList serverList;
  QDomDocument xmlResponse;
  xmlResponse.setContent(testResponse);
  serverList.callMethod(xmlResponse);

  ASSERT_TRUE(serverList.getServers().size());
}