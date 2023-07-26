#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>

typedef struct node
{
    char *word;
    struct node *left;
    struct node *right;
} node;

struct node *newnode(char *word)
{
    struct node *node = (struct node *)malloc(sizeof(struct node));
    node->word = (char *)malloc(strlen(word) + 1);
    strcpy(node->word, word);
    node->left = NULL;
    node->right = NULL;

    return (node);
}

node *insert(struct node *root, char *word)
{
    struct node *temp = NULL;

    if (root == NULL)
    {
        root = newnode(word);
    }

    else if (strcasecmp(word, root->word) < 0)
    {
        root->left = insert(root->left, word);
    }
    else if (strcasecmp(word, root->word) > 0)
    {
        root->right = insert(root->right, word);
    }
    return root;
}

node *find(char *target, node *root)
{
    int x = strcasecmp(target, root->word);
    if (x == 0)
        return root;
    if (x < 0)
    {
        if (root->left == NULL)
            return root;
        else
            return find(target, root->left);
    }
    if (x > 0)
    {
        if (root->right == NULL)
            return root;
        else
            return find(target, root->right);
    }
}

void searchInDictionary(char *target, node *root)
{
    node *found = find(target, root);
    if (strcasecmp(target, found->word) == 0)
    {
        printf("%s - CORRECT\n", target);
        return;
    }
    node *predecessor;
    node *successor;
    node *temp;
    int x;
    // to get predecessor
    if (found->left != NULL)
    {
        temp = found->left;
        while (temp->right != NULL)
        {
            temp = temp->right;
        }
        predecessor = temp;
    }
    else
    {
        temp = root;
        while (temp != found)
        {
            x = strcasecmp(found->word, temp->word);
            if (x < 0)
            {
                temp = temp->left;
            }
            if (x > 0)
            {
                predecessor = temp;
                temp = temp->right;
            }
        }
    }
    // to get successor
    if (found->right != NULL)
    {
        temp = found->right;
        while (temp->left != NULL)
        {
            temp = temp->left;
        }
        successor = temp;
    }
    else
    {
        temp = root;
        while (temp != found)
        {
            x = strcasecmp(found->word, temp->word);
            if (x < 0)
            {
                successor = temp;
                temp = temp->left;
            }
            if (x > 0)
            {
                temp = temp->right;
            }
        }
    }
    printf("%s - Incorrect, Suggestions: %s %s %s\n", target, found->word, predecessor->word, successor->word);
}
int height(struct node *n)
{
if(n == NULL)
return 0;
else
{
int lefth;
int righth;
lefth = height(n -> left);
righth = height(n -> right);
if(lefth > righth)
{
return lefth + 1;

}
else
return righth + 1;
}
}

int main()
{

    FILE *fp;
    char word[100];
    int c = 0;
    struct node *root = NULL;

    fp = fopen("EN-US-Dictionary.txt", "r");

    while (fscanf(fp, "%s", word) != EOF)
    {
        c++;
        root = insert(root, word);
    }

    fclose(fp);
    printf("Dictionary Loaded Successfully...!\n");
    printf("..................................\n");
    printf("Size = %d\n",c);
    printf("..................................\n");
    printf("Height = %d\n",height(root));
    printf("..................................\n");
    printf("Enter a sentence\n");
    gets(word);
    char *token = strtok(word, " ");
    while (token != NULL)
    {
        searchInDictionary(token, root);
        token = strtok(NULL, " ");
    }
}
