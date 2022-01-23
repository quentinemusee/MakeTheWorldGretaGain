#ifndef CHARACTER_H
#define CHARACTER_H

#include <QGraphicsView>
#include "entity.h"

#define FRAME_COUNT 10

class Character : public Entity
{
    Q_OBJECT
    public :
        /* Constructors */
        explicit Character(QObject *parent = nullptr, const qreal efficientX = 0, const qreal efficientY = 0) : Entity(parent, efficientX, efficientY),
                                                                                                                m_lastDirection(direction::NONE),
                                                                                                                m_jumpCount(0),
                                                                                                                m_attackCooldownCounter(0),
                                                                                                                m_isJumping(false)
                                                                                                                {}

        /* Getters and setters */
        direction::direction_t lastDirection() const  {return m_lastDirection;        }
        qsizetype attackCooldownCounter() const       {return m_attackCooldownCounter;}
        bool isJumping() const                        {return m_isJumping;            }
        qsizetype jumpCount() const                   {return m_jumpCount;            }

        /* Collisions functions */
        virtual QPainterPath shape() const override {
                                                        QPainterPath path;
                                                        path.addRect(boundingRect());
                                                        return path;
                                                    }
        /* Collisions */
        virtual void collision(QList<Entity*> *entitiesList)  override {
                                                                            if (entitiesList->at(0)->invincible())
                                                                                return;

                                                                            qsizetype gretaX = entitiesList->at(0)->x();
                                                                            qsizetype gretaY = entitiesList->at(0)->y();

                                                                            if (collideWith(entitiesList->at(0)))
                                                                            {
                                                                                qDebug() << "Greta's y : " << gretaY;
                                                                                qDebug() << "Greta's x : " << gretaX;
                                                                                qDebug() << "Ennemie's y : " << y();
                                                                                qDebug() << "Ennemie's x : " << x();
                                                                                qobject_cast<Character*>(entitiesList->at(0))->die(entitiesList);
                                                                            }
                                                                        }

        /* Painting functions */
        virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override = 0;
        virtual void incrementFrameCounter() override {
                                                           m_frameCounter += 1;
                                                           if (m_frameCounter >= FRAME_COUNT)
                                                           {
                                                               m_frameCounter = 0;
                                                               nextFrame();
                                                           }
                                                       }
        virtual void resetFrameCounter(const direction::direction_t direction) {
                                                                                   m_lastDirection = direction;
                                                                                   m_frameCounter = FRAME_COUNT-1;
                                                                                   m_spriteCounter = 0;
                                                                               }
        void face(const Entity *entity) {
                                            if (x() > entity->x())
                                                    resetFrameCounter(direction::LEFT);
                                            else
                                                resetFrameCounter(direction::RIGHT);
                                        }

        /* Actions functions */
        virtual void moveDirection(QList<Entity*> *entitiesList) = 0;
        virtual void attack(QList<Entity*> *entitiesList) = 0;
        virtual void jump() = 0;
        virtual void fall() = 0;

        /* Update functions */
        virtual void updateX(QList<Entity*> *entitiesList) override = 0;

    protected :
        direction::direction_t m_lastDirection;
        qsizetype m_jumpCount, m_attackCooldownCounter;;
        bool m_isJumping;
};

#endif // CHARACTER_H
