#include <RestApi/CommandBase>
#include <gtest/gtest.h>

class CommandTest : public ::testing::Test
{
public:
    void execute(GGS::RestApi::CommandBase *command);
    void executeWithAuth(GGS::RestApi::CommandBase *command);
};

