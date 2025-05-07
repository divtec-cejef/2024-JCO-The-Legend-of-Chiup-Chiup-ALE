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

const int SCENE_WIDTH = 5500;
const int SCENE_HEIGHT = 4000;
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

    //Initialise le timer pour la réapparition du monstre
    m_respawnTimer = new QTimer(this);
    connect(m_respawnTimer, &QTimer::timeout, this, &GameCore::respawnMonster);

    //Création du monstre
    Sprite* pMonster = new Sprite(GameFramework::imagesPath() + "brickbreaker/Snake1.gif");
    pMonster->setPos(1000, 1000);
    pMonster->addAnimationFrame(GameFramework::imagesPath() + "brickbreaker/Snake2.png");
    pMonster->startAnimation(200);
    m_pScene->addSpriteToScene(pMonster);

    Monster* monster = new Monster(pMonster, 100, 1, pMonster->pos());
    m_monsters.append(monster);

    // Barre de vie
    m_healthBarBackground = new QGraphicsRectItem(0, 0, 100, 10);
    m_healthBarBackground->setBrush(Qt::gray);
    m_healthBarBackground->setPos(10, 10);
    m_pScene->addItem(m_healthBarBackground);

    m_healthBar = new QGraphicsRectItem(0, 0, 100, 10);
    m_healthBar->setBrush(Qt::green);
    m_healthBar->setPos(10, 10);
    m_pScene->addItem(m_healthBar);

    // Création de la barre de vie
    m_healthBarBackground = new QGraphicsRectItem(0, 0, 100, 10);
    m_healthBarBackground->setBrush(Qt::gray);
    m_pScene->addItem(m_healthBarBackground);
    m_healthBarBackground->setPos(pMonster->pos().x(), pMonster->pos().y() - 20);

    m_healthBar = new QGraphicsRectItem(0, 0, 100, 10);
    m_healthBar->setBrush(Qt::red);
    m_pScene->addItem(m_healthBar);
    m_healthBar->setPos(pMonster->pos().x(), pMonster->pos().y() - 20);

    // Barre d'XP
    m_xpBarBackground = new QGraphicsRectItem(0, 0, 100, 5);
    m_xpBarBackground->setBrush(Qt::gray);
    m_xpBarBackground->setPos(10, 25);
    m_pScene->addItem(m_xpBarBackground);

    m_xpBar = new QGraphicsRectItem(0, 0, 0, 5);
    m_xpBar->setBrush(Qt::blue);
    m_xpBar->setPos(10, 25);
    m_pScene->addItem(m_xpBar);

    // Texte de niveau
    m_levelText = new QGraphicsTextItem(QString("Niv. %1").arg(m_level));
    m_levelText->setDefaultTextColor(Qt::white);
    m_levelText->setFont(QFont("Arial", 10, QFont::Bold));
    m_levelText->setPos(120, 15);
    m_pScene->addItem(m_levelText);

    // Initialisation du timer pour la disparition du monstre
    m_deathTimer = new QTimer(this);
    connect(m_deathTimer, &QTimer::timeout, this, &GameCore::onMonsterDeath);

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

    //création de la bulle de dialogue
    m_pDialogueBubble = new QGraphicsTextItem();
    m_pDialogueBubble->setPlainText("");
    m_pDialogueBubble->setDefaultTextColor(Qt::white);
    m_pDialogueBubble->setFont(QFont("Arial", 12));
    m_pScene->addItem(m_pDialogueBubble);
    m_pDialogueBubble->setPos(200, 900);

    //centre la bulle
    m_pDialogueBubble->setPos(SCENE_WIDTH / 2 - 100, SCENE_HEIGHT - 50);

    // Création de l'NPC
    m_pNpc = new Sprite(GameFramework::imagesPath() + "brickbreaker/E.png");
    m_pNpc->setPos(900, 1200);
    m_pScene->addSpriteToScene(m_pNpc);

    // Définit les dialogues de l'NPC
    m_npcDialog << "Mh ? Oh un bonhomme rose... qu'est ce que je peux faire pour toi ?"
                << "Tu veux aller battre Ganon pour sauver ta princesse ?"
                << "*reflechis et te regarde de travers* mais ça va pas la tete ?"
                << "Tu va jamais survivre avec la silouhette que t'as..."
                << "Mais je pense que je peux t'aider... vas me tuer un certain nombre de serpents."
                << "Et tu reviens me voir quand tu te sentiras prete.";

    //création du texte pour indiquer l'action
    m_pTalkHint = new QGraphicsTextItem("Appuie sur E pour parler");
    m_pTalkHint->setDefaultTextColor(Qt::yellow);
    m_pTalkHint->setFont(QFont("Arial", 10));
    m_pTalkHint->setVisible(false);
    m_pScene->addItem(m_pTalkHint);
    m_pTalkHint->setPos(m_pNpc->pos().x(), m_pNpc->pos().y() - 30);

    //création de la bulle de dialogue
    m_pDialogueBubble = new QGraphicsTextItem();
    m_pDialogueBubble->setPlainText("");
    m_pDialogueBubble->setDefaultTextColor(Qt::black);
    m_pDialogueBubble->setFont(QFont("Arial", 12));
    m_pScene->addItem(m_pDialogueBubble);

    //Créer un fond blanc derrière la bulle
    m_pDialogueBackground = new QGraphicsRectItem();
    m_pDialogueBackground->setBrush(Qt::white);
    m_pDialogueBackground->setPen(Qt::NoPen);
    m_pDialogueBackground->setZValue(m_pDialogueBubble->zValue() - 1);
    m_pScene->addItem(m_pDialogueBackground);

    // Position initiale de la bulle
    m_pDialogueBubble->setVisible(false);
    m_pDialogueBubble->setZValue(1000);
    m_pDialogueBubble->setPos(m_pNpc->pos().x() - 50, m_pNpc->pos().y() - 60);
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

