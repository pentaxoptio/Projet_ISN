#include <iostream>
#include "Dungeon.h"
#include <time.h>
#include <stdlib.h>

Dungeon::Dungeon(Difficulty diff):
    m_grid() ,
    m_player() ,
	m_ennemies()
{
    setDifficulty(diff);
    // appeler une fonction et y mettre le code du contructeur
}
/*entrée : difficultée choisie (enum)
 * sortie : rien
 *
 */
void Dungeon::setDifficulty(Difficulty diff)
{
    if (diff == Easy)
    {
        m_player.setPosition(sf::Vector2u(40, 35));
        std::srand((unsigned int)std::time(0));
        int roomsCount = 5; //à modifier
        int width = rand() % 25 + 65,
            height = rand() % 15 + 40;
        m_grid = Grid(width, std::vector<Keep::Tile>(height, Keep::Wall));
        placeRooms(roomsCount);
        placeEnnemy(5);
    }

    else if (diff == Normal)
    {
        m_player.setPosition(sf::Vector2u(40, 35));
        std::srand((unsigned int)std::time(0));
        int roomsCount = 10; //à modifier
        int width = rand() % 25 + 75,
            height = rand() % 15 + 50;
        m_grid = Grid(width, std::vector<Keep::Tile>(height, Keep::Wall));
        placeRooms(roomsCount);
        placeEnnemy(10);
    }
    else
    {
        m_player.setPosition(sf::Vector2u(40, 35));
        std::srand((unsigned int)std::time(0));
        int roomsCount = 15; //à modifier
        int width = rand() % 25 + 90,
            height = rand() % 15 + 70;
        m_grid = Grid(width, std::vector<Keep::Tile>(height, Keep::Wall));
        placeRooms(roomsCount);
        placeEnnemy(15);
    }

}

void Dungeon::placeEnnemy(int nbrEnnemy)
{
    int cpt(0);
    while (cpt<nbrEnnemy)
    {
        int xPosition = rand() % (int)m_grid.size();
        int yPosition = rand() % (int)m_grid[0].size();
        if(m_grid[xPosition][yPosition]==Keep::Air)
        {
            m_ennemies.push_back(Ennemy(Zombie));
            m_ennemies[m_ennemies.size()-1].setPosition(sf::Vector2u(xPosition,yPosition));
            ++cpt;
        }
    }

}

void Dungeon::playerMove(unsigned int x, unsigned int y)
{
    m_player.setPosition(sf::Vector2u(x, y));
    //Ici TimothÃ© gÃ¨re les actions des ennemis
}

void Dungeon::playerMove(sf::Vector2u newPos)
{
    m_player.setPosition(newPos);
}

sf::Vector2u Dungeon::getSize() const
{
    return sf::Vector2u((unsigned int)m_grid.size(), (unsigned int)m_grid[0].size());
}

Keep::Tile Dungeon::getTile(unsigned int x, unsigned int y) const
{
    return m_grid[x][y];
}

sf::Vector2u Dungeon::getPlayerPosition() const
{
    return m_player.getPosition();
}

//Creation de donjon

/* entrée : Int nombre de pieces a créer
 * sortie : rien (le donjon a été directement modifié
 * descrition : on créé un donjon d'une taille variable mais bornée
 * on y insere un certain nombre de salles. Les coordonées de ses salles sont stoquées dans deux vecteur
 * on apelle la fonction connect une fois que les salles sont créées pour lier toute les salles
 */

void Dungeon::placeRooms(int roomsCount)
{
    std::vector<sf::IntRect> rooms;
    std::vector<int> xRooms;
    std::vector<int> yRooms;
    int cpt(0);

    while (cpt < roomsCount)
    {
        //Génération de la position et de la taille de la salle
        int xPosition = rand() % (int)m_grid.size();
        int yPosition = rand() % (int)m_grid[0].size();
        int xPositionMax = xPosition + rand()%5 + 7;
        int yPositionMax = yPosition + rand()%5 + 7;

        if ((unsigned int)xPositionMax > m_grid.size()) //salle sort de la grille
            continue;
        if ((unsigned int)yPositionMax + 1 > m_grid[0].size())
            continue;

        sf::IntRect newRoom(xPosition, yPosition, xPositionMax-xPosition+1, yPositionMax-yPosition+1);

        bool intersect = false;
        if (rooms.size() > 0)
        {
            for (sf::IntRect room : rooms)
                if (newRoom.intersects(room))
                    intersect = true;
        }

        if (!intersect)
        {
            rooms.push_back(newRoom);
            xRooms.push_back(newRoom.left+(newRoom.width/2)); //pour demarer le chemin au milleu de la salle
            yRooms.push_back(newRoom.top+(newRoom.height/2));
            ++cpt;
        }
        else
        {
            continue;
        }

        for (int x(xPosition); x < xPositionMax; ++x)
            for (int y(yPosition); y < yPositionMax; ++y)
                m_grid[x][y] = Keep::Air;

    } //end while

    m_player.setPosition(sf::Vector2u(xRooms[0], yRooms[0]));//on place le joueur au centre d'une salle
    connect(xRooms, yRooms);
    m_grid[xRooms[roomsCount-1]][yRooms[roomsCount-1]]= Keep::Stairs;//on met un escalier dans la derniere salle crée
}

