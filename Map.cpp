#include "Map.h"

using namespace std;

// Void
string space = "........";
string spaceBetweenRooms = ".......";
string spaceExtra = ".";

// Walls
string roomXaxisFull = "--------";
string roomXaxisExtra = "-";
string roomXaxis = "--";
string roomXaxis2 = "---";
string roomYaxis = "|";

// Doors
string roomXDoors = " ";
string roomYDoors = "   ";

// Room contents
string roomEmpty = "       ";
string roomPlayerTop = "  _o_  ";
string roomPlayerMiddle = "   |   ";
string roomPlayerBottom = "  / \\  ";

Map::Map(Dungeon &inDungeon)
{
    dungeon = &inDungeon;
    allDungeonRooms = &inDungeon.allDungeonRooms;
    allDungeonDoors = &inDungeon.allDungeonDoors;

    lowestX = 0;
    lowestY = 0;
    highestX = 0;
    highestY = 0;

    map = "";
}

void Map::calculateDungeonSize()
{
    for (auto i = allDungeonRooms->begin(); i != allDungeonRooms->end(); i++)
    {
        if (i->second.roomPos.x < lowestX && i->second.isDiscovered == true)
            lowestX = i->second.roomPos.x;
        if (i->second.roomPos.x > highestX && i->second.isDiscovered == true)
            highestX = i->second.roomPos.x;
        if (i->second.roomPos.y < lowestY && i->second.isDiscovered == true)
            lowestY = i->second.roomPos.y;
        if (i->second.roomPos.y > highestY && i->second.isDiscovered == true)
            highestY = i->second.roomPos.y;
    }
}

bool Map::roomExists(Position &pos)
{
    return (allDungeonRooms->find(pos.toString()) != allDungeonRooms->end());
}

bool Map::roomIsDiscovered(Position &pos)
{
    return (allDungeonRooms->find(pos.toString())->second.isDiscovered == true);
}

void Map::drawYDividers(int yLevel)
{
    Position currentPos(lowestX, yLevel);

    // Go from left to right
    for (int xpos = lowestX; xpos <= highestX; xpos++)
    {
        currentPos = Position(xpos, yLevel);

        // Capture positions closeby of relevance
        Position WRoom = currentPos + Position(-1, 0);
        Position NRoom = currentPos + Position(0, 1);
        Position NWRoom = currentPos + Position(-1, 1);

        // If there is a room on current pos
        if (roomExists(currentPos))
        {
            // If the position of this room is to the far left
            if (xpos == lowestX)
            {
                // If this, or the north, room is discovered
                if (roomIsDiscovered(currentPos) || (roomExists(NRoom) && roomIsDiscovered(NRoom)))
                    map.append(roomXaxisExtra);
                else
                    map.append(spaceExtra);
            }

            // Or if there is no room to the W or NW
            else if (!roomExists(WRoom) && !roomExists(NWRoom))
            {
                // If this, or the north, room is discovered
                if (roomIsDiscovered(currentPos) || (roomExists(NRoom) && roomIsDiscovered(NRoom)))
                    map.append(roomXaxisExtra);
                else
                    map.append(spaceExtra);
            }

            // If there is a door to the north room
            if (dungeon->areRoomsConnected(currentPos, NRoom))
            {
                // If this, or the north, room is discovered
                if (roomIsDiscovered(currentPos) || (roomExists(NRoom) && roomIsDiscovered(NRoom)))
                {
                    map.append(roomXaxis);  // Add left part of north wall
                    map.append(roomYDoors); // Add door part of north wall
                    map.append(roomXaxis2); // Add right part of north wall
                }
                else
                    map.append(space);
            }

            // Or else there is just a solid wall
            else
            {
                // If this, or the north, room is discovered
                if (roomIsDiscovered(currentPos) || (roomExists(NRoom) && roomIsDiscovered(NRoom)))
                {
                    map.append(roomXaxisFull);
                }
                else
                    map.append(space);
            }
        }

        // If there is NOT a room on current pos
        else
        {
            if (allDungeonRooms->find(NRoom.toString()) != allDungeonRooms->end())
            {
                if (xpos == lowestX || (allDungeonRooms->find(WRoom.toString()) == allDungeonRooms->end() &&
                                        allDungeonRooms->find(NWRoom.toString()) == allDungeonRooms->end()))
                {
                    map.append(roomXaxisExtra); //One extra sign to align correctly from start
                }
                map.append(roomXaxisFull);
            }
            else
            {
                if (xpos == lowestX || (allDungeonRooms->find(WRoom.toString()) == allDungeonRooms->end() &&
                                        allDungeonRooms->find(NWRoom.toString()) == allDungeonRooms->end()))
                {
                    map.append(spaceExtra); //one extra space for correct alignment
                }
                map.append(spaceBetweenRooms);
                if (xpos == highestX)
                {
                    map.append(spaceExtra);
                }
            }
        }
    }

    map.append("\n");
}

