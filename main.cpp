#include <QApplication>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "weisscard.h"
#include "weisscardmodel.h"
#include "weisscardfullmodel.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    WeissCardModel deckModel;
    WeissCardFullModel collectionModel;

    QQmlApplicationEngine engine;
    WeissCard::registerQmlType();
    engine.rootContext()->setContextProperty("deckModel", &deckModel);
    engine.rootContext()->setContextProperty("collectionModel", &collectionModel);
    engine.rootContext()->setContextProperty("realDeck", deckModel.getDeck());
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    return app.exec();
}

