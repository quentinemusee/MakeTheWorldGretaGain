#include "explosion.h"

Explosion::Explosion(QObject *parent, const qreal efficientX, const qreal efficientY, const qsizetype explosionDuration) : Entity(parent, efficientX, efficientY),
                                                                                                                           m_explosionDuration(explosionDuration)
{
    setPixmap(QPixmap(":/ressources/images/explosionS.png"));

    m_width = EXPLOSION_WIDTH;
    m_height = EXPLOSION_HEIGHT;

    m_spriteCounterLimit = EXPLOSION_SPRITE_COUNT_LIMIT;
    m_frameCounterLimit  = EXPLOSION_FRAME_COUNT_LIMIT;

    setPos(efficientX, efficientY);
    setZValue(1);
}

void Explosion::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0, 0, pixmap(), (m_spriteCounter%8)*m_width, (m_spriteCounter/8)*m_height, m_width, m_height);
    //setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget);
    Q_UNUSED(option);
}

void Explosion::incrementFrameCounter()
{
    m_explosionDuration--;
    if (++m_frameCounter >= m_frameCounterLimit)
    {
        m_frameCounter = 0;
        nextFrame();
    }
}

void Explosion::updateState(QList<Entity*> *entitiesList)
{
    if (!m_explosionDuration)
     {
        qobject_cast<QGraphicsScene*>(parent())->removeItem(this);
        m_explosionDuration--;
        for (qsizetype i = ENNEMIES_POS; i < entitiesList->length(); i++)
            if (entitiesList->at(i) == this)
                entitiesList->removeAt(i);
    }
}

QRectF Explosion::boundingRect() const
{
    return QRectF(0, 0, 0, 0);
}

void Explosion::updateX(QList<Entity*> *entitiesList)
{
    updateState(entitiesList);
    incrementFrameCounter();
}
