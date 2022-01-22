#ifndef POOPBULLET_H
#define POOPBULLET_H

#include <QVector2D>
#include "bullet.h"
#include "character.h"
#include "greta.h"

class PoopBullet : public Bullet
{
    Q_OBJECT
    public :
        /* Constructors */
        explicit PoopBullet(QObject *parent = nullptr, const qreal efficientX = 0, const qreal efficientY = 0, const qreal y = 0, const QVector2D *sens = nullptr, const qreal bulletType = 0);

        /* Painting functions */
        virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

        /* Actions functions */
        void die(QList<Entity*> *entitiesList = NULL) override;

        /* Collisions functions */
        QRectF boundingRect() const override;
        QPainterPath shape() const override {
                                                 QPainterPath path;
                                                 path.addRect(QRectF(0, 0, 0, 0));
                                                 return path;
                                            };
        void collision(QList<Entity*> *entitiesList) override;

        /* Update functions */
        void updateX(QList<Entity*> *entitiesList) override;
};

#endif // POOPBULLET_H
