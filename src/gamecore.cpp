/**
  Fichier qui contient toute la logique du jeu.
  
  @author   JCO
  @date     Février 2014
 */
#include "gamecore.h"

#include <cmath>

#include <QDebug>
#include <QSettings>

#include "gamescene.h"
#include "gamecanvas.h"
#include "resources.h"
#include "utilities.h"
#include "sprite.h"

const int SCENE_WIDTH = 3500;
const int SCENE_HEIGHT = 1000;
const int CHIUP_SPEED = 500;
const int ATTACK_RANGE = 50;

//! Initialise le contrôleur de jeu.
//! \param pGameCanvas  GameCanvas pour lequel cet objet travaille.
//! \param pParent      Pointeur sur le parent (afin d'obtenir une destruction automatique de cet objet).
GameCore::GameCore(GameCanvas* pGameCanvas, QObject* pParent) : QObject(pParent) {
    
    // Mémorise l'accès au canvas (qui gère le tick et l'affichage d'une scène)
    m_pGameCanvas = pGameCanvas;
    
    // Créé la scène de base et indique au canvas qu'il faut l'afficher.
    m_pScene = pGameCanvas->createScene(0, 0, SCENE_WIDTH,
                                        SCENE_WIDTH / GameFramework::screenRatio());
    // Image de fond
    /*m_pScene->setBackgroundImage(QImage(GameFramework::imagesPath() +
                                        "brickbreaker/map.png"));*/
    pGameCanvas->setCurrentScene(m_pScene);
    // Si on veut une scène dont les dimensions sont proportionnelles à celles de l'écran : createScene(0, 0, SCENE_WIDTH, SCENE_WIDTH / GameFramework::screenRatio());
    // Si on veut une scène dont les dimensions correspondent à celle de la fenêtre : createScene(0, 0, pGameCanvas->gameView()->size().width(), pGameCanvas->gameView()->size().height());
    pGameCanvas->setCurrentScene(m_pScene);
    
    // Trace un rectangle blanc tout autour des limites de la scène.
    m_pScene->addRect(m_pScene->sceneRect(), QPen(Qt::white));

    // Charge la carte avec les tiles
    loadMap();

    //nitialiser un point de spawn par défaut
    m_spawnPoint = QPointF(2 * TILE_SIZE, 2 * TILE_SIZE);
    
    // Instancier et initialiser les sprite ici :
    Sprite* pSprite = new Sprite(GameFramework::imagesPath() + "tutorial/player_m1.png");
    pSprite->setPos(20,20);
    m_pScene->addSpriteToScene(pSprite);
    // ...
    Sprite* pChiup = new Sprite(GameFramework::imagesPath() + "brickbreaker/Chiup.png"); // Sprite du personnage jouable
    m_pScene->addSpriteToScene(pChiup);
    pChiup->setPos(m_pScene->width()/2.0, m_pScene->height()/2.0);
    pChiup->addAnimationFrame(GameFramework::imagesPath() + "brickbreaker/Chiup2.png"); //Animation du personnage
    pChiup->startAnimation(200);

    m_pChiup = pChiup;

    //Création du monstre
    Sprite* pMonster = new Sprite(GameFramework::imagesPath() + "brickbreaker/Snake1.gif");
    pMonster->setPos(1000, 1000);
    pMonster->addAnimationFrame(GameFramework::imagesPath() + "brickbreaker/Snake2.png");
    pMonster->startAnimation(200);
    m_pScene->addSpriteToScene(pMonster);

    m_pMonster = pMonster;

    // Initialisation des états des touches
    m_keyUpPressed = false;
    m_keyDownPressed = false;
    m_keyLeftPressed = false;
    m_keyRightPressed = false;

    // Démarre le tick pour que les animations qui en dépendent fonctionnent correctement.
    // Attention : il est important que l'enclenchement du tick soit fait vers la fin de cette fonction,
    // sinon le temps passé jusqu'au premier tick (ElapsedTime) peut être élevé et provoquer de gros
    // déplacements, surtout si le déboggueur est démarré.
    m_pGameCanvas->startTick();

    // Création de l'NPC
    m_pNpc = new Sprite(GameFramework::imagesPath() + "brickbreaker/E.png");
    m_pNpc->setPos(900, 1200);
    m_pScene->addSpriteToScene(m_pNpc);

    // Définit les dialogues de l'NPC
    m_npcDialog << "E: Bonjour, comment ça va Chiup Chiup ?"
                << "E: Tu veux m'aider pour une quete ?"
                << "E: En echange je t'aide pour retrouver la princesse";
}

//! Destructeur de GameCore : efface les scènes
GameCore::~GameCore() {
    delete m_pScene;
    m_pScene = nullptr;
}

//! Traite le relâchement d'une touche.
//! \param key Numéro de la touche (voir les constantes Qt)
void GameCore::keyReleased(int key) {
    switch (key) {
    case Qt::Key_Up:    m_keyUpPressed      = false; break;
    case Qt::Key_Down:  m_keyDownPressed    = false; break;
    case Qt::Key_Left:  m_keyLeftPressed    = false; break;
    case Qt::Key_Right: m_keyRightPressed   = false; break;
    }
}

