#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* WHAT TO DO ----------------------------------------------------------------------------------------------------------------------------------------------
1. Add Loyalty Points to a particular customer
2. Subtract Loyalty Points from a particular customer
3. Delete a particular customer
4. Search for a particular customer in the binary search tree. If the customer is found, report both their number of loyalty points and their depth in the tree 
(distance from the root in # of links to follow)
5. Count the number of customers whose names come alphabetically before a particular customer)

At the end of the input, store pointers to each struct storing customer data and sort that data by loyalty points, from highest to lowest, breaking ties alphabetically.
(For two customers with the same number of loyalty points, the one whose name comes frist alphabetically should be listed first.) This should be sorted via Merge or Quick Sort.

IMPLEMENTATION REQUIREMENTS ---------------------------------------------------------------------------------------------------------------------------------
1. A binary search tree of nodes of type treenode will be used to store the data as commands are processed.
2. The run-time for processing each of the commands should be O(h), where h is the current height of the tree. 
3. There should be two compare functions, one to be used by the binary search tree functions and a different one to be used by the sorting functions.
4. Only one full copy of each customer struct should exist. The array to be sorted should be of type customer**, sorting an array of pointers to struct.
5. The sort implemented at the end of the program must be either merge sort or quick sort.
6. Free all memory.
*/

#define MAXLEN 19

// Customer Struct
typedef struct customer {
    char name[MAXLEN + 1];
    int points;
} customer;

// Binary Tree Struct
typedef struct treenode {
    customer* cPtr;
    int size;
    struct treenode* left;
    struct treenode* right;
} treenode;


// Traversing and Printing BST
void inorder(struct treenode* current_ptr) {

    // Only traverse the node if it's not null.
    if (current_ptr != NULL) {
        inorder(current_ptr->left); // Go Left.
        printf("%s ", current_ptr->cPtr->name); // Print the name
        printf("%d ", current_ptr->cPtr->points); // Print points
        printf("%d ", current_ptr->size);
        printf("\n");
        inorder(current_ptr->right); // Go Right.
    }
}

// Insert node into BST
struct treenode* insert(struct treenode* root,
    struct treenode* element) {

    // Inserting into an empty tree.
    if (root == NULL) {
  
        return element;
    }

    else {

        // increment size
        root->size++;

        // element should be inserted to the right.
        if (strcmp(element->cPtr->name, root->cPtr->name) > 0) {

            // There is a right subtree to insert the node.
            if (root->right != NULL) {
                root->right = insert(root->right, element);
            }

            // Place the node directly to the right of root.
            else {
                root->right = element;
            }
        }

        // element should be inserted to the left.
        else {

            // There is a left subtree to insert the node.
            if (root->left != NULL) {
                root->left = insert(root->left, element);
            }

            // Place the node directly to the left of root.
            else {
                root->left = element;
            }
        }

        // Return the root pointer of the updated tree.
        return root;
    }
}

// Create node
struct treenode* create_node(char* name, int points) {

    // Allocate space for the node and customer, set the fields.
    struct treenode* temp;
    struct customer* tempCustomer;

    temp = (struct treenode*)malloc(sizeof(struct treenode));
    
    tempCustomer = malloc(sizeof(struct customer));
    strcpy(tempCustomer->name, name);
    tempCustomer->points = points;
    
    temp->cPtr = tempCustomer;
    temp->size = 1;
    temp->left = NULL;
    temp->right = NULL;
   
    return temp; // Return a pointer to the created node.
}

// Finding a node in BST
int find(struct treenode* current_ptr, char* name) {

    // Check if there are nodes in the tree.
    if (current_ptr != NULL) {

        // Found the value at the root.
        if (strcmp(current_ptr->cPtr->name, name) == 0) {
            return 1;
        }

        // Search to the left. Name comes alphabetically before current_ptr name
        if (strcmp(current_ptr->cPtr->name, name) > 0) {
            return find(current_ptr->left, name);
        }

        // Or...search to the right.
        else {
            return find(current_ptr->right, name);
        }
    }

    // Not found
    else {
        return 0;
        
    }
}

// Returns the parent of the node pointed to by node in the tree rooted at
// root. If the node is the root of the tree, or the node doesn't exist in
// the tree, null will be returned.
struct treenode* parent(struct treenode* root, struct treenode* node) {

    // Take care of NULL cases.
    if (root == NULL || root == node) {
        return NULL;
    }

    // The root is the direct parent of node.
    if (root->left == node || root->right == node) {
        return root;
    }


    // Look for node's parent in the left side of the tree.
    if (strcmp(root->cPtr->name, node->cPtr->name) > 0) {
        return parent(root->left, node);
    }

