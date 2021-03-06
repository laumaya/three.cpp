#include <QGuiApplication>
#include <QQmlEngine>
#include <QQmlContext>
#include <QQmlComponent>
#include <QDebug>
#include <threepp/quick/Three.h>

int main(int argc, char *argv[]) {
  QGuiApplication app(argc, argv);
  QQmlEngine qmlEngine;
  QQmlContext *mainQmlContext = new QQmlContext(&qmlEngine);

  three::quick::init();

  QQmlComponent maincomponent(&qmlEngine);
  //maincomponent.loadUrl(QUrl("qrc:///geometries.qml"));
  //maincomponent.loadUrl(QUrl("qrc:///spotlight.qml"));
  //maincomponent.loadUrl(QUrl("qrc:///material_envmap.qml"));
  //maincomponent.loadUrl(QUrl("qrc:///orbit_controls.qml"));
  //maincomponent.loadUrl(QUrl("qrc:///3ds_model.qml"));
  //maincomponent.loadUrl(QUrl("qrc:///load_model.qml"));
  //maincomponent.loadUrl(QUrl("qrc:///voxelpainter.qml"));
  maincomponent.loadUrl(QUrl("qrc:///hemisphere.qml"));
  //maincomponent.loadUrl(QUrl("qrc:///cameras.qml"));

  if (maincomponent.isError()) {
    qCritical() << "error loading main screen: " << maincomponent.errorString();
    return -1;
  }

  maincomponent.create(mainQmlContext);
  int ret = app.exec();

  return ret;
}
