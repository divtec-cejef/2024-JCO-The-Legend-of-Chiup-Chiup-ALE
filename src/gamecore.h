/**
  \file
  \brief    Déclaration de la classe GameCore.
  \author   JCO
  \date     septembre 2018
*/
#define GAMECORE_H

#include <QObject>
#include <QPointF>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QVector>
#include <QDebug>

#include <QTimer>


class GameCanvas;
class GameScene;
class Sprite;

struct Monster {
    Sprite* sprite;
    int health;
    int maxHealth;
    int level;
    QPointF position;
    bool alive;

    Monster(Sprite* s, int hp, int lvl, QPointF pos)
        : sprite(s), health(hp), maxHealth(hp), level(lvl), position(pos), alive(true) {}
};

//! \brief Classe qui gère la logique du jeu.
//!
//! Dans son état actuel, cette classe crée une scène vide, délimite
//! sa surface avec une ligne blanche puis démarre la cadence du jeu.
class GameCore : public QObject
{
    Q_OBJECT
public:
    explicit GameCore(GameCanvas* pGameCanvas, QObject *parent = nullptr);
    ~GameCore() override;

    //Déclarez la fonction canHitMonster
    bool canHitMonster();

    void keyPressed(int key);
    void keyReleased(int key);

    void mouseMoved(QPointF newMousePosition);
    void mouseButtonPressed(QPointF mousePosition, Qt::MouseButtons buttons);
    void mouseButtonReleased(QPointF mousePosition, Qt::MouseButtons buttons);

    void tick(long long elapsedTimeInMilliseconds);

    //Initialiser la santé du monstre
    void initializeMonsterHealth(int initialHealth);

    //définir le point de spawn
    void setSpawnPoint(int x, int y);

    //Applique les dégat au monstre
    void takeDamage(int damage);

signals:
    void notifyMouseMoved(QPointF newMousePosition);
    void notifyMouseButtonPressed(QPointF mousePosition, Qt::MouseButtons buttons);
    void notifyMouseButtonReleased(QPointF mousePosition, Qt::MouseButtons buttons);
    void notifyKeyPressed(int key);
    void notifyKeyReleased(int key);

private:

    GameCanvas* m_pGameCanvas = nullptr;
    GameScene* m_pScene = nullptr;
    Sprite* m_pChiup = nullptr;
    Sprite* m_pSnake = nullptr;

    QVector<Monster*> m_monsters;

    void spawnMonsters();
    Monster* getMonsterInRange();

    Sprite* m_pBoss = nullptr;
    bool spawnBoss = false;
    void spawnFinalBoss();

    //Timer pour la mort du monstre
    QTimer* m_deathTimer;
    void onMonsterDeath();
    void onSnakeDeath();

    //Timer pour faire réaparaitre le monstre après un certains temps
    QTimer* m_respawnTimer;

    int m_health = 3;
    void takeDamage();

    // Liste des coeurs et mise à jour de l'affichage
    QVector<QGraphicsItem*> m_hearts;
    void updateHearts();

    void checkMonsterCollision();

    void monsterDistance();

    // Barre de vie
    QGraphicsRectItem* m_healthBarBackground;
    QGraphicsRectItem* m_healthBar;

    int m_maxHealth = 100;
    int m_currentHealth = 100;

    void updateHealthBar();
    void respawnMonster();

    void updateDialogueBubble(const QString& text);

    //barre d'XP
    int m_xp = 0;
    int m_level = 1;
    int m_xpToNextLevel = 100;
    QGraphicsRectItem* m_xpBar;
    QGraphicsRectItem* m_xpBarBackground;
    QGraphicsTextItem* m_levelText;

    void updateXpBar();
    void winXp(int amount, QPointF pos);

    //dialogue du NPC
    Sprite* m_pNpc;
    QStringList m_npcDialog;
    int m_dialogIndex = 0;
    QGraphicsTextItem* m_pDialogueBubble;

    void npcDialogue();

    QGraphicsTextItem* m_pTalkHint;
    QGraphicsRectItem* m_pDialogueBackground;

    //point de spawn du joueur
    QPointF m_spawnPoint;

    int m_ChiupDirection = 0;

    bool canMoveTo(qreal x, qreal y) const;

    bool m_keyUpPressed = false;
    bool m_keyDownPressed = false;
    bool m_keyLeftPressed = false;
    bool m_keyRightPressed = false;

    const int ATTACK_RANGE = 50;
    const int MONSTER_DAMAGE = 10;

    static const int TILE_SIZE = 96;  // Taille d'une tuile en pixels
    static const int MAP_WIDTH = 37;  // Largeur de la carte en tiles
    static const int MAP_HEIGHT = 34;  // Hauteur de la carte en tiles

