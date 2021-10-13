#include "Dungeon.h"
#include <iostream>
#include <string>

Dungeon::Dungeon()
{

    createStartRoom();

    createNextRoom(NORTH, "Room 1");
    createNextRoom(NORTH, "Room 2");
    createNextRoom(WEST, "Room 3");
    createNextRoom(NORTH, "Room 4");

    // Room secondRoom(Position(1,0), "Room 1");
    // allDungeonRooms.push_back(secondRoom);

    // Room thirdRoom(Position(2,0), "Room 2");
    // allDungeonRooms.push_back(thirdRoom);

    // Door newDoor("Room 0-1", allDungeonRooms.at(0).roomName, allDungeonRooms.at(1).roomName);
    // allDungeonDoors.push_back(newDoor);

    //---new roomgeneration idea:---
    //start with one room. create new one in random direction (plus door inbetween)
    //continue with this in random directions.
    //if the new room, in that particular direction hits an existing room, instead
    //randomize if a door is to be created, and the pick another direction for a new room
    //and repeat.
    //Rooms probably need coordinates to check collisions, and if map idea should work
}

void Dungeon::createStartRoom()
{
    Room starterRoom(Position(0, 0), "Room 0");
    allDungeonRooms.push_back(starterRoom);
    lastBuiltRoom = &(allDungeonRooms.back());
}

void Dungeon::createNextRoom(Direction dir, std::string name)
{
    Position lastBuiltPos = lastBuiltRoom->roomPos;

    // std::cout << "lastBuiltPos before nextRoom(): " << lastBuiltPos << std::endl;

    switch (dir)
    {
    case NORTH:
        createRoom(lastBuiltPos + Position(0, 1), name);
        break;
    case SOUTH:
        createRoom(lastBuiltPos + Position(0, -1), name);
        break;
    case WEST:
        createRoom(lastBuiltPos + Position(-1, 0), name);
        break;
    case EAST:
        createRoom(lastBuiltPos + Position(1, 0), name);
        break;
    }
}

void Dungeon::createRoom(Position pos, std::string name){
    Room newRoom(pos, name);
    allDungeonRooms.push_back(newRoom);
    lastBuiltRoom = &(allDungeonRooms.back());
}

std::vector<std::string> Dungeon::getRoomDoors(std::string currentRoomName)
{
    std::vector<std::string> roomDoors;
    for (int index = 0; index < allDungeonDoors.size(); index++)
    {
        if (allDungeonDoors.at(index).roomA == currentRoomName ||
            allDungeonDoors.at(index).roomB == currentRoomName)
        {
            roomDoors.push_back(allDungeonDoors.at(index).doorName);
        }
    }
    return roomDoors;
}