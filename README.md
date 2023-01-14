# Exercise 1 Shortest Path
The CSV file probabilities.csv contains information for his 11 players in the game.
In this file, the player's value on the main diagonal is the probability that the player will score.
goal. Each value in a row other than those on the main diagonal is a probability
A successful pass from that player to the relevant player. For example, the value in row 1,
Column 2 is the probability of a successful pass from player 1 to player 2. null value
A player on the main diagonal means that the player cannot shoot and there is no one
probability of scoring a goal. But any other zero value means no edge from a.
From one player to another. So in this exercise the ball is in the hands of the designated player and
The goal is to find a way to maximize the probability of a particular player scoring a goal.
Path length is the sum of the values at the ends of the path. to minimize it
It's a product, not a sum. Take the logarithm. edge value
Logarithmic, the shortest path is the smallest product (because log(a*b)=loga + logb). However, rather than minimizing joint probabilities, we should maximize them. So we
Multiply the edge value by -1. edge value preprocessing and
A shortest-path algorithm that maximizes the product instead of minimizing the sum.

Two positional command line arguments are passed to the program.


1. Probability file path (e.g. data/probabilities.csv)

2. A positive integer s specifying the player index.

We can assume that both path and s are valid (such a file exists and 0 ≤ s ≤ 10). This program is expected to:

1. Create a directed graph.

2. Read the probabilities.csv file line by line and add the probabilities to the graph.

3. Display the matrix specified in the file.

4. Preprocess the edge values, excluding unique edges of the graph.
Log 10 of the edge value and multiply by -1. 5. Run Dijkstra's shortest path algorithm with the specified player as the source.
Vertices using preprocessed values.

5. Because not all players can find the pass that maximizes their shots in the game
Probability of scoring for a given player, for which the program performs post-processing
Archer. Multiply the shooter's calculated value by its probability
A shooter who scores a goal. If a given player is a shooter, the probability of scoring a goal is
Goals are already given, no need for multiplication.

6. Display the path that maximizes the probability of the specified player scoring the goal.

# Exercise 2: Greedy Algorithms

This exercise uses time rather than probability. The CSV file times.csv contains
Information about his 11 player times present in the game. main diagonal value
Provide player shooting time. Each other value in the row is a time
Players are taken to pass the ball to each player. As in Exercise 1, null values
on the main diagonal indicates that the player cannot shoot, other zero values ​​are
The ball is not passed, indicating no advantage from one player to another. of
In this exercise the ball is at a designated player and the player tries to score like a goal
as soon as possible. Find the path for the ball to reach the goal in the shortest time.
The idea is that if the player in possession of the ball can shoot, the player shoots. Otherwise,
A player gives a pass to whoever the player can pass in the shortest time. but the player
Players already in possession of the ball are not selected. if there are multiple
The player with the shortest time, the one with the lowest index, will be selected.
If there is no one to pass the ball, it means that you can't shoot anyway, and the input is
invalid. You might think that such a situation would never happen.

The program will display the matrix specified in the file and the path that will take the ball to the goal
shortest time.
