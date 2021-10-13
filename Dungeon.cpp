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

    Door newDoor("Room 1-2", allDungeonRooms.at("Room 1").roomName, allDungeonRooms.at("Room 2").roomName);
    allDungeonDoors.insert({"Room 1-2", newDoor});

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
    allDungeonRooms.insert({"Room 0", starterRoom});
    lastBuiltRoom = &(allDungeonRooms.at("Room 0"));
}

void Dungeon::createNextRoom(Direction dir, std::string name)
{
    Position lastBuiltPos = lastBuiltRoom->roomPos;

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
    allDungeonRooms.insert({name, newRoom});
    lastBuiltRoom = &(allDungeonRooms.at(name));
}

std::vector<std::string> Dungeon::getRoomDoors(std::string currentRoomName)
{
    std::vector<std::string> roomDoors;
    for (auto i = allDungeonDoors.begin(); i != allDungeonDoors.end(); i++)
	{
        if(i->second.roomA == currentRoomName || i->second.roomB == currentRoomName){
            roomDoors.push_back(i->first);
        }
	}
    return roomDoors;
}