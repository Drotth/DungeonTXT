#include "Dungeon.h"
#include <iostream>
#include <string>

Dungeon::Dungeon()
{

    Room firstRoom("Room 0");
    allDungeonRooms.push_back(firstRoom);

    Room secondRoom("Room 1");
    allDungeonRooms.push_back(secondRoom);

    Room thirdRoom("Room 2");
    allDungeonRooms.push_back(thirdRoom);

    Door newDoor("Room 0-1", allDungeonRooms.at(0).roomName, allDungeonRooms.at(1).roomName);
    allDungeonDoors.push_back(newDoor);
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