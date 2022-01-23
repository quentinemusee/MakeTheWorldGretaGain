#ifndef ENTITY_H
#define ENTITY_H

#include <cmath>
#include <iostream>

namespace direction
{
    typedef enum
    {
        NONE,
        RIGHT,
        LEFT
    } direction_t;
}

class Entity
{
    public :
        explicit Entity(const float efficientX = 0, const float efficientY = 0) :
                                                                                     m_x(efficientX),
                                                                                     m_y(efficientY),
                                                                                     m_efficientX(efficientX),
                                                                                     m_efficientY(efficientY),
                                                                                     m_width(200),
                                                                                     m_height(100),
                                                                                     m_spriteCounter(0),
                                                                                     m_frameCounter(0),
                                                                                     m_spriteCounterLimit(3),
                                                                                     m_frameCounterLimit(0),
                                                                                     m_invincible(false)
                                                                                     {}

        /* Getters & Setters */
        float x() const                   {return m_x;            }
        float y() const                   {return m_y;            }
        float efficientX() const          {return m_efficientX;   }
        float efficientY() const          {return m_efficientY;   }
        float width() const               {return m_width;        }
        float height() const              {return m_height;       }
        std::size_t spriteCounter() const {return m_spriteCounter;}
        bool invincible() const           {return m_invincible;   }
        void efficientX(const float efficientX)        {m_efficientX = efficientX;}
        void invincible(const bool invincible)         {m_invincible = invincible;}

        void spriteCounter(const float spriteCounter) {m_spriteCounter = spriteCounter; m_frameCounter = m_frameCounterLimit-1;}

        /* Utilities functions */
        float distance(const Entity *entity) const {return sqrt(pow((m_efficientX - entity->m_efficientX), 2) + pow((m_efficientY - entity->m_efficientY), 2));}

        /* Painting functions */
        void nextFrame() {
                              m_spriteCounter++;
                              if (m_spriteCounter == m_spriteCounterLimit)
                                  m_spriteCounter = 0;
                         }
        void addItemToScene(Entity *item, std::list<Entity*> *entitiesList) {entitiesList->push_back(item);}

        /* Collisions functions */
        bool collideWith(const Entity *entity) const {
                                                          return (x() - 12 < entity->x() + entity->width() &&
                                                                  x() + m_width > entity->x() - 12 &&
                                                                  y() - 12 < entity->y() + entity->height() &&
                                                                  y() + m_height > entity->y() - 12);
                                                     }


        /* Action functions */
        void move(const float dx, const float dy)                        {m_x += dx;m_y += dy; m_efficientX += dx, m_efficientY += dy;}
        void setPosition(const float dx, const float dy, const float y)  {m_x = dx; m_y = y; m_efficientX = dx;  m_efficientY = dy;  }

        /* Operators */
        Entity& operator+=(float shift) {
                                            move((float)((int)(shift)), 100*(float)(shift-(int)(shift)));
                                            return *this;
                                        }

    protected :
        float m_x, m_y, m_efficientX, m_efficientY;
        float m_width, m_height;
        std::size_t m_spriteCounter, m_frameCounter;
        std::size_t m_spriteCounterLimit, m_frameCounterLimit;
        bool m_invincible;
};

#endif // ENTITY_H
