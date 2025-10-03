/**
 * @file main.cpp
 * @brief Main program file for the Social Network application
 *
 * This file implements a console-based interface for interacting with the social network.
 * It provides a menu-driven system allowing users to:
 * - Add and remove people from the network
 * - Manage friendships between people
 * - Find paths between people
 * - Get friend recommendations
 * - View the entire network structure
 */

#include "SocialNetwork.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/**
 * @brief Displays the main menu options for the social network application
 *
 * Prints a formatted list of all available operations that can be performed
 * on the social network, including:
 * - Adding/removing people
 * - Managing friendships
 * - Finding paths
 * - Getting recommendations
 * - Viewing the network
 */
void displayMenu()
{
    cout << "\n===== Social Network Menu =====" << endl;
    cout << "1. Add Person" << endl;
    cout << "2. Add Friend Connection" << endl;
    cout << "3. Remove Friend Connection" << endl;
    cout << "4. Delete Person" << endl;
    cout << "5. Check if Two People are Friends" << endl;
    cout << "6. Display Shortest Path Between Two People" << endl;
    cout << "7. Display Shortest Path Avoiding Specific People" << endl;
    cout << "8. Display Top K Friend Recommendations" << endl;
    cout << "9. Display Entire Social Network" << endl;
    cout << "0. Exit" << endl;
    cout << "===============================" << endl;
    cout << "Enter your choice: ";
}

/**
 * @brief Main entry point of the Social Network application
 *
 * Implements an interactive console interface that allows users to manage
 * a social network. It creates an instance of the SocialNetwork class and
 * provides a menu-driven interface for all supported operations.
 *
 * @return int Returns 0 on successful execution
 */
int main()
{
    SocialNetwork socialNetwork;
    int choice;
    string personA, personB;

    cout << "Welcome to Social Network Manager!" << endl;

    do
    {
        displayMenu();
        cin >> choice;
        cin.ignore(); // Clear the newline character

        switch (choice)
        {
        case 1: // Add Person
            cout << "Enter person's name: ";
            getline(cin, personA);
            socialNetwork.addPerson(personA);
            cout << personA << " has been added to the network." << endl;
            break;

        case 2: // Add Friend Connection
            cout << "Enter first person's name: ";
            getline(cin, personA);
            cout << "Enter second person's name: ";
            getline(cin, personB);

            if (personA == personB)
            {
                cout << "Error: Cannot add friendship with self." << endl;
                break;
            }

            socialNetwork.addFriend(personA, personB);
            cout << personA << " and " << personB << " are now friends." << endl;
            break;

        case 3: // Remove Friend Connection
            cout << "Enter first person's name: ";
            getline(cin, personA);
            cout << "Enter second person's name: ";
            getline(cin, personB);

            socialNetwork.unfriend(personA, personB);
            cout << personA << " and " << personB << " are no longer friends." << endl;
            break;

        case 4: // Delete Person
            cout << "Enter person's name to delete: ";
            getline(cin, personA);

            if (socialNetwork.deletePerson(personA))
            {
                cout << personA << " has been deleted from the network." << endl;
            }
            else
            {
                cout << "Person not found in the network." << endl;
            }
            break;

        case 5: // Check if Two People are Friends
            cout << "Enter first person's name: ";
            getline(cin, personA);
            cout << "Enter second person's name: ";
            getline(cin, personB);

            if (socialNetwork.areFriends(personA, personB))
            {
                cout << personA << " and " << personB << " are friends." << endl;
            }
            else
            {
                cout << personA << " and " << personB << " are not friends." << endl;
            }
            break;

        case 6: // Display Shortest Path Between Two People
            cout << "Enter starting person's name: ";
            getline(cin, personA);
            cout << "Enter ending person's name: ";
            getline(cin, personB);

            cout << "Shortest path: ";
            socialNetwork.displayShortestPath(personA, personB);
            cout << endl;
            break;

        case 7: // Display Shortest Path Avoiding Specific People
        {
            cout << "Enter starting person's name: ";
            getline(cin, personA);
            cout << "Enter ending person's name: ";
            getline(cin, personB);

            cout << "Enter number of people to avoid: ";
            int numToAvoid;
            cin >> numToAvoid;
            cin.ignore();

            vector<string> blacklist;
            string person;
            for (int i = 0; i < numToAvoid; i++)
            {
                cout << "Enter name " << (i + 1) << " to avoid: ";
                getline(cin, person);
                blacklist.push_back(person);
            }

            cout << "Shortest path avoiding specified people: ";
            socialNetwork.displayShortestPathAvoidingNodes(personA, personB, blacklist);
            cout << endl;
        }
        break;

        case 8: // Display Top K Friend Recommendations
            cout << "Enter person's name: ";
            getline(cin, personA);
            cout << "Enter number of recommendations (K): ";
            int k;
            cin >> k;
            cin.ignore();

            cout << "Top " << k << " recommendations for " << personA << ": ";
            socialNetwork.displayTopKPeople(personA, k);
            cout << endl;
            break;

        case 9: // Display Entire Social Network
            cout << "\n----- Social Network Graph -----" << endl;
            socialNetwork.displaySocialNetWork();
            cout << "-------------------------------" << endl;
            break;

        case 0: // Exit
            cout << "Exiting Social Network Manager. Goodbye!" << endl;
            break;

        default:
            cout << "Invalid choice. Please try again." << endl;
        }

    } while (choice != 0);

    return 0;
}