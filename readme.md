# classes
- Engine
- Textures
- Scene
- Game_singleplayer : scene
- Map
- Thing
- Ship : Thing
- Block : Thing
- Bullets *(plural as this will be a bullet manager)*

## Engine
Highest object, controls the current scene, can change between scenes.

## Textures
Loads textures from a file into a map, can be quiried to return a texture

## Scene
A scene template to allow different scenes to be treated the same way

## Game_Singleplayer
Does single player loop stuff. It would be better to get this working first as it shows more.

## Map
Controls everything moving around the map, updates there positions from velocity and draws them. Leaves Game_Singleplayer
to make exceptions like updating the velocity of the player controlled ship. Controls bullets.

## Thing
A thing that can move and be draw to the screen

## Ship
A ship, controls all of its blocks

## Block
Does block stuff, can exist in the map on its own as a thing