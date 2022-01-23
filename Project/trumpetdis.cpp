#include "trumpetdis.h"

TrumpetDIS::TrumpetDIS(QObject *parent, const qreal y, const qreal efficientX, const qreal efficientY) : TrumpetCAC(parent, y, efficientX, efficientY),
                                                                                                         m_endTriggered(false),
                                                                                                         m_jumpOverTrigger(false)
{
    setPixmap(QPixmap(":/ressources/images/TrumpetDISS.png"));

    m_width = TRUMPETDIS_WIDTH;
    m_height = TRUMPETDIS_HEIGHT;

    m_spriteCounterLimit = TRUMPETDIS_SPRITE_COUNT_LIMIT;
    m_frameCounterLimit  = TRUMPETDIS_FRAME_COUNT_LIMIT;
}

void TrumpetDIS::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0, 0, pixmap(), m_spriteCounter*TRUMPETDIS_WIDTH, (m_lastDirection == direction::LEFT)*TRUMPETDIS_HEIGHT, TRUMPETDIS_WIDTH, TRUMPETDIS_HEIGHT);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void TrumpetDIS::moveDirection(QList<Entity*> *entitiesList)
{
    Entity *greta = entitiesList->at(0);

    if ((!m_isTriggered && (abs(greta->x() - x()) > 200)) || m_endTriggered)
        return;

    m_isTriggered = true;
    if (distance(entitiesList->at(0)) > 700)
    {
        face(greta);
        m_endTriggered = true;
        m_attackCooldownCounter = 0;
        return;
    }

    short horizontalOffset = 14;
    qsizetype gretaEfficientX = greta->efficientX();

    if (m_efficientX > gretaEfficientX)
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

void TrumpetDIS::attack(QList<Entity*> *entitiesList)
{
    Entity *greta = entitiesList->at(0);

    if (distance(greta) > 1000)
        return;

    if (!m_jumpOverTrigger && abs(greta->x() - x()) < 10)
    {
        m_jumpOverTrigger = true;
        m_attackCooldownCounter = 0;
    }

    if (m_attackCooldownCounter)
        m_attackCooldownCounter--;
    else
    {
        face(greta);

        /* Angle for bullet's direction vector computing */
        m_attackCooldownCounter = ATTACK_COOLDOWN_COUNT;
        qreal angle = qAtan(qAbs(greta->y() - y())/qAbs(greta->x() - x()));
        qreal xDir = (x() > greta->x()) ? -5*qCos(angle) : 5*qCos(angle);
        qreal yDir = (y() > greta->y()) ? -5*qSin(angle) : 5*qSin(angle);
        qreal newBulletX = (x() > greta->x()) ? + x() - TRUMPETDIS_WIDTH/4 : x() + 5*TRUMPETDIS_WIDTH/4;
        qreal newBulletEfficientY = m_efficientY + TRUMPETDIS_HEIGHT/2;
        qreal newBulletY =  y() + TRUMPETDIS_HEIGHT/2;

        Bullet *newBullet = new Bullet(parent(), newBulletX, newBulletEfficientY, newBulletY, new QVector2D((1 + 1*m_endTriggered)*xDir, (1 + 1*m_endTriggered)*yDir));
        entitiesList->append(newBullet);
        qobject_cast<QGraphicsScene*>(parent())->addItem(newBullet);
    }
}

void TrumpetDIS::jump()
{
    return;
}

void TrumpetDIS::fall()
{
    if (!m_isJumping)
    {
        move(0, 25);
        while (!collidingItems().isEmpty())
            move(0, -1);
    }
}

void TrumpetDIS::updateX(QList<Entity*> *entitiesList)
{
    moveDirection(entitiesList);
    attack(entitiesList);
    collision(entitiesList);
    fall();
}
