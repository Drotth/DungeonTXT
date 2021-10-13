#include "Dungeon.h"
#include <iostream>
#include <string>

Dungeon::Dungeon()
{

    Room firstRoom(Position(0,0), "Room 0");
    allDungeonRooms.push_back(firstRoom);

    Room secondRoom(Position(1,0), "Room 1");
    allDungeonRooms.push_back(secondRoom);

    Room thirdRoom(Position(2,0), "Room 2");
    allDungeonRooms.push_back(thirdRoom);

    Door newDoor("Room 0-1", allDungeonRooms.at(0).roomName, allDungeonRooms.at(1).roomName);
    allDungeonDoors.push_back(newDoor);

    //---new roomgeneration idea:---
    //start with one room. create new one in random direction (plus door inbetween)
    //continue with this in random directions.
    //if the new room, in that particular direction hits an existing room, instead
    //randomize if a door is to be created, and the pick another direction for a new room
    //and repeat.
    //Rooms probably need coordinates to check collisions, and if map idea should work
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