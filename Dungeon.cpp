#include <iostream>
#include "Dungeon.h"
#include <time.h>
#include <stdlib.h>

Dungeon::Dungeon():
    m_grid()
    ,m_player()
{
    m_player.setPosition(sf::Vector2u(40, 35));
    int roomsCount = 10; //à modifier
    std::srand((unsigned int)std::time(0));
    int width = rand() % 25 + 75,
        height = rand() % 15 + 50;
    m_grid = Grid(width, std::vector<Keep::Tile>(height, Keep::Wall));
    placeRooms(roomsCount);
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
            std::cout<< newRoom.left+(newRoom.width/2) << " IXI  " << newRoom.top+(newRoom.height/2)<<std::endl;
            ++cpt;
        }
        else
        {
            continue;
        }

        for (int x(xPosition); x < xPositionMax; ++x)
            for (int y(yPosition); y < yPositionMax; ++y)
                m_grid[x][y] = Keep::Air;
        std::cout << "nbr de pieces : " << cpt <<  std::endl;
    } //end while

    m_player.setPosition(sf::Vector2u(xRooms[0], yRooms[0]));//on place le joueur au centre d'une salle
    connect(xRooms, yRooms);
}

/* entrée : 4 int ; ce sont les coordonées de deux point a relier, ici le millieu de deux salles
 * sortie : rien (le donjon est modifié)
 * description : on crée un chemin entre deux point. Pour qu'il soit pas direct on lui rajoute du detour avec des +ou- 1 mais l'arrivée est la meme
 */

void Dungeon::createWay(int x, int y, int xDest, int yDest)
{

    /* A verifier
    if(x>xDest)//Pour que x soit bien le + a gauche
    {
        int a= x;
        x=xDest;
        xDest=a;
    }
    if(y>yDest)//Pour que y soit bien le + en haut (le + petit)
    {
        int a= y;
        y=yDest;
        yDest=a;
    }
    */

    int xDiff = xDest - x;
    int x1 = x;//x créé pour désindanté lors de la toute premiere version
    int y1 = y;
    int yDiff = yDest - y;
    int xDetour =  10 /*rand()%5 + 5*/;
    int yDetour = 10  /*rand()%5 + 5*/;

    std::cout << "          xdiff   " << xDiff << "  yDiff  "<<  yDiff<< "  x detour  " << xDetour<< "y detour  "<< yDetour << std::endl;


    std::vector<int> yCoords;//on crée un liste de mouvement des y ( +1 , 0 ou -1)
    std::vector<int> xCoords;

    for (int cpt(0); cpt < xDiff; ++cpt)//on crée un bon nombre de mouvenement positifs
        xCoords.push_back(1);



    for (int cpt(0); cpt < xDetour; ++cpt) // on crée un nombre de case de detour
    {
        xCoords.push_back(-1);
        xCoords.push_back(1);
    }


    for (int cpt(0); cpt < yDiff; ++cpt) // on fait la meme chose pour les Y
        yCoords.push_back(1);
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
     xCoords= dontGetOutX(x1,xCoords);
     yCoords= dontGetOutY(y1,yCoords);
     x1= x1+xCoords[cpt];
     y1= y1+yCoords[cpt];
    m_grid[x1][y1] = Keep::Air;

         //if (m_grid[x1-1][y1]== Keep::Wall)//Pour eviter qu'il y ait des chemins trop moches ( pas besoin de rajouter un air si pas besoin)
        //{
         //   if(x1+1<m_grid.size() )
           //     m_grid[x1+1][y1]= Keep::Air;
        //}

    }
}

    /* entrée : deux vector contenant chacun les coordonées x / y des salles créées
    * sortie : rien => on appelle create way qui modifie directement le donjon
    * description : On lie toute les salles grace a la fonction createWay. Cette fonction sers a faire en sorte que toute les salles soient liées
    */


void Dungeon::connect(std::vector<int> xPositions, std::vector<int> yPositions)
{
/*

 * Gerer dans la fonction soit apres les connection impossibles

*/

    for(int x(0); x<xPositions.size() ; ++x)
    {
        std::cout << x <<"  x : "<< xPositions[x]<< "  y : "<< yPositions[x] << std::endl;
    }

    int lenth = xPositions.size();
    int cpt(0);
    while (cpt < lenth)//
    {
        std::cout<<"on connecte [" << int(xPositions[cpt]) << " : "<< int(yPositions[cpt]) <<"] a   ["<< xPositions[cpt+1] << " : " << yPositions[cpt+1]<< "]"<< std::endl;


        if(cpt+1 < lenth)
        {
            createWay(xPositions[cpt], yPositions[cpt], xPositions [cpt+1], yPositions[cpt+1]);
            //createWay(0,0,10,10);
            std::cout<<"c est bon"<<std::endl;
            //createWay(15,15,30,30);
            std::cout<<"c est bon"<<std::endl;
            ++cpt;
            ++cpt;
        }
       //  else //au cas ou le nombre de salle est impair
           // createWay(xPositions[cpt], yPositions[cpt], xPositions[1],yPositions[1]);

       // std::cout << "nbr de create way fait" << cpt/2 << std::endl;

    }


}

std::vector<int> Dungeon::dontGetOutX(int depart,std::vector<int> direction)
{
    std::cout <<'entréeee dans Dont GEt Out :* ' << std::endl;
    for (int cpt(0); cpt <= direction.size(); ++cpt)
       {
           if (cpt < direction.size() )//Tant qu'on n'a pas fini le chemin, on ajoute ou retire 1 des x ou y  de la ou on est pour créer un chemin
           {
               if (depart + direction[cpt] > 0 )//si on ne sort pas vers l'exterieur haut ou gauche
               {
                   if (depart + direction[cpt] < m_grid/*ICI rajouter [0] si on parle de largeur ou longueur*/.size() ) // et ni vers l'exterieur bas ou droite
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
                std::cout <<" point de depart : " << depart << std::endl;
        }

    return direction;
}

std::vector<int> Dungeon::dontGetOutY(int depart,std::vector<int> direction)
{
    std::cout <<'entréeee dans Dont GEt Out :* ' << std::endl;
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
                std::cout <<" point de depart : " << depart << std::endl;
        }

    return direction;
}
