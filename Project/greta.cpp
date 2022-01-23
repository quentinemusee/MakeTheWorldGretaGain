#include "greta.h"

Greta::Greta(QObject *parent, const qreal efficientX, const qreal efficientY, QElapsedTimer *elapsedTimer) : Character(parent, efficientX, efficientY),
                                                                                                             m_moveRightFlag(false),
                                                                                                             m_moveLeftFlag(false),
                                                                                                             m_jumpFlag(false),
                                                                                                             m_attackFlag(false),
                                                                                                             m_shiftFlag(false),
                                                                                                             m_isDead(true),
                                                                                                             m_isMoving(false),
                                                                                                             m_canMove(true),
                                                                                                             m_canFall(true),
                                                                                                             m_canJump(true),
                                                                                                             m_fitInView(true),
                                                                                                             m_elapsedTimer(elapsedTimer)
{
    setPixmap(QPixmap(":/ressources/images/gretaS.png"));

    m_width = GRETA_WIDTH;
    m_height = GRETA_HEIGHT;

    m_spriteCounterLimit = GRETA_SPRITE_COUNT_LIMIT;
    m_frameCounterLimit  = GRETA_FRAME_COUNT_LIMIT;

    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();
}

void Greta::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (m_isDead)
        return;

    if (m_attackCooldownCounter)
    {
        if (m_isJumping)
        {
            if (m_lastDirection == direction::LEFT)
                painter->drawPixmap(-70, 0, pixmap(), 227, 3*GRETA_HEIGHT-1, GRETA_WIDTH + 35, GRETA_HEIGHT);
            else
                painter->drawPixmap(35, 0, pixmap(), 233, GRETA_HEIGHT-1, GRETA_WIDTH + 34, GRETA_HEIGHT);
        }
        else
        {
            if (m_lastDirection == direction::LEFT)
                painter->drawPixmap(-70, 6, pixmap(), 30, 3*GRETA_HEIGHT-1, GRETA_WIDTH + 35, GRETA_HEIGHT);
            else
                painter->drawPixmap(35, 7, pixmap(), 34, GRETA_HEIGHT, GRETA_WIDTH + 34, GRETA_HEIGHT-7);
        }
    }
    else
    {
        if (m_spriteCounter%2)
        {
            if (m_lastDirection == direction::LEFT)
                painter->drawPixmap(0, 0, pixmap(), GRETA_WIDTH, 2*GRETA_HEIGHT-1, GRETA_WIDTH, GRETA_HEIGHT);
            else
                painter->drawPixmap(0, 0, pixmap(), GRETA_WIDTH, 0, GRETA_WIDTH, GRETA_HEIGHT);
        }
        else
        {
            if (m_lastDirection == direction::LEFT)
                painter->drawPixmap(0, 0, pixmap(), m_spriteCounter*GRETA_WIDTH, 2*GRETA_HEIGHT-1, GRETA_WIDTH, GRETA_HEIGHT);
            else
                painter->drawPixmap(0, 0, pixmap(), m_spriteCounter*GRETA_WIDTH, 0, GRETA_WIDTH - (m_spriteCounter==2), GRETA_HEIGHT);
        }
    }

    if (m_invincible)
    {
        painter->setPen(QColor::fromRgb(0, 255, 0, 255));
        painter->setFont(QFont("Arial", 20));
        painter->drawText(-30, -25, "Invincible : on");
        painter->setPen(QColor::fromRgb(0, 0, 0, 0));
    }

    Q_UNUSED(widget);
    Q_UNUSED(option);
}

void Greta::incrementFrameCounter()
{
    m_frameCounter += 1+m_shiftFlag;
    if (m_frameCounter >= FRAME_COUNT)
    {
        m_frameCounter = 0;
        nextFrame();
    }
}

void Greta::resetFrameCounter(const direction::direction_t direction)
{
    m_lastDirection = direction;
    m_frameCounter = FRAME_COUNT-1;
    m_spriteCounter = 0;
}

