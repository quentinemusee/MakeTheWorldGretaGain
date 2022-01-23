#include "trumpet.h"

qreal ATTACK_COOLDOWN_COUNT = 100;

Trumpet::Trumpet(QObject *parent, const qreal y, const qreal efficientX, const qreal efficientY, QElapsedTimer *elapsedTimer) : Character(parent, efficientX, efficientY),
                                                                                                                                m_HP(10),
                                                                                                                                m_isHit(false),
                                                                                                                                m_state(0),
                                                                                                                                m_stateCounter(0),
                                                                                                                                m_moveCounter(0),
                                                                                                                                m_isHitCounter(0),
                                                                                                                                m_leftLimit(efficientX - 100),
                                                                                                                                m_rightLimit(efficientX + 100),
                                                                                                                                m_repulseGretaCounter(0),
                                                                                                                                m_elapsedTimer(elapsedTimer)
{
    resetFrameCounter(direction::LEFT);

    setPixmap(QPixmap(":/ressources/images/trumpetS.png"));

    m_width = TRUMPET1_WIDTH;
    m_height = TRUMPET1_HEIGHT;

    m_spriteCounterLimit = TRUMPET_SPRITE_COUNT_LIMIT;
    m_frameCounterLimit  = TRUMPET_FRAME_COUNT_LIMIT;

    setPosition(efficientX, efficientY, y);
}

bool Trumpet::wait(const qsizetype N)
{
    if (++m_stateCounter == N)
        return true;
    return false;
}

QRectF Trumpet::boundingRect() const
{
    if (m_state >= 10)
        return QRectF(0, 0, 2*m_width, 3*m_height);
    if (m_state >= 7)
        return QRectF(0, 0, 0, 0);
    return QRectF(0, 0, m_width, m_height);
}

void Trumpet::collision(QList<Entity*> *entitiesList)
{
    if (m_state > 8)
        return;

    Greta *greta = qobject_cast<Greta*>(entitiesList->at(0));

    if (greta->invincible())
        return;

    qsizetype gretaX = greta->x();
    qsizetype gretaY = greta->y();

    if (collideWith(greta))
    {
        qDebug() << "Greta's y : " << gretaY;
        qDebug() << "Greta's x : " << gretaX;
        qDebug() << "Ennemie's y : " << y();
        qDebug() << "Ennemie's x : " << x();
        m_repulseGretaCounter = 1;
    }
}

void Trumpet::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    const QPixmap GG = QPixmap(":/ressources/images/GGS.png");
    switch(m_state)
    {
        case 0 :
            painter->drawPixmap(0, 0, pixmap(), 0, 0, m_width, m_height);
            break;
        case 1 :
            painter->drawPixmap(0, 0, pixmap(), 160, 0, m_width, m_height);
            break;
        case 2 :
            painter->drawPixmap(0, 0, pixmap(), 320, 0, m_width, m_height);
            break;
        case 3 :
            painter->drawPixmap(-160, 0, pixmap(), 0, 230, m_width, m_height);
            break;
        case 4 :
            painter->drawPixmap(-160, 0, pixmap(), 0, 523, m_width, m_height);
            break;
        case 5 :
            if (!m_isHit || m_isHitCounter%4 < 2)
                painter->drawPixmap(0, 0, pixmap(), 320, 316, m_width, m_height);
            break;
        case 6 :
            painter->drawPixmap(0, 0, pixmap(), 320, 316, m_width, m_height);
            break;
        case 7 :
            painter->drawPixmap(0, 0, pixmap(), 320, 316, m_width, m_height);
            break;
        case 8 :
            if (!m_isHit || m_isHitCounter%4 < 2)
                painter->drawPixmap(0, 0, pixmap(), 519, 332, m_width, m_height);
            break;
        case 9 :
            painter->drawPixmap(0, 0, pixmap(), 519, 332, m_width, m_height);
            break;
        case 10 :
            painter->drawPixmap(0, 197, pixmap(), 480, 0, m_width, m_height);
            break;
        case 11 :
            painter->drawPixmap(57, 239, pixmap(), 724, 0, m_width, m_height);
            break;
        case 12 :
            painter->drawPixmap(57, 407, pixmap(), 911, 94, m_width, m_height);
            break;
        case 13 :
            painter->drawPixmap(57, 407, pixmap(), 911, 94, m_width, m_height);
            painter->drawPixmap(25, 0, GG, 0, 0, 360, 240);
            break;
        case 14 :
            painter->drawPixmap(57, 407, pixmap(), 911, 94, m_width, m_height);
            painter->drawPixmap(25, 0, GG, 0, 0, 360, 240);
            break;
        default :
            painter->drawPixmap(57, 407, pixmap(), 911, 94, m_width, m_height);
            painter->drawPixmap(25, 0, GG, 0, 0, 360, 240);
            QFont font = painter->font();
            font.setPixelSize(48);
            painter->setFont(font);
            qint64 seconds = m_elapsedTime/1000;
            qint64 minutes = seconds/60;
            qint64 hours = minutes/60;
            minutes %= 60;
            seconds %= 60;
            QString timeToString = QString("Temps : ");
            if (hours)
            {
                painter->drawText(25, -50,
                                  timeToString
                                  +
                                  QString::number(hours)
                                  +
                                  QString("h ")
                                  +
                                  QString::number(minutes)
                                  +
                                  QString("m ")
                                  +
                                  QString::number(seconds)
                                  +
                                  QString("s"));
            }
            else
            {
                painter->drawText(50, -50,
                                  timeToString
                                  +
                                  QString::number(minutes)
                                  +
                                  QString("m ")
                                  +
                                  QString::number(seconds)
                                  +
                                  QString("s"));
            }

            painter->drawText(0, -100, "Press enter to replay.");


            break;
    }
    Q_UNUSED(widget);
    Q_UNUSED(option);
}

