#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QMediaPlayer>
#include <QAudioOutput>

#include <QGraphicsView>
#include "ingamescene.h"
#include "update.h"

class MainWindow : public QGraphicsView
{
    Q_OBJECT
    public :
        /* Constructors */
        explicit MainWindow(QGraphicsScene *scene = nullptr, QWidget *parent = nullptr);

        /* Destructors */
        virtual ~MainWindow();

    public slots :
        /* Update functions */
        void updateX();

    private :
        Update *m_update;
        InGameScene* m_scene;
        QMediaPlayer m_player;
        QAudioOutput m_audioOutput;
};

#endif // MAINWINDOW_H
