#include <RestApi/ProtocolOneCredential.h>
#include <RestApi/CommandBase.h>

#include <QtCore/QMetaType>

namespace P1 {
  namespace RestApi {

    void registerTypes()
    {
      qRegisterMetaType<P1::RestApi::CommandBase::Error>("P1::RestApi::CommandBase::Error");
      qRegisterMetaType<P1::RestApi::ProtocolOneCredential>("P1::RestApi::ProtocolOneCredential");                                 
      qRegisterMetaType<P1::RestApi::CommandBase::CommandResults>("P1::RestApi::CommandBase::CommandResults");
    }
  }
}

