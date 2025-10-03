#include "SocialNetwork.h"
#include <algorithm>
#include <queue>

// ==============================
// Node Implementation
// ==============================

SocialNetwork::Node::Node(string name)
{
    this->name = name;
}

SocialNetwork::Node::Node()
{
    this->name = "";
}

string SocialNetwork::Node::getName() const
{
    return name;
}

void SocialNetwork::Node::setName(string name)
{
    this->name = name;
}

bool SocialNetwork::Node::operator==(const Node &node) const
{
    return this->name == node.name;
}

// ==============================
// Edge Implementation
// ==============================

SocialNetwork::Edge::Edge(Node node1, Node node2)
{
    this->node1 = node1;
    this->node2 = node2;
}

const SocialNetwork::Node &SocialNetwork::Edge::getNode1() const
{
    return node1;
}

const SocialNetwork::Node &SocialNetwork::Edge::getNode2() const
{
    return node2;
}

// ==============================
// SocialNetwork Implementation
// ==============================

SocialNetwork::SocialNetwork() {}

SocialNetwork::SocialNetwork(vector<Edge> &edge_list, vector<Node> &nodes_list)
{
    this->edgeList = edge_list;
    this->nodesList = nodes_list;
}

int SocialNetwork::isnodefound(const Node &node) const
{
    for (size_t i = 0; i < nodesList.size(); i++)
    {
        if (nodesList[i] == node)
        {
            return i;
        }
    }
    return -1;
}

void SocialNetwork::addPerson(const string &person)
{
    Node node(person);
    if (isnodefound(node) == -1)
    {
        nodesList.push_back(node);
    }
}

void SocialNetwork::addFriend(const string &personA, const string &personB)
{
    Node node1(personA);
    Node node2(personB);
    if (isnodefound(node1) == -1 || isnodefound(node2) == -1)
        return;
    if (areFriends(node1.getName(), node2.getName()))
        return;
    edgeList.push_back(Edge(node1, node2));
}

void SocialNetwork::unfriend(const string &personA, const string &personB)
{
    Node node1(personA);
    Node node2(personB);
    for (size_t i = 0; i < edgeList.size(); i++)
    {
        if ((edgeList[i].getNode1() == node1 && edgeList[i].getNode2() == node2) ||
            (edgeList[i].getNode1() == node2 && edgeList[i].getNode2() == node1))
        {
            edgeList.erase(edgeList.begin() + i);
            return; // FIX: Exit after finding and removing the edge
        }
    }
}

bool SocialNetwork::deletePerson(const string &person)
{
    Node node(person);

    // FIX: Iterate backwards to avoid index shifting issues
    for (int i = edgeList.size() - 1; i >= 0; i--)
    {
        if (edgeList[i].getNode1() == node || edgeList[i].getNode2() == node)
        {
            edgeList.erase(edgeList.begin() + i);
        }
    }

    if (isnodefound(node) != -1)
    {
        nodesList.erase(nodesList.begin() + isnodefound(node));
        return true;
    }
    return false;
}

bool SocialNetwork::areFriends(const string &personA, const string &personB) const
{
    Node node1(personA);
    Node node2(personB);
    for (size_t i = 0; i < edgeList.size(); i++)
    {
        if ((edgeList[i].getNode1() == node1 && edgeList[i].getNode2() == node2) ||
            (edgeList[i].getNode1() == node2 && edgeList[i].getNode2() == node1))
        {
            return true;
        }
    }
    return false;
}

vector<SocialNetwork::Node> SocialNetwork::getNeighbors(const Node &node1) const
{
    vector<SocialNetwork::Node> allfriends;
    for (size_t i = 0; i < edgeList.size(); i++)
    {
        if (edgeList[i].getNode1() == node1 || edgeList[i].getNode2() == node1)
        {
            if (edgeList[i].getNode1() == node1)
                allfriends.push_back(edgeList[i].getNode2());
            else
                allfriends.push_back(edgeList[i].getNode1());
        }
    }
    return allfriends;
}

vector<SocialNetwork::Node> SocialNetwork::shortestPath(const string &begin, const string &finish) const
{
    Node start(begin);
    Node end(finish);
    if (isnodefound(start) == -1 || isnodefound(end) == -1)
    {
        return vector<Node>();
    }

    if (start == end)
    {
        return vector<Node>{start};
    }

    vector<bool> visited(nodesList.size(), false);
    vector<int> parent(nodesList.size(), -1);
    queue<int> q;

    int startIdx = isnodefound(start);
    visited[startIdx] = true;
    q.push(startIdx);

    while (!q.empty())
    {
        int current = q.front();
        q.pop();

        if (nodesList[current] == end)
        {
            break;
        }

        vector<Node> neighbors = getNeighbors(nodesList[current]);
        for (size_t i = 0; i < neighbors.size(); ++i)
        {
            const Node &neighbor = neighbors[i];
            int neighborIdx = isnodefound(neighbor);
            if (!visited[neighborIdx])
            {
                visited[neighborIdx] = true;
                parent[neighborIdx] = current;
                q.push(neighborIdx);
            }
        }
    }

    vector<Node> path;
    int endIdx = isnodefound(end);
    if (parent[endIdx] == -1)
        return path;

    for (int at = endIdx; at != -1; at = parent[at])
    {
        path.push_back(nodesList[at]);
    }

    reverse(path.begin(), path.end());
    return path;
}

