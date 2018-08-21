#include <CommandTest.h>
#include <RestApi/Commands/Service/GetHosts.h>

using P1::RestApi::Commands::Service::GetHosts;

class GetHostsTest : public CommandTest
{
};

TEST_F(GetHostsTest, successNetworkTest)
{
  P1::RestApi::Commands::Service::GetHosts cmd;

  execute(&cmd);

  ASSERT_TRUE(cmd.servicesData().count() > 0);

  QMap<QString, QString> value;
  Q_FOREACH(value, cmd.servicesData()) {
    ASSERT_TRUE(value.contains("serviceId"));
    ASSERT_TRUE(value.contains("gameId"));
    ASSERT_TRUE(value.contains("folderName"));
    ASSERT_TRUE(value.contains("torrentUrl"));
    ASSERT_TRUE(value.contains("hasDownloadPath"));
    ASSERT_TRUE(value.contains("isBrowserGame"));
    ASSERT_TRUE(value.contains("extractorType"));
    ASSERT_TRUE(value.contains("executeUrl"));
    ASSERT_TRUE(value.contains("dependencyList"));
    ASSERT_TRUE(value.contains("gameSize"));
    ASSERT_TRUE(value.contains("downloadHooks"));
    ASSERT_TRUE(value.contains("executorHooks"));
    ASSERT_TRUE(value.contains("isPublishedInApp"));
    ASSERT_TRUE(value.contains("iconInApp"));
  }
}