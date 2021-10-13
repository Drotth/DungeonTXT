#include <iostream>
#include "Dungeon.h"

using namespace std;

int main()
{
	Dungeon newDungeon;

	// Verify room/door setups
	// cout << "Nbr of rooms: " << newDungeon.dungeonRooms.size() << endl;
	// cout << "Nbr of doors: " << newDungeon.dungeonDoors.size() << endl;

	// for (Room room : newDungeon.dungeonRooms)
	// {
	// 	cout << "Roomlist: " << room.roomName << endl;
	// }

	// for (Door door : newDungeon.dungeonDoors)
	// {
	// 	cout << "doorlist: Room A: " << door.roomA << endl;
	// 	cout << "doorlist: Room B: " << door.roomB << endl;
	// }

	string currentRoom = "Room 2";
	vector<string> doors = newDungeon.getRoomDoors(currentRoom);

	cout << "Doors in " << currentRoom << endl;
	for (string door : doors)
	{
		cout << door << endl;
	}
}