/* entrée : 4 int ; ce sont les coordonées de deux point a relier, ici le millieu de deux salles
 * sortie : rien (le donjon est modifié)
 * description : on crée un chemin entre deux point. Pour qu'il soit pas direct on lui rajoute du detour avec des +ou- 1 mais l'arrivée est la meme
 */

void Dungeon::createWay(int x, int y, int xDest, int yDest)
{
    int xDiff = abs(xDest - x);
    int x1 = x;//x créé pour désindanté lors de la toute premiere version
    int y1 = y;
    int yDiff = abs(yDest - y);
    int xDetour =  rand()%5 + 5;
    int yDetour = rand()%5 + 5;

    std::vector<int> yCoords;//on crée un liste de mouvement des y ( +1 , 0 ou -1)
    std::vector<int> xCoords;

    if(x1<xDest)
    {
        for (int cpt(0); cpt < xDiff; ++cpt)//on crée un bon nombre de mouvenement positifs
            xCoords.push_back(1);
    }
    else
        for (int cpt(0); cpt < xDiff; ++cpt)//on crée un bon nombre de mouvenement positifs
            xCoords.push_back(-1);



    for (int cpt(0); cpt < xDetour; ++cpt) // on crée un nombre de case de detour
    {
        xCoords.push_back(-1);
        xCoords.push_back(1);
    }

    if(y1<yDest)
    {
        for (int cpt(0); cpt < yDiff; ++cpt) // on fait la meme chose pour les Y
            yCoords.push_back(1);
    }
    else
        for(int cpt(0); cpt< yDiff; ++cpt)
            yCoords.push_back(-1);

    for (int cpt(0); cpt < yDetour; ++cpt)
    {
        yCoords.push_back(-1);
        yCoords.push_back(1);
    }



    while (xCoords.size() > yCoords.size()) // Pour egaliser les listes et que les deux soient lues en entier
        yCoords.push_back(0);
    while (yCoords.size() > xCoords.size())
        xCoords.push_back(0);


    std::random_shuffle(xCoords.begin(), xCoords.end()); // On melange les listes pour que le chemin ait un detour aléatoire
    std::random_shuffle(yCoords.begin(), yCoords.end());



    for(int cpt(0); cpt < xCoords.size(); ++cpt)
    {
        //en cas d'echec deplacer juste apres le for
        xCoords= dontGetOutX(x1,xCoords);
        yCoords= dontGetOutY(y1,yCoords);

        diagonal(x1,y1,xCoords[cpt],yCoords[cpt]);
        x1= x1+xCoords[cpt];
        y1= y1+yCoords[cpt];

        m_grid[x1][y1] = Keep::Air;

    }
}

    /* entrée : deux vector contenant chacun les coordonées x / y des salles créées
    * sortie : rien => on appelle create way qui modifie directement le donjon
    * description : On lie toute les salles grace a la fonction createWay. Cette fonction sers a faire en sorte que toute les salles soient liées
    */


void Dungeon::connect(std::vector<int> xPositions, std::vector<int> yPositions)
{
    int lenth = xPositions.size();
    int cpt(0);
    while (cpt < lenth)//
    {
        if(cpt < lenth)
        {
            createWay(xPositions[cpt], yPositions[cpt], xPositions [cpt+1], yPositions[cpt+1]);
            ++cpt;
        }
        else
            ++cpt;//pour eviter une boucle infinie
        //surement a delet, a verifier
    }
}

