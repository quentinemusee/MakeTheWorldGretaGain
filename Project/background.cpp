#include "background.h"

Background::Background(QObject *parent, const qreal efficientX, const qreal efficientY) : Entity(parent, efficientX, efficientY)
{
    setPixmap(QPixmap(":/ressources/images/backgroundS.png"));

    m_width = BACKGROUND_WIDTH;
    m_height = BACKGROUND_HEIGHT;

    m_spriteCounterLimit = BACKGROUND_SPRITE_COUNT_LIMIT;
    m_frameCounterLimit  = BACKGROUND_FRAME_COUNT_LIMIT;

    setPos(efficientX, efficientY);
}

void Background::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0, 0, pixmap(), 0, 0, m_width, m_height);
    //setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget);
    Q_UNUSED(option);
}

void Background::moveDirection(QList<Entity*> *entitiesList, const bool centerFlag)
{
    Greta *greta = qobject_cast<Greta*>(entitiesList->at(0));

    if (centerFlag || !greta->isMoving())
        return;

    if (greta->moveRightFlag())
        move(-1, 0);
    else if (greta->moveLeftFlag())
        move(1, 0);
}

QRectF Background::boundingRect() const
{
    return QRectF(0, 0, m_width, m_height);
}

void Background::updateX(QList<Entity*> *entitiesList, const bool centerFlag)
{
    moveDirection(entitiesList, centerFlag);
    //qDebug() << ""
}
