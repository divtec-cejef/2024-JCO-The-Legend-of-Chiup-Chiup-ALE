/**
  \file
  \brief    Déclaration de la classe RigidFollowerTickHandler.
  \author   JCO
  \date     décembre 2023
*/
#ifndef RIGIDFOLLOWERTICKHANDLER_H
#define RIGIDFOLLOWERTICKHANDLER_H

#include "followertickhandler.h"

class RigidFollowerTickHandler : public FollowerTickHandler
{
public:
    RigidFollowerTickHandler(Sprite* pSpriteToFollow, int delay = 20, Sprite* pParentSprite = nullptr);

    void tick(long long elapsedTimeInMilliseconds) override;

private:
    QQueue<QPointF> m_posQueue;
    int m_delayMillisecs;
    int m_shiftAmount = -1;

};

#endif // RIGIDFOLLOWERTICKHANDLER_H