void Trumpet::updateState(QList<Entity*> *entitiesList)
{
    Greta *greta = qobject_cast<Greta*>(entitiesList->at(0));

    qreal trumpetCenterX, trumpetCenterY;

    if (m_isHitCounter)
        if (!--m_isHitCounter)
            m_isHit = false;

    switch(m_state)
    {
        case 0 :
            if (m_efficientX - greta->efficientX() < 700)
            {
                greta->fitInView(false);
                greta->spriteCounter(0);
                if (!m_stateCounter)
                    greta->canMove(false);
                if (wait(75))
                {
                    m_state++;
                    m_stateCounter = 0;
                    m_width = TRUMPET1_WIDTH;
                    m_height = TRUMPET1_HEIGHT;
                }
            }
            return;
        case 1 :
            if (wait(75))
            {
                m_state++;
                m_stateCounter = 0;
                m_width = TRUMPET2_WIDTH;
                m_height = TRUMPET2_HEIGHT;
            }
            return;
        case 2 :
            if (wait(75))
            {
                m_state++;
                m_stateCounter = 0;
                m_width = TRUMPET3_WIDTH;
                m_height = TRUMPET3_HEIGHT;
            }
            return;
        case 3 :
            if (wait(75))
            {
                m_state++;
                m_stateCounter = 0;
                m_width = TRUMPET4_WIDTH;
                m_height = TRUMPET4_HEIGHT;
            }
            return;
        case 4 :
            if (wait(200))
            {
                m_state++;
                m_stateCounter = 0;
                m_attackCooldownCounter = 60;
                m_width = TRUMPET5_WIDTH;
                m_height = TRUMPET5_HEIGHT;
                greta->canMove(true);
            }
            return;

        case 5 :
            // FIRST FIGHTING PHASE
            return;

        case 6 :
            // EXPLOSION PHASE
            m_state++;
            m_stateCounter = 0;
            m_width = TRUMPET6_WIDTH;
            m_height = TRUMPET6_HEIGHT;
            trumpetCenterX = x() + m_width/2 - EXPLOSION_WIDTH/2 - 10;
            trumpetCenterY = y() + m_height/2 - EXPLOSION_HEIGHT/2;
            addItemToScene(new Explosion(parent(), trumpetCenterX - 15, trumpetCenterY - 165, 300), entitiesList);
            addItemToScene(new Explosion(parent(), trumpetCenterX - 120, trumpetCenterY - 75, 300), entitiesList);
            addItemToScene(new Explosion(parent(), trumpetCenterX + 75, trumpetCenterY - 30, 300), entitiesList);
            addItemToScene(new Explosion(parent(), trumpetCenterX - 55, trumpetCenterY + 40, 300), entitiesList);
            addItemToScene(new Explosion(parent(), trumpetCenterX + 10, trumpetCenterY + 150, 300), entitiesList);
            return;
        case 7 :
            // WAIT FOR EXPLOSION TO END PHASE
            if (wait(300))
            {
                m_state++;
                m_stateCounter = 0;
                m_width = TRUMPET7_WIDTH;
                m_height = TRUMPET7_HEIGHT;
                move(-(m_width/3), -(m_height - TRUMPET7_WIDTH));
                move(0, -266);
            }
            return;
        case 8 :
            // SECOND FIGHTING PHASE

            return;
        case 9 :
            // DIMENSIONS UPDATE BEFORE DEATH ANIMATION
            m_state++;
            m_stateCounter = 0;
            m_width = TRUMPET8_WIDTH;
            m_height = TRUMPET8_HEIGHT;
            return;

        case 10 :
            // First death animation
            if (wait(100))
            {
                m_state++;
                m_stateCounter = 0;
                m_width = TRUMPET9_WIDTH;
                m_height = TRUMPET9_HEIGHT;
            }
            return;
        case 11 :
            // Second death animation
            if (wait(100))
            {
                m_state++;
                m_stateCounter = 0;
                m_width = TRUMPET10_WIDTH;
                m_height = TRUMPET10_HEIGHT;
            }
            return;
        case 12 :
            // Third death animation
            if (wait(100))
            {
                m_state++;
                m_stateCounter = 0;
                m_width = TRUMPET11_WIDTH;
                m_height = TRUMPET11_HEIGHT;
            }
            return;
        case 13 :
            // GG spawn animation
            if (wait(100))
            {
                m_state++;
                m_stateCounter = 0;
            }
            return;
        case 14 :
            // Time spawn animation
            if (wait(100))
            {
                m_state++;
                m_stateCounter = 0;
                greta->hasWon(true);
            }
            return;
        case 15 :
            if (!greta->hasWon())
            {
                qobject_cast<QGraphicsScene*>(parent())->removeItem(this);
                for (qsizetype i = ENNEMIES_POS; i < entitiesList->length(); i++)
                    if (entitiesList->at(i) == this)
                        entitiesList->removeAt(i);
            }
        default :
            return;
    }
}