//! Cadence.
//! \param elapsedTimeInMilliseconds  Temps écoulé depuis le dernier appel.
void GameCore::tick(long long elapsedTimeInMilliseconds) {
    // Calcul du déplacement en fonction des touches pressées
    qreal deltaX = 0;
    qreal deltaY = 0;
    if (m_keyUpPressed)    deltaY -= CHIUP_SPEED;
    if (m_keyDownPressed)  deltaY += CHIUP_SPEED;
    if (m_keyLeftPressed)  deltaX -= CHIUP_SPEED;
    if (m_keyRightPressed) deltaX += CHIUP_SPEED;

    QPointF delta(deltaX * elapsedTimeInMilliseconds / 1000,
                  deltaY * elapsedTimeInMilliseconds / 1000);

    // Mise à jour de la nouvelle position
    QPointF newPosition = m_pChiup->pos() + delta;

    // Vérification des limites de la scène
    QRectF spriteBounds = m_pChiup->boundingRect().translated(newPosition);
    if (m_pScene->isInsideScene(spriteBounds) && canMoveTo(newPosition.x(), newPosition.y())) {
        m_pChiup->setPos(newPosition);
    }

    // Centre la caméra sur le personnage
    m_pScene->centerViewOn(m_pChiup);
}

//!
//! \brief GameCore::canMoveTo
//! \param x
//! \param y
//! \return le type de tiles sur lesquels le joueur peut marcher
//!
bool GameCore::canMoveTo(qreal x, qreal y) {
    int tileX = static_cast<int>(x + TILE_SIZE / 2) / TILE_SIZE;
    int tileY = static_cast<int>(y + TILE_SIZE / 2) / TILE_SIZE;

    qDebug() << "Checking move to (" << x << "," << y << ")";
    qDebug() << "Corresponding tile: (" << tileX << "," << tileY << ") -> Type:" << m_map[tileY][tileX];

    if (tileX < 0 || tileX >= MAP_WIDTH || tileY < 0 || tileY >= MAP_HEIGHT) {
        qDebug() << "Out of bounds!";
        return false;
    }

    int tileType = m_map[tileY][tileX];

    bool canMove = (tileType == 0 || tileType == 3 || tileType == 5 || tileType == 6);
    qDebug() << "Can move? " << canMove;

    return canMove;
}

//!
//! \brief GameCore::canHitMonster
//! \return
//!
bool GameCore::canHitMonster() {
    qreal dist = QLineF(m_pChiup->pos(), m_pMonster->pos()).length();
    return dist <= ATTACK_RANGE;
}

void GameCore::keyPressed(int key) {
    switch (key)  {
    case Qt::Key_Up:    m_keyUpPressed      = true; break;
    case Qt::Key_Down:  m_keyDownPressed    = true; break;
    case Qt::Key_Right: m_keyRightPressed   = true; break;
    case Qt::Key_Left:  m_keyLeftPressed    = true; break;
    case Qt::Key_Space: {
        if (canHitMonster()) {
            qDebug() << "Vous avez frappé le monstre!";
            // Réduire la vie du monstre ou supprimer le monstre
            m_pScene->removeSpriteFromScene(m_pMonster);
            delete m_pMonster;
            m_pMonster = nullptr;
        }
        break;
    }
    case Qt::Key_J: {
        // Vérifier la distance entre le joueur et l'NPC
        qreal dist = QLineF(m_pChiup->pos(), m_pNpc->pos()).length();
        if (dist < 100) {
            //affiche un dialogue du NPC et permet de passer à un suivant
            if (m_dialogIndex < m_npcDialog.size()) {
                qDebug() << "E: " << m_npcDialog[m_dialogIndex];
                m_dialogIndex++;
            } else {
                qDebug() << "E: d'accord a plus tard !";
                m_dialogIndex = 0;
            }
        }
        break;
    }
    }
}

//! La souris a été déplacée.
//! Pour que cet événement soit pris en compte, la propriété MouseTracking de GameView
//! doit être enclenchée avec GameCanvas::startMouseTracking().
void GameCore::mouseMoved(QPointF newMousePosition) {
    emit notifyMouseMoved(newMousePosition);
}

//! Traite l'appui sur un bouton de la souris.
void GameCore::mouseButtonPressed(QPointF mousePosition, Qt::MouseButtons buttons) {
    emit notifyMouseButtonPressed(mousePosition, buttons);
}

//! Traite le relâchement d'un bouton de la souris.
void GameCore::mouseButtonReleased(QPointF mousePosition, Qt::MouseButtons buttons) {
    emit notifyMouseButtonReleased(mousePosition, buttons);
}

//!
//! \brief GameCore::loadMap
//! parcourt la map et les images correspondantes pour chaque tuile
void GameCore::loadMap() {
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            QString tileImage;

            switch (m_map[y][x]) {
            case 0: tileImage = "brickbreaker/way.png"; break;
            case 1: tileImage = "brickbreaker/bush.png"; break;
            case 2: tileImage = "brickbreaker/plant.png"; break;
            case 3: tileImage = "brickbreaker/grass.png"; break;
            case 4: tileImage = "brickbreaker/water.png"; break;
            case 5: tileImage = "brickbreaker/sand.jpg"; break;
            case 6: tileImage = "brickbreaker/dalle.png"; break;
            default: tileImage = "brickbreaker/grass.png"; break;
            }

            Sprite* tile = new Sprite(GameFramework::imagesPath() + tileImage);
            tile->setPos(x * TILE_SIZE, y * TILE_SIZE);
            m_pScene->addSpriteToScene(tile);
        }
    }
}

void GameCore::setSpawnPoint(int x, int y) {

    // Vérifie si la case est valide (sol libre)
    if (x >= 0 && x < MAP_WIDTH && y >= 0 && y < MAP_HEIGHT && m_map[y][x] == 0)
    {
        m_spawnPoint = QPointF(x * TILE_SIZE, y * TILE_SIZE);
    }
    else
    {
        qWarning() << "Position de spawn invalide";
    }
}

