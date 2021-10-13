#include "Map.h"

using namespace std;

Map::Map(unordered_map<string, Room> &rooms, unordered_map<string, Door> &doors)
{
    allDungeonRooms = &rooms;
    allDungeonDoors = &doors;
}

void Map::printMap()
{
    int nbrRooms = allDungeonRooms->size();
    string map;

    switch (nbrRooms)
    {
    case 0:
        map =
            string("__________\n") +
            string("|        |\n") +
            string("|    0   |\n") +
            string("|        |\n") +
            string("----------\n");
        break;

    case 1:
        map =
            string("__________\n") +
            string("|        |\n") +
            string("|    1   |\n") +
            string("|        |\n") +
            string("----------\n");
        break;
    case 2:
        map =
            string("__________\n") +
            string("|        |\n") +
            string("|    2   |\n") +
            string("|        |\n") +
            string("----------\n");
        break;
    case 3:
        map =
            string("__________\n") +
            string("|        |\n") +
            string("|    3   |\n") +
            string("|        |\n") +
            string("----------\n");
        break;
    case 4:
        map =
            string("__________\n") +
            string("|        |\n") +
            string("|    4   |\n") +
            string("|        |\n") +
            string("----------\n");
        break;
    default:
        cout << "Oopsie poopsie" << endl;
    }

    system("CLS");
    cout << map;
}