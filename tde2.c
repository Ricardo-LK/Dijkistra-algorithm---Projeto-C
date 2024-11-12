#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct Node Node;
typedef struct Street Street;

struct Node
{
    char name;
    Street *adjacentStreets[4];
    Node *prev;
    char firstCrossroad[50];
    char secondCrossroad[50];
    float x, y;
    float weight;
    int visited;
};

struct Street
{
    char name[50];
    Node *dest;
    float weight;
};

void initializeNodes(Node nodes[], int numNodes, Node *start)
{
    for (int i = 0; i < numNodes; i++)
    {
        nodes[i].weight = INFINITY;
        nodes[i].prev = NULL;
        nodes[i].visited = 0;
    }

    start->weight = 0.0;
}

Node *getMinWeight(Node nodes[], int numNodes)
{
    Node *minNode = NULL;
    float minWeight = INFINITY;

    for (int i = 0; i < numNodes; i++)
    {
        if (!nodes[i].visited && nodes[i].weight < minWeight)
        {
            minWeight = nodes[i].weight;
            minNode = &nodes[i];
        }
    }

    return minNode;
}

float calculateDistance(Node *origin, Node *dest)
{
    return sqrt(pow((origin->x - dest->x), 2) + pow((origin->y - dest->y), 2));
}

void dijkstra(Node nodes[], int numNodes, Node *start, Node *dest)
{
    Node *currentNode = getMinWeight(nodes, numNodes);

    while (currentNode != NULL && currentNode != dest)
    {
        currentNode->visited = 1;

        for (int i = 0; i < 4; i++)
        {
            Street *street = currentNode->adjacentStreets[i];
            if (street == NULL)
                continue;

            Node *neighbor = street->dest;

            if (!neighbor->visited)
            {
                float newWeight = currentNode->weight + street->weight;

                if (newWeight < neighbor->weight)
                {
                    neighbor->weight = newWeight;
                    neighbor->prev = currentNode;
                }
            }
        }

        currentNode = getMinWeight(nodes, numNodes);
    }
}

void printGraph(Node *node)
{
    if (node->prev == NULL)
    {
        printf("Primeiro Node %c", node->name);
    }
    else
    {
        printGraph(node->prev);
        printf(" -> Movendo para %c", node->name);
    }
}

int main()
{
    // PLACEHOLDER

    Node nodes[100];
    int numNodes = 5;

    nodes[0].name = 'A';
    nodes[1].name = 'B';
    nodes[2].name = 'C';
    nodes[3].name = 'D';
    nodes[4].name = 'E';

    Street street1 = {"Rua Alecrim", &nodes[1], 10.0};  // A -> B
    Street street2 = {"Rua Lavanda", &nodes[2], 15.0};  // B -> C
    Street street3 = {"Rua Bromelia", &nodes[3], 10.0}; // C -> D
    Street street4 = {"Rua Hortensia", &nodes[4], 5.0}; // D -> E

    nodes[0].adjacentStreets[0] = &street1; // A connects to B
    nodes[1].adjacentStreets[0] = &street2; // B connects to C
    nodes[2].adjacentStreets[0] = &street3; // C connects to D
    nodes[3].adjacentStreets[0] = &street4; // D connects to E

    // PLACEHOLDER

    initializeNodes(nodes, numNodes, &nodes[0]);
    dijkstra(nodes, numNodes, &nodes[0], &nodes[4]);
    printGraph(&nodes[3]);

    return 0;
}