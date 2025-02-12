/**
  \file
  \brief    Déclaration de la classe FollowerTickHandler.
  \author   JCO
  \date     décembre 2023
*/
#ifndef FOLLOWERTICKHANDLER_H
#define FOLLOWERTICKHANDLER_H

#include "spritetickhandler.h"

#include <QLineF>
#include <QPointF>
#include <QQueue>

//! \brief Gestionnaire de déplacement qui suit un sprite cible.
//!
//! Gestionnaire de déplacement qui se base sur le tick.
//!
//! Déplace le sprite de sorte qu'il suive un autre sprite donné.
//!
//! Cette classe est abstraite et ne se charge que de mémoriser le sprite
//! qu'il faudra suivre (m_pSpriteToFollow).
//!
//! La façon dont le sprite est suivi doit être implémenté dans une classe dérivée.
//!
class FollowerTickHandler : public SpriteTickHandler
{
public:

    FollowerTickHandler(Sprite* pSpriteToFollow, Sprite* pParentSprite = nullptr);

protected:
    Sprite* m_pSpriteToFollow = nullptr;

};

#endif // FOLLOWERTICKHANDLER_H
