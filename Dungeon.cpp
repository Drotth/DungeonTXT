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
    createNextRoom(SOUTH, "Room 5");
    createNextRoom(NORTH, "Room 6");
}

void Dungeon::createStartRoom()
{
    Position startPos = Position(0, 0);

    Room starterRoom(startPos, "Room 0");
    allDungeonRooms.insert({startPos.toString(), starterRoom});
    lastBuiltRoom = &(allDungeonRooms.at(startPos.toString()));
}

bool Dungeon::createNextRoom(Direction dir, std::string name)
{
    Position lastBuiltPos = lastBuiltRoom->roomPos;
    Position newRoomPos;

    switch (dir)
    {
    case NORTH:
    {
        newRoomPos = lastBuiltPos + Position(0, 1);
        break;
    }
    case SOUTH:
    {
        newRoomPos = lastBuiltPos + Position(0, -1);
        break;
    }
    case WEST:
    {
        newRoomPos = lastBuiltPos + Position(-1, 0);
        break;
    }
    case EAST:
    {
        newRoomPos = lastBuiltPos + Position(1, 0);
        break;
    }
    default:
        return false;
    }

    if (allDungeonRooms.find(newRoomPos.toString()) == allDungeonRooms.end())
    {
        createRoom(newRoomPos, name);

        std::string newDoorName = "Door"+lastBuiltPos.toString()+"-"+newRoomPos.toString();
        Door newDoor(newDoorName, allDungeonRooms.at(lastBuiltPos.toString()).roomName, allDungeonRooms.at(newRoomPos.toString()).roomName);
        allDungeonDoors.insert({newDoorName, newDoor});

        return true;
    }
    else
        return false;
}

void Dungeon::createRoom(Position pos, std::string name)
{
    Room newRoom(pos, name);
    allDungeonRooms.insert({pos.toString(), newRoom});
    lastBuiltRoom = &(allDungeonRooms.at(pos.toString()));
}

std::vector<std::string> Dungeon::getRoomDoors(std::string currentRoomName)
{
    std::vector<std::string> roomDoors;
    for (auto i = allDungeonDoors.begin(); i != allDungeonDoors.end(); i++)
    {
        if (i->second.roomA == currentRoomName || i->second.roomB == currentRoomName)
        {
            roomDoors.push_back(i->first);
        }
    }
    return roomDoors;
}