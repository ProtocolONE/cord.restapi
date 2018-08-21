#include <RestApi/GameNetCredential.h>
#include <RestApi/CommandBase.h>

#include <QtCore/QMetaType>

namespace P1 {
  namespace RestApi {

    void registerTypes()
    {
      qRegisterMetaType<P1::RestApi::CommandBase::Error>("P1::RestApi::CommandBase::Error");
      qRegisterMetaType<P1::RestApi::GameNetCredential>("P1::RestApi::GameNetCredential");                                 
      qRegisterMetaType<P1::RestApi::CommandBase::CommandResults>("P1::RestApi::CommandBase::CommandResults");
    }
  }
}