void GameCore::updateDialogueBubble(const QString& text) {
    qDebug() << "text: " << text;
    if (m_pDialogueBubble && m_pDialogueBackground) {
        m_pDialogueBubble->setPlainText(text);
        m_pDialogueBubble->setVisible(true);

        QRectF textRect = m_pDialogueBubble->boundingRect();
        m_pDialogueBackground->setRect(textRect.adjusted(-10, -10, 10, 10));
        m_pDialogueBackground->setPos(m_pDialogueBubble->pos());
        m_pDialogueBackground->setVisible(true);
    } else {
        m_pDialogueBubble->setVisible(false);
        m_pDialogueBackground->setVisible(false);
    }
}

void GameCore::npcDialogue()
{
    if (!m_pNpc || !m_pChiup)
        return;

    qreal distance = QLineF(m_pNpc->pos(), m_pChiup->pos()).length();
    if (distance < 100)
    {
        if (m_dialogIndex < m_npcDialog.size()) {
            updateDialogueBubble(m_npcDialog[m_dialogIndex]);
            m_dialogIndex++;
        } else {
            updateDialogueBubble("");
            m_dialogIndex = 0;
        }
    }
}

void GameCore::spawnFinalBoss() {
    m_pBoss = new Sprite(GameFramework::imagesPath() + "brickbreaker/Boss.png");
    m_pBoss->addAnimationFrame(GameFramework::imagesPath() + "brickbreaker/Boss2.png");
    m_pBoss->addAnimationFrame(GameFramework::imagesPath() + "brickbreaker/Boss3.png");
    m_pBoss->addAnimationFrame(GameFramework::imagesPath() + "brickbreaker/Boss4.png");
    m_pBoss->addAnimationFrame(GameFramework::imagesPath() + "brickbreaker/Boss5.png");
    m_pBoss->addAnimationFrame(GameFramework::imagesPath() + "brickbreaker/Boss6.png");
    m_pBoss->addAnimationFrame(GameFramework::imagesPath() + "brickbreaker/Boss8.png");
    m_pBoss->startAnimation(300);
    m_pBoss->setPos(2750, 400);

    m_pScene->addSpriteToScene(m_pBoss);

    //barre de vie du boss
    m_healthBarBackground = new QGraphicsRectItem(0, 0, 100, 10);
    m_healthBarBackground->setBrush(Qt::gray);
    m_healthBarBackground->setPos(m_pBoss->pos().x(), m_pBoss->pos().y() - 20);
    m_pScene->addItem(m_healthBarBackground);

    m_healthBarBoss = new QGraphicsRectItem(0, 0, 100, 10);
    m_healthBarBoss->setBrush(Qt::red);
    m_healthBarBoss->setPos(m_pBoss->pos().x(), m_pBoss->pos().y() - 20);
    m_pScene->addItem(m_healthBarBoss);

    bossActive = true;
}

