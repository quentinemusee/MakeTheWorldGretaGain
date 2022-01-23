#include <QApplication>
#include <QDebug>

#include "ingamescene.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QGraphicsScene *scene = new InGameScene(NULL, QGuiApplication::primaryScreen()->geometry());

    QGraphicsView *view = new MainWindow(scene);
    view->setMinimumSize(QGuiApplication::primaryScreen()->geometry().width(), QGuiApplication::primaryScreen()->geometry().height());
    view->show();

    return a.exec();
}
