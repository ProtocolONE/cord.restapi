#include <RestApi/ProtocolOneCredential.h>
#include <RestApi/Command/CommandBase.h>

#include <QtCore/QMetaType>

#include <Windows.h>


namespace P1 {
  namespace RestApi {

    void registerTypes()
    {
      qRegisterMetaType<P1::RestApi::ProtocolOneCredential>("P1::RestApi::ProtocolOneCredential");
      qRegisterMetaType<P1::RestApi::Command::CommandBase::CommandResults>("P1::RestApi::Command::CommandBase::CommandResults");
    }
  
  }
}