void Trumpet::moveDirection(QList<Entity*> *entitiesList)
{
    Q_UNUSED(entitiesList);

    if (m_state != 5)
        return;

    if (!m_moveCounter)
    {
        m_lastDirection = (direction::direction_t) (1 + QRandomGenerator::global()->bounded(2));
        m_moveCounter = 20 + 2*QRandomGenerator::global()->bounded(11);
    }

    if (m_lastDirection == direction::LEFT)
    {
        if (m_efficientX == m_leftLimit)
        {
            m_moveCounter = 0;
            return;
        }
        move(-1, 0);
    }
    else
    {
        if (m_efficientX == m_rightLimit)
        {
            m_moveCounter = 0;
            return;
        }
        move(1, 0);
    }


    m_moveCounter--;

    return;
}

void Trumpet::attack(QList<Entity*> *entitiesList)
{
    m_attackCooldownCounter--;

    if (m_state == TRUMPET_PHASE_1)
    {
        if (m_attackCooldownCounter < 0)
        {
            m_attackCooldownCounter = ATTACK_COOLDOWN_COUNT;
            qreal poopBulletType =     QRandomGenerator::global()->bounded(3);
            qreal poopBulletPosition = QRandomGenerator::global()->bounded(4);

            qreal newBulletX = x() - m_width;
            qreal newBulletEfficientY = m_efficientY + poopBulletPosition*POOPBULLET1_HEIGHT*1.3;
            qreal newBulletY = y() + poopBulletPosition*POOPBULLET1_HEIGHT*1.3;


            PoopBullet *newBullet = new PoopBullet(parent(), newBulletX, newBulletEfficientY, newBulletY, new QVector2D(-(1 + poopBulletType)*5, 0), poopBulletType);
            addItemToScene(newBullet, entitiesList);
        }
    }

    if (m_state == TRUMPET_PHASE_2)
    {
        if (m_attackCooldownCounter < 0)
        {
            m_attackCooldownCounter = ATTACK_COOLDOWN_COUNT/4;
            if (m_HP <= 3)
                m_attackCooldownCounter/=1.5;
            if (m_HP == 1)
                m_attackCooldownCounter/=3;

            qreal newBulletnewNuclearBombX = QRandomGenerator::global()->bounded(x() - NUCLEARBOMB_WIDTH);
            qreal newNuclearBombEfficientY = -250;
            qreal newNuclearBombY = newNuclearBombEfficientY - 430;


            NuclearBomb *newNuclearBomb = new NuclearBomb(parent(), newBulletnewNuclearBombX, newNuclearBombEfficientY, newNuclearBombY, new QVector2D(0, 5));
            addItemToScene(newNuclearBomb, entitiesList);
        }
    }
}

