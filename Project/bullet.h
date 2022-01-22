#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsScene>
#include <QPixmap>
#include <QPainter>
#include <QKeyEvent>
#include <QTimer>
#include <QVector2D>
#include "entity.h"
#include "character.h"

class Bullet : public Entity
{
    Q_OBJECT
    public :
        /* Constructors */
        explicit Bullet(QObject *parent = nullptr, const qreal efficientX = 0, const qreal efficientY = 0, const qreal y = 0, const QVector2D *sens = nullptr);

        /* Destructor */
        virtual ~Bullet();

        /* Painting functions */
        virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
        void incrementFrameCounter() override {return;}

        /* Actions functions */
        void moveDirection();
        virtual void die(QList<Entity*> *entitiesList = NULL) override;

        /* Collisions functions */
        virtual QRectF boundingRect() const override;
        virtual QPainterPath shape() const override {
                                                        QPainterPath path;
                                                        path.addRect(boundingRect());
                                                        return path;
                                                    };
        void collision(QList<Entity*> *entitiesList) override;

        /* Update functions */
        void updateX(QList<Entity*> *entitiesList) override;

    protected :
        const QVector2D *m_sens;
        qreal m_initialEfficientX, m_initialEfficientY, m_initialY;
        qsizetype m_throwCounter;
};

#endif // BULLET_H
