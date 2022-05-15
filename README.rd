To play this game : 
Lauch Game.exe in repertory Game
    
To compile this game :

(If you don't have the compilator g++, you can get it by installing tdm64-gcc-10.3.0-2.exe)

Open the Terminal, then go in project game repertory

cd Code
g++ -std=c++14 -O3 main.cpp DataGame/DataGame.cpp DataGame\Actor/Actor.cpp DataGame\Block/Block.cpp DataGame\Camera/Camera.cpp DataGame\Collider/Box.cpp DataGame\Collider/Collider.cpp DataGame\Collision/Collision.cpp DataGame\Items/Coin.cpp DataGame\Items/Shroom.cpp DataGame\Map/Map.cpp DataGame\Map/TileMap.cpp DataGame\Math/Radius.cpp DataGame\Math/RandomNumber.cpp DataGame\Math/Vector2D.cpp DataGame\Personnage\Ennemies/Ennemies.cpp DataGame\Personnage\Ennemies/Goomba.cpp DataGame\Personnage\Ennemies/ParaGoomba.cpp DataGame\Personnage\Ennemies/Rex.cpp DataGame\Personnage\Mario/Mario.cpp DataGame\Personnage\Mario\Ability/Jump.cpp DataGame\SFML/SfmlAudio.cpp DataGame\SFML/SfmlImage.cpp DataGame/UHD/Uhd.cpp DataGame/WayPoint/WayPoint.cpp Game\Game.cpp Game\GameEngine.cpp Game\GameOverEngine.cpp System\Input.cpp  -o ./../Game/Game.exe -I SFML-2.5.1/include -L SFML-2.5.1\lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

<It take a while> 30s for me

Then you can lauch Game.exe 

cd ./../Game && .\Game

(You can also double click on it)

You can also compile with the Python file Compile.py :
python Compile.py

(It doesn't work with double click)

Enjoy !
