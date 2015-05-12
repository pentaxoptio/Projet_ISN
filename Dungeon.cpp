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
	ia();
}

void Dungeon::playerMove(sf::Vector2u newPos)
{
    m_player.setPosition(newPos);
	ia();
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

std::vector<Ennemy> const& Dungeon::getEnnemies() const
{
	return m_ennemies;
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

void Dungeon::ia()
{
	std::cout << "ia" << std::endl;
	for (unsigned int e(0); e<m_ennemies.size(); ++e)
	{
		std::cout << "Ennemy n" << e << std::endl;
		Grid detectionDown,detectionUp;
		std::vector<Keep::Tile> detectionLeft,detectionRight;
		sf::Vector2u pos = m_ennemies[e].getPosition();
		
		int d=0;
		std::vector<int> limites = traitementLimites(pos.x, pos.y, d);

		std::cout << "testA" << std::endl;
		for (int i=0; i<limites[2]; ++i){						//Creer la partie basse de la vision ennemie
			limites=traitementLimites(pos.x,pos.y,i) ;			//
			int posD=pos.y+i+1;									//				e
																//			 ///!\\\  /
			for (int z=limites[0]; z<limites[1]+1;++z){			//            //!\\	  /
				detectionDown[i].push_back(m_grid[z][posD]);	//			   /!\    /
			}
		}
		for (int i=0; i<limites[2]; ++i){                    //  Creer la partie haute de la vision ennemie
			limites=traitementLimites(pos.x,pos.y,i) ;		 //
			int posU=pos.y-d-1 ;								 //				   \!/
															//               \\!//
			for (int z=limites[0]; z<limites[1]+1;++z){		 //              \\\!///
				detectionUp[i].push_back(m_grid[z][posU]);	 //				    e
			}
		}


		std::cout << "testB" << std::endl;
		for (int i=0; i<limites[4];++i){							//Creer la partie gauche de la vision ennemie
			detectionLeft.push_back(m_grid[pos.x-i-1][pos.y]);}	//		 ---e
		
		for (int i=0; i<limites[5];++i){							//Creer la partie droite de la vision ennemie
			detectionRight.push_back(m_grid[pos.x+i+1][pos.y]);}	//			e---

		detectionUp=traitementUD(detectionUp);			
		detectionDown=traitementUD(detectionDown);

		std::reverse(detectionDown[0].begin(), detectionDown[0].end());
		std::reverse(detectionUp[0].begin(), detectionUp[0].end());

		Grid traitementrl = traitementRL(detectionRight,limites[5],detectionUp[0],detectionDown[0]);

		detectionDown[0]=traitementrl[2];
		detectionUp[0]=traitementrl[1];
		detectionRight=traitementrl[0];


		std::cout << "testC" << std::endl;
		std::reverse(detectionDown[0].begin(), detectionDown[0].end());
		std::reverse(detectionUp[0].begin(), detectionUp[0].end());

		traitementrl = traitementRL(detectionLeft,limites[4],detectionUp[0],detectionDown[0]);

		detectionDown[0]=traitementrl[2];
		detectionUp[0]=traitementrl[1];
		detectionLeft=traitementrl[0];
			
		std::vector<Grid> traitementdia = traitementDia(detectionUp,detectionDown,detectionRight,detectionLeft);
		detectionDown=traitementdia[1];
		detectionUp=traitementdia[0];
		
		std::cout << "testD" << std::endl;
		moveEnnemies(e, detectionUp,detectionDown,detectionRight,detectionLeft);
	}
}

Grid Dungeon::traitementUD(Grid detection)
{
	for (unsigned int i(0); i<detection.size(); ++i){ 
		for (unsigned int j(0); j<detection[i].size(); ++j){
		
		if (detection[i][j] == Keep::Wall)
        {
			if (i==0)
			{
				if (j<3){
					detection[0][j]=Keep::Stairs;

					for (int x=0; x<j+1;++x)
					detection[0][x]=Keep::Stairs;
				
					if (j==2){
						detection[0][j]=Keep::Stairs;
						if (detection.size()>=2){
							for (int x=0 ;x<2;++x)
									detection[1][j]=Keep::Stairs;

								}
						if (detection.size()==3)
							detection[2][0]=Keep::Stairs;
					}
				}
				if (j==3){
					if (detection.size()>=2){
						for (int x=0 ;x<4;++x){
							detection[1][x]=Keep::Stairs;

						if (detection.size()==3)
							detection[2][x-1]=Keep::Stairs;
						}
					}
				}
                   if (j>3){
                        for (int x=0; x<3;++x)
                            std::reverse(detection[x].begin(), detection[x].end());
						
						for (unsigned int a(0); a<detection.size(); ++a){ 
							for (unsigned int b(0); b<detection[a].size(); ++b){
								
								detection[0][b]=Keep::Stairs;

								for (int x=0;x<j+1;++x)
									detection[0][x]=Keep::Stairs;

								if (b==2)
									if (detection.size()>=2){
										for (int x=0;x<2;++x)
											detection[1][x]=Keep::Stairs;}

									if (detection.size()==3)
										detection[2][0]=Keep::Stairs;
										
						for (int x=0; x<3;++x)
                            std::reverse(detection[x].begin(), detection[x].end());
									}
						}
				   }

                if (i==1){
                    if (j==0){
                        if (detection.size()>=2)
							detection[1][j]=Keep::Stairs;}

                    if (j==1){
                        detection[1][j]=Keep::Stairs;

                        if (detection.size()==3)
							detection[2][0]=Keep::Stairs;
					}


                    if (j==2){
                        detection[1][j]=Keep::Stairs;

                        if (detection.size()>=2)
                            detection[1][2]=Keep::Stairs;

                        if (detection.size()==3){
                            for (int x=0;x<3;++x)
								detection[2][i]=Keep::Stairs;}
					}

                    if (j==3){
                        detection[1][j]=Keep::Stairs;

                        if (detection.size()==3)
							detection[2][2]=Keep::Stairs;}

                    if (j==4)
                        detection[1][j]=Keep::Stairs;
				}

                if (i==3){
					detection[2][j]=Keep::Stairs;}
			}
		}
		}
	}
	return detection;
}

Grid Dungeon::traitementRL(std::vector<Keep::Tile> detection, int portee, std::vector<Keep::Tile> detectionUp, std::vector<Keep::Tile> detectionDown)
{
	for (unsigned int i(0); i<detection.size(); ++i){ 
		 if (detection[i] == Keep::Wall){

			 if (i==0){
				for (int x=0;x<portee;++x)
					detection[x]=Keep::Stairs;

				if (detectionDown.size()!=0){
					for (int x=0;x<portee-1;++x)
						detectionDown[x]=Keep::Stairs;}

				if (detectionUp.size()!=0){
					for (int x=0;x<portee-1;++x)
						detectionUp[x]=Keep::Stairs;}

			 }
			if (i==1){
				for (int x=1;x<portee;++x)
					detection[x]=Keep::Stairs;

				if (detectionDown.size()!=0){
					for (int x=0;x<portee-2;++x)
						detectionDown[x]=Keep::Stairs;}

				if (detectionUp.size()!=0){
					for (int x=0;x<portee-2;++x)
						detectionUp[x]=Keep::Stairs;}
			}


			if (i==2)
				detection[i]=Keep::Stairs;
		 }
	 }
	 Grid ret;
	 ret.push_back(detection);
	 ret.push_back(detectionUp);
	 ret.push_back(detectionDown);
	 return	ret;
}

std::vector<Grid> Dungeon::traitementDia(Grid detectionUp, Grid detectionDown, std::vector<Keep::Tile> detectionRight, std::vector<Keep::Tile> detectionLeft)
{
	if (detectionUp.size()>=1 && detectionLeft.size()>=1){
		if (detectionUp[0][3]==Keep::Stairs && detectionLeft[0]==Keep::Stairs){
			detectionUp[0][2]=Keep::Stairs;
			if(detectionUp.size()>=2 && detectionLeft.size()>=2)
				detectionUp[1][0]=Keep::Stairs;}
	}

    if (detectionUp.size()>=1 && detectionRight.size()>=1){
		if (detectionUp[0][3]==Keep::Stairs && detectionRight[0]==Keep::Stairs){
			detectionUp[0][4]=Keep::Stairs;
			if(detectionUp.size()>=2 && detectionRight.size()>=2)
				detectionUp[1][4]=Keep::Stairs;}
	}

	if (detectionDown.size()>=1 && detectionLeft.size()>=1){
		if (detectionDown[0][3]==Keep::Stairs && detectionLeft[0]==Keep::Stairs){
			detectionDown[0][2]=Keep::Stairs;
			if(detectionDown.size()>=2 && detectionLeft.size()>=2)
				detectionDown[1][0]=Keep::Stairs;}
	}

    if (detectionDown.size()>=1 && detectionRight.size()>=1){
		if (detectionDown[0][3]==Keep::Stairs && detectionRight[0]==Keep::Stairs){
			detectionDown[0][4]=Keep::Stairs;
			if(detectionDown.size()>=2 && detectionRight.size()>=2)
				detectionDown[1][4]=Keep::Stairs;}
	}
	std::vector<Grid> ret;
	ret.push_back(detectionUp);
	ret.push_back(detectionDown);
	return ret;
}

std::vector<int> Dungeon::traitementLimites(int posX, int posY, int d)
{
	int posL=posX-3+d;
    int posR=posX+3-d;
    int reachL=3;
    int reachR=3;
    int x=3;
    int xU=3;
	int limy = (int)getSize().y;
	int limx = (int)getSize().x;

    if (posY==limy-1){
		x=0;}
    if (posY==limy-2){
		x=1;}
    if (posY==limy-3){
		x=2;}

    if (posY==0){
		xU=0;}

    if (posY==1){
		xU=1;}

    if (posY==2){
		xU=2;}

    if (posX==0){
		reachL=0;
		posL=posX;}

    if (posX==1){
		reachL=1;
		posL=posX-1+d;}

    if (posX==2){
		reachL=2;
		posL=posX-2+d;}

    if (posX==limx-1){
		reachR=0;
		posR=posX;}

    if (posX==limx-2){
		reachR=1;
		posR=posX+1-d;}

    if (posX==limx-3){
        reachR=2;
		posR=posX+2-d;}

	std::vector<int> ret;
	ret.push_back(posL);
	ret.push_back(posR);
	ret.push_back(x);
	ret.push_back(xU);
	ret.push_back(reachL);
	ret.push_back(reachR);
    return ret;
}

void Dungeon::moveEnnemies(unsigned int ennemyIndex, Grid detectionUp, Grid detectionDown, std::vector<Keep::Tile> detectionRight, std::vector<Keep::Tile> detectionLeft)
{
	sf::Vector2i pos((int)m_ennemies[ennemyIndex].getPosition().x, (int)m_ennemies[ennemyIndex].getPosition().y);
	sf::Vector2i posPlayer((int)m_player.getPosition().x, (int)m_player.getPosition().y);

	if (abs(pos.x-posPlayer.x)<=3 || abs(pos.y-posPlayer.y)<=3){
		if (pos.x-posPlayer.x>0){
			if( pos.y-posPlayer.y<0)
				m_ennemies[ennemyIndex].setPosition(sf::Vector2u(pos.x-1,pos.y-1));
			if ( pos.y-posPlayer.y==0)
				m_ennemies[ennemyIndex].setPosition(sf::Vector2u(pos.x-1,pos.y));
			if ( pos.y-posPlayer.y>0)
				m_ennemies[ennemyIndex].setPosition(sf::Vector2u(pos.x-1,pos.y+1));}

		if (pos.x-posPlayer.x<0){
			if( pos.y-posPlayer.y<0)
				m_ennemies[ennemyIndex].setPosition(sf::Vector2u(pos.x+1,pos.y+1));
			if ( pos.y-posPlayer.y==0)
				m_ennemies[ennemyIndex].setPosition(sf::Vector2u(pos.x+1,pos.y));
			if ( pos.y-posPlayer.y>0)
				m_ennemies[ennemyIndex].setPosition(sf::Vector2u(pos.x+1,pos.y+1));

		}
	}
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
        //xCoords= dontGetOutX(x1,xCoords);
        //yCoords= dontGetOutY(y1,yCoords);

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
        if(cpt+1 < lenth)
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
