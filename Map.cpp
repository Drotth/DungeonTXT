#include "Map.h"

using namespace std;

string space = "         ";
string roomXaxisFull = "---------";
string roomXaxis = "---";
string roomYaxis = "|";
string roomEmpty = "       ";
string roomYDoors = "=";
string roomXDoors = "| |";
string roomPlayerTop = "|  _o_  |";
string roomPlayerMiddle = "|   |   |";
string roomPlayerBottom = "|  / \\  |";

Map::Map(Dungeon& inDungeon)
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
        if (i->second.roomPos.x < lowestX)
            lowestX = i->second.roomPos.x;
        if (i->second.roomPos.x > highestX)
            highestX = i->second.roomPos.x;
        if (i->second.roomPos.y < lowestY)
            lowestY = i->second.roomPos.y;
        if (i->second.roomPos.y > highestY)
            highestY = i->second.roomPos.y;
    }
}

void Map::drawYDividers(int yLevel)
{
    Position currentPos(lowestX, yLevel);

    for (int xpos = lowestX; xpos <= highestX; xpos++)
    {
        currentPos = Position(xpos, yLevel);

        if (allDungeonRooms->find(currentPos.toString()) != allDungeonRooms->end())
        {
            Position potentialNorthRoom = currentPos + Position(0, 1);
            if (dungeon->areRoomsConnected(currentPos, potentialNorthRoom)){
                map.append(roomXaxis);
                map.append(roomXDoors);
                map.append(roomXaxis);
            } else map.append(roomXaxisFull);
        }
        else
        {
            Position potentialNorthRoom = currentPos + Position(0, 1);
            if (allDungeonRooms->find(potentialNorthRoom.toString()) != allDungeonRooms->end())
            {
                map.append(roomXaxisFull);
            }
            else
                map.append(space);
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
            if (allDungeonRooms->find(currentPos.toString()) != allDungeonRooms->end())
            {
                map.append(roomYaxis);
                map.append(roomEmpty);
                map.append(roomYaxis);
            }
            else
            {
                map.append(space);
            }
            break;
        }
        case MIDDLE:
        {
            if (allDungeonRooms->find(currentPos.toString()) != allDungeonRooms->end())
            {
                map.append(roomYaxis);
                map.append(roomEmpty);
                map.append(roomYaxis);
            }
            else
            {
                map.append(space);
            }
            break;
        }
        case BOTTOM:
        {
            if (allDungeonRooms->find(currentPos.toString()) != allDungeonRooms->end())
            {
                map.append(roomYaxis);
                map.append(roomEmpty);
                map.append(roomYaxis);
            }
            else
            {
                map.append(space);
            }
            break;
        }
        }
    }

    map.append("\n");
}

void Map::printMap()
{
    int xLength = (highestX - lowestX) + 1;
    int yLength = (highestY - lowestY) + 1;

    system("CLS");

    for (int index = highestY; index >= lowestY; index--)
    {
        drawYDividers(index);
        drawRowRooms(index, TOP);
        drawRowRooms(index, MIDDLE);
        drawRowRooms(index, BOTTOM);

        if (index == lowestY) drawYDividers(index-1);
    }

    cout << endl
         << map << flush;
}