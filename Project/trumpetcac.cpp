#include "trumpetcac.h"

TrumpetCAC::TrumpetCAC(QObject *parent, const qreal y, const qreal efficientX, const qreal efficientY) : Character(parent, efficientX, efficientY),
                                                                                                         m_isTriggered(false)
{
    resetFrameCounter(direction::LEFT);

    setPixmap(QPixmap(":/ressources/images/TrumpetCACS.png"));

    m_width = TRUMPETCAC_WIDTH;
    m_height = TRUMPETCAC_HEIGHT;

    m_spriteCounterLimit = TRUMPETCAC_SPRITE_COUNT_LIMIT;
    m_frameCounterLimit  = TRUMPETCAC_FRAME_COUNT_LIMIT;

    setPosition(efficientX, efficientY, y);
}

void TrumpetCAC::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0, 0, pixmap(), m_spriteCounter*TRUMPETCAC_WIDTH, (m_lastDirection == direction::LEFT)*TRUMPETCAC_HEIGHT, TRUMPETCAC_WIDTH, TRUMPETCAC_HEIGHT);
    //setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget);
    Q_UNUSED(option);
}

void TrumpetCAC::moveDirection(QList<Entity*> *entitiesList)
{
    if ((!m_isTriggered && (distance(entitiesList->at(0)) > 600)))
        return;

    if (abs(x() - (entitiesList->at(0))->x()) <= 5)
        return;

    m_isTriggered = true;
    short horizontalOffset = 3;

    qsizetype gretaEfficientX = entitiesList->at(0)->efficientX();


    if (m_efficientX < gretaEfficientX)
    {
        moveBy(horizontalOffset, 0);
        if (collidingItems().isEmpty())
            move(horizontalOffset, 0);
        if (m_lastDirection == direction::RIGHT)
            incrementFrameCounter();
        else
            resetFrameCounter(direction::RIGHT);
        moveBy(-horizontalOffset, 0);
        m_lastDirection = direction::RIGHT;
    }
    else
    {
        moveBy(-horizontalOffset, 0);
        if (collidingItems().isEmpty())
            move(-horizontalOffset, 0);
        if (m_lastDirection == direction::LEFT)
            incrementFrameCounter();
        else
            resetFrameCounter(direction::LEFT);
        moveBy(horizontalOffset, 0);
        m_lastDirection = direction::LEFT;
    }
}

void TrumpetCAC::jump()
{
    return;
}

void TrumpetCAC::fall()
{
    if (!m_isJumping)
    {
        move(0, 20);
        while (!collidingItems().isEmpty())
            move(0, -1);
    }
}

void TrumpetCAC::die(QList<Entity*> *entitiesList)
{
    qobject_cast<QGraphicsScene*>(parent())->removeItem(this);
    for (qsizetype i = ENNEMIES_POS; i < entitiesList->length(); i++)
        if (entitiesList->at(i) == this)
            entitiesList->removeAt(i);
    return;
}

void TrumpetCAC::updateX(QList<Entity*> *entitiesList)
{
    moveDirection(entitiesList);
    collision(entitiesList);
    fall();
}
