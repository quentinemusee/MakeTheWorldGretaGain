#ifndef EXPLOSION_H
#define EXPLOSION_H

#include <QGraphicsScene>
#include <QPixmap>
#include <QPainter>
#include <QKeyEvent>
#include <QTimer>
#include "entity.h"

class Explosion : public Entity
{
    Q_OBJECT
    public :
        /* Constructors */
        explicit Explosion(QObject *parent = nullptr, const qreal efficientX = 0, const qreal efficientY = 0, const qsizetype explosionDuration = 300);

        /* Painting functions */
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
        void incrementFrameCounter() override;

        /* Actions functions */
        void updateState(QList<Entity*> *entitiesList);
        void die(QList<Entity*> *entitiesList = NULL) override {Q_UNUSED(entitiesList);return;}

        /* Collisions functions */
        virtual QRectF boundingRect() const override;
        virtual QPainterPath shape() const override {
                                                        QPainterPath path;
                                                        path.addRect(boundingRect());
                                                        return path;
                                                    };
        void collision(QList<Entity*> *entitiesList) override {Q_UNUSED(entitiesList);return;}

        /* Update functions */
        void updateX(QList<Entity*> *entitiesList) override;

    protected :
        qsizetype m_explosionDuration;
};

#endif // EXPLOSION_H
