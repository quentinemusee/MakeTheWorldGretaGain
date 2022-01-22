#include "mainwindow.h"

bool lastCenterOn = false;
int verticalSettingsOffset = 0;

MainWindow::MainWindow(QGraphicsScene *scene, QWidget *parent) : QGraphicsView(scene, parent),
                                                                 m_update(new Update(this)),
                                                                 m_scene(qobject_cast<InGameScene *>(this->scene())),
                                                                 m_killAllTrumpetFlag(false)
{
    m_player.setAudioOutput(&m_audioOutput);
    m_audioOutput.setVolume(50);
    m_player.setSource(QUrl("qrc:/ressources/sounds/mainMusiqueS.mp3"));
    m_player.setLoops(QMediaPlayer::Infinite);
    m_player.play();
}

MainWindow::~MainWindow()
{
    delete m_update;
    delete m_scene;
}

void MainWindow::updateX()
{
    /* Variables */
    Greta *greta = m_scene->greta();
    QList<Entity*> *entitiesList = m_scene->entitiesList();
    bool centerFlag = (greta->efficientX() < (qsizetype) (size().width()/2 - GRETA_WIDTH/2));

    /* Background update */
    qgraphicsitem_cast<Background*>(m_scene->items().at(m_scene->items().size() - 1))->updateX(entitiesList, centerFlag);

    /* Greta update */
    if (greta->updateX(entitiesList, centerFlag))
    {
        // RESET LES ENNEMIES ET PLATFORMS;
        m_scene->restart();
        greta->canMove(true);
        verticalSettingsOffset = 0;
    }

    /* Ennemies, platforms and bullets update */
    for (qsizetype i = 1; i < entitiesList->length(); i++)
       entitiesList->at(i)->updateX(entitiesList);

    /* Setting offset */
    if (!centerFlag && lastCenterOn)
        verticalSettingsOffset += 6*(1+greta->shiftFlag());
    lastCenterOn = centerFlag;

    /* Kill all ennemies except the boss */
    if (!m_killAllTrumpetFlag && greta->efficientX() >= 20514 && greta->attackCooldownCounter())
    {
        m_killAllTrumpetFlag = true;
        for (qsizetype i = 1; i < entitiesList->length();)
        {
            if (qobject_cast<TrumpetDIS*>(entitiesList->at(i)) != nullptr || qobject_cast<TrumpetCAC*>(entitiesList->at(i)) != nullptr)
                entitiesList->at(i)->die(entitiesList);
            else
                i++;
        }
    }

    /* Repaint */
    viewport()->repaint();

    /* Center the camera */
    if (greta->fitInView())
        fitInView(GRETA_WIDTH/8 + verticalSettingsOffset, 0, size().width(), size().height());

    /* Center the background */
    if (centerFlag)
        qgraphicsitem_cast<Background*>(m_scene->items().at(m_scene->items().size() - 1))->setPos(verticalSettingsOffset, -380);
}
