#include "Map.h"

using namespace std;

// Void
string space = "........";
string spaceBetweenRooms = ".......";
string spaceExtra = ".";

// Walls
string roomXaxisFull = "--------";
string roomXaxisFull2 = "-------";
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
        // If this is the first position to the left
        if (xpos == lowestX)
        {
            if ((roomExists(currentPos) && roomIsDiscovered(currentPos)) ||
                (roomExists(NRoom) && roomIsDiscovered(NRoom)))
            {
                map.append(roomXaxisExtra);
            }
            else
                map.append(spaceExtra);
        }

        // If it not the first to the left, but first part of another room
        else
        {
            if ((roomExists(currentPos) && roomIsDiscovered(currentPos)) ||
                (roomExists(NRoom) && roomIsDiscovered(NRoom)) ||
                (roomExists(WRoom) && roomIsDiscovered(WRoom)) ||
                (roomExists(NWRoom) && roomIsDiscovered(NWRoom)))
            {
                map.append(roomXaxisExtra);
            }
            else
                map.append(spaceExtra);
        }

        // What to fill the remainder with
        if ((roomExists(currentPos) && roomIsDiscovered(currentPos)) ||
            (roomExists(NRoom) && roomIsDiscovered(NRoom)))
        {
            if(roomExists(currentPos) && roomExists(NRoom)){
                if(dungeon->areRoomsConnected(currentPos, NRoom)){
                    map.append(roomXaxis);
                    map.append(roomYDoors);
                    map.append(roomXaxis);
                } else map.append(roomXaxisFull2);
            } else map.append(roomXaxisFull2);
        }
        else
        {
            map.append(spaceBetweenRooms);
        }

        if (xpos == highestX)
        {
            if ((roomExists(currentPos) && roomIsDiscovered(currentPos)) ||
                (roomExists(NRoom) && roomIsDiscovered(NRoom)))
            {
                map.append(roomXaxisExtra);
            }
            else
            {
                map.append(spaceExtra);
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

        // Capture positions closeby of relevance
        Position WRoom = currentPos + Position(-1, 0);
        Position ERoom = currentPos + Position(1, 0);

        // Room content is built in three layers - top, middle & bottom
        switch (part)
        {

        // Build room top content
        case TOP:
        {
            // If current room exists AND is discovered
            if (roomExists(currentPos) && roomIsDiscovered(currentPos))
            {
                //If this is the first room from the left OR
                //there is not an existing or a discovered room to the left
                if (xpos == lowestX || !roomExists(WRoom) || !roomIsDiscovered(WRoom))
                {
                    map.append(roomYaxis);
                }

                // Add player top graphic
                if (playerPos == currentPos)
                {
                    map.append(roomPlayerTop);
                }
                // Or an empty room content
                else
                    map.append(roomEmpty);

                // Draw the right wall
                map.append(roomYaxis);
            }

            // If current room exists AND is NOT discovered
            else if (roomExists(currentPos) && !roomIsDiscovered(currentPos))
            {
                //If this is the first room from the left
                if ((xpos == lowestX && !roomExists(WRoom)) || !roomExists(WRoom))
                {
                    map.append(spaceExtra);
                }
                // If a room to the left exists
                if (roomExists(WRoom))
                {
                    if (!roomIsDiscovered(WRoom))
                    {
                        map.append(spaceExtra);
                    }
                }

                //Draw space
                map.append(spaceBetweenRooms);

                //Draw extra space if this is the far right room of the map
                if (xpos == highestX)
                {
                    map.append(spaceExtra);
                }
            }

            // Or room doesn't exist
            else
            {
                //If this is the first position from the left
                if (xpos == lowestX || !roomExists(WRoom) || !roomIsDiscovered(WRoom))
                {
                    map.append(spaceExtra);
                }

                map.append(spaceBetweenRooms);

                //Draw extra space if this is the far right position of the map
                if (xpos == highestX)
                {
                    map.append(spaceExtra);
                }
            }
        }
        break;

        // Build room middle content
        case MIDDLE:
        {
            // If current room exists AND is discovered
            if (roomExists(currentPos) && roomIsDiscovered(currentPos))
            {
                //If this is the first room from the left OR
                //there is not an existing or a discovered room to the left
                if ((xpos == lowestX && !roomExists(WRoom)) || !roomExists(WRoom))
                {
                    map.append(roomYaxis);
                }

                // If a room to the left exists
                else if (roomExists(WRoom))
                {
                    // If the left room is connected by a door
                    if (dungeon->areRoomsConnected(currentPos, WRoom))
                    {
                        if (!roomIsDiscovered(WRoom))
                        {
                            map.append(roomXDoors);
                        }
                    }
                    else
                    {
                        if (!roomIsDiscovered(WRoom))
                        {
                            map.append(roomYaxis);
                        }
                    }
                }

                // Add player top graphic
                if (playerPos == currentPos)
                {
                    map.append(roomPlayerMiddle);
                }
                // Or an empty room content
                else
                    map.append(roomEmpty);

                // Draw the right wall
                if (dungeon->areRoomsConnected(currentPos, ERoom))
                {
                    map.append(roomXDoors);
                }
                else
                    map.append(roomYaxis);
            }

            // If current room exists AND is NOT discovered
            else if (roomExists(currentPos) && !roomIsDiscovered(currentPos))
            {
                //If this is the first room from the left
                if ((xpos == lowestX && !roomExists(WRoom)) || !roomExists(WRoom))
                {
                    map.append(spaceExtra);
                }
                // If a room to the left exists
                if (roomExists(WRoom))
                {
                    // If the left room is connected by a door
                    if (dungeon->areRoomsConnected(currentPos, WRoom))
                    {
                        if (!roomIsDiscovered(WRoom))
                        {
                            map.append(spaceExtra);
                        }
                    }
                    else
                    {
                        if (!roomIsDiscovered(WRoom))
                        {
                            map.append(spaceExtra);
                        }
                    }
                }

                //Draw space
                map.append(spaceBetweenRooms);

                //Draw extra space if this is the far right room of the map
                if (xpos == highestX)
                {
                    map.append(spaceExtra);
                }
            }

            // Or room doesn't exist
            else
            {
                //If this is the first position from the left
                if (xpos == lowestX || !roomExists(WRoom) || !roomIsDiscovered(WRoom))
                {
                    map.append(spaceExtra);
                }

                map.append(spaceBetweenRooms);

                //Draw extra space if this is the far right position of the map
                if (xpos == highestX)
                {
                    map.append(spaceExtra);
                }
            }
        }
        break;

        // Build room bottom content
        case BOTTOM:
        {
            // If current room exists AND is discovered
            if (roomExists(currentPos) && roomIsDiscovered(currentPos))
            {
                //If this is the first room from the left OR
                //there is not an existing or a discovered room to the left
                if (xpos == lowestX || !roomExists(WRoom) || !roomIsDiscovered(WRoom))
                {
                    map.append(roomYaxis);
                }

                // Add player top graphic
                if (playerPos == currentPos)
                {
                    map.append(roomPlayerBottom);
                }
                // Or an empty room content
                else
                    map.append(roomEmpty);

                // Draw the right wall
                map.append(roomYaxis);
            }

            // If current room exists AND is NOT discovered
            else if (roomExists(currentPos) && !roomIsDiscovered(currentPos))
            {
                //If this is the first room from the left
                if ((xpos == lowestX && !roomExists(WRoom)) || !roomExists(WRoom))
                {
                    map.append(spaceExtra);
                }
                // If a room to the left exists
                if (roomExists(WRoom))
                {
                    if (!roomIsDiscovered(WRoom))
                    {
                        map.append(spaceExtra);
                    }
                }

                //Draw space
                map.append(spaceBetweenRooms);

                //Draw extra space if this is the far right room of the map
                if (xpos == highestX)
                {
                    map.append(spaceExtra);
                }
            }

            // Or room doesn't exist
            else
            {
                //If this is the first position from the left
                if (xpos == lowestX || !roomExists(WRoom) || !roomIsDiscovered(WRoom))
                {
                    map.append(spaceExtra);
                }

                map.append(spaceBetweenRooms);

                //Draw extra space if this is the far right position of the map
                if (xpos == highestX)
                {
                    map.append(spaceExtra);
                }
            }
        }
        break;
        }
    }

    map.append("\n");
}

/*
    TODO: In regards to the two above functions drawYDividers and drawRowRooms:

    A better solution would be to handle room content and room walls seperately.
    E.g. in drawYdividers:
        1. First check if there is a room on this pos OR above and draw walls
           accordingly, i.e. if anyone of them is discovered. 
           Checks if it is first room from left etc is still needed.
        2. Check if there are both rooms and draw door, otherwise a solid wall.
    E.g. in drawRowRooms:
        1. First check if there is a room on this pos OR to the left and draw 
           walls accordingly, i.e. if anyone of them is discovered. 
        2. Check if there are both rooms and draw door, otherwise a solid wall.
        3. Continue with drawing room content, only if room is discovered.

    But for whatever reason, this logic failed severely and I need to come back
    to this later.
    Update: the drawYDividers refactoring is complete.
*/

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