#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <QGraphicsScene>
#include <QPixmap>
#include <QPainter>
#include <QKeyEvent>
#include <QTimer>
#include <QVector2D>
#include "entity.h"
#include "character.h"
#include "greta.h"

#define BACKGROUND_WIDTH  15140
#define BACKGROUND_HEIGHT 1200

#define BACKGROUND_SPRITE_COUNT_LIMIT 0
#define BACKGROUND_FRAME_COUNT_LIMIT  0

class Background : public Entity
{
    Q_OBJECT
    public :
        /* Constructors */
        explicit Background(QObject *parent = nullptr, const qreal efficientX = 0, const qreal efficientY = 0);

        /* Painting functions */
        virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
        void incrementFrameCounter() override {return;}

        /* Actions functions */
        void moveDirection(QList<Entity*> *entitiesList, const bool centerFlag);
        virtual void die(QList<Entity*> *entitiesList = NULL) override {Q_UNUSED(entitiesList);return;}

        /* Collisions functions */
        virtual QRectF boundingRect() const override;
        virtual QPainterPath shape() const override {
                                                        QPainterPath path;
                                                        path.addRect(QRectF(0, 0, 0, 0));
                                                        return path;
                                                    };
        void collision(QList<Entity*> *entitiesList) override {Q_UNUSED(entitiesList);return;}

        /* Update functions */
        void updateX(QList<Entity*> *entitiesList, const bool centerFlag);
        void updateX(QList<Entity*> *entitiesList) override {Q_UNUSED(entitiesList);return;}

};

#endif // BACKGROUND_H
