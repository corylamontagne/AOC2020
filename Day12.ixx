export module Day12;

import std.core;

namespace Day12
{
    export typedef std::tuple<char, int> CommandValue;
    export typedef std::vector<CommandValue> CommandValueMap;

    export struct Vec2D
    {
        Vec2D& operator+=(const Vec2D& r)
        {
            this->x += r.x;
            this->y += r.y;
            return *this;
        }
        Vec2D operator*(const int& r)
        {
            Vec2D result;
            result.x = this->x * r;
            result.y = this->y * r;
            return result;
        }

        int x;
        int y;
    };

    static std::map<char, Vec2D> DIRECTIONS = { {'N', {1, 0}},
                                                {'E', {0, 1}},
                                                {'W', {0, -1}},
                                                {'S', {-1, 0}} };
    static std::string Compass = "NESW";
    static int NumberOfDirs = 4;

    export CommandValueMap ConvertToCVM(const std::vector<std::string>& input)
    {
        CommandValueMap result;

        std::for_each(input.begin(), input.end(), [=, &result](std::string s) { result.push_back(CommandValue(s[0], stoi(s.substr(1, s.length())))); });

        return result;
    }

    export int GetDistance(const CommandValueMap& data, char initialDirection)
    {
        Vec2D position(0, 0);
        Vec2D direction(DIRECTIONS[initialDirection]);
        char crDir = initialDirection;

        for (auto [command, value] : data)
        {
            if (command == 'F')
            {
                position += (direction * value);
            }
            else if (command == 'R' || command == 'L')
            {
                int index = Compass.find(crDir);
                index += ((value / 90) * ((command == 'R') ? 1 : -1));
                if (index >= NumberOfDirs) 
                { 
                    index -= NumberOfDirs; 
                }
                else if (index < 0) 
                { 
                    index += NumberOfDirs;
                }
                crDir = Compass[index];
                direction = DIRECTIONS[crDir];
            }
            else
            {
                position += (DIRECTIONS[command] * value);
            }
        }

        return abs(position.x) + abs(position.y);
    }

    export int GetDistanceToWaypoint(const CommandValueMap& data, Vec2D initialWPPosition)
    {
        Vec2D position(0, 0);
        Vec2D waypointPosition(initialWPPosition);

        for (auto [command, value] : data)
        {
            if (command == 'F')
            {
                position += (waypointPosition * value);
            }
            else if (command == 'R' || command == 'L')
            {
                bool right = (command == 'R');
                int angle = value / 90;
                for (int i = 0; i < angle; ++i)
                {
                    int x = waypointPosition.y * (right ? -1 : 1);
                    int y = waypointPosition.x * (right ? 1 : -1);
                    waypointPosition.x = x;
                    waypointPosition.y = y;
                }
            }
            else
            {
                waypointPosition += (DIRECTIONS[command] * value);
            }
        }

        return abs(position.x) + abs(position.y);
    }
}