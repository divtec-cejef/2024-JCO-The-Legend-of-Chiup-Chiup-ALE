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


class GameCanvas;
class GameScene;
class Sprite;

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

    void keyPressed(int key);
    void keyReleased(int key);

    void mouseMoved(QPointF newMousePosition);
    void mouseButtonPressed(QPointF mousePosition, Qt::MouseButtons buttons);
    void mouseButtonReleased(QPointF mousePosition, Qt::MouseButtons buttons);

    void tick(long long elapsedTimeInMilliseconds);

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

    Sprite* m_pNpc;  // NPC en tant que sprite
    QStringList m_npcDialog;  // Liste des dialogues de l'NPC
    int m_dialogIndex = 0;  // Pour savoir où on en est dans le dialogue

    int m_ChiupDirection = 0;

    bool canMoveTo(qreal x, qreal y) const;

    bool m_keyUpPressed = false;
    bool m_keyDownPressed = false;
    bool m_keyLeftPressed = false;
    bool m_keyRightPressed = false;

    static const int TILE_SIZE = 96;  // Taille d'une tuile en pixels
    static const int MAP_WIDTH = 18;  // Largeur de la carte en tiles
    static const int MAP_HEIGHT = 18;  // Hauteur de la carte en tiles

    // Carte du jeu (0 = sol, 1 = buisson, 2 = arbre, 3 = herbe, 4 = eau, 5 = sable, 6 = pont)
    const int m_map[MAP_HEIGHT][MAP_WIDTH] = {
        { 3, 3, 0, 0, 3, 1, 3, 3, 3, 3, 3, 3, 1, 3, 0, 0, 3, 3 },
        { 3, 3, 0, 0, 3, 1, 3, 3, 3, 3, 3, 3, 3, 1, 0, 0, 3, 3 },
        { 3, 3, 0, 0, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 3, 3 },
        { 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3 },
        { 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 0, 0, 3, 3 },
        { 3, 3, 0, 0, 3, 3, 3, 1, 3, 3, 0, 0, 3, 1, 0, 0, 3, 3 },
        { 3, 3, 0, 0, 3, 3, 3, 3, 3, 3, 0, 0, 3, 1, 0, 0, 0, 3 },
        { 3, 3, 0, 0, 3, 4, 4, 4, 3, 3, 0, 0, 3, 3, 3, 0, 0, 3 },
        { 3, 3, 0, 0, 3, 4, 4, 4, 4, 3, 6, 6, 3, 3, 3, 0, 0, 3 },
        { 3, 3, 0, 0, 3, 3, 3, 3, 4, 4, 6, 6, 4, 3, 3, 6, 6, 3 },
        { 3, 3, 0, 0, 3, 3, 3, 3, 4, 4, 6, 6, 4, 4, 4, 6, 6, 4 },
        { 3, 3, 0, 0, 3, 4, 4, 4, 4, 3, 6, 6, 3, 4, 4, 6, 6, 4 },
        { 3, 3, 0, 0, 3, 4, 4, 4, 3, 3, 3, 3, 3, 3, 3, 6, 6, 3 },
        { 3, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 3 },
        { 3, 0, 0, 3, 3, 3, 3, 1, 3, 3, 3, 3, 3, 3, 3, 0, 0, 3 },
        { 3, 0, 0, 3, 3, 3, 1, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0 },
        { 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0 },
        { 0, 0, 3, 3, 3, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 }
    };

    void loadMap();  // Méthode pour charger la
    bool canMoveTo(qreal x, qreal y);  // Vérifie si le joueur peut aller sur une case

private slots:

};
