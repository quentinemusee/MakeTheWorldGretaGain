#ifndef NUCLEARBOMB_H
#define NUCLEARBOMB_H

#include <QGraphicsScene>
#include <QPixmap>
#include <QPainter>
#include <QKeyEvent>
#include <QTimer>
#include <QVector2D>
#include "bullet.h"
#include "character.h"
#include "greta.h"
#include "platform.h"
#include "explosion.h"

class NuclearBomb : public Bullet
{
    Q_OBJECT
    public :
        /* Constructors */
        explicit NuclearBomb(QObject *parent = nullptr, const qreal efficientX = 0, const qreal efficientY = 0, const qreal y = 0, const QVector2D *sens = nullptr);

        /* Painting functions */
        virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

        /* Action functions */
        void moveDirection();
        void die(QList<Entity*> *entitiesList = NULL) override;

        /* Collisions functions */
        virtual QRectF boundingRect() const override;
        QPainterPath shape() const override;
        void collision(QList<Entity*> *entitiesList) override;

        /* Update functions */
        void updateX(QList<Entity*> *entitiesList) override;

    protected :
        qreal m_acceleration;
};

#endif // NUCLEARBOMB_H
