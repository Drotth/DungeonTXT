#pragma once
#include <string>
#include <iostream>

struct Position
{
    int x;
    int y;

    // default + parameterized constructor
    Position(int x = 0, int y = 0) : x(x), y(y)
    {
    }

    Position &operator=(const Position &a)
    {
        x = a.x;
        y = a.y;
        return *this;
    }

    Position operator+(const Position& a) const
    {
        return Position(a.x+x, a.y+y);
    }

    bool operator==(const Position &a) const
    {
        return (x == a.x && y == a.y);
    }

    friend std::ostream &operator<<(std::ostream &os, const Position &pos)
    {
        return os << "x:" << pos.x << ", y:" << pos.y;
    }

    std::string toString() {
        return "x:" + std::to_string(x) + ", y:" + std::to_string(y); 
    }
};

class Room
{
public:
    Position roomPos;
    std::string roomName;
    Room(Position, std::string);
};