void GameCore::moveBossToPlayer() {
    if (!m_pBoss || !m_pChiup || !bossActive) return;

    // Calcul de la distance entre boss et joueur
    qreal distance = QLineF(m_pBoss->pos(), m_pChiup->pos()).length();

    // Si joueur est trop loin -> on ne fait rien
    if (distance > 500) return;

    // Si joueur est dans la portée d'attaque -> boss attaque
    if (distance < BOSS_ATTACK_RANGE) {
        bossAttack();
        return;
    }

    // Calcul vecteur de déplacement vers joueur
    qreal dx = m_pChiup->pos().x() - m_pBoss->pos().x();
    qreal dy = m_pChiup->pos().y() - m_pBoss->pos().y();
    qreal length = sqrt(dx * dx + dy * dy);

    if (length > 0) {
        dx /= length;
        dy /= length;
    }

    // Déplacement du boss vers joueur
    QPointF newPosition = m_pBoss->pos() + QPointF(dx * BOSS_SPEED * 0.01, dy * BOSS_SPEED * 0.01);
    m_pBoss->setPos(newPosition);
}

void GameCore::bossAttack() {

    // Appliquer des dégâts au joueur
    takeDamage(20);

    // Effet visuel
    QPixmap originalPixmap = m_pChiup->pixmap();
    QImage image = originalPixmap.toImage();

    // Applique un filtre rouge sur l'image
    for (int y = 0; y < image.height(); ++y) {
        for (int x = 0; x < image.width(); ++x) {
            QColor color = image.pixelColor(x, y);
            color.setRed(255);
            color.setGreen(0);
            color.setBlue(0);
            image.setPixelColor(x, y, color);
        }
    }

    // Appliquer l'image modifiée au sprite
    m_pChiup->setPixmap(QPixmap::fromImage(image));

    QTimer::singleShot(200, this, [this, originalPixmap]() {
        m_pChiup->setPixmap(originalPixmap);
    });
}


//!
//! \brief GameCore::takeDamage
//! \param damage
//!
void GameCore::takeDamage(int damage) {
    onMonsterDeath();
}

void GameCore::winXp(int amount, QPointF pos) {
    m_xp += amount;

    QGraphicsTextItem* xpText = new QGraphicsTextItem(QString("+%1 XP").arg(amount));
    xpText->setDefaultTextColor(Qt::yellow);
    xpText->setFont(QFont("Arial", 10, QFont::Bold));
    m_pScene->addItem(xpText);
    xpText->setPos(pos.x(), pos.y() - 40);

    QTimer::singleShot(1000, this, [=]() {
        m_pScene->removeItem(xpText);
        delete xpText;
    });

    while (m_xp >= m_xpToNextLevel) {
        m_xp -= m_xpToNextLevel;
        m_level++;
        m_xpToNextLevel += 50;

        if (m_level == 2 && !spawnBoss) {
            spawnFinalBoss();
            spawnBoss = true;
        }
    }

    updateXpBar();
}


void GameCore::updateXpBar() {
    double ratio = static_cast<double>(m_xp) / m_xpToNextLevel;
    m_xpBar->setRect(0, 0, 100 * ratio, 5);

    m_levelText->setPlainText(QString("Niv. %1").arg(m_level));
}

//!
//! \brief GameCore::onMonsterDeath
//!
void GameCore::onMonsterDeath() {
    QPixmap deadPixmap(GameFramework::imagesPath() + "brickbreaker/DeadSnake.png");

    for (Monster* m : m_monsters) {
        if (!m->alive) {
            m->sprite->setPixmap(deadPixmap);
            winXp(100, m->sprite->pos());
        }
    }

    m_deathTimer->stop();
    m_respawnTimer->start(200);
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

    // Mise à jour la position de la barre de vie pour qu'elle suive le monstre
    for (Monster* m : m_monsters) {
        if (!m->alive) continue;

        double ratio = static_cast<double>(m->health) / m->maxHealth;

        m_healthBar->setPos(m->sprite->pos().x(), m->sprite->pos().y() - 20);
        m_healthBarBackground->setPos(m->sprite->pos().x(), m->sprite->pos().y() - 20);
        m_healthBar->setRect(0, 0, 100 * ratio, 10);
    }

    // Centre la caméra sur le personnage
    m_pScene->centerViewOn(m_pChiup);

    // Vérifier si le joueur est en collision avec le monstre
    checkMonsterCollision();

    monsterDistance();

    //Dialogue
    if (QLineF(m_pChiup->pos(), m_pNpc->pos()).length() < 100) {
        m_pTalkHint->setVisible(true);
    } else {
        m_pTalkHint->setVisible(false);
    }

    moveBossToPlayer();

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
        return false;
    }

    int tileType = m_map[tileY][tileX];

    bool canMove = (tileType == 0 || tileType == 3 || tileType == 5 || tileType == 6);

    return canMove;
}