    // Carte du jeu (0 = sol, 1 = buisson, 2 = arbre, 3 = herbe, 4 = eau, 5 = sable, 6 = pont)
    const int m_map[MAP_HEIGHT][MAP_WIDTH] = {
        { 3, 3, 3, 3, 3, 1, 3, 3, 3, 3, 3, 3, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 6, 6, 6, 6, 3, 3, 3, 3, 3, 3},
        { 3, 3, 3, 3, 3, 1, 3, 3, 3, 3, 3, 3, 3, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 6, 5, 5, 5, 5, 6, 3, 3, 3, 3, 3},
        { 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 6, 5, 5, 5, 5, 5, 5, 6, 3, 3, 3, 3},
        { 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 6, 5, 5, 5, 5, 5, 5, 5, 5, 6, 3, 3, 3},
        { 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 0, 0, 3, 3, 3, 3, 0, 0, 0, 0, 6, 5, 5, 5, 5, 5, 5, 5, 5, 6, 3, 3, 3},
        { 3, 3, 0, 0, 3, 3, 3, 1, 3, 3, 0, 0, 3, 1, 0, 0, 3, 3, 3, 3, 0, 0, 0, 0, 6, 5, 5, 5, 5, 5, 5, 5, 5, 6, 3, 3, 3},
        { 3, 3, 0, 0, 3, 3, 3, 3, 3, 3, 0, 0, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 6, 5, 5, 5, 5, 5, 5, 5, 5, 6, 3, 3, 3},
        { 3, 3, 0, 0, 3, 4, 4, 4, 3, 3, 0, 0, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 6, 5, 5, 5, 5, 5, 5, 6, 3, 3, 3, 3},
        { 3, 3, 0, 0, 3, 4, 4, 4, 4, 3, 6, 6, 3, 3, 3, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 6, 5, 5, 5, 5, 6, 3, 3, 3, 3, 3},
        { 3, 3, 0, 0, 3, 3, 3, 3, 4, 4, 6, 6, 4, 3, 3, 6, 6, 4, 4, 4, 4, 3, 3, 3, 3, 3, 3, 6, 6, 6, 6, 3, 3, 3, 3, 3, 3},
        { 3, 3, 0, 0, 3, 3, 3, 3, 4, 4, 6, 6, 4, 4, 4, 6, 6, 4, 3, 3, 4, 4, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
        { 3, 3, 0, 0, 3, 4, 4, 4, 4, 3, 6, 6, 3, 4, 4, 6, 6, 4, 3, 3, 4, 4, 4, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
        { 3, 0, 0, 0, 3, 4, 4, 4, 3, 3, 0, 0, 3, 3, 3, 6, 6, 3, 3, 3, 3, 3, 4, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
        { 3, 0, 0, 0, 3, 3, 3, 3, 3, 3, 0, 0, 3, 3, 3, 0, 0, 0, 0, 0, 0, 6, 6, 6, 6, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
        { 3, 0, 0, 3, 3, 3, 3, 1, 3, 3, 0, 0, 3, 3, 3, 0, 0, 0, 0, 0, 0, 6, 6, 6, 6, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
        { 3, 0, 0, 3, 3, 3, 1, 3, 3, 3, 0, 0, 3, 3, 3, 0, 0, 3, 3, 3, 3, 5, 5, 5, 5, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
        { 3, 0, 0, 0, 0, 0, 0, 0, 3, 3, 0, 0, 3, 3, 3, 0, 0, 3, 3, 3, 3, 5, 5, 5, 5, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
        { 3, 0, 0, 0, 0, 0, 0, 0, 3, 3, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 1, 4, 4, 4, 4, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
        { 3, 3, 3, 3, 3, 3, 0, 0, 3, 3, 0, 0, 3, 3, 3, 3, 3, 1, 1, 1, 4, 4, 4, 4, 4, 4, 1, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3},
        { 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 3, 3, 3, 3, 3, 3, 3},
        { 6, 6, 6, 6, 6, 3, 0, 0, 0, 0, 0, 0, 3, 3, 3, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 3, 3, 3, 3, 3, 3},
        { 6, 3, 3, 3, 6, 3, 3, 3, 3, 3, 0, 0, 3, 3, 3, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 3, 3, 3, 3, 3, 3},
        { 6, 3, 3, 3, 6, 3, 3, 3, 3, 3, 0, 0, 3, 3, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 3, 3, 3, 3, 3},
        { 6, 3, 3, 3, 6, 6, 6, 6, 6, 6, 0, 0, 6, 6, 6, 6, 6, 6, 6, 6, 4, 4, 4, 4, 4, 4, 6, 6, 6, 6, 6, 3, 3, 3, 3, 3, 3},
        { 6, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 6, 4, 4, 4, 4, 4, 4, 6, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
        { 6, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 6, 4, 4, 4, 4, 4, 4, 6, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
        { 6, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 6, 4, 4, 4, 4, 4, 4, 6, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
        { 6, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 6, 4, 4, 4, 4, 4, 4, 6, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
        { 6, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 6, 4, 4, 4, 4, 4, 4, 6, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
        { 6, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 6, 4, 4, 4, 4, 4, 4, 6, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
        { 6, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 6, 4, 4, 4, 4, 4, 4, 6, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
        { 6, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 6, 4, 4, 4, 4, 4, 4, 6, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
        { 6, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 6, 4, 4, 4, 4, 4, 4, 6, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
        { 6, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 6, 4, 4, 4, 4, 4, 4, 6, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
    };

    void loadMap();
    bool canMoveTo(qreal x, qreal y);  // Vérifie si le joueur peut aller sur une case

private slots:

};
