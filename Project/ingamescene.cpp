#include "ingamescene.h"



InGameScene::InGameScene(QObject *parent, const QRect rect) : QGraphicsScene(parent),
                                                              m_rect(rect),
                                                              m_greta(new Greta(this)),
                                                              m_firstFrame(false)

{

    addItem(new Background(this, 0, -380));

    m_elapsedTimer = new QElapsedTimer();

    m_greta = new Greta(this, 750, 0, m_elapsedTimer);

    m_entitiesList = new QList<Entity*>();
    addItemToScene(m_greta);
    addItemToScene(new Platform(this, 0, 600, platformType::FLOOR1));

    setSceneRect(0, -250, 30000, 880);
}

InGameScene::~InGameScene()
{
    for (const auto &entity : *m_entitiesList)
        delete entity;
    delete m_entitiesList;
    delete m_elapsedTimer;
    for (const auto &graphicsItem : items())
        delete graphicsItem;

}

void InGameScene::initEnnemies()
{ //350 | 140
    //m_entitiesList->append(new Platform(this, 0, 600, platformType::DEFAULT_FLOOR));

    addItemToScene(new Platform(this, 0, 600, platformType::FLOOR1)); //ENNEMIES_POS = 2
    addItemToScene(new Platform(this, 4729, 600, platformType::FLOOR1)); //ENNEMIES_POS = 3
    addItemToScene(new Platform(this, 11115, 600, platformType::FLOOR1)); //ENNEMIES_POS = 4
    addItemToScene(new Platform(this, 16500, 600, platformType::FLOOR1)); //ENNEMIES_POS = 5
    addItemToScene(new Platform(this, 20615, 600, platformType::FLOOR1)); //ENNEMIES_POS = 6

    addItemToScene(new Platform(this, 600, 300, platformType::PLATFORMGREY)); //ENNEMIES_POS = 7
    addItemToScene(new Platform(this, 9000, 350, platformType::FLYINGFLOOR1)); //ENNEMIES_POS = 8
    addItemToScene(new Platform(this, 9800, 200, platformType::FLYINGFLOOR1)); //ENNEMIES_POS = 9
    addItemToScene(new Platform(this, 10600, 350, platformType::FLYINGFLOOR1)); //ENNEMIES_POS = 10
    addItemToScene(new Platform(this, 15300, -150, platformType::FLYINGFLOOR1)); //ENNEMIES_POS = 11
    addItemToScene(new Platform(this, 15700, 400, platformType::FLYINGFLOOR1)); //ENNEMIES_POS = 12
    addItemToScene(new Platform(this, 16050, -150, platformType::FLYINGFLOOR1)); //ENNEMIES_POS = 13

    addItemToScene(new Platform(this, 3300, 300, platformType::SHORTPIPE)); //ENNEMIES_POS = 14
    addItemToScene(new Platform(this, 3735, 200, platformType::LARGEPIPE)); //ENNEMIES_POS = 15
    addItemToScene(new Platform(this, 7200, 300, platformType::SHORTPIPE)); //ENNEMIES_POS = 16
    addItemToScene(new Platform(this, 8150, 300, platformType::SHORTPIPE)); //ENNEMIES_POS = 17
    addItemToScene(new Platform(this, 20615, -480, platformType::GRID)); //ENNEMIES_POS = 18
    //qDebug() << "ENNEMIES_POS = " << m_entitiesList->length();
    addItemToScene(new TrumpetCAC(this, 600-TRUMPETCAC_HEIGHT, 1950, 0));
    addItemToScene(new TrumpetCAC(this, 200-TRUMPETCAC_HEIGHT, 3325, 0));
    addItemToScene(new TrumpetDIS(this, 600-TRUMPETDIS_HEIGHT, 5250, 0));
    addItemToScene(new TrumpetCAC(this, 600-TRUMPETCAC_HEIGHT, 7450, 0));
    addItemToScene(new TrumpetCAC(this, 600-TRUMPETCAC_HEIGHT, 8000, 0));
    addItemToScene(new TrumpetDIS(this, 350-TRUMPETDIS_HEIGHT, 9100, 0));
    addItemToScene(new TrumpetCAC(this, 200-TRUMPETCAC_HEIGHT, 10000, 0));
    addItemToScene(new TrumpetDIS(this, 350-TRUMPETDIS_HEIGHT, 10850, 0));
    addItemToScene(new TrumpetDIS(this, -150-TRUMPETDIS_HEIGHT, 15425, 0));
    addItemToScene(new TrumpetDIS(this, -150-TRUMPETDIS_HEIGHT, 16175, 0));
    addItemToScene(new TrumpetCAC(this, 600-TRUMPETCAC_HEIGHT, 18500, 0));


    addItemToScene(new Trumpet(this, 600-TRUMPET1_HEIGHT, 23000, 0, m_elapsedTimer));
}

void InGameScene::deleteEnnemies()
{
    qsizetype length = m_entitiesList->length();
    for (qsizetype i = 1; i < length; i++)
    {
        removeItem(m_entitiesList->at(1));
        m_entitiesList->removeAt(1);
    }
}

void InGameScene::addItemToScene(Entity *item)
{
    m_entitiesList->append(item);;
    addItem(item);
}

void InGameScene::restart()
{
    deleteEnnemies();
    initEnnemies();
    qgraphicsitem_cast<Background*>(items().at(items().size() - 1))->setPos(0, -380);
    m_greta->setPosition(750, 0, 600-TRUMPETCAC_HEIGHT);
    m_greta->canFall(true);
    if (!m_firstFrame)
    {
        m_firstFrame = true;
        m_elapsedTimer->start();
    }
}