    // Look for node's parent in the right side of the tree.
    else if (strcmp(root->cPtr->name, node->cPtr->name) < 0) {

        return parent(root->right, node);
    }

    return NULL; // Catch any other extraneous cases.
}

void sizeDecrement(struct treenode* root, struct treenode* node) {

    // Take care of NULL cases.
    if (root == NULL || root == node) {
        return;
    }

    root->size--;
    // The root is the direct parent of node.
    if (root->left == node || root->right == node) {
        return;
    }


    // Look for node's parent in the left side of the tree.
    if (strcmp(root->cPtr->name, node->cPtr->name) > 0) {
        sizeDecrement(root->left, node);
    }

    // Look for node's parent in the right side of the tree.
    else if (strcmp(root->cPtr->name, node->cPtr->name) < 0) {

        sizeDecrement(root->right, node);
    }

    return; // Catch any other extraneous cases.
}


// Returns a pointer to the node storing the minimum value in the tree
// with the root, root. Will not work if called with an empty tree.
struct treenode* minVal(struct treenode* root) {

    // Root stores the minimal value.
    if (root->left == NULL) {
        return root;
    }

    // The left subtree of the root stores the minimal value.
    else {
        return minVal(root->left);
    }
}


// Returns a pointer to the node storing the maximum value in the tree
// with the root, root. Will not work if called with an empty tree.
struct treenode* maxVal(struct treenode* root) {

    // Root stores the maximal value.
    if (root->right == NULL) {
        return root;
    }

    // The right subtree of the root stores the maximal value.
    else {
        return maxVal(root->right);
    }
}

// Returns 1 if node is a leaf node, 0 otherwise.
int isLeaf(struct treenode* node) {
    return (node->left == NULL && node->right == NULL);
}

// Returns 1 iff node has a left child and no right child.
int hasOnlyLeftChild(struct treenode* node) {
    return (node->left != NULL && node->right == NULL);
}

// Returns 1 if node has a right child and no left child.
int hasOnlyRightChild(struct treenode* node) {
    return (node->left == NULL && node->right != NULL);
}

// finds the depth of a node
int findDepth(struct treenode* current_ptr, char* name, int depth) {

    // Found the value at the root.
    if (strcmp(current_ptr->cPtr->name, name) == 0) {
        return depth;
    }

    // Search to the left.
    if (strcmp(current_ptr->cPtr->name, name) > 0) {
        depth++;
        findDepth(current_ptr->left, name, depth);
        
    }

    // Or...search to the right.
    else {
        depth++;
        findDepth(current_ptr->right, name, depth);
    }
}

struct treenode* findNode(struct treenode* current_ptr, char* name) {

    // Check if there are nodes in the tree.
    if (current_ptr != NULL) {
        // Found the value at the root.
        if (strcmp(current_ptr->cPtr->name, name) == 0) {
            return current_ptr;
        }

        // Search to the left.
        if (strcmp(current_ptr->cPtr->name, name) > 0) {
            return findNode(current_ptr->left, name);
        }

        // Or...search to the right.
        else {
            return findNode(current_ptr->right, name);
        }

    }
    else {
        return NULL; // No node found.
    }
}

int countSmaller(struct treenode* current_ptr, char* name) {
    if (current_ptr == NULL) {
        return 0;
    }

    // don't count names that are greater than
    if (strcmp(current_ptr->cPtr->name, name) >= 0) {
        return countSmaller(current_ptr->left, name);
    }

    // current_ptr is less than the name
    else {
        // its children are null so only return 1
        if (current_ptr->left == NULL && current_ptr->right == NULL) {
            return 1;
        }

        // left is null so only add right
        else if (current_ptr->left == NULL) {
            return 1 + countSmaller(current_ptr->right, name);
        }

        // right is null so only add left
        else if (current_ptr->right == NULL) {
            return 1 + current_ptr->left->size;
        }

        // add everything
        else {
            return 1 + current_ptr->left->size + countSmaller(current_ptr->right, name);
        }
        
    }
}


// Will delete the node storing value in the tree rooted at root. The
// value must be present in the tree in order for this function to work.
// The function returns a pointer to the root of the resulting tree.
struct treenode* delete(struct treenode* root, char* name) {

    struct treenode *delnode, *new_del_node, *save_node;
    delnode = findNode(root, name); // Get a pointer to the node to delete.
    struct treenode* par = parent(root, delnode); // Get the parent of this node.

