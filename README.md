## Segatale (CS 222 project)
This is the repo for our CS 222 final project

Here are some design prinicples we abide by:
1. Keep saving memory at the front of your mind
2. Accuracy above compromise
3. Strictly stick to the source material

License for materials:
Code - GPLv3
Assets and Music - Copyright Toby Fox
Covers of the following tracks made by John Tay, with modifications made for size purposes:
Megalovania
Fallen Down
Another Medium
Death by Glamour
Its showtime!
Heartache
Ruins
Shop
Thundersnail

## Summary of Project

This is a remake of the Steam Game Undertale using Genesis and SGDK. This program will allow users to play a Sega Genesis rom file based off of Undertale. Users will get to choose their name, explore the ruins, kill or spare monsters, buy spider donuts, meet new friends, listen to music encoded through Sega Genesis and everything else one would expect for the first chapter of Undertale. 

One should be able to:
  Start a new game
  Save the game
  Engage in combat
  Traverse the world
  Talk to NPCs
  Finish the first chapter


## Technical Architecture
1) Programming Language and Libraries:
  1.1. Language: C programming language will be used for development.
SGDK (Sega Genesis Development Kit): Utilized for Sega Genesis game development, providing necessary APIs and tools.
  1.2. rescomp: A program within SGDK for transferring sprites into the Sega Genesis without requiring knowledge of assembly language.
Emulation and Testing:

2) Genesis Plus: Emulator used for running Sega Genesis ROM files on Mac OS X.
  2.1. Valgrind Integration: Exploration into integrating Valgrind into the emulator for enhanced debugging capabilities.
  2.2. Assert Functionality: Leveraging SGDK's assert function within its API for effective debugging.
  2.3. Testing and Debugging: Implementation of a comprehensive debug menu and structured testing library for testing and debugging processes.
  
3) Graphics Development:
  3.1. Graphics Tools: Aseprite and GIMP are used by team members for graphics development.

4) Game Development Infrastructure:
  4.1. Game States Management: Stack-based management of game states for navigation and interaction within the game.
  4.2. Save Game Mechanism: Implementation of save game functionality for players to save their progress.
Continuous Integration and Deployment:
  4.3. Testing and Debugging Integration: Testing functionality incorporated through preprocessor definitions to ensure code robustness.
  4.4. Pull Request Workflow: Defined workflow for code review and collaboration among team members.
  4.5. Docker Environment: Utilization of Docker for maintaining consistent development environments across different systems and editors.

5)Memory Management and Optimization:
  5.1. Memory Constraints Mitigation: Due to the limited memory on Sega Genesis cartridges, significant efforts in optimizations and compression will be required.
  5.2. Careful Memory Allocation: Due to the absence of system-level exceptions, careful memory allocation and access management will be crucial to avoid breaking operations like array access.

6)Team Collaboration:
  6.1. Division of Labor: Each team member has specific responsibilities assigned, including music development, battle scenes, overworld development, and intro development.
  6.2. Conflict Resolution: The team leader (Chase) is positioned to handle conflicts and escalate them to the Teaching Assistant if necessary.

## Installation instructions
1) Install SGDK
Navigate to https://github.com/Stephane-D/SGDK and download SGDK 1.90
2) Install Docker
Navigate to https://www.docker.com/ and install Docker 2.0
3) Install VS Code Studio
Navigate to https://code.visualstudio.com/updates/v0_9_0 and install VS code studio. Open the repository and run docker run --rm -v ${PWD}:/src sgdk to generate output file called rom.bin.
5) Install Genesis Game Simulator
   1. If you are windows user, please navigator to https://www.retroarch.com/ and install retroarch
     1.1 Then setup the load core to Sega - MS/GG/MD/CD
     1.2 Then click load content and navigate to out folder and run rom.bin
   2. If you are IOS/Linux user, please navigate to https://www.emulator-zone.com/doc.php/genesis/ and install sega genesis emulator.
      2.1 Then run the rom.bin file in the out folder

## Group members and their role

Hinkle Chase - overworld of undertale developer
Kyle Croarin - battle scenes developer
Joe Dorion - music development and integration
Charles Chen - intro development and progress Recorder
