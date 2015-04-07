#TextureId
Cet enum représente les différentes textures disponibles. Les valeurs suivantes sont possibles (avec le nom du fichier correspondant) :
* _Tiles_ : `tiles.png`
* _Player_ : `player.png`
* _Buttons_ : `buttons.png`
* _Effects_ : `effects.png`

#RectId
Cet enum représente les découpages dans les textures, c'est à dire les rectangles de la texture correspondant au sprite voulu. Exemple : la texture _Buttons_ contient trois boutons verticalements disposés : un bouton au repos, un survolé et un activé. A chacun correspond un rectangle indiquant les coordonnées des pixels correspondants. Ainsi on trouve :
* _Wall_ : La case représentant un mur -> _Tiles_
* _Air_ : La case représentant du sol (sans obstacle) -> _Tiles_
* _Stairs_ : La case représentant des escaliers -> _Tiles_
* _RedEffect_ : L'effect qui surligne une case en rouge -> _Effects_
* _BlueEffect_ : L'effet qui surligne une case en bleu -> _Effects_
* _ButtonNormal_ : Un bouton au repos -> _Buttons_
* _ButtonSelect_ : Un bouton survolé -> _Buttons_
* _ButtonActivate_ : Un bouton activé -> _Buttons_

#TextureHolder
Cette classe sert de conteneur et de gestionnaire de textures : elle se charge de créer de de conserver les `sf::Texture` et de les restituer sur demande. Elle fonctionne très simplement.

##Méthodes publiques
* TextureHolder()
    * Constructeur
* ~TextureHolder()
    * Destructeur
	* Comme les `sf::Texture` sont allouées dynamiquement, ils faut également les détruire.
* registerTexture(TextureId id, std::string filename)
    * __return__ : void
	* __param__ _id_ : L'id de la texture que l'on charge. On ne peux pas charger deux textures avec le même id.
	* __param__ _filename_ : Le nom du fichier contenant la texture. Peut être n'importe quel fichier image (PNG à préferrer)
	* Cette fonction enregistre un texture que l'on pourra retrouver avec son ID. Il s'agit d'une `sf::Texture` allouée dynamiquement et stockée dans `m_textures`
* getTexture(TextureId id) const
    * __return__ : `sf::Texture const&`
	* __param__ _id_ : L'id de la texture voulue.
	* Cette fonction renvoie une référence constante (non modifiable) vers une texture stockée, à partir de l'id de cette texture. Cela suppose que ladit texture a déjà été enregistrée.
* registerRect(RectId id, sf::IntRect rect)
    * __return__ : void
	* __param__ _id_ : L'id du rectangle enregistré.
	* __param__ _rect_ : Le rectangle correspondant à l'id.
	* Permet d'enregister un rectangle associé à un ID, comme pour une texture. Le rectangle correspond à un sprite de la texture.
* getRect(RectId id) const
    * __return__ : `sf::IntRect`
	* __param__ _id_ : L'id du rectangle à récupérer
	* Retourne le rectangle correspondant à l'id demandé. Bien entendu, il faut préalablement avoir enregistré le rectangle.

##Attributs
* `std::map<TextureId, sf::Texture*> m_textures`
    * Une map associant un `TextureId` à un pointeur vers une texture. Cete map est remplie dynamiquement à chaque appel à `registerTexture`.
* `std::map<RectId, sf::IntRect> m_rects`
    * Une map associant un `RectId` à un `sf::IntRect` qui est donc un rectangle, ici en pixels. Est rempli dynamiquement par `registerRect`.
