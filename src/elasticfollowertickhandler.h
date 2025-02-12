/**
  \file
  \brief    Déclaration de la classe FollowerTickHandler.
  \author   JCO
  \date     décembre 2023
*/
#ifndef ELASTICFOLLOWERTICKHANDLER_H
#define ELASTICFOLLOWERTICKHANDLER_H

#include "followertickhandler.h"

//! \brief Gestionnaire de déplacement qui suit un autre sprite de façon élastique.
//!
//! Gestionnaire de déplacement qui se base sur le tick.
//!
//! Ce gestionnaire de déplacement maintient la distance entre la sprite à gérer et
//! le sprite à suivre. Si c'est distance grandi car le sprite à suivre bouge, le
//! sprite à géré se déplace de façon élastique afin de retrouver la distance initiale
//! entre les deux sprites.
//!
//! L'élasticité peut être ajustée avec setElasticity().
//!
class ElasticFollowerTickHandler : public FollowerTickHandler
{
public:
    ElasticFollowerTickHandler(Sprite* pSpriteToFollow, float elasticity = 5.F, Sprite* pParentSprite = nullptr);

    void init() override;
    void tick(long long elapsedTimeInMilliseconds) override;

    float elasticity() const;
    void setElasticity(float newElasticity);

private:
    int m_initialDistance = 0;
    float m_elasticTension = 0.0f;
    float m_elasticity = 0;

    QLineF lineToSpriteToFollow() const;
    float distanceToSpriteToFollow() const;

};

#endif // ELASTICFOLLOWERTICKHANDLER_H
