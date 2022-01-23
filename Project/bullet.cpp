#include "bullet.h"

Bullet::Bullet(QObject *parent, const qreal efficientX, const qreal efficientY, const qreal y, const QVector2D *sens) : Entity(parent, efficientX, efficientY),
                                                                                                                        m_sens(sens),
                                                                                                                        m_initialEfficientX(efficientX),
                                                                                                                        m_initialEfficientY(efficientY),
                                                                                                                        m_initialY(y),
                                                                                                                        m_throwCounter(0)
{
    setPixmap(QPixmap(":/ressources/images/bulletS.png"));

    m_width = BULLET_WIDTH;
    m_height = BULLET_HEIGHT;

    m_spriteCounterLimit = BULLET_SPRITE_COUNT_LIMIT;
    m_frameCounterLimit  = BULLET_FRAME_COUNT_LIMIT;

    setPosition(efficientX, efficientY, y);
}

Bullet::~Bullet()
{
    delete m_sens;
}

void Bullet::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0, 0, pixmap(), 0, 0, m_width, m_height);
    Q_UNUSED(widget);
    Q_UNUSED(option);
}

void Bullet::moveDirection()
{
    move(m_sens->x(), m_sens->y());
    m_throwCounter+=(sqrt(pow(m_sens->x(), 2) + pow(m_sens->y(), 2)));
}

QRectF Bullet::boundingRect() const
{
    return QRectF(0, 0, 0, 0);
}

void Bullet::collision(QList<Entity*> *entitiesList)
{
    if (entitiesList->at(0)->invincible())
        return;

    qsizetype gretaX = entitiesList->at(0)->x();
    qsizetype gretaY = entitiesList->at(0)->y();

    if (collideWith(entitiesList->at(0)))
    {
        qDebug() << "Greta's y : " << gretaY;
        qDebug() << "Greta's x : " << gretaX;
        qDebug() << "Ennemie's y : " << y();
        qDebug() << "Ennemie's x : " << x();
        qobject_cast<Character*>(entitiesList->at(0))->die(entitiesList);
        qobject_cast<QGraphicsScene*>(parent())->removeItem(this);
        for (qsizetype i = ENNEMIES_POS; i < entitiesList->length(); i++)
            if (entitiesList->at(i) == this)
                entitiesList->removeAt(i);
    }

    if (m_throwCounter >= 2000)
        die(entitiesList);
}

void Bullet::die(QList<Entity*> *entitiesList)
{
    qobject_cast<QGraphicsScene*>(parent())->removeItem(this);
    for (qsizetype i = ENNEMIES_POS; i < entitiesList->length(); i++)
        if (entitiesList->at(i) == this)
            entitiesList->removeAt(i);
    return;
}

void Bullet::updateX(QList<Entity*> *entitiesList)
{
    moveDirection();
    collision(entitiesList);
}
