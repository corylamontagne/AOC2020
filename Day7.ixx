export module Day7;

import std.core;

namespace Day7
{
    export typedef std::vector<std::pair<std::string, int>> BagCountPair;
    export typedef std::map<std::string, BagCountPair> MatryoshkaBags;

    //Interesting but so SLOW, do not replicate!
    //The matryoshkaBags structure is non-intuitive and I shoudl refacor everything
    //Each key is a bag, and inside are the parents of that bag and how many of them they contain.
    //So [A, [B, 5]] means bag is is contained within bag B 5 times.
    //This is not only terrible to think about, but in practice the solution of reiterating over maps of vecs in this case
    //is god awful, but abbreviated time does not always permit the best solution
    BagCountPair GetParentsOfBag(MatryoshkaBags data, const std::string& name)
    {
        BagCountPair results;

        auto bag = data.find(name);
        
        if (bag != data.end())
        {
            for (auto i : bag->second)
            {
                BagCountPair r = GetParentsOfBag(data, i.first);
                results.insert(results.end(), r.begin(), r.end());
            }

            results.insert(results.end(), bag->second.begin(), bag->second.end());
        }

        return results;
    }

    export unsigned int GetNumberOfParents(MatryoshkaBags matryoshkaBags, const std::string& name)
    {
        BagCountPair bagTrain = GetParentsOfBag(matryoshkaBags, name);

        std::set<std::string> s;
        std::for_each(bagTrain.begin(), bagTrain.end(), [=,&s](const std::pair<std::string, int> c) {s.insert(c.first); });

        return s.size();
    }

    export MatryoshkaBags GetMatryoshkaBags(const std::vector<std::string>& input, const std::string& name)
    {
        MatryoshkaBags matryoshkaBags;

        for (auto rule : input)
        {
            std::string word[3], desc;
            std::stringstream iss(rule);

            std::string parent;
            while (iss >> desc)
            {
                if (desc.find("bag") != std::string::npos)
                {
                    std::string bag = word[1] + " " + word[2];

                    if (parent.empty()) { parent = bag; }
                    else if (bag == "no other") {/* Do nothing */}
                    else 
                    { 
                        matryoshkaBags[bag].push_back( std::make_pair(parent, stoi(word[0]))); 
                    }
                }
                word[0] = word[1];
                word[1] = word[2];
                word[2] = desc;
            }
        }

        return matryoshkaBags;
    }

    //this wasnt the worst considering
    export unsigned int GetNumberOfBagsToContain(MatryoshkaBags matryoshkaBags, const std::string& name)
    {
        unsigned int results = 0;

        for (auto i : matryoshkaBags)
        {
            for (auto j : i.second)
            {
                if (j.first == name)
                {
                    int contained = j.second;
                    results += contained + contained * GetNumberOfBagsToContain(matryoshkaBags, i.first);
                }
            }
        }

        return results;
    }
}