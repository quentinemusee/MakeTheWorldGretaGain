#ifndef TRUMPETCAC_H
#define TRUMPETCAC_H

#include <QDebug>

#include <QPixmap>
#include <QPainter>
#include <QKeyEvent>
#include <QTimer>
#include "character.h"
#include "greta.h"

#define FRAME_COUNT 10

class TrumpetCAC : public Character
{
    Q_OBJECT
    public :
        /* Constructors */
        explicit TrumpetCAC(QObject *parent = nullptr, const qreal y = 0, const qreal efficientX = 750, const qreal efficientY = 0);

        /* Getters and setters */
        bool triggered() const {return m_isTriggered;}

        /* Painting functions */
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

        /* Actions functions */
        void moveDirection(QList<Entity*> *entitiesList) override;
        virtual void attack(QList<Entity*> *entitiesList) override {Q_UNUSED(entitiesList);return;}
        void jump() override;
        void fall() override;
        void die(QList<Entity*> *entitiesList = NULL) override;

        /* Update functions */
        void updateX(QList<Entity*> *entitiesList) override;

    protected :
        bool m_isTriggered;
};

#endif // TRUMPETCAC_H
