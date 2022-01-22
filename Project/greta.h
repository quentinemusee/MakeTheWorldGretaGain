#ifndef GRETA_H
#define GRETA_H

#include <QDebug>

#include <QPixmap>
#include <QPainter>
#include <QKeyEvent>
#include <QTimer>
#include <QElapsedTimer>
#include "character.h"

#define FRAME_COUNT 10

class Greta : public Character
{
    Q_OBJECT
    public :
        /* Constructors */
        explicit Greta(QObject *parent = nullptr, const qreal efficientX = 750, const qreal efficientY = 0, QElapsedTimer *elapsedTimer = nullptr);

        /* Getters & Setters */
        bool moveRightFlag() const {return m_moveRightFlag;}
        bool moveLeftFlag() const  {return m_moveLeftFlag; }
        bool jumpFlag() const      {return m_jumpFlag;     }
        bool shiftFlag() const     {return m_shiftFlag;    }
        bool isDead() const        {return m_isDead;       }
        bool canMove() const       {return m_canMove;      }
        bool canFall() const       {return m_canFall;      }
        bool fitInView() const     {return m_fitInView;    }
        bool isMoving() const      {return m_isMoving;     }
        bool hasWon() const        {return m_hasWon;       }
        /************************************************************************/
        void canMove(const bool canMove)     {m_canMove = canMove;    }
        void canFall(const bool canFall)     {m_canFall = canFall;    }
        void fitInView(const bool fitInView) {m_fitInView = fitInView;}
        void hasWon(const bool hasWon)       {m_hasWon = hasWon;      }
        /************************************************************************/
        void endJump() {m_isJumping = false;m_jumpFlag = false;}

        /* Painting function */
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
        void incrementFrameCounter() override;
        void resetFrameCounter(const direction::direction_t direction) override;

        /* Keyboard event functions */
        void keyPressEvent(QKeyEvent *event) override;
        void keyReleaseEvent(QKeyEvent *event) override;
        void focusOutEvent(QFocusEvent *event) override;

        /* Actions functions */
        void moveDirection(QList<Entity*> *entitiesList, const bool centerFlag);
        void moveDirection(QList<Entity*> *entitiesList) override {Q_UNUSED(entitiesList);return;}
        void attack(QList<Entity*> *entitiesList) override;
        void jump() override;
        void fall() override;
        void die(QList<Entity*> *entitiesList = NULL) override;
        bool revive();

        /* Update functions */
        bool updateX(QList<Entity*> *entitiesList, const bool centerFlag);
        void updateX(QList<Entity*> *entitiesList) override {Q_UNUSED(entitiesList);return;}

    private :
        bool m_moveRightFlag, m_moveLeftFlag, m_jumpFlag, m_attackFlag, m_shiftFlag;
        bool m_isDead, m_isMoving, m_canMove, m_canFall, m_canJump, m_fitInView;
        bool m_hasWon;
        QElapsedTimer *m_elapsedTimer;
};

#endif // GRETA_H
