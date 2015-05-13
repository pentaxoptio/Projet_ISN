#ifndef DUNGEON_H
#define DUNGEON_H

#include "Player.h"
#include "Ennemy.h"
#include "Utils.h"

#include <vector>
#include <SFML/Graphics.hpp>

namespace Keep
{
    enum Tile
    {
        Air,
        Wall,
        Stairs
    };
}

typedef std::vector<std::vector<Keep::Tile> > Grid;

class Dungeon
{
    public :
        Dungeon(Difficulty diff);
        void playerMove(unsigned int x, unsigned int y);
        void playerMove(sf::Vector2u newPos);

        sf::Vector2u getSize() const;
        Keep::Tile getTile(unsigned int x, unsigned int y) const;
        sf::Vector2u getPlayerPosition() const;
		std::vector<Ennemy> const& getEnnemies() const;

	private :
        /* entrée : Int nombre de pieces a créer
         * sortie : rien (le donjon a été directement modifié
         * descrition : on créé un donjon d'une taille variable mais bornée
         * on y insere un certain nombre de salles. Les coordonées de ses salles sont stoquées dans deux vecteur
         * on apelle la fonction connect une fois que les salles sont créées pour lier toute les salles
         */
		void placeRooms(int roomsCount);

        /* entrée : 4 int ; ce sont les coordonées de deux point a relier, ici le millieu de deux salles
         * sortie : rien (le donjon est modifié)
         * description : on crée un chemin entre deux point. Pour qu'il soit pas direct on lui rajoute du detour avec des +ou- 1 mais l'arrivée est la meme
         */
		void createWay(int x, int y, int xDest, int yDest);

        /* entrée : deux vector contenant chacun les coordonées x / y des salles créées
        * sortie : rien => on appelle create way qui modifie directement le donjon
        * description : On lie toute les salles grace a la fonction createWay. Cette fonction sers a faire en sorte que toute les salles soient liées
        */
		void connect(std::vector<int> xPositions, std::vector<int> yPositions);

        /* entrée : int  et vector int. correspond respectivment a la position sur l'abscice du chemin, et au futurs mouvement du chemin sur l'axe des x
         * sortie : vector<int> . Ce vecteur renvoie les mouvements du chemins de telle maniere à ce que le chemin ne sorte pas du donjon
         * description : la fonction prends la position du chemin. Elle aditionne ensuite les futurs nouvement du chemin et deplace a la fin les directions qui font sortir le chemin du donjon
         */
        std::vector<int> dontGetOutX(int depart, std::vector<int> direction);

        /*
         * idem que dont get out X mais sur l'axe des ordonées
         */
        std::vector<int> dontGetOutY(int depart, std::vector<int> direction);

        /* entrée : deux int pour la position et deux autre pour la direction que la prendre le joueur ( +1 ; 0 ; -1 )
         * sortie : rien => on modifie directement le donjon
         * description : Cette fonction sers lors de la creation de chemin; Le joueur ne peut se deplacer directement en diagonale (entre deux coins de murs)
         * Donc cette fonction sers a rajouter un air pour que la diagonale se transforme en escalier [exemple en dessous]
         *          a w w   |   a w w               avant | apres
         *          w a w   |   a a w               On voit bien l'endroit ou a été créé le a
         *          w w a   |   w a a
         * Cette fonction ne crée un a que si c est une diagonale parfaire ( comme dans avant )
         */
        void diagonal(int xPosition, int yPosition, int xDirection, int yDirection);

        /* entrée : difficultée choisie (enum)
         * sortie : rien
         * description : cette fonction modifie les propritétés du donjon(nbr de salles, d'ennemis etc..) en fonction de la difficultée choisie.
         */
        void setDifficulty(Difficulty diff);

        /* entrée : int . Il definit le nombre d'ennemis a créer et a placer
         * sortie : rien
         * description : On choisit aléatoirement une case dans le donjon. Si cette case est vide(air) alors on place l'ennemi et on incremente le compteur d'ennemis créés.
         */
        void placeEnnemy(int nbrEnnemy);

		//intelligence artificielle
		void ia();
		Grid traitementUD(Grid detection);
		Grid traitementRL(std::vector<Keep::Tile> detection, int portee, std::vector<Keep::Tile> detectionUp, std::vector<Keep::Tile> detectionDown);
		std::vector<Grid> traitementDia(Grid detectionUp, Grid detectionDown, std::vector<Keep::Tile> detectionRight, std::vector<Keep::Tile> detectionLeft);
		std::vector<int> traitementLimites(int posX, int posY, int d);
		void moveEnnemies(unsigned int ennemyIndex, Grid detectionUp, Grid detectionDown, std::vector<Keep::Tile> detectionRight, std::vector<Keep::Tile> detectionLeft);
		
    private :
        Grid m_grid;
        Player m_player;
		std::vector<Ennemy> m_ennemies;
};

#endif
