#include <RestApi/CommandBase.h>
#include <gtest/gtest.h>

class CommandTest : public ::testing::Test
{
public:
    void execute(P1::RestApi::CommandBase *command);
    void executeWithAuth(P1::RestApi::CommandBase *command);
};

