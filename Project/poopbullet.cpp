#include "poopbullet.h"

PoopBullet::PoopBullet(QObject *parent, const qreal efficientX, const qreal efficientY, const qreal y, const QVector2D *sens, const qreal bulletType) : Bullet(parent,
                                                                                                                                                        efficientX,
                                                                                                                                                        efficientY,
                                                                                                                                                        y,
                                                                                                                                                        sens)
{
    if (!bulletType)
    {
        setPixmap(QPixmap(":/ressources/images/poopBullet1S.png"));
        m_width = POOPBULLET1_WIDTH;
        m_height = POOPBULLET1_HEIGHT;
    }
    else if (bulletType == 1)
    {
        setPixmap(QPixmap(":/ressources/images/poopBullet2S.png"));
        m_width = POOPBULLET2_WIDTH;
        m_height = POOPBULLET2_HEIGHT;
    }
    else
    {
        setPixmap(QPixmap(":/ressources/images/poopBullet3S.png"));
        m_width = POOPBULLET3_WIDTH;
        m_height = POOPBULLET3_HEIGHT;
    }

    m_spriteCounterLimit = POOPBULLET_SPRITE_COUNT_LIMIT;
    m_frameCounterLimit  = POOPBULLET_FRAME_COUNT_LIMIT;

    setPosition(efficientX, efficientY, y);
}

void PoopBullet::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0, 0, pixmap(), 0, 0, m_width, m_height);
    //setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget);
    Q_UNUSED(option);
}

void PoopBullet::collision(QList<Entity*> *entitiesList)
{
    Greta *greta = qobject_cast<Greta*>(entitiesList->at(0));

    qsizetype gretaX = greta->x();
    qsizetype gretaY = greta->y();

    if (collideWith(greta))
    {
        if (greta->invincible())
            return;

        qDebug() << "Greta's y : " << gretaY;
        qDebug() << "Greta's x : " << gretaX;
        qDebug() << "Ennemie's y : " << y();
        qDebug() << "Ennemie's x : " << x();
        greta->die(entitiesList);
        qobject_cast<QGraphicsScene*>(parent())->removeItem(this);
        for (qsizetype i = ENNEMIES_POS; i < entitiesList->length(); i++)
            if (entitiesList->at(i) == this)
                entitiesList->removeAt(i);
    }

    if (m_sens->x() < 0)
        return;

    Entity *trumpet = entitiesList->at(ENNEMIES_POS);

    qsizetype trumpetX = trumpet->x();
    qsizetype trumpetY = trumpet->y();

    if (collideWith(trumpet))
    {
        qDebug() << "Trumpet's y : " << trumpetY;
        qDebug() << "Trumpet's x : " << trumpetX;
        qDebug() << "Ennemie's y : " << y();
        qDebug() << "Ennemie's x : " << x();
        trumpet->die(entitiesList);
        qobject_cast<QGraphicsScene*>(parent())->removeItem(this);
        for (qsizetype i = ENNEMIES_POS; i < entitiesList->length(); i++)
            if (entitiesList->at(i) == this)
                entitiesList->removeAt(i);
    }
}

void PoopBullet::die(QList<Entity*> *entitiesList)
{
    Q_UNUSED(entitiesList);
    float newSens = -m_sens->x();
    delete m_sens;
    m_sens = new QVector2D(newSens, 0);
    return;
}

QRectF PoopBullet::boundingRect() const
{
    return QRectF(0, 0, m_width, m_height);
}

void PoopBullet::updateX(QList<Entity*> *entitiesList)
{
    moveDirection();
    collision(entitiesList);
}
