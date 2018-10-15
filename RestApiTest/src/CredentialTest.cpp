#include <gtest/gtest.h>

#include <RestApi/ProtocolOneCredential.h>

using P1::RestApi::ProtocolOneCredential;

TEST(ProtocolOneCredential, Empty)
{
  ProtocolOneCredential credential;
  ASSERT_TRUE(credential.isEmpty());
  ASSERT_FALSE(credential.isValid());
}

TEST(ProtocolOneCredential, Normal)
{
  QString userId("5bbd9de33489d29c830fdb0d");
  QString jwt(
    "eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiJ9.eyJpYXQiOjE1MzkxNTM0MTEsImV4cCI6MTUzOTE1NTI"
    "xMSwicm9sZXMiOlsiUk9MRV9VU0VSIl0sImlkIjoiNWJiZDlkZTMzNDg5ZDI5YzgzMGZkYjBkIn0.SKo"
    "EfLk7b4GshpXWXobtQeF00XVjWh1vQDe41hWVtcHGf_qSEG3WqcRFsgRdWsJ1vBTBSHjmoSupxSdNyHY"
    "6lP04wlnaFwr7w5ofBVeNPaP78bX6qnXvmBpfrvRzLX2IQBJLw89CAqfiCDJgTZzJ9Gu9K8Vwygjwdtj"
    "qEhq3ugEbaBslO_dHQ-6rXwk5CnjsSTsTleyTERCIathB_Zl4L0UUXHgjXZ3gE_4CdTmuCnHjFOjdGmL"
    "td1v80ZXWyuQifbwL32QPV4FniRXCrI7zEEXcBJAlGwF0gPYeOht3G2wgpYw4rD0dADYEX1J5gtAnKuj"
    "xdULdvR1S6Xnq0Rt9rKAkC0OC2Gz9RjWfY92Kw-NPDeFlXHBEaIm0Q6XOvX9ctRSb5S7K4_FbPFTlIBQ"
    "nlzipWt7pXUH6ObSJw0y_ZsmBfvbL0nCgqyZzKCAYOo2T88gjhbdl7hivICjcVNWD6R1cU5llwEC85t2"
    "AyqLpZPDdgpuevwDjXOwCDJLylrYxTK5oL_bi-2fKLzxRqNNhAYQ3Hs4CpAMML1PqmcxKXApN8U7d1jx"
    "gteL8l0XIEK47ZjoyD2kXL9fHCK0HmDeY5GWv1yRpVPExLxATcQiHyTZJQ51vdnWxn1zx9bVU8ZUCuJg"
    "GwbZYB1oVSXNWH7t5y_2Bh6_dfmxeg3ITUWZ0kCI");
  QDateTime expiredTime = QDateTime::currentDateTimeUtc().addSecs(30);
  ProtocolOneCredential credential(jwt, expiredTime);
  ASSERT_EQ(jwt, credential.acccessTokent());
  ASSERT_FALSE(credential.isEmpty());
  ASSERT_TRUE(credential.isValid());
  ASSERT_EQ(userId, credential.userId());
}

TEST(ProtocolOneCredential, Invalid)
{
  QString userId("5bbd9de33489d29c830fdb0d");
  QString jwt(
    "eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiJ9.eyJpYXQiOjE1MzkxNTM0MTEsImV4cCI6MTUzOTE1NTI"
    "xMSwicm9sZXMiOlsiUk9MRV9VU0VSIl0sImlkIjoiNWJiZDlkZTMzNDg5ZDI5YzgzMGZkYjBkIn0.SKo"
    "EfLk7b4GshpXWXobtQeF00XVjWh1vQDe41hWVtcHGf_qSEG3WqcRFsgRdWsJ1vBTBSHjmoSupxSdNyHY"
    "6lP04wlnaFwr7w5ofBVeNPaP78bX6qnXvmBpfrvRzLX2IQBJLw89CAqfiCDJgTZzJ9Gu9K8Vwygjwdtj"
    "qEhq3ugEbaBslO_dHQ-6rXwk5CnjsSTsTleyTERCIathB_Zl4L0UUXHgjXZ3gE_4CdTmuCnHjFOjdGmL"
    "td1v80ZXWyuQifbwL32QPV4FniRXCrI7zEEXcBJAlGwF0gPYeOht3G2wgpYw4rD0dADYEX1J5gtAnKuj"
    "xdULdvR1S6Xnq0Rt9rKAkC0OC2Gz9RjWfY92Kw-NPDeFlXHBEaIm0Q6XOvX9ctRSb5S7K4_FbPFTlIBQ"
    "nlzipWt7pXUH6ObSJw0y_ZsmBfvbL0nCgqyZzKCAYOo2T88gjhbdl7hivICjcVNWD6R1cU5llwEC85t2"
    "AyqLpZPDdgpuevwDjXOwCDJLylrYxTK5oL_bi-2fKLzxRqNNhAYQ3Hs4CpAMML1PqmcxKXApN8U7d1jx"
    "gteL8l0XIEK47ZjoyD2kXL9fHCK0HmDeY5GWv1yRpVPExLxATcQiHyTZJQ51vdnWxn1zx9bVU8ZUCuJg"
    "GwbZYB1oVSXNWH7t5y_2Bh6_dfmxeg3ITUWZ0kCI");
  QDateTime expiredTime = QDateTime::currentDateTimeUtc().addSecs(-30);
  ProtocolOneCredential credential(jwt, expiredTime);
  ASSERT_EQ(jwt, credential.acccessTokent());
  ASSERT_FALSE(credential.isEmpty());
  ASSERT_FALSE(credential.isValid());
  ASSERT_EQ(userId, credential.userId());
}
