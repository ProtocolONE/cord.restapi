#include "Auth/Vkontakte/VkontakteAuth.h"
#include "Auth/GenericAuth.h"
#include "Auth/AuthManager.h"
#include "Auth/AuthManagerViewModel.h"

#include <QtCore/QDebug>
#include <QtCore/QObject>
#include <QtGui/QApplication>
#include <QtGui/QGraphicsObject>
#include <QtDeclarative/QDeclarativeView>
#include <QtDeclarative/QDeclarativeContext>
#include <QtDeclarative/QDeclarativeEngine>

//#include "AuthManagerViewModel.h"

#ifdef _DEBUG
  #pragma comment(lib, "RestApiX86d.lib")
#else
  #pragma comment(lib, "RestApiX86.lib")
#endif 
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    /*
    //QString root = app.applicationDirPath();
    //QString imageFormatsPath = root;
    //root.append("/plugins");
    //app.addLibraryPath(root);
    //qDebug() << app.libraryPaths();

    //QUrl url(QUrl::fromLocalFile("qGNA.Main/qGNA_Main.qml"));

    using GGS::RestApi::Auth::AuthManagerViewModel;
    qmlRegisterType<AuthManagerViewModel>("qGNA.Library", 1, 0, "AuthManagerViewModel");

    QUrl url(QUrl::fromLocalFile("qml/main.qml"));
    QDeclarativeView *nQMLContainer = new QDeclarativeView(url);       
    nQMLContainer->setAlignment(Qt::AlignCenter);                                                                               
    nQMLContainer->setResizeMode(QDeclarativeView::SizeRootObjectToView);                                                       

    nQMLContainer->showNormal();
    
    GGS::RestApi::Auth::AuthManager authManger;

    GGS::RestApi::Auth::Vkontakte::VkontakteAuth vkauth;
    vkauth.setApplicationId("2755495");
    vkauth.setAuthReturnPath("http://www-trunk.sabirov.dev/virality/auth");
    vkauth.setTitleUrlHost("gnlogin-trunk.sabirov.dev");
    authManger.registerMethod(&vkauth);

    GGS::RestApi::Auth::GenericAuth genericAuth;
    genericAuth.setAuthUrl("https://gnlogin.gamenet.dev/");
    authManger.registerMethod(&genericAuth);

    QObject *item = nQMLContainer->rootObject();
    qDebug() << QObject::connect(item, SIGNAL(authRequest(QString)), &authManger, SLOT(login(QString)));
    //qDebug() << QObject::connect(item, SIGNAL(authLoginChanged(QString)), &genericAuth, SLOT(setLogin(QString)));
    //qDebug() << QObject::connect(item, SIGNAL(authPasswordChanged(QString)), &genericAuth, SLOT(setPassword(QString)));

    AuthManagerViewModel* authModel = item->findChild<AuthManagerViewModel*>("authManager");


    //AuthManagerViewModel
    //AuthManagerViewModel authModel;
    authModel->setAuthManager(&authManger);
    authModel->setGenericAuth(&genericAuth);

    qDebug() << QObject::connect(&authManger, SIGNAL(started()), authModel, SLOT(managerAuthStarted()));
    qDebug() << QObject::connect(&authManger, SIGNAL(finishedSuccessfully()), authModel, SLOT(managerAuthFinished()));
    qDebug() << QObject::connect(&authManger, SIGNAL(error(int)), authModel, SLOT(managerAuthError(int)));

    //nQMLContainer->rootContext()->setContextProperty("authModel", &authModel);
    */
    return app.exec();
}