void Greta::keyPressEvent(QKeyEvent *event)
{
    if (event->isAutoRepeat())
        return;

    m_shiftFlag = (event->modifiers() & Qt::ShiftModifier);
    switch(event->key())
    {
        case Qt::Key_Z :
            m_jumpFlag = true;
            break;
        case Qt::Key_Q :
            m_moveLeftFlag = true;
            break;
        case Qt::Key_D :
            m_moveRightFlag = true;
            break;
        case Qt::Key_Space :
            m_attackFlag = true;
            break;
        case Qt::Key_Return :
            if (!m_hasWon)
                return;
            m_hasWon = false;
            m_invincible = false;
            m_efficientY = 1000;
            m_elapsedTimer->restart();
            break;
        default :
            break;
    }
}

void Greta::keyReleaseEvent(QKeyEvent *event)
{
    if (event->isAutoRepeat())
        return;

    m_shiftFlag = (event->modifiers() & Qt::ShiftModifier);
    switch(event->key())
    {
        case Qt::Key_Z :
            m_jumpFlag = false;
            break;
        case Qt::Key_Q :
            m_moveLeftFlag = false;
            break;
        case Qt::Key_D :
            m_moveRightFlag = false;
            break;
        case Qt::Key_Space :
            m_attackFlag = false;
            break;
        case Qt::Key_G :
            m_invincible = !m_invincible;
            break;
        default :
            break;
    }
}

void Greta::focusOutEvent(QFocusEvent *event)
{
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();
    Q_UNUSED(event);
}

void Greta::moveDirection(QList<Entity*> *entitiesList, const bool centerFlag)
{
    if (m_attackCooldownCounter || !m_canMove)
    {
        m_isMoving = false;
        return;
    }

    short horizontalOffset = 6 + 6*m_shiftFlag;
    bool moveByOffset = true;

    if (m_moveRightFlag && !m_isDead)
    {
        moveBy(horizontalOffset, 0);

        if (collidingItems().isEmpty())
        {
            m_isMoving = true;
            if (centerFlag || !m_fitInView)
                //move(horizontalOffset, 0);
                *this+=(horizontalOffset);
            else
            {
                m_efficientX += horizontalOffset;
                for (qsizetype i = 1; i < entitiesList->length(); i++)
                   entitiesList->at(i)->moveBy(-horizontalOffset, 0);
            }
        }
        else
        {
            m_isMoving = false;
            if (centerFlag || !m_fitInView)
            {
                while (!collidingItems().isEmpty())
                {
                    moveBy(-1, 0);
                    moveByOffset = false;
                }
            }
            else
                moveByOffset = true;
         }
        if (m_lastDirection == direction::RIGHT)
            incrementFrameCounter();
        else
            resetFrameCounter(direction::RIGHT);
        if (moveByOffset)
            moveBy(-horizontalOffset, 0);
    }
    else if (m_moveLeftFlag && !m_isDead)
    {
        moveBy(-horizontalOffset, 0);
        if ((centerFlag && (m_efficientX - horizontalOffset >= 0)) || !m_fitInView)
            *this+=(-horizontalOffset);
        else
            if (collidingItems().isEmpty() && (m_efficientX - horizontalOffset >= 0))
            {
                m_isMoving = true;
                m_efficientX -= horizontalOffset;
                for (qsizetype i = 1; i < entitiesList->length(); i++)
                   entitiesList->at(i)->moveBy(horizontalOffset, 0);
            }
            else
            {
                m_isMoving = false;
            }
        if (m_lastDirection == direction::LEFT)
            incrementFrameCounter();
        else
            resetFrameCounter(direction::LEFT);
        moveBy(horizontalOffset, 0);
    }
    else
    {
        resetFrameCounter(m_lastDirection);
        m_isMoving = false;
    }

    if (!m_fitInView)
        m_isMoving = false;

    if (!m_fitInView && x() < 0)
        setX(0);

    if (m_efficientY >= 600)
        die(entitiesList);
}

