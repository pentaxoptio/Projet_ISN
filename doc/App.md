#App
Cette classe représente et contient les éléments du jeu. C'est elle qui se charge de mettre à jour, de gérer les évènements et de dessiner les éléments graphiques.

##Méthodes publiques
* App()
    * Constructeur
	* Initialise les textures et les polices de caractères
* run()
	* __return__ : void
	* Cette fonction déclenche le début du jeu, en particulier la boucle principale. Elle exécute les actions suivantes :
	    1. Récupérer le temps écoulé depuis la dernière boucle (`sf::Time deltaTime`)
		2. `handleEvents()`
		3. `update(deltaTime)`
		4. `render()`

##Méthodes privées
* handleEvents()
    * __return__ : void
	* Récupère les évènnements de la fenêtre (via `sf::Window::pollEvent`) et les traite
* update(sf::Time dt)
    * __return__ : void
	* __param__ _dt_ : Le temps écoulé depuis la dernière boucle
	* Mets à jour les composants graphiques
* render()
	* __return__ : void
	* Affiche les composants graphiques

##Attributs
* `sf::RenderWindow m_w`
    * La fenêtre de rendu. cf. doc SFML
* `TextureHolder m_textures`
    * Le gestionnaire de textures. cf. Textures.h
* `FontHolder m_fonts`
    * Le gestionnaire de polices. cf. Fonts.h
* `Dungeon m_dungeon`
    * Le donjon du jeu. cf. Dungeon.h
* `DungeonRenderer m_renderer`
    * La classe chargée d'afficher le donjon. cf. DungeonRenderer.h
