# classes
- Engine
- Textures
- Scene
- Scene_Game : Scene
- Scene_Setup : Scene

- Ship
- AI
- AI_ : AI
- Weapon
- Weapon_ : Weapon
- Module
- Module_ : Module

- UI_Item
- UI_Button : UI_Item
- UI_Grid : UI_Item
- UI_Text : UI_Item

## Engine
Highest object, controls the current scene, can change between scenes.

## Textures
Loads textures from a file into a map, can be quiried to return a texture

## Scene
A scene template to allow different scenes to be treated the same way

## Game_Singleplayer
Does single player loop stuff. It would be better to get this working first as it shows more.

## Ship
This is the one that does the boid stuff, but it makes its desitions based off the AI object in it,
A ship, has an array of module spots, you pass ship a shipdef containing its module structure and it builds itself accordingly


## AI
ship passes this object the stuff it needs and it makes the desition where to go. This is a seperate class from boid so you can make
the boids make different desitions like if it wants to protect its own ships or charge the enermy without having a hundred ship classes

## AI_
also AI is a template so each diffent ones name is added after the _

## Weapon
basic weapon template, takes in a type and a size, sizes of weapon small medium and large arnt going to be different classes becuase there
too similar, just stat multipliers

## Weapon_
each unique weapon has a different way of firing and doing stuff so it gets its own derived class

## Module
basic module template

## Module_
modules can be stuff like sheilds, armour, anti-missile point deffence, reactors, that stuff, again does stat modifiers and maybe
requires updates each loop



## UI_Item
a item that can be drawn, has children, positions them somehow, a size, something like that. has a color or a backgorund?

## UI_Button
an item with text and can be clicked, does click event stuff

## UI_Grid
positions children in a grid with set rows and colums, or ajustable rows and columns

## UI_Text
has text inside of it, draws said text, cool right

## UI_InputFeild
its an input feild


# Timeline
- setup seperate scenes
- **game**
	- setup ship to work with ai
	- ai settings structs
	- make simple boid ai that takes struct and does stuff
	- make boids do boid things
	- make boids shoot at other boids
	- make boids die
	- boid base stats
	- make get armour modules working with boids
	- get reactor modules working with boids
	- add other weapons and modules
- **setup menu**
	- get item working
	- get text working
	- get buttons working
	- make simple menu where you can add ship types to your fleet
	- get click and drag working
	- customise modules in ships
	- get input feilds working
	- cusstomise ship ai settings with input feilds

ok i may have made this larger than sessasary