void Greta::attack(QList<Entity *> *entitiesList)
{
    if (m_attackCooldownCounter > 1)
        m_attackCooldownCounter--;
    else if (m_attackCooldownCounter == 1)
    {
        if (!m_attackFlag)
            m_attackCooldownCounter = 0;
    }
    else
    {
        if (!m_attackFlag || !m_canMove)
            return;

        if (m_lastDirection == direction::RIGHT)
        {
            for (qsizetype i = ENNEMIES_POS; i < entitiesList->length(); i++)
            {
                if (x()+ m_width - 12 < entitiesList->at(i)->x() + entitiesList->at(i)->width() &&
                    x() + m_width + 75> entitiesList->at(i)->x() - 12 &&
                    y() - 12 < entitiesList->at(i)->y() + entitiesList->at(i)->height() &&
                    y() + m_height > entitiesList->at(i)->y() - 12)
                {
                    entitiesList->at(i)->die(entitiesList);
                }
            }

        }
        else
            for (qsizetype i = ENNEMIES_POS; i < entitiesList->length(); i++)
                if (x() - 75 - 12 < entitiesList->at(i)->x() + entitiesList->at(i)->width() &&
                    x() > entitiesList->at(i)->x() - 12 &&
                    y() - 12 < entitiesList->at(i)->y() + entitiesList->at(i)->height() &&
                    y() + m_height > entitiesList->at(i)->y() - 12)
                {
                    entitiesList->at(i)->die(entitiesList);
                }

        m_frameCounter = FRAME_COUNT-1;
        m_spriteCounter = 0;
        m_attackCooldownCounter = 31;
    }
}

void Greta::jump()
{

    if (m_jumpFlag && !m_isJumping && !m_attackCooldownCounter && m_canJump)
    {
        if (!m_canMove)
                return;
        m_isJumping = true;
        m_jumpCount = 30;
    }
    if (m_isJumping)
    {
        if (m_jumpCount > 5)
        {
            *this+=((-14 + (m_jumpCount < 10)*5)/100.0f);
            if (!collidingItems().isEmpty())
                m_jumpCount = 0;
            while (!collidingItems().isEmpty())
                *this+=(1/100.0f);
            m_jumpCount--;
        }
        else if (m_jumpCount > 0)
        {
            m_jumpCount--;
        }
        else
        {
            *this+=(15/100.0f);
            if (!collidingItems().isEmpty())
            {
                while (!collidingItems().isEmpty())
                    *this+=(-1/100.0f);
                m_isJumping = false;
                resetFrameCounter(m_lastDirection);
                return;
            }
        }

        m_spriteCounter = 2;
    }
}

void Greta::fall()
{
    if (!m_isJumping && m_canFall)
    {
        *this+=(15/100.0f);
        if (collidingItems().isEmpty())
            m_canJump = false;
        else
            m_canJump = true;
        while (!collidingItems().isEmpty())
            *this+=(-1/100.0f);
    }
}

void Greta::die(QList<Entity*> *entitiesList)
{
    if (m_invincible && m_efficientY < 600) return;

    m_isDead = true;
    m_invincible = true;
    m_isJumping = false;
    m_jumpCount = 0;
    setPosition(entitiesList->at(1)->x() + 750, 0, 0);
}

bool Greta::revive()
{
    if (m_isDead)
    {
        bool res = false;
        *this+=(1/100.0f);
        if (!collidingItems().isEmpty())
        {
            res = true;
            m_fitInView = true;
            m_isDead = false;
            m_invincible = false;
            resetFrameCounter(direction::RIGHT);
            m_efficientY = 0;
        }
        return res;
    }
    return false;
}

bool Greta::updateX(QList<Entity*> *entitiesList, const bool centerFlag)
{
    moveDirection(entitiesList, centerFlag);
    attack(entitiesList);
    jump();
    fall();
    return revive();
}