    // Take care of the case where the node to delete is a leaf node.
    if (isLeaf(delnode)) {
        sizeDecrement(root, delnode);

        // Deleting the only node in the tree.
        if (par == NULL) {
            free(root->cPtr);
            free(root); // free the memory for the node.
            return NULL;
        }

        // Deletes the node if it's a left child.
        if (strcmp(par->cPtr->name, name) > 0) {
            free(par->left->cPtr);
            free(par->left); // Free the memory for the node.
            par->left = NULL;
        }

        // Deletes the node if it's a right child.
        else {
            free(par->right->cPtr);
            free(par->right); // Free the memory for the node.
            par->right = NULL;

         
        }

        return root; // Return the root of the new tree.
    }

    // Take care of the case where the node to be deleted only has a left 
    // child.
    if (hasOnlyLeftChild(delnode)) {
        sizeDecrement(root, delnode);
        // Deleting the root node of the tree.
        if (par == NULL) {
            save_node = delnode->left;
            free(delnode->cPtr);
            free(delnode); // Free the node to delete.
            return save_node; // Return the new root node of the resulting tree.
        }

        // Deletes the node if it's a left child.
        if (strcmp(par->cPtr->name, name) > 0) {
            save_node = par->left; // Save the node to delete.
            par->left = par->left->left; // Readjust the parent pointer.
            
            free(save_node->cPtr);
            free(save_node); // Free the memory for the deleted node.

            
        }

        // Deletes the node if it's a right child.
        else {
            save_node = par->right; // Save the node to delete.
            par->right = par->right->left; // Readjust the parent pointer.

            free(save_node->cPtr);
            free(save_node); // Free the memory for the deleted node.

            
        }

        return root; // Return the root of the tree after the deletion.
    }

    // Takes care of the case where the deleted node only has a right child.
    if (hasOnlyRightChild(delnode)) {
        sizeDecrement(root, delnode);
        // Node to delete is the root node.
        if (par == NULL) {
            save_node = delnode->right;
            free(delnode->cPtr);
            free(delnode);
            return save_node;
        }

        // Delete's the node if it is a left child.
        if (strcmp(par->cPtr->name, name) > 0) {
            save_node = par->left;
            par->left = par->left->right;

            free(save_node->cPtr);
            free(save_node);

            
        }

        // Delete's the node if it is a right child.
        else {
            save_node = par->right;
            par->right = par->right->right;

            free(save_node->cPtr);
            free(save_node);

           
        }
        return root;
    }

    // Find the new physical node to delete.
    new_del_node = maxVal(delnode->left);

    char save_name[MAXLEN];
    strcpy(save_name, new_del_node->cPtr->name);
    int save_points = new_del_node->cPtr->points;

    delete(root, save_name);  // Now, delete the proper value.

    // Restore the data to the original node to be deleted.
    strcpy(delnode->cPtr->name, save_name);
    delnode->cPtr->points = save_points;

    return root;
}

// swap function
void swap(struct customer* xp, struct customer* yp)
{
    struct customer temp = *xp;
    *xp = *yp;
    *yp = temp;
}

// function that adds customers from bst to struct customer array
void addCustomersToCustomerArray(struct treenode* current_ptr, struct customer** c, int *k) {
    
    if (current_ptr != NULL) {
        addCustomersToCustomerArray(current_ptr->left, c, k); // Go Left.

        // copy data
        strcpy(c[*k]->name, current_ptr->cPtr->name);
        c[*k]->points = current_ptr->cPtr->points;

        // increment k
        ++*k;

        addCustomersToCustomerArray(current_ptr->right, c, k); // Go Right.
    }
}


int partition(struct customer** c, int low, int high) {
    
    // Pick a random partition element and swap it into index low.
    int i = low + rand() % (high - low + 1);
 
    swap(c[low], c[i]);
    int lowpos = low; //here is our pivot located.
    low++; //our starting point is after the pivot.
    
    // Run the partition so long as the low and high counters don't cross.
    while (low <= high)
    {
        // Move the low pointer until we find a value too large for this side.
        while (low <= high && c[low]->points >= c[lowpos]->points) {
            
            // when points are equal, switch positions only if c[low] name is greater than c[lowpos] name
            if (c[low]->points == c[lowpos]->points) {
                if (strcmp(c[lowpos]->name, c[low]->name) < 0) {
                    break;
                }
            }
            low++;
        }
        // Move the high pointer until we find a value too small for this side.
        while (high >= low && c[high]->points <= c[lowpos]->points) {
            
            // when points are equal, switch positions only if c[high] name is less than c[lowpos] name
            if (c[high]->points == c[lowpos]->points) {
                if (strcmp(c[lowpos]->name, c[high]->name) > 0) {
                    break;
                }
            }
            high--;
        }

        // Now that we've identified two values on the wrong side, swap them.
        if (low < high) {
            swap(c[low], c[high]);
        }
    }
   
    // Swap the pivot element element into its correct location.
    swap(c[lowpos], c[high]);
   
    return high; //return the partition point
}

