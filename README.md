# Example Game

Loading the Project, click the Green Code button on the repository
And then Open With Visual Studio 

![image](https://user-images.githubusercontent.com/9059588/226904104-6db1b61d-2ca4-4c09-acdc-aa4fe73a48a3.png)


Today we will look at an example game built with the programming framework we use over the first 
12 weeks of Fundamentals of Games and Graphical Systems Development module.

The game we will be looking at today has been built using Visual Studio 2022 and uses a variety of 
technologies which have been wrapped up into a helpful programming framework called S2D 
written in the industry standard language, C++. 

The underlying technologies at work in this framework are OpenGL, OpenAL and freeglut. 
You find out more about these throughout the modules. 

Visual Studio is a very complex piece of software with many features. You will learn about many of 
these throughout modules taught on the Games Technology degree programs.


## Debug Menus and The Code Window. 

<b>Green Local Windows Debugger Button</b> : Runs the Application. 

<b>Solution Explorer Window</b> : Lists all of the files in the Solution.

<b>Double Click</b> a folder, then a file to open in the Code Window. 

Try double clicking ‘PlatformerGame.cpp’!

![image](https://user-images.githubusercontent.com/9059588/226861622-e29c3c6d-acc2-4ef6-97eb-3d1ec6f1ecab.png)![image](https://user-images.githubusercontent.com/9059588/226860947-98f6dfdc-53d0-4810-a7bc-a0b2c8eaa832.png)

The solution explorer contains all the files that comprise the project.

All the files that have the .h extension are called header files. 

These describe the functionality that will be containing in the matching .cpp file. 
The .cpp files (C++ source files) implement what the header files say will be included. 

You will learn a lot more about header and source files later within modules. Be careful not to delete any 
files from the solution as they are all necessary to compile and run the game! 

## Building and Debugging the Game
Choose ‘Local Windows Debugger' from the overlay. Play the game using the following controls:
<b>WASD</b> : Movement
<b>Space</b> : Jump

![image](https://user-images.githubusercontent.com/9059588/226863337-52aefeec-00cd-4729-aaa9-d14cfc6abb68.png)


## Code Window
This is the area you write your code. You’re currently looking at ‘PlatformerGame.cpp’ 
An important 
file of the Platformer Demo which controls the game logic.
![image](https://user-images.githubusercontent.com/9059588/226863908-568b38f4-4cc9-40c9-bfd0-31002da9ce30.png)


## Making Modifications
There are many aspects of this game which can be modified, in fact everything can be modified since 
you have access to the source code. 

Open the ‘Enemy.cpp’ file. You should notice some Constant floating point values have been 
defined called ‘MaxWaitTime’ and ‘MoveSpeed’. 
You can see they've been given the decimal values 0.5f, and 64.0f

Change these values and see what effect this has on the enemies in level 2 and 3.

## Modify a Level
The platformer demo provides code that can automatically load new levels from the text files. 

The text files are named in numerical sequential order starting from zero E.g., 0.txt, 1.txt, 2.txt.

Look at level 0 by double clicking the text file. Examine the contents of this file that comprise the 
first level. It looks like the following:

![image](https://user-images.githubusercontent.com/9059588/226885398-45d97c1d-26b6-4d90-aefc-54d12164c030.png)![image](https://user-images.githubusercontent.com/9059588/226885456-131e64ac-157d-42bb-8da2-b2fb793c7378.png)


Each level is a 20-character by 16-character grid.  
Code is already in place to load each tile of the game world from the text file.  
Each time the player reaches an exit, the next level is loaded from the text file and the game continues.  

The supported characters that represent game tiles are:  
<b>Period (.)</b> – represents blank space  
<b>X</b> – Exit  
<b>G</b> – collectable gem  
<b>Hyphen (-)</b> – floating platform  
<b>A, B, C, D</b> – represent different types of monsters  
<b>Tilde (~)</b> – platform block  
<b>Colon (:)</b> – Variety platform tile  
<b>1</b> – Player start position  
<b>Hash (#)</b> – impassable block (floor)  

Try mdifying 0.txt level map with the above characters.


## Add a level

Right Click <b>S2DPlatformer</b> in the <b>Solution Explorer</b> and <b>Add</b> a <b>New Item</b>
Name this "3.txt" and it will create in the Solution Explorer.
You can click and drag this into the LevelMaps filter.

The text files are not compiled like code and are treated as external items.

Next open ‘PlatformerGame.cpp’ in Visual Studio from the Solution Explorer and locate the constant 
variable called NumberOfLevels near the top of the file. 
Change this value to 4 and you should now have a new 4th level. 

You may notice your level doesn’t look quite right...can you work out what is wrong? 

## Challenge

By right clicking S2DPlatformer in the Solution Explorer, we can Open Folder in File Explorer
Try and solve the problem with the 4th level

Alternatively, try changing the sprites loaded to cusotmise your game.

## Summary
Congratulations! You have completed an introduction to game programming using S2D, built on 
OpenGL and OpenAL. Having completed the exercises, you will have experienced first-hand games 
programming using C++. This tutorial has only begun to touch on the potential of this framework. 
Feel free to experiment further with this Demo. 

You will get the opportunity to build new games with this framework within the module. 
To experience more of the programming aspect of games programming, you may wish to familiarise 
yourself with C++ in general. 
Have fun, happy coding
