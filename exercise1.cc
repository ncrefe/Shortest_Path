#include <iostream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

/**
 * It takes a string and a delimiter character and returns a vector of strings
 *
 * @param str The string to split
 * @param delimiter The character that separates the string into tokens.
 *
 * @return A vector of strings.
 */
vector<string> splitString(string str, char delimiter)
{
    vector<string> internal;
    stringstream ss(str); // Turn the string into a stream.
    string tok;

    while (getline(ss, tok, delimiter))
    {
        internal.push_back(tok);
    }

    return internal;
}

/**
 * This function reads a file and returns a vector of vectors of strings
 *
 * @param fileName The name of the file to read from.
 *
 * @return A vector of vectors of strings.
 */
vector<vector<string>> readFileString(const string &fileName)
{
    ifstream file(fileName);
    string line;
    vector<vector<string>> possibilities;
    while (getline(file, line))
    {
        vector<string> split = splitString(line, ',');
        vector<string> row;
        for (int i = 0; i < split.size(); i++)
        {
            row.push_back(split[i]);
        }
        possibilities.push_back(row);
    }
    file.close();

    return possibilities;
}

/**
 * A node is a struct that has two fields, one of type int and one of type double.
 * @property {int} shirtNumber - The number on the player's shirt.
 * @property {double} goalChance - The chance of the player scoring a goal.
 */
struct node
{
    int shirtNumber;
    double goalChance;
};

/**
 * It reads a CSV file and returns a vector of vectors of doubles
 *
 * @param fileName The name of the file to read from.
 *
 * @return A vector of vectors of doubles.
 */
vector<vector<double>> readFile(const string &fileName)
{
    ifstream file(fileName);
    string line;
    vector<vector<double>> possibilities;
    while (getline(file, line))
    {
        vector<string> split = splitString(line, ',');
        vector<double> row;
        for (int i = 0; i < split.size(); i++)
        {
            row.push_back(stod(split[i].c_str()));
        }
        possibilities.push_back(row);
    }
    file.close();

    return possibilities;
}

struct edge
{
    node &from;
    node &to;
    double passChance;

    edge(node &from, node &to) : from(from), to(to) {}

    void setPassChance(double p)
    {
        passChance = p;
    }
};

/**
 * > The function takes a p-value and returns the negative log of the p-value
 *
 * @param value the value to be processed
 *
 * @return The log10 of the value.
 */
double preProcessing(double value)
{
    return -log10(value);
}

/**
 * It takes a vector of vectors of doubles and returns a vector of nodes
 *
 * @param possibilities a vector of vectors of doubles. Each vector of doubles represents the chances
 * of a player scoring a goal.
 *
 * @return A vector of nodes.
 */
vector<node> createNodes(vector<vector<double>> possibilities)
{
    vector<node> nodes;
    for (int i = 0; i < possibilities.size(); i++)
    {
        node player;
        player.goalChance = possibilities[i][i];
        player.shirtNumber = i;
        nodes.push_back(player);
    }
    return nodes;
}

/**
 * It takes a vector of vectors of strings and prints each string in each vector of strings on a new
 * line
 *
 * @param possibilities a vector of vectors of strings. Each vector of strings represents a possible
 * combination of the input.
 */
void printPossibilities(vector<vector<string>> possibilities)
{
    for (int i = 0; i < possibilities.size(); i++)
    {
        for (int a = 0; a < possibilities.size(); a++)
        {
            if (a != possibilities.size() - 1)
            {
                cout << (possibilities[i][a]) << ",";
            }
            else
            {
                cout << (possibilities[i][a]) << endl;
            }
        }
    }
}

/**
 * It takes a file path and a number, and returns the shortest path from the number to a goal scorer
 *
 * @param argc number of arguments
 * @param argv
 *
 * @return The program is returning the shortest path from the player with the shirt number given as
 * the second argument to the goal.
 */
int main(int argc, char **argv)
{
    string path = argv[1];
    int number = atoi(argv[2]);

    vector<vector<double>> possibilities = readFile(path);

    vector<vector<string>> possibilitiesString = readFileString(path);
    printPossibilities(possibilitiesString);

    vector<node> players = createNodes(possibilities);

    vector<int> whoCanScore;
    for (int i = 0; i < players.size(); i++)
    {
        if (players[i].goalChance > 0)
        {
            whoCanScore.push_back(players[i].shirtNumber);
        }
    }

    vector<edge> passes;
    for (int i = 0; i < possibilitiesString.size(); i++)
    {
        for (int a = 0; a < possibilities[i].size(); a++)
        {
            if (possibilitiesString[i][a] != "0" && i != a)
            {
                edge pass(players[i], players[a]);
                pass.setPassChance(preProcessing(stod(possibilitiesString[i][a])));
                passes.push_back(pass);
            }
        }
    }

    node currentNode = players[number];
    vector<double> distances;
    vector<int> parents;
    for (int i = 0; i < players.size(); i++)
    {
        distances.push_back(INT_MAX);
        parents.push_back(-1);
    }
    distances[currentNode.shirtNumber] = 0;

    vector<int> visited;
    while (true)
    {
        vector<edge> canPass;
        for (int i = 0; i < passes.size(); i++)
        {
            if (passes[i].from.shirtNumber == currentNode.shirtNumber)
            {
                canPass.push_back(passes[i]);
            }
        }

        for (int i = 0; i < canPass.size(); i++)
        {
            if (canPass[i].passChance + distances[currentNode.shirtNumber] < distances[canPass[i].to.shirtNumber])
            {
                distances[canPass[i].to.shirtNumber] = canPass[i].passChance + distances[currentNode.shirtNumber];
                parents[canPass[i].to.shirtNumber] = currentNode.shirtNumber;
            }
        }

        visited.push_back(currentNode.shirtNumber);
        if (visited.size() == players.size())
        {
            break;
        }

        double smallestDistance = FLT_MAX;
        int smallestElement = currentNode.shirtNumber;
        for (int i = 0; i < distances.size(); i++)
        {
            if (distances[i] < smallestDistance)
            {
                bool include = false;

                for (int j = 0; j < visited.size(); j++)
                {
                    if (visited[j] == i)
                    {
                        include = true;
                    }
                }

                if (!include)
                {
                    smallestDistance = distances[i];
                    smallestElement = i;
                }
            }
        }
        currentNode = players[smallestElement];
    }

    distances[number] = 1;
    double minimum = 0;
    int shooter = -1;
    for (int i = 0; i < whoCanScore.size(); i++)
    {
        if (players[whoCanScore[i]].goalChance * distances[whoCanScore[i]] > minimum)
        {
            minimum = players[whoCanScore[i]].goalChance * distances[whoCanScore[i]];
            shooter = whoCanScore[i];
        }
    }

    vector<int> result;
    result.push_back(shooter);
    for (int i = 0; i < parents.size(); i++)
    {
        if (shooter == number)
        {
            break;
        }
        result.push_back(parents[shooter]);
        shooter = parents[shooter];
    }
    reverse(result.begin(), result.end());
    for (int i = 0; i < result.size(); i++)
    {
        if (result.size() - 1 == i)
        {
            cout << result[i] << endl;
        }
        else
        {
            cout << result[i] << " ";
        }
    }

    return 0;
}
