#ifndef _GGS_RESTAPI_REQUESTINTERFACE_H_
#define _GGS_RESTAPI_REQUESTINTERFACE_H_

//#include "CommandBaseInterface.h"
#include "CommandBaseArgumentWraper.h"
#include <QtCore/QString>
namespace GGS {
  namespace RestApi {


    /// <summary>Request interface. ���������� ������ ������� ���� ���������������.</summary>
    /// <remarks>Ilya.Tkachenko, 13.02.2012.</remarks>
    class RequestInterface{
    public:
      virtual ~RequestInterface() {};

       /// <summary>����������� ������ �� ������ ������ ��������. ��������� �������� � ������� ���������
       ///  ������, ��������� � �������.</summary>
       /// <remarks>Ilya.Tkachenko, 13.02.2012.</remarks>
       /// <param name="arguments">     [in] If non-null, the command.</param>
       virtual void execute(CommandBaseArgumentWraper &arguments) = 0;
    };

  }
}
#endif // _GGS_RESTAPI_REQUESTINTERFACE_H_