void Map::drawRowRooms(int yLevel, ROOMPART part)
{
    Position currentPos(lowestX, yLevel);

    for (int xpos = lowestX; xpos <= highestX; xpos++)
    {
        currentPos = Position(xpos, yLevel);

        switch (part)
        {
        case TOP:
        {
            if (allDungeonRooms->find(currentPos.toString()) != allDungeonRooms->end() && allDungeonRooms->find(currentPos.toString())->second.isDiscovered == true)
            {
                Position WRoom = currentPos + Position(-1, 0);
                if (xpos == lowestX || allDungeonRooms->find(WRoom.toString()) == allDungeonRooms->end())
                {
                    map.append(roomYaxis);
                }
                if (playerPos == currentPos)
                {
                    map.append(roomPlayerTop);
                }
                else
                    map.append(roomEmpty);
                map.append(roomYaxis);
            }
            else
            {
                Position WRoom = currentPos + Position(-1, 0);
                if (xpos == lowestX || allDungeonRooms->find(WRoom.toString()) == allDungeonRooms->end())
                {
                    map.append(spaceExtra); //one extra space for correct alignment
                }
                map.append(spaceBetweenRooms);
                if (xpos == highestX)
                {
                    map.append(spaceExtra);
                }
            }
            break;
        }
        case MIDDLE:
        {
            if (allDungeonRooms->find(currentPos.toString()) != allDungeonRooms->end() && allDungeonRooms->find(currentPos.toString())->second.isDiscovered == true)
            {
                Position WRoom = currentPos + Position(-1, 0);
                Position potentialEastRoom = currentPos + Position(1, 0);

                if (dungeon->areRoomsConnected(currentPos, WRoom))
                {
                    // If the room is connected to a room to the left AND
                    // If it's the first room or there is no room to the left
                    if (xpos == lowestX && allDungeonRooms->find(WRoom.toString()) != allDungeonRooms->end())
                    {
                        map.append(roomXDoors);
                    }
                }
                else
                {
                    // If the room is not connected to a room to the left AND
                    // If it's the first room or there is no room to the left
                    if (xpos == lowestX || allDungeonRooms->find(WRoom.toString()) == allDungeonRooms->end())
                    {
                        map.append(roomYaxis);
                    }
                }

                if (playerPos == currentPos)
                {
                    map.append(roomPlayerMiddle);
                }
                else
                    map.append(roomEmpty);

                if (dungeon->areRoomsConnected(currentPos, potentialEastRoom))
                {
                    if (allDungeonRooms->find(potentialEastRoom.toString()) != allDungeonRooms->end())
                    {
                        map.append(roomXDoors);
                    }
                }
                else
                    map.append(roomYaxis);
            }
            else
            {
                Position WRoom = currentPos + Position(-1, 0);
                if (xpos == lowestX || allDungeonRooms->find(WRoom.toString()) == allDungeonRooms->end())
                {
                    map.append(spaceExtra); //one extra space for correct alignment
                }
                map.append(spaceBetweenRooms);
                if (xpos == highestX)
                {
                    map.append(spaceExtra);
                }
            }
            break;
        }
        case BOTTOM:
        {
            if (allDungeonRooms->find(currentPos.toString()) != allDungeonRooms->end() && allDungeonRooms->find(currentPos.toString())->second.isDiscovered == true)
            {
                Position WRoom = currentPos + Position(-1, 0);
                if (xpos == lowestX || allDungeonRooms->find(WRoom.toString()) == allDungeonRooms->end())
                {
                    map.append(roomYaxis);
                }
                if (playerPos == currentPos)
                {
                    map.append(roomPlayerBottom);
                }
                else
                    map.append(roomEmpty);
                map.append(roomYaxis);
            }
            else
            {
                Position WRoom = currentPos + Position(-1, 0);
                if (xpos == lowestX || allDungeonRooms->find(WRoom.toString()) == allDungeonRooms->end())
                {
                    map.append(spaceExtra); //one extra space for correct alignment
                }
                map.append(spaceBetweenRooms);
                if (xpos == highestX)
                {
                    map.append(spaceExtra);
                }
            }
            break;
        }
        }
    }

    map.append("\n");
}

void Map::setPlayerPos(Position &pos)
{
    playerPos = pos;
}

void Map::printMap()
{
    calculateDungeonSize();

    int xLength = (highestX - lowestX) + 1;
    int yLength = (highestY - lowestY) + 1;

    system("CLS");

    for (int index = highestY; index >= lowestY; index--)
    {
        drawYDividers(index);
        drawRowRooms(index, TOP);
        drawRowRooms(index, MIDDLE);
        drawRowRooms(index, BOTTOM);

        if (index == lowestY)
            drawYDividers(index - 1);
    }

    cout << endl
         << map << flush;
}