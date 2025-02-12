/**
  \file
  \brief    Définition de la classe FollowerTickHandler.
  \author   JCO
  \date     décembre 2023
*/
#include "followertickhandler.h"
#include "sprite.h"

#include <QGraphicsItem>


FollowerTickHandler::FollowerTickHandler(Sprite* pSpriteToFollow,
                                         Sprite* pParentSprite) : SpriteTickHandler(pParentSprite),
    m_pSpriteToFollow(pSpriteToFollow)
{
}
