# Space Shooter Game

A dynamic 2D space shooter game developed using C++ and SFML, featuring multiple enemy types, power-ups, and progressive difficulty levels.

## Table of Contents
- [Overview](#overview)
- [Game Features](#game-features)
- [Controls](#controls)
- [Game Elements](#game-elements)
  - [Player Ship](#player-ship)
  - [Enemies](#enemies)
  - [Power-ups](#power-ups)
  - [Levels and Phases](#levels-and-phases)
- [Technical Implementation](#technical-implementation)
- [Installation](#installation)
- [Requirements](#requirements)

## Overview

Space Shooter is a classic arcade-style vertically scrolling shooter game where the player controls a spaceship and battles waves of enemies. The game features multiple levels of increasing difficulty, diverse enemy types, and special power-ups to enhance gameplay.

## Game Features

- **Menu System**: Interactive main menu with Start Game, Instructions, Scores, and Quit options
- **Progressive Difficulty**: Multiple phases and levels with different enemy types
- **Boss Battles**: Special challenging boss encounters
- **Power-up System**: Various power-ups that enhance player abilities
- **Lives System**: Player has multiple lives with visual indicators
- **Score Tracking**: Real-time score display
- **Dynamic Weapons**: Multiple weapon types and upgrades

## Controls

- **Arrow Keys**: Move the player ship (Up, Down, Left, Right)
- **Diagonal Movement**: Combined movement keys for diagonal navigation
- **Enter**: Select menu options
- **ESC**: Pause the game
- **Auto-Fire**: Ship automatically fires weapons

## Game Elements

### Player Ship

The player controls a spaceship with the following features:
- Different weapon types (basic, triple shot, wide spread)
- Shield capabilities
- Various movement speeds
- Visual destruction effects

### Enemies

The game features several types of enemies:

- **Alpha**: Basic enemy ships with standard movement patterns
- **Beta**: More complex enemies with targeted shooting
- **Gemma**: Fast-moving enemies that are harder to hit
- **Monster**: Special boss-type enemy with multiple attack patterns
- **Dragon**: Powerful boss with complex attack patterns
- **Rebel**: Advanced enemy with strategic movement

Each enemy has unique:
- Movement patterns
- Attack strategies
- Health points
- Visual destruction effects

### Power-ups

Various power-ups appear during gameplay:

- **Power**: Enhances weapon strength and spread
- **Fire**: Increases fire rate
- **Live**: Grants an additional life
- **Danger**: Negative power-up to avoid

### Levels and Phases

The game progression includes:

- **Three Levels**: Each with increasing difficulty
- **Three Phases per Level**: Progressive waves of enemies
- **Boss Encounters**: Special challenging battles at the end of phases
- **Dragon Battle**: Ultimate boss fight

## Technical Implementation

The game is built with the following components:

- **SFML Graphics Library**: For rendering, sprite management, and windowing
- **Object-Oriented Design**: Extensive use of classes and inheritance
- **Collision Detection**: Precise hit detection between game elements
- **Game Clock**: Time-based events and animations
- **Resource Management**: Efficient loading and usage of textures and sounds

Key classes:
- `Menu`: Handles the main menu interface
- `Game`: Core game loop and state management
- `Player`: Player ship functionality and weapons
- `Enemy`: Base class for all enemy types
- `AddOn`: Power-up system implementation

## Installation

1. Clone the repository
2. Open the project in Visual Studio
3. Build the solution
4. Run the game executable

## Requirements

- Visual C++ Redistributable
- SFML 2.5.1 or later
- Windows OS (Developed and tested on Windows 10)
- Graphics card with support for rendering 2D graphics

---

This project was developed as part of the Object-Oriented Programming Laboratory course. 