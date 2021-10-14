#include "Map.h"

using namespace std;

string space = "         ";
string roomXaxis = "---------";
string roomEmpty = "|       |";
string roomPlayerTop = "|  _o_  |";
string roomPlayerMiddle = "|   |   |";
string roomPlayerBottom = "|  / \\  |";

Map::Map(unordered_map<string, Room> &rooms, unordered_map<string, Door> &doors)
{
    allDungeonRooms = &rooms;
    allDungeonDoors = &doors;

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
        // cout << i->second.roomPos.x << "\t" << i->second.roomPos.y << endl;
        if (i->second.roomPos.x < lowestX)
            lowestX = i->second.roomPos.x;
        if (i->second.roomPos.x > highestX)
            highestX = i->second.roomPos.x;
        if (i->second.roomPos.y < lowestY)
            lowestY = i->second.roomPos.y;
        if (i->second.roomPos.y > highestY)
            highestY = i->second.roomPos.y;
    }

    // cout << "Lowest X (low left corner):\t" + to_string(lowestX) << endl
    //      << "Highest X (low right corner):\t" + to_string(highestX) << endl
    //      << "Lowest Y (high left corner):\t" + to_string(lowestY) << endl
    //      << "Highest Y (high right corner):\t" + to_string(highestY) << endl;
}

void Map::addYDivider(int yLevel)
{
    Position currentPos(lowestX, yLevel);

    for (int xpos = lowestX; xpos <= highestX; xpos++)
    {
        currentPos = Position(xpos, yLevel);
        // cout << "At position: " << currentPos;
        if (allDungeonRooms->find(currentPos.toString()) != allDungeonRooms->end())
        {
            // cout << roomXaxis;
            map.append(roomXaxis);
        }
        else
        {
            // cout << space;
            map.append(space);
        }
    }

    // cout << endl;
    map.append("\n");
}

void Map::printMap()
{
    int xLength = (highestX - lowestX) + 1;
    int yLength = (highestY - lowestY) + 1;

    system("CLS");

    for (int index = highestY; index >= lowestY; index--)
    {
        addYDivider(index);
        // build 3 row rooms
        // If last iteration, add final Y divider
    }

    cout << endl
         << map;
}