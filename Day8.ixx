export module Day8;

import std.core;

namespace Day8
{
    export typedef std::tuple<std::string, int> CommandValue;
    typedef std::tuple<int, bool> ProgramResult;

    export ProgramResult ProcessInput(const std::vector<CommandValue>& data)
    {
        ProgramResult result{0, true};

        std::set<int> executedInstructions;

        size_t currentInstruction = 0;
        size_t maxInstruction = data.size();

        while (currentInstruction >= 0 && currentInstruction < maxInstruction)
        {
            auto [command, value] = data[currentInstruction];

            //check for infinite loop
            if (executedInstructions.find(currentInstruction) != executedInstructions.end())
            {
                std::get<1>(result) = false;
                return result;
            }

            executedInstructions.insert(currentInstruction);

            currentInstruction++;
            //these should be data driven
            if (command == "acc")
            {
                std::get<0>(result) += value;
            }
            else if (command == "jmp")
            {
                currentInstruction += (value-1);
            }
            else if (command == "nop")
            {
                /* do nothing */
            }
            else
            {
                std::get<1>(result) = false;
                break;
            }
        }

        return result;
    }

    export ProgramResult FindSwappedCommand(std::vector<CommandValue> data, const std::map<std::string, std::string>& commandsToSwap)
    {
        ProgramResult result{ 0, false };

        for (size_t i = 0; i < data.size(); ++i)
        {
            auto [command, value] = data[i];

            auto cmdIter = commandsToSwap.find(command);
            if (cmdIter != commandsToSwap.end())
            {
                std::get<0>(data[i]) = cmdIter->second;
                auto [value, success] = ProcessInput(data);
                if (success)
                {
                    std::get<1>(result) = true;
                    return ProgramResult{value, success};
                }
                else
                {
                    std::get<0>(data[i]) = cmdIter->first;
                }
            }
        }

        return result;
    }
}