//!
//! \brief GameCore::canHitMonster
//! \return
//!
bool GameCore::canHitMonster() {
    for (Monster* m : m_monsters) {
        if (m->alive && QLineF(m->sprite->pos(), m_pChiup->pos()).length() <= ATTACK_RANGE) {
            return true;
        }
    }
    return false;
}

void GameCore::checkMonsterCollision() {
    // Vérifier si le joueur est en collision avec le monstre
    for (Monster* monster : m_monsters) {
        if (monster->alive && m_pChiup->collidesWithItem(monster->sprite)) {
            takeDamage();
        }
    }
}

void GameCore::takeDamage() {
    m_health -= MONSTER_DAMAGE;
    if (m_health <= 0) {
        m_health = 0;
    }

    QPixmap originalPixmap = m_pChiup->pixmap();
    QImage image = originalPixmap.toImage();

    // Applique un filtre rouge sur l'image
    for (int y = 0; y < image.height(); ++y) {
        for (int x = 0; x < image.width(); ++x) {
            QColor color = image.pixelColor(x, y);
            color.setRed(255);
            color.setGreen(0);
            color.setBlue(0);
            image.setPixelColor(x, y, color);
        }
    }

    // Appliquer l'image modifiée au sprite
    m_pChiup->setPixmap(QPixmap::fromImage(image));

    QTimer::singleShot(200, this, [this, originalPixmap]() {
        m_pChiup->setPixmap(originalPixmap);
    });
}


void GameCore::monsterDistance() {
    for (Monster* m : m_monsters) {
        if (!m || !m->alive) continue;

        qreal dist = QLineF(m->sprite->pos(), m_pChiup->pos()).length();
        if (dist < 100) {
        }
    }
}


void GameCore::keyPressed(int key) {
    switch (key)  {
    case Qt::Key_Up:    m_keyUpPressed      = true; break;
    case Qt::Key_Down:  m_keyDownPressed    = true; break;
    case Qt::Key_Right: m_keyRightPressed   = true; break;
    case Qt::Key_Left:  m_keyLeftPressed    = true; break;
    case Qt::Key_E:     npcDialogue();       break;
    case Qt::Key_Space: {
        for (Monster* m : m_monsters) {
            if (m->alive && QLineF(m->sprite->pos(), m_pChiup->pos()).length() <= ATTACK_RANGE) {
                m->health -= 10;
                if (m->health <= 0) {
                    m->alive = false;
                    onMonsterDeath();
                }
                break;
            }
        }
    }
    }
}


//! Mise à jour de la taille de la barre de vie
void GameCore::updateHealthBar() {
    if (m_currentHealth < 0) m_currentHealth = 0;

    float healthPercent = (float)m_currentHealth / m_maxHealth;
    m_healthBar->setRect(0, 0, 100 * healthPercent, 10);

    if (healthPercent > 0.5) {
        m_healthBar->setBrush(Qt::green);
    } else if (healthPercent > 0.2) {
        m_healthBar->setBrush(Qt::yellow);
    } else {
        m_healthBar->setBrush(Qt::red);
    }
}

void GameCore::spawnMonsters() {
    QVector<QPointF> spawnPoints = { {1000, 1000}, {1200, 800}, {1400, 600} };

    for (int i = 0; i < spawnPoints.size(); ++i) {
        Sprite* s = new Sprite(GameFramework::imagesPath() + "brickbreaker/Snake1.gif");
        s->addAnimationFrame(GameFramework::imagesPath() + "brickbreaker/Snake2.png");
        s->startAnimation(200);
        s->setPos(spawnPoints[i]);
        m_pScene->addSpriteToScene(s);

        Monster* m = new Monster(s, 50 + i * 20, 1 + i, spawnPoints[i]);
        m_monsters.append(m);
    }
}

//! Réinitialiser la position du monstre et la vie du monstre
void GameCore::respawnMonster() {
    for (Monster* m : m_monsters) {
        m->alive = true;
        m->health = m->maxHealth;
        m->sprite->setPixmap(QPixmap(GameFramework::imagesPath() + "brickbreaker/Snake1.gif"));
        m->sprite->setPos(m->position);
    }
    m_respawnTimer->stop();
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