void Trumpet::repulseGreta(QList<Entity*> *entitiesList)
{
    if (m_state > 8)
        return;

    Greta *greta = qobject_cast<Greta*>(entitiesList->at(0));
    if (greta->isDead())
    {
        m_repulseGretaCounter = 0;
        return;
    }

    if (m_repulseGretaCounter)
    {
        if (m_repulseGretaCounter == 1)
        {
            greta->canMove(false);
            greta->canFall(false);
            greta->endJump();
        }
        qreal shift = -(30 - m_repulseGretaCounter);
        greta->move(-17, shift);
        m_repulseGretaCounter++;

        if (m_repulseGretaCounter > 10)
        {
            greta->move(0, 15);
            if (!greta->collidingItems().isEmpty())
            {
                greta->canMove(true);
                greta->canFall(true);
                m_repulseGretaCounter = 0;
                while (!greta->collidingItems().isEmpty())
                    greta->move(0, -1);
            }
            else
                greta->move(0, -15);
        }
    }
}

void Trumpet::jump()
{
    return;
}

void Trumpet::fall()
{
    if (m_state >= 7)
        return;

    if (!m_isJumping)
    {
        move(0, 20);
        while (!collidingItems().isEmpty())
            move(0, -1);
    }
}

void Trumpet::die(QList<Entity*> *entitiesList)
{
    Greta *greta = qobject_cast<Greta*>(entitiesList->at(0));

    if (m_state > 8 && m_isHitCounter)
        return;

    if (x() - entitiesList->at(0)->x() <= GRETA_WIDTH + 90)
    {
        if (!greta->invincible())
            m_repulseGretaCounter = 1;
        if (m_state < TRUMPET_PHASE_2)
            return;
    }


    m_isHit = true;
    m_isHitCounter = 30;
    m_attackCooldownCounter = 45;
    m_HP--;

    if (m_state == TRUMPET_PHASE_2)
    {
        QVector<QPointF> entitiesPositions;

        for (qsizetype i = ENNEMIES_POS+1; i < entitiesList->length();)
        {
            entitiesPositions.append(entitiesList->at(i)->pos());
            qobject_cast<QGraphicsScene*>(parent())->removeItem(entitiesList->at(i));
            entitiesList->removeAt(i);
        }
        for (qsizetype i = 0; i < entitiesPositions.length(); i++)
        {
            addItemToScene(new Explosion(parent(),
                                         entitiesPositions.at(i).x() - (EXPLOSION_WIDTH - NUCLEARBOMB_WIDTH),
                                         entitiesPositions.at(i).y(),
                                         90),
                                         entitiesList);
        }
    }

    if (m_HP == 5)
    {
        m_state++;
        for (qsizetype i = ENNEMIES_POS+1; i < entitiesList->length();)
        {
            qobject_cast<QGraphicsScene*>(parent())->removeItem(entitiesList->at(i));
            entitiesList->removeAt(i);
        }
    }

    if (m_HP == 1)
    {
        greta->invincible(true);
    }

    if (!m_HP)
    {
        m_state++;
        m_elapsedTime = m_elapsedTimer->elapsed();
        for (qsizetype i = ENNEMIES_POS+1; i < entitiesList->length();)
        {
            qobject_cast<QGraphicsScene*>(parent())->removeItem(entitiesList->at(i));
            entitiesList->removeAt(i);
        }
    }
}

void Trumpet::updateX(QList<Entity*> *entitiesList)
{
    updateState(entitiesList);
    moveDirection(entitiesList);
    attack(entitiesList);
    collision(entitiesList);
    repulseGreta(entitiesList);
    fall();
}
