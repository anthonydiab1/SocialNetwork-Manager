#ifndef SOCIALNETWORK_H
#define SOCIALNETWORK_H

#include <vector>
#include <string>
#include <iostream>

using namespace std;

/**
 * @brief The SocialNetwork class simulates a basic social network using an undirected, unweighted graph.
 *
 * Each person is represented as a node, and each friendship is an edge between two nodes.
 * The graph is stored as an edge list and supports operations such as:
 * - Adding/removing people and friendships
 * - Finding shortest communication paths
 * - Recommending friends based on mutual connections
 * - Displaying the network
 */
class SocialNetwork
{
private:
    /**
     * @brief Internal class representing a person in the social network.
     */
    class Node
    {
        string name; ///< The name of the person

    public:
        /**
         * @brief Parameterized constructor.
         * @param name The name to assign to the node.
         */
        Node(string name);

        /**
         * @brief Default constructor. Initializes an empty name.
         */
        Node();

        /**
         * @brief Sets the person's name.
         * @param name New name for the person.
         */
        void setName(string name);

        /**
         * @brief Retrieves the person's name.
         * @return The name of the node.
         */
        string getName() const;

        /**
         * @brief Equality operator. Compares nodes by name.
         * @param node The node to compare with.
         * @return True if both nodes have the same name.
         */
        bool operator==(const Node &node) const;
    };

    /**
     * @brief Internal class representing a friendship (edge) between two people.
     */
    class Edge
    {
    private:
        Node node1; ///< First person
        Node node2; ///< Second person

    public:
        /**
         * @brief Constructs an edge (friendship) between two people.
         * @param node1 First person.
         * @param node2 Second person.
         */
        Edge(Node node1, Node node2);

        /**
         * @brief Gets the first node of the edge.
         * @return Reference to the first node.
         */
        const Node &getNode1() const;

        /**
         * @brief Gets the second node of the edge.
         * @return Reference to the second node.
         */
        const Node &getNode2() const;
    };

private:
    /**
     * @brief List of all friendships in the network
     *
     * Each Edge object represents a bidirectional friendship between two people.
     * Since the graph is undirected, the order of nodes in an edge doesn't matter.
     * When a friendship is removed, the corresponding edge is deleted from this list.
     */
    vector<Edge> edgeList;

    /**
     * @brief List of all people in the network
     *
     * Maintains a list of all Node objects, where each node represents a person.
     * The index of a node in this list can be used as a unique identifier.
     * When a person is deleted, their node is removed from this list and all
     * their associated edges are removed from edgeList.
     */
    vector<Node> nodesList;

public:
    /**
     * @brief Default constructor. Initializes an empty network.
     */
    SocialNetwork();

    /**
     * @brief Parameterized constructor to initialize the network with existing people and friendships.
     * @param edge_list List of friendships.
     * @param nodes_list List of people.
     */
    SocialNetwork(vector<Edge> &edge_list, vector<Node> &nodes_list);

    /**
     * @brief Internal helper method that finds a person's index in the network.
     * @note This method name doesn't follow standard naming conventions and could be renamed to isNodeFound or findNode in future versions.
     * @param node The person to search for.
     * @return Index of the node in nodesList if found, -1 otherwise.
     */
    int isnodefound(const Node &node) const;

    /**
     * @brief Adds a person to the network.
     * @param person The name of the person to add.
     */
    void addPerson(const string &person);

    /**
     * @brief Creates a friendship between two existing people.
     * @param personA Name of the first person.
     * @param personB Name of the second person.
     */
    void addFriend(const string &personA, const string &personB);

    /**
     * @brief Removes the friendship between two people.
     * @param personA First person.
     * @param personB Second person.
     */
    void unfriend(const string &personA, const string &personB);

    /**
     * @brief Deletes a person and all their friendships from the network.
     * @param person The name of the person to remove.
     * @return True if the person was found and deleted.
     */
    bool deletePerson(const string &person);

    /**
     * @brief Checks whether two people are friends.
     * @param PersonA Name of the first person.
     * @param PersonB Name of the second person.
     * @return True if a friendship exists between them.
     */
    bool areFriends(const string &PersonA, const string &PersonB) const;

private:
    /**
     * @brief Computes the shortest path between two people using Breadth-First Search (BFS).
     * @param begin Name of the starting person.
     * @param finish Name of the destination person.
     * @return A list of nodes representing the path, or empty if unreachable.
     * @note Implementation uses BFS which guarantees the shortest path in an unweighted graph.
     * Time complexity: O(V + E) where V is number of people and E is number of friendships.
     * Space complexity: O(V) for the queue and visited array.
     */
    vector<Node> shortestPath(const string &begin, const string &finish) const;

    /**
     * @brief Finds the shortest path while avoiding specific people.
     * @param begin Name of the starting person.
     * @param finish Name of the destination person.
     * @param blacklister List of names to avoid.
     * @return A list of nodes forming the valid path, or empty if blocked.
     */
    vector<Node> shortestPathAvoidingNodes(const string &begin, const string &finish, const vector<string> &blacklister) const;

    /**
     * @brief Counts the number of mutual friends between two people.
     * @param node1 First person.
     * @param node2 Second person.
     * @return Number of common neighbors.
     */
    int nbOfCommonFriends(const Node &node1, const Node &node2) const;

    /**
     * @brief Recommends top-K potential friends for a person based on mutual connections.
     * @param person Name of the person to recommend for.
     * @param k Number of recommendations.
     * @return List of recommended people (nodes).
     */
    vector<Node> topKPeople(const string &person, int k);

public:
    /**
     * @brief Displays the top-K friend recommendations for a given person.
     * @param person Name of the person.
     * @param k Number of suggestions.
     */
    void displayTopKPeople(const string &person, int k);

    /**
     * @brief Displays the shortest path between two people.
     * @param begin Starting person's name.
     * @param finish Destination person's name.
     */
    void displayShortestPath(const string &begin, const string &finish);

    /**
     * @brief Displays the shortest path avoiding certain people.
     * @param begin Starting person.
     * @param finish Destination person.
     * @param blacklister List of people to avoid.
     */
    void displayShortestPathAvoidingNodes(const string &begin, const string &finish, const vector<string> &blacklister);

    /**
     * @brief Displays the entire social network (people and their connections).
     */
    void displaySocialNetWork();

    /**
     * @brief Retrieves all friends (neighbors) of a given person.
     * @param node The person whose friends to retrieve.
     * @return List of neighboring nodes.
     */
    vector<Node> getNeighbors(const Node &node) const;
};

#endif // SOCIALNETWORK_H