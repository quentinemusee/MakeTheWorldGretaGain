#ifndef TRUMPET_H
#define TRUMPET_H

#include <QDebug>

#include <QPixmap>
#include <QPainter>
#include <QKeyEvent>
#include <QTimer>
#include <QRandomGenerator>
#include <QElapsedTimer>
#include "character.h"
#include "greta.h"
#include "poopbullet.h"
#include "nuclearbomb.h"
#include "explosion.h"

#define TRUMPET_PHASE_1 5
#define TRUMPET_PHASE_2 8

class Trumpet : public Character
{
    Q_OBJECT
    public :
        /* Constructors */
        explicit Trumpet(QObject *parent = nullptr, const qreal y = 0, const qreal efficientX = 750, const qreal efficientY = 0, QElapsedTimer *elapsedTimer = nullptr);

        /* Getters and setters */
        qsizetype state() const        {return m_state;       }
        qsizetype stateCounter() const {return m_stateCounter;}

        /* Utilities functions */
        bool wait(const qsizetype N);

        /* Collision functions */
        virtual QRectF boundingRect() const override;
        void collision(QList<Entity*> *entitiesList) override;

        /* Painting functions */
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

        /* Actions functions */
        void updateState(QList<Entity*> *entitiesList);
        void moveDirection(QList<Entity*> *entitiesList) override;
        void attack(QList<Entity*> *entitiesList) override;
        void repulseGreta(QList<Entity*> *entitiesList);
        void jump() override;
        void fall() override;
        void die(QList<Entity*> *entitiesList = NULL) override;


        /* Update functions */
        void updateX(QList<Entity*> *entitiesList) override;

    protected :
        char m_HP;
        bool m_isHit;
        qsizetype m_state, m_stateCounter;
        qsizetype m_moveCounter;
        qsizetype m_isHitCounter;
        qreal m_leftLimit, m_rightLimit;
        qreal m_repulseGretaCounter;
        QElapsedTimer *m_elapsedTimer;
        qint64 m_elapsedTime;
};

#endif // TRUMPET_H