vector<SocialNetwork::Node> SocialNetwork::shortestPathAvoidingNodes(const string &begin, const string &finish, const vector<string> &blacklister) const
{
    Node start(begin);
    Node end(finish);
    vector<Node> blacklist(blacklister.size());
    for (size_t i = 0; i < blacklister.size(); i++)
    {
        blacklist[i].setName(blacklister[i]);
    }

    if (isnodefound(start) == -1 || isnodefound(end) == -1)
    {
        return vector<Node>();
    }

    for (size_t i = 0; i < blacklist.size(); ++i)
    {
        const Node &node = blacklist[i];
        if (node == start || node == end)
        {
            return vector<Node>();
        }
    }

    if (start == end)
    {
        return vector<Node>{start};
    }

    vector<bool> visited(nodesList.size(), false);
    vector<int> parent(nodesList.size(), -1);

    for (size_t i = 0; i < blacklist.size(); ++i)
    {
        const Node &node = blacklist[i];
        int nodeIdx = isnodefound(node);
        if (nodeIdx != -1)
        {
            visited[nodeIdx] = true;
        }
    }

    queue<int> q;
    int startIdx = isnodefound(start);
    visited[startIdx] = false;
    q.push(startIdx);
    visited[startIdx] = true;

    while (!q.empty())
    {
        int current = q.front();
        q.pop();

        if (nodesList[current] == end)
        {
            break;
        }

        vector<Node> neighbors = getNeighbors(nodesList[current]);
        for (size_t i = 0; i < neighbors.size(); ++i)
        {
            const Node &neighbor = neighbors[i];
            int neighborIdx = isnodefound(neighbor);
            if (!visited[neighborIdx])
            {
                visited[neighborIdx] = true;
                parent[neighborIdx] = current;
                q.push(neighborIdx);
            }
        }
    }

    vector<Node> path;
    int endIdx = isnodefound(end);
    if (parent[endIdx] == -1)
        return path;

    for (int at = endIdx; at != -1; at = parent[at])
    {
        path.push_back(nodesList[at]);
    }

    reverse(path.begin(), path.end());
    return path;
}

int SocialNetwork::nbOfCommonFriends(const Node &node1, const Node &node2) const
{
    if (isnodefound(node1) == -1 || isnodefound(node2) == -1)
    {
        return 0;
    }

    vector<Node> friends1 = getNeighbors(node1);
    vector<Node> friends2 = getNeighbors(node2);

    int count = 0;
    for (size_t i = 0; i < friends1.size(); ++i)
    {
        const Node &friend1 = friends1[i];
        for (size_t j = 0; j < friends2.size(); ++j)
        {
            const Node &friend2 = friends2[j];
            if (friend1 == friend2)
            {
                count++;
                break;
            }
        }
    }

    return count;
}

vector<SocialNetwork::Node> SocialNetwork::topKPeople(const string &person, int k)
{
    Node targetNode(person);
    vector<Node> recommendations;

    if (isnodefound(targetNode) == -1 || k <= 0)
    {
        return recommendations;
    }

    vector<pair<Node, int>> potentialFriends;

    for (size_t i = 0; i < nodesList.size(); i++)
    {
        const Node &currentNode = nodesList[i];

        if (currentNode == targetNode)
        {
            continue;
        }

        if (areFriends(targetNode.getName(), currentNode.getName()))
        {
            continue;
        }

        int commonFriends = nbOfCommonFriends(targetNode, currentNode);

        if (commonFriends > 0)
        {
            potentialFriends.push_back(make_pair(currentNode, commonFriends));
        }
    }

    sort(potentialFriends.begin(), potentialFriends.end(),
         [](const pair<Node, int> &a, const pair<Node, int> &b)
         {
             return a.second > b.second;
         });

    for (int i = 0; i < min(k, (int)potentialFriends.size()); i++)
    {
        recommendations.push_back(potentialFriends[i].first);
    }

    return recommendations;
}

void SocialNetwork::displayTopKPeople(const string &person, int k)
{
    vector<Node> n = topKPeople(person, k);
    for (size_t i = 0; i < n.size(); i++)
    {
        cout << n[i].getName() << " ";
    }
}

void SocialNetwork::displayShortestPath(const string &begin, const string &finish)
{
    vector<Node> n = shortestPath(begin, finish);
    for (size_t i = 0; i < n.size(); i++)
    {
        cout << n[i].getName() << " ";
    }
}

void SocialNetwork::displayShortestPathAvoidingNodes(const string &begin, const string &finish, const vector<string> &blacklister)
{
    vector<Node> n = shortestPathAvoidingNodes(begin, finish, blacklister);
    for (size_t i = 0; i < n.size(); i++)
    {
        cout << n[i].getName() << " ";
    }
}

void SocialNetwork::displaySocialNetWork()
{
    for (size_t i = 0; i < nodesList.size(); i++)
    {
        cout << nodesList[i].getName() << ":";
        for (const Edge &edge : edgeList)
        {
            if (edge.getNode1() == nodesList[i] || edge.getNode2() == nodesList[i])
            {
                if (edge.getNode1() == nodesList[i])
                    cout << edge.getNode2().getName() << " ";
                else
                    cout << edge.getNode1().getName() << " ";
            }
        }
        cout << endl;
    }
}