std::vector<int> Dungeon::dontGetOutX(int depart,std::vector<int> direction)
{
    //  /!\ il peut il y avoir encore un +1 ou un -1 apres, verifier et les rajouter (2 ou plus au lieu d'un a la fin)
    for (int cpt(0); cpt <= direction.size(); ++cpt)
       {
           if (cpt < direction.size() )//Tant qu'on n'a pas fini le chemin, on ajoute ou retire 1 des x ou y  de la ou on est pour créer un chemin
           {
               if (depart + direction[cpt] > 0 )//si on ne sort pas vers l'exterieur haut ou gauche
               {
                   if (depart + direction[cpt] < m_grid.size() ) // et ni vers l'exterieur bas ou droite
                   {
                       continue; // si on ne depasse ni a droite ni a gauche c est bon
                   }
                   else //si on vas vers la droite on rajoute on supprime le +1 qui va vers la droite et on le met a la fin pour que ca ne pose plus probleme
                   {
                       direction.erase(direction.begin()+cpt);
                       direction.push_back(1);
                       while(cpt+1 == 1)
                       {
                           direction.erase(direction.begin()+cpt);
                           direction.push_back(1);
                           ++cpt;
                       }
                   }
               }
               else// si on vas vers l'exterieur gauche on supprime le -1 et on le rajoute en fin de liste
               {
                   direction.erase(direction.begin()+cpt);
                   direction.push_back(-1);
                   while(cpt+1 == -1)
                   {
                       direction.erase(direction.begin()+cpt);
                       direction.push_back(-1);
                       ++cpt;
                   }
               }

           }

                depart += direction[cpt];//on fait avancer le pt de depart
    }




    return direction;
}


std::vector<int> Dungeon::dontGetOutY(int depart,std::vector<int> direction)
{

    for (int cpt(0); cpt <= direction.size(); ++cpt)
       {
           if (cpt < direction.size() )//Tant qu'on n'a pas fini le chemin, on ajoute ou retire 1 des x ou y  de la ou on est pour créer un chemin
           {
               if (depart + direction[cpt] > 0 )//si on ne sort pas vers l'exterieur haut ou gauche
               {
                   if (depart + direction[cpt] < m_grid[0].size() ) // ICI se tient avec les X ;p /!\  la difference avec et ni vers l'exterieur bas ou droite
                   {
                       continue; // si on ne depasse ni a droite ni a gauche c est bon
                   }
                   else //si on vas vers la droite on rajoute on supprime le +1 qui va vers la droite et on le met a la fin pour que ca ne pose plus probleme
                   {
                       direction.erase(direction.begin()+cpt);
                       direction.push_back(1);
                   }
               }
               else// si on vas vers l'exterieur gauche on supprime le -1 et on le rajoute en fin de liste
               {
                   direction.erase(direction.begin()+cpt);
                   direction.push_back(-1);
               }

           }
                depart += direction[cpt];//on fait avancer le pt de depart
        }

    return direction;
}

    /* entrée : deux int pour la position et deux autre pour la direction que la prendre le joueur ( +1 ; 0 ; -1 )
     * sortie : rien => on modifie directement le donjon
     * description : Cette fonction sers lors de la creation de chemin; Le joueur ne peut se deplacer directement en diagonale (entre deux coins de murs)
     * Donc cette fonction sers a rajouter un air pour que la diagonale se transforme en escalier [exemple en dessous]
     *          a w w   |   a w w               avant | apres
     *          w a w   |   a a w               On voit bien l'endroit ou a été créé le a
     *          w w a   |   w a a
     * Cette fonction ne crée un a que si c est une diagonale parfaire ( comme dans avant )
     */

void Dungeon::diagonal(int xPosition, int yPosition, int xDirection, int yDirection)
{


    //    /!\ au +1 et au +1 si ca sort du donjon, quoique ca ferai juste planter la fonction donc pas si grave
    // faire en sorte que les chemins de passe pas a moins de 1 case des cotés.



    if(xDirection==1 && yDirection==-1)//si on monte en diagonale en haut a droite
    {
        if(m_grid[xPosition][yPosition-1]== Keep::Wall && m_grid[xPosition+1][yPosition]== Keep::Wall )//et qu'il y a du mur de telle maniere a ce que le personnage ne puisse passer
        {

            m_grid[xPosition+1][yPosition]= Keep::Air;

        }
    }

    if(xDirection==1 && yDirection==1)//diagonale vers bas droite
    {

        if(m_grid[xPosition][yPosition+1]== Keep::Wall && m_grid[xPosition+1][yPosition]== Keep::Wall )
        {
            m_grid[xPosition+1][yPosition]= Keep::Air;

        }
    }

    if(xDirection==-1 && yDirection==1)//diagonale vers bas gauche
    {
        if(m_grid[xPosition-1][yPosition]== Keep::Wall && m_grid[xPosition][yPosition+1]== Keep::Wall )
        {
            m_grid[xPosition][yPosition+1]= Keep::Air;

        }
    }

    if(xDirection==-1 && yDirection==-1)//diagonale vers haut gauche
    {
        if(m_grid[xPosition-1][yPosition]== Keep::Wall && m_grid[xPosition][yPosition-1]== Keep::Wall )
        {
            m_grid[xPosition][yPosition-1] = Keep::Air;
        }
    }
}
