#include <stdio.h>
#include <stdlib.h>

// Define the node structure
typedef struct node
{
    unsigned char data;
    struct node *above;
    struct node *below;
    struct node *left;
    struct node *right;
    struct node *next;
    struct node *prev;
} Node;

// Define the 3D buffer structure
typedef struct buffer
{
    int x_size;
    int y_size;
    int z_size;
    Node ***data;
} Buffer;

// Function to initialize a new node
Node *createNode(unsigned char data)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->above = NULL;
    newNode->below = NULL;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

// Function to initialize a new 3D buffer
Buffer *createBuffer(int x_size, int y_size, int z_size)
{
    // Allocate memory for the buffer struct
    Buffer *newBuffer = (Buffer *)malloc(sizeof(Buffer));
    newBuffer->x_size = x_size;
    newBuffer->y_size = y_size;
    newBuffer->z_size = z_size;

    // Allocate memory for the data array
    newBuffer->data = (Node ***)malloc(x_size * sizeof(Node **));
    for (int i = 0; i < x_size; i++)
    {
        newBuffer->data[i] = (Node **)malloc(y_size * sizeof(Node *));
        for (int j = 0; j < y_size; j++)
        {
            newBuffer->data[i][j] = (Node *)malloc(z_size * sizeof(Node));
            for (int k = 0; k < z_size; k++)
            {
                newBuffer->data[i][j][k] = *createNode(0);
            }
        }
    }

    // Link the nodes in each direction
    for (int i = 0; i < x_size; i++)
    {
        for (int j = 0; j < y_size; j++)
        {
            for (int k = 0; k < z_size; k++)
            {
                if (k > 0)
                {
                    newBuffer->data[i][j][k].above = &newBuffer->data[i][j][k - 1];
                    newBuffer->data[i][j][k - 1].below = &newBuffer->data[i][j][k];
                }
                if (j > 0)
                {
                    newBuffer->data[i][j][k].left = &newBuffer->data[i][j - 1][k];
                    newBuffer->data[i][j - 1][k].right = &newBuffer->data[i][j][k];
                }
                if (i > 0)
                {
                    newBuffer->data[i][j][k].prev = &newBuffer->data[i - 1][j][k];
                    newBuffer->data[i - 1][j][k].next = &newBuffer->data[i][j][k];
                }
            }
        }
    }

    return newBuffer;
}

int main()
{
    // Create a new 3D buffer with size 3x3x3
    Buffer *myBuffer = createBuffer(7, 7, 7);

    // Accessing a node in the buffer and changing its value

    myBuffer->data[0][1][1].data = 6;
    myBuffer->data[1][1][1].data = 7;
    myBuffer->data[2][1][1].data = 8;

    myBuffer->data[1][1][1].right->data = 2;
    myBuffer->data[1][1][1].left->data = 3;

    myBuffer->data[0][1][1].next->below->data = 1;
    myBuffer->data[2][1][1].prev->above->data = 9;

    // Print the value of the node we just changed
    printf("The value of the node at (1, 1, 1) is %d\n", myBuffer->data[1][1][1].data);
    printf("The value of the node at above is %d\n", myBuffer->data[1][1][1].above->data);
    printf("The value of the node at below is %d\n", myBuffer->data[1][1][1].below->data);
    printf("The value of the node at left is %d\n", myBuffer->data[1][1][1].left->data);
    printf("The value of the node at right is %d\n", myBuffer->data[1][1][1].right->data);
    printf("The value of the node at next is %d\n", myBuffer->data[1][1][1].next->data);
    printf("The value of the node at prev is %d\n", myBuffer->data[1][1][1].prev->data);

    // Free the memory allocated for the buffer and its nodes
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            free(myBuffer->data[i][j]);
        }
        free(myBuffer->data[i]);
    }
    free(myBuffer->data);
    free(myBuffer);

    return 0;
}
