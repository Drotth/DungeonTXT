#include "Dungeon.h"
#include <iostream>

std::random_device dev;
std::mt19937 rng(dev());
std::uniform_int_distribution<std::mt19937::result_type> dist2(1, 2);
std::uniform_int_distribution<std::mt19937::result_type> dist4(1, 4);
std::uniform_int_distribution<std::mt19937::result_type> dist6(1, 6);

Dungeon::Dungeon()
{
    roomResult res = createStartRoom();
    Position lastPos = std::get<1>(res);

    lastPos = std::get<1>(createNextRoom(lastPos, NORTH, "Room 1"));
    allDungeonRooms.at(lastPos.toString()).isDiscovered = true;
    lastPos = std::get<1>(createNextRoom(lastPos, NORTH, "Room 2"));
    allDungeonRooms.at(lastPos.toString()).isDiscovered = true;
    lastPos = std::get<1>(createNextRoom(lastPos, WEST, "Room 3"));
    allDungeonRooms.at(lastPos.toString()).isDiscovered = true;
    lastPos = std::get<1>(createNextRoom(lastPos, SOUTH, "Room 4"));
    allDungeonRooms.at(lastPos.toString()).isDiscovered = true;
    lastPos = std::get<1>(createNextRoom(lastPos, EAST, "Room 5"));
    allDungeonRooms.at(lastPos.toString()).isDiscovered = true;

    // lastPos = createNextRoom(lastPos, NORTH, "Room 1");
    // allDungeonRooms.at(lastPos.toString()).isDiscovered = true;
    // lastPos = createNextRoom(lastPos, NORTH, "Room 2");
    // allDungeonRooms.at(lastPos.toString()).isDiscovered = true;
    // createRoom(lastPos + Position(1,0), "Extraroom for test");
    // // allDungeonRooms.at((lastPos + Position(1,0)).toString()).isDiscovered = true;
    // lastPos = createNextRoom(lastPos, WEST, "Room 3");
    // allDungeonRooms.at(lastPos.toString()).isDiscovered = true;
    // lastPos = createNextRoom(lastPos, NORTH, "Room 4");
    // // allDungeonRooms.at(lastPos.toString()).isDiscovered = true;
    // lastPos = createNextRoom(lastPos, SOUTH, "Room 5");
    // lastPos = createNextRoom(lastPos, NORTH, "Room 6");
    // createRoom(lastPos + Position(0,1), "Extraroom for test");
    // // allDungeonRooms.at((lastPos + Position(0,1)).toString()).isDiscovered = true;
    // lastPos = createNextRoom(lastPos, EAST, "Room 7");
    // lastPos = createNextRoom(lastPos, EAST, "Room 8");
    // lastPos = createNextRoom(lastPos, EAST, "Room 9");
    // allDungeonRooms.at(lastPos.toString()).isDiscovered = true;
    // lastPos = createNextRoom(lastPos, SOUTH, "Room 10");
    // createRoom(lastPos + Position(-1,0), "Extraroom for test");
    // lastPos = createNextRoom(lastPos, EAST, "Room 11");
    // lastPos = createNextRoom(lastPos, SOUTH, "Room 12");
    // lastPos = createNextRoom(lastPos, SOUTH, "Room 13");

    // createNextRoom(lastPos, EAST, "Room 1");
    // createNextRoom(lastPos, NORTH, "Room 1");
    // createNextRoom(lastPos, WEST, "Room 1");
    // lastPos = createNextRoom(lastPos, SOUTH, "Room 1");
    // lastPos = createNextRoom(lastPos, EAST, "Room 2");
    // lastPos = createNextRoom(lastPos, EAST, "Room 3");
    // lastPos = createNextRoom(lastPos, NORTH, "Room 4");
    // lastPos = createNextRoom(lastPos, NORTH, "Room 5");
    // lastPos = createNextRoom(lastPos, NORTH, "Room 6");
    // lastPos = createNextRoom(lastPos, WEST, "Room 7");
    // lastPos = createNextRoom(lastPos, WEST, "Room 8");
}

Dungeon::Dungeon(int nbrOfRooms)
{
    roomResult resStart = createStartRoom();
    Position lastPos = std::get<1>(resStart);
    Direction lastDir;
    int createdRooms = 1;

    for (int index = 0; index < nbrOfRooms; index++){

        Direction dir;

        if(dist4(rng) == 1) dir = NORTH;
        else if (dist4(rng) == 2) dir = SOUTH;
        else if (dist4(rng) == 3) dir = WEST;
        else if (dist4(rng) == 4) dir = EAST;

        roomResult res = createNextRoom(lastPos, dir, "Room " + createdRooms+1);

        // If a new room was built
        if(std::get<0>(res) == 1){
            createdRooms += 1;
            lastDir = dir;
            lastPos = std::get<1>(res);
        }

        allDungeonRooms.at(lastPos.toString()).isDiscovered = true;
    }
}

roomResult Dungeon::createStartRoom()
{
    Position startPos = Position(0, 0);

    Room starterRoom(startPos, "Room 0");
    starterRoom.isDiscovered = true;
    allDungeonRooms.insert({startPos.toString(), starterRoom});

    return roomResult(true, startPos);
}

roomResult Dungeon::createNextRoom(Position previousPos, Direction dir, std::string name)
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
        return roomResult(false, previousPos);
    }

    if (createRoom(newRoomPos, name))
    {
        std::string newDoorName = "Door" + previousPos.toString() + "-" + newRoomPos.toString();
        Door newDoor(newDoorName, allDungeonRooms.at(previousPos.toString()).roomPos, allDungeonRooms.at(newRoomPos.toString()).roomPos);
        allDungeonDoors.insert({newDoorName, newDoor});

        return roomResult(true, newRoomPos);
    }
    else
    {
        if (!areRoomsConnected(previousPos, newRoomPos))
        {
            if (dist2(rng) == 1)
            {
                std::string newDoorName = "Door" + previousPos.toString() + "-" + newRoomPos.toString();
                Door newDoor(newDoorName, allDungeonRooms.at(previousPos.toString()).roomPos, allDungeonRooms.at(newRoomPos.toString()).roomPos);
                allDungeonDoors.insert({newDoorName, newDoor});
            }
        }
        return roomResult(false, previousPos);
    }
}

bool Dungeon::createRoom(Position pos, std::string name)
{
    if (allDungeonRooms.find(pos.toString()) == allDungeonRooms.end())
    {
        Room newRoom(pos, name);
        allDungeonRooms.insert({pos.toString(), newRoom});
        return true;
    }
    else
        return false;
}

std::vector<Door *> Dungeon::getRoomDoors(Position &currentRoomPos)
{
    std::vector<Door *> roomDoors;
    for (auto i = allDungeonDoors.begin(); i != allDungeonDoors.end(); i++)
    {
        if (*i->second.roomA == currentRoomPos || *i->second.roomB == currentRoomPos)
        {
            roomDoors.push_back(&i->second);
        }
    }
    return roomDoors;
}

bool Dungeon::areRoomsConnected(Position &firstRoom, Position &secondRoom)
{
    std::vector<Door *> firstRoomDoors = getRoomDoors(firstRoom);
    std::vector<Door *> secondRoomDoors = getRoomDoors(secondRoom);

    for (Door *firstRoomDoor : firstRoomDoors)
    {
        for (Door *secondRoomDoor : secondRoomDoors)
        {
            if (firstRoomDoor->doorName == secondRoomDoor->doorName)
            {
                return true;
            }
        }
    }
    return false;
}