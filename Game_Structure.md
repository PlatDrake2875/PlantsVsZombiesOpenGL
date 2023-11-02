
# PvZ Game Structure

## Class Game
  - [Inputs](#inputs)
  - [Collision](#collision)
  - [Gameplay](#gameplay)
  - [Animations](#animations)

## Class Game

Handles events related to:
- Inputs (keyboard/mouse)
- Collisions 
- Gameplay 
- Animations 

### 1. Inputs

A class that implements methods to detect the following inputs:

1. Left click and hold on a plant (also verifies if the player has enough currency for the chosen plant).
2. Left click on a pink star (also verifies if the player is at max star capacity).
3. Right click on a Plant (deletes it).
4. (bonus) + (speeds up the game).
5. (bonus) Spacebar (pauses the game).
6. (bonus) - (slows down the game).

### 2. Collision

A class that provides methods to detect the following collisions:

1. Zombie-Finish line.
2. Zombie-Plant.
3. Projectile-Zombie.
4. Plant-Dirt Square (validates if a dragged plant is dropped on a permissible square).

### 3. Gameplay 

At least one class handling the subsequent events:

- Inputs
  - (1.1) -> Adds the Plant to the plant list; reduces the star counter by Plant_type_cost.
  - (1.2) -> Increases the star counter by 1.
  - (1.3) -> Identifies the clicked plant and removes it.
  - (1.4/5/6) -> Modifies the deltaTime variable for animation speed.
  
- Collisions
  - (2.1) -> Ends the game (bonus: shows player score & run time).
  - (2.2) -> Chews on the Plant for a duration (eliminates it if the collision remains for a specific time).
  - (2.3) -> Damages the Zombie (eliminates it if its HP is 0 or less).
  - (2.4) -> Either places the Plant on the square or removes it.

- Stars
  - Randomly spawns 2-4 stars on the screen.
  - Players can have up to X stars.
  
- Plants
  - Available in 3 varieties.
  - Each variety has a unique HP, projectile speed, and damage.
  
- Zombies
  - Have similar features as Plants.

### 4. Animations
* Projectiles should be spinning and translating 
* Plants/Zombies change colour/texture when they get damaged (bonus: they can heal when not in combat)
* Plants/Zombies should fade quickly when they die
* Stars should fade quickly when they get collected (even if max_stars is achieved)


