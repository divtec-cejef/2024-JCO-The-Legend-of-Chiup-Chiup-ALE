/**
  \file
  \brief    Définition de la classe RigidFollowerTickHandler.
  \author   JCO
  \date     décembre 2023
*/
#include "rigidfollowertickhandler.h"

#include "sprite.h"

//! Construit un gestionnaire qui suit un sprite donné de façon rigide.
//! \param pSpriteToFollow Sprite à suivre.
//! \param delay           Temps (en millisecondes) de décalage avec le sprite à suivre.
//! \param pParentSprite   Sprite à contrôler.
RigidFollowerTickHandler::RigidFollowerTickHandler(Sprite *pSpriteToFollow, int delay, Sprite *pParentSprite) :
    FollowerTickHandler(pSpriteToFollow, pParentSprite)
{
    m_delayMillisecs = delay;
}

//! Cadence de déplacement.
void RigidFollowerTickHandler::tick(long long elapsedTimeInMilliseconds)
{
    // Calcul approximativement le décalage de position selon le décalage temporel souhaité.
    int shiftAmount = m_delayMillisecs / elapsedTimeInMilliseconds;

    m_posQueue.enqueue(m_pSpriteToFollow->pos());
    if (m_posQueue.count() >= shiftAmount) {
        m_pParentSprite->setPos(m_posQueue.dequeue());
    }
}