// Pre-condition: s and f are value indexes into numbers.
// Post-condition: The values in numbers will be sorted in between indexes s
// and f.
void quickSort(struct customer** c, int low, int high) {
    // Only have to sort if we are sorting more than one number
    if (low < high) {
        int split = partition(c, low, high);
        quickSort(c, low, split - 1);
        quickSort(c, split + 1, high);
    }
}

// free BST
void freeBST(struct treenode* node) {
    if (node == NULL) {
        return;
    }

    freeBST(node->left);
    freeBST(node->right);

    free(node->cPtr);
    free(node);
}

// compare function
int cmpfunc(const void* a, const void* b) {
    struct customer* custA = *(struct customer**)a;
    struct customer* custB = *(struct customer**)b;

    
    if (custA->points == custB->points) {
        return(strcmp(custA->name, custB->name));
    }
    
    return custB->points - custA->points;
}

// Main function
int main() {

    struct treenode* my_root = NULL, *temp_node;
    
    // Collect Input
    int numCommands;
    scanf("%d", &numCommands);

    // Input variables
    char customerName[MAXLEN + 1];
    int numPoints;
    
    for (int i = 0; i < numCommands; i++) {
       
        // read the command
        char command[MAXLEN + 1];
        scanf("%s", command);

        // command is add (command 1)
        if (strcmp("add", command) == 0) {
            scanf("%s %d", customerName, &numPoints);

            // customer already exists
            if (find(my_root, customerName)) {

                // add points
                temp_node = findNode(my_root, customerName);
                temp_node->cPtr->points += numPoints;

                // Output
                printf("%s %d\n", temp_node->cPtr->name, temp_node->cPtr->points);
            }

            // customer doesn't exist
            else {

                // create node
                temp_node = create_node(customerName, numPoints);

                // add to BST
                my_root = insert(my_root, temp_node);

                // Output
                printf("%s %d\n", customerName, numPoints);

            }
        }

        // command is sub (command 2)
        else if (strcmp("sub", command) == 0) {
            scanf("%s %d", customerName, &numPoints);
           
            // found
            if (find(my_root, customerName)) {

                // find the node
                temp_node = findNode(my_root, customerName);

                // delete points
                if (numPoints > temp_node->cPtr->points) {
                    temp_node->cPtr->points = 0;
                }

                else {
                    temp_node->cPtr->points -= numPoints;
                }

                // Output
                printf("%s %d\n", temp_node->cPtr->name, temp_node->cPtr->points);
            }

            // not found
            else {
                // Output
                printf("%s not found\n", customerName);
            }

            
        }

        // command is del (command 3)
        else if (strcmp("del", command) == 0) {
            scanf("%s", customerName);

            // delete if found
            if (find(my_root, customerName)) {
                my_root = delete(my_root, customerName);
                printf("%s deleted\n", customerName);
            }
            
            // not found 
            else {
                printf("%s not found\n", customerName);
            }
        }

        // command is search (command 4)
        else if (strcmp("search", command) == 0) {
            scanf("%s", customerName);

            // found
            if (find(my_root, customerName)) {

                // find the node
                temp_node = findNode(my_root, customerName);
                int depth = findDepth(my_root, customerName, 0);

                // Output
                printf("%s %d %d\n", temp_node->cPtr->name, temp_node->cPtr->points, depth);
            }

            // not found
            else {
                // Output
                printf("%s not found\n", customerName);
            }
        }

        // command is count_smaller (command 5)
        else {
            scanf("%s", customerName);

            int count = countSmaller(my_root, customerName);
            
            printf("%d\n", count);
            
        }
    }

    // Create customers struct array
    struct customer** allCustomers = malloc(sizeof(struct customer*) * my_root->size);
    for (int i = 0; i < my_root->size; i++) {
        allCustomers[i] = malloc(sizeof(struct customer));

    }

    int k = 0;
    addCustomersToCustomerArray(my_root, allCustomers, &k);

    // sort customers
    quickSort(allCustomers, 0, my_root->size - 1);

   
    //qsort(&allCustomers[0], my_root->size, sizeof(allCustomers[0]), cmpfunc);
   
    // print array
    for (int i = 0; i < my_root->size; i++) {
        printf("%s ", allCustomers[i]->name);
        printf("%d", allCustomers[i]->points);
        printf("\n");
    }
    
    // free memory
    
    // free customer struct array
    for (int i = 0; i < my_root->size; i++) {
        free(allCustomers[i]);
    }
    free(allCustomers);
    
    // free bst
    freeBST(my_root);

    return 0;
}
