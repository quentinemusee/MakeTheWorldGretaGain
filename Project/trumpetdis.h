#ifndef TRUMPETDIS_H
#define TRUMPETDIS_H

#include <QDebug>

#include <QPixmap>
#include <QPainter>
#include <QKeyEvent>
#include <QTimer>
#include <QGraphicsScene>
#include "trumpetcac.h"
#include "greta.h"
#include "bullet.h"

#define FRAME_COUNT 10
#define ATTACK_COOLDOWN_COUNT 150

class TrumpetDIS : public TrumpetCAC
{
    Q_OBJECT
    public :
        /* Constructors */
        explicit TrumpetDIS(QObject *parent = nullptr, const qreal y = 0, const qreal efficientX = 750, const qreal efficientY = 0);

        /* Getters and setters */
        qsizetype attackCooldownCounter() const {return m_attackCooldownCounter;}
        bool endTriggered() const               {return m_endTriggered;         }

        /* Painting functions */
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

        /* Actions functions */
        void moveDirection(QList<Entity*> *entitiesList) override;
        void attack(QList<Entity*> *entitiesList) override;
        void jump() override;
        void fall() override;

        /* Update functions */
        void updateX(QList<Entity*> *entitiesList) override;

    protected :
        bool m_endTriggered, m_jumpOverTrigger;
};

#endif // TRUMPETDIS_H
