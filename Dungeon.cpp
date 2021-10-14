#include "Dungeon.h"
#include <iostream>
#include <string>

Dungeon::Dungeon()
{

    Position lastPos = createStartRoom();

    lastPos = createNextRoom(lastPos, NORTH, "Room 1");
    lastPos = createNextRoom(lastPos, NORTH, "Room 2");
    lastPos = createNextRoom(lastPos, WEST, "Room 3");
    lastPos = createNextRoom(lastPos, NORTH, "Room 4");
    lastPos = createNextRoom(lastPos, SOUTH, "Room 5");
    lastPos = createNextRoom(lastPos, NORTH, "Room 6");
}

Position Dungeon::createStartRoom()
{
    Position startPos = Position(0, 0);

    Room starterRoom(startPos, "Room 0");
    allDungeonRooms.insert({startPos.toString(), starterRoom});

    return startPos;
}

Position Dungeon::createNextRoom(Position previousPos, Direction dir, std::string name)
{
    Position newRoomPos;

    switch (dir)
    {
    case NORTH:
    {
        newRoomPos = previousPos + Position(0, 1);
        break;
    }
    case SOUTH:
    {
        newRoomPos = previousPos + Position(0, -1);
        break;
    }
    case WEST:
    {
        newRoomPos = previousPos + Position(-1, 0);
        break;
    }
    case EAST:
    {
        newRoomPos = previousPos + Position(1, 0);
        break;
    }
    default:
        return previousPos;
    }

    if (createRoom(newRoomPos, name))
    {
        std::string newDoorName = "Door" + previousPos.toString() + "-" + newRoomPos.toString();
        Door newDoor(newDoorName, allDungeonRooms.at(previousPos.toString()).roomName, allDungeonRooms.at(newRoomPos.toString()).roomName);
        allDungeonDoors.insert({newDoorName, newDoor});

        return newRoomPos;
    }
    else{
        //randomize if there is to be a door created before returning previous pos
        //also that needs a check if there already is a door
        return previousPos;
    }
}

bool Dungeon::createRoom(Position pos, std::string name)
{
    if (allDungeonRooms.find(pos.toString()) == allDungeonRooms.end())
    {
        Room newRoom(pos, name);
        allDungeonRooms.insert({pos.toString(), newRoom});
        return true;
    } else return false;
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