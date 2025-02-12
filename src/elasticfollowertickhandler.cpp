/**
  \file
  \brief    Définition de la classe ElasticFollowerTickHandler.
  \author   JCO
  \date     décembre 2023
*/
#include "elasticfollowertickhandler.h"

#include "sprite.h"

const float ELASTIC_MAX_TENSION = 1.0f;

//! Construit un gestionnaire qui suit un sprite donné de façon élastique.
//! \param pSpriteToFollow Sprite à suivre.
//! \param elasticity      Elasticité.
//! \param pParentSprite   Sprite à contrôler.
//!
ElasticFollowerTickHandler::ElasticFollowerTickHandler(Sprite *pSpriteToFollow,
                                                       float elasticity,
                                                       Sprite *pParentSprite) :
    FollowerTickHandler(pSpriteToFollow, pParentSprite)
{
    setElasticity(elasticity);
}

//! Mémorise la distance qui sépare ce sprite du sprite à suivre.
//! C'est cette distance qui sera toujours conservée.
void ElasticFollowerTickHandler::init()
{
    m_initialDistance = distanceToSpriteToFollow();
}

//! Cadence de déplacement.
void ElasticFollowerTickHandler::tick(long long elapsedTimeInMilliseconds)
{
    Q_UNUSED(elapsedTimeInMilliseconds);
    Q_ASSERT(m_pSpriteToFollow);
    Q_ASSERT(m_pParentSprite);

    int currentDistance = distanceToSpriteToFollow();

    // Si la distance entre les deux sprites dépasse la distance initiale, la tension
    // augment petit à petit, sinon elle diminue.
    if (currentDistance > m_initialDistance)
        m_elasticTension += 0.1;
    else if (currentDistance < m_initialDistance)
        m_elasticTension -= 0.2;
    else
        m_elasticTension = 0;

    m_elasticTension = qBound(0., m_elasticTension, ELASTIC_MAX_TENSION);

    // Réduit la distance entre ce sprite et le sprite cible en tenant compte de la tension sur
    // l'élastique (plus elle est grande, plus le déplacement sera important) et l'élasticité
    // (plus elle est grande, moins le déplacement sera important)
    float moveDistance = qAbs(currentDistance - m_initialDistance) * m_elasticTension / m_elasticity;

    // Détermine la trajectoire et la distance à parcourir et calcul la coordonnée d'arrivée.
    QLineF lineToSprite = lineToSpriteToFollow();
    QPointF direction = lineToSprite.unitVector().p2() - lineToSprite.unitVector().p1();
    QPointF destPoint = direction * moveDistance;
    m_pParentSprite->moveBy(destPoint.x(), destPoint.y());
}

//! \return l'élasticité de ce gestionnaire.
//!
float ElasticFollowerTickHandler::elasticity() const
{
    return m_elasticity;
}

//! Change l'elasticité de ce gestionnaire.
//! \param newElasticity Nouvelle élasticité. Doit être supérieure ou égale à 1.
void ElasticFollowerTickHandler::setElasticity(float newElasticity)
{
    m_elasticity = qBound(1.0F, newElasticity, 100.F);
}

//! \return le vecteur reliant les deux sprites.
QLineF ElasticFollowerTickHandler::lineToSpriteToFollow() const {
    QPointF posA = m_pParentSprite->pos();
    QPointF posB = m_pSpriteToFollow->pos();

    return QLineF(posA, posB);
}

//! \return la distance entre les deux sprites.
float ElasticFollowerTickHandler::distanceToSpriteToFollow() const {
    return lineToSpriteToFollow().length();
}
