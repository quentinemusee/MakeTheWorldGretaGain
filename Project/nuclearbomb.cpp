#include "nuclearbomb.h"

NuclearBomb::NuclearBomb(QObject *parent, const qreal efficientX, const qreal efficientY, const qreal y, const QVector2D *sens) : Bullet(parent, efficientX, efficientY, y, sens),
                                                                                                                                  m_acceleration(1)
{
    setPixmap(QPixmap(":/ressources/images/nuclearS.png"));

    m_width = NUCLEARBOMB_WIDTH;
    m_height = NUCLEARBOMB_HEIGHT;

    m_spriteCounterLimit = NUCLEARBOMB_SPRITE_COUNT_LIMIT;
    m_frameCounterLimit  = NUCLEARBOMB_FRAME_COUNT_LIMIT;
}

void NuclearBomb::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0, 0, pixmap(), 0, 0, m_width, m_height);
    //setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget);
    Q_UNUSED(option);
}

void NuclearBomb::moveDirection()
{
    m_acceleration*=1.04;
    move(0, m_acceleration*m_sens->y());
}

QRectF NuclearBomb::boundingRect() const
{
    return QRectF(0, 0, m_width, m_height);
}

QPainterPath NuclearBomb::shape() const
{
    QPainterPath path;
    path.addRect(QRectF(0, 0, 0, 0));
    return path;
};

void NuclearBomb::collision(QList<Entity*> *entitiesList)
{
    Greta *greta = qobject_cast<Greta*>(entitiesList->at(0));

    if (y() >= 120)
        die(entitiesList);

    qsizetype gretaX = greta->x();
    qsizetype gretaY = greta->y();

    if (collideWith(greta))
    {
        if (greta->invincible())
        {
            die(entitiesList);
            return;
        }
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


}

void NuclearBomb::die(QList<Entity*> *entitiesList)
{
    addItemToScene(new Explosion(parent(), x() - (EXPLOSION_WIDTH -  m_width), y() - (EXPLOSION_HEIGHT -  m_height), 90), entitiesList);
    qobject_cast<QGraphicsScene*>(parent())->removeItem(this);
    for (qsizetype i = ENNEMIES_POS; i < entitiesList->length(); i++)
        if (entitiesList->at(i) == this)
            entitiesList->removeAt(i);
    return;
}

void NuclearBomb::updateX(QList<Entity*> *entitiesList)
{
    moveDirection();
    collision(entitiesList);
}
