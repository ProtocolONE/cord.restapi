#include <RestApi/Auth/RegistryCredentialStorage.h>
#include <RestApi/GameNetCredential.h>

#include <gtest/gtest.h>

using GGS::RestApi::Auth::RegistryCredentialStorage;
using GGS::RestApi::GameNetCredential;

class RegistryCredentialStorageTest : public ::testing::Test
{
public:
  void basicSaveLoadTest(RegistryCredentialStorage &storage)
  {
    GameNetCredential credential;
    QString userId("123123123");
    QString appKey("jk1rghksdfgnsdjklfgnsdjklfgn34");
    QString cookie("djkflsghui2n5489dfjkln12093=-12mfsdf1=12+123");
    credential.setUserId(userId);
    credential.setAppKey(appKey);
    credential.setCookie(cookie);

    GameNetCredential credential1;
    ASSERT_FALSE(storage.tryLoad(credential1));

    storage.save(credential);

    GameNetCredential credential2;
    ASSERT_TRUE(storage.tryLoad(credential2));

    ASSERT_EQ(0, credential.userId().compare(credential2.userId()));
    ASSERT_EQ(0, credential.appKey().compare(credential2.appKey()));
    ASSERT_EQ(0, credential.cookie().compare(credential2.cookie()));

    storage.reset();

    GameNetCredential credential3;
    ASSERT_FALSE(storage.tryLoad(credential3));
  }
};

TEST_F(RegistryCredentialStorageTest, saveLoad)
{
  RegistryCredentialStorage storage;
  storage.reset();
  
  basicSaveLoadTest(storage);
}

TEST_F(RegistryCredentialStorageTest, saveLoadCustomPath)
{
  RegistryCredentialStorage storage("HKEY_CURRENT_USER\\Software\\GGS\\SomePath\\");
  storage.reset();

  basicSaveLoadTest(storage);
}