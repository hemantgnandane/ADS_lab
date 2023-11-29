#include<stdio.h>
#include<stdlib.h>

#define MAX_STACK_SIZE 100

struct node {
    int data;
    struct node* left;
    struct node* right;
};

struct stack {
    struct node* data[MAX_STACK_SIZE];
    int top;
};

void initializeStack(struct stack* s) {
    s->top = -1;
}

void push(struct stack* s, struct node* n) {
    if (s->top < MAX_STACK_SIZE - 1) {
        s->data[++(s->top)] = n;
    } else {
        printf("Stack Overflow\n");
        exit(EXIT_FAILURE);
    }
}

struct node* pop(struct stack* s) {
    if (s->top >= 0) {
        return s->data[(s->top)--];
    } else {
        printf("Stack Underflow\n");
        exit(EXIT_FAILURE);
    }
}

int isEmpty(struct stack* s) {
    return (s->top == -1);
}

void createBinaryTree(struct node** root) {
    *root = (struct node*)malloc(sizeof(struct node));
    (*root)->data = 1;
    (*root)->left = (struct node*)malloc(sizeof(struct node));
    (*root)->left->data = 2;
    (*root)->right = (struct node*)malloc(sizeof(struct node));
    (*root)->right->data = 3;
    (*root)->left->left = (*root)->left->right = (*root)->right->left = (*root)->right->right = NULL;
}

void preorderTraversal(struct node* root) {
    struct stack s;
    initializeStack(&s);
    struct node* current = root;

    while (current != NULL || !isEmpty(&s)) {
        if (current != NULL) {
            printf("%d ", current->data);
            if (current->right != NULL) {
                push(&s, current->right);
            }
            current = current->left;
        } else {
            current = pop(&s);
        }
    }
}

void inorderTraversal(struct node* root) {
    struct stack s;
    initializeStack(&s);
    struct node* current = root;

    while (current != NULL || !isEmpty(&s)) {
        if (current != NULL) {
            push(&s, current);
            current = current->left;
        } else {
            current = pop(&s);
            printf("%d ", current->data);
            current = current->right;
        }
    }
}

void postorderTraversal(struct node* root) {
    struct stack s1, s2;
    initializeStack(&s1);
    initializeStack(&s2);

    push(&s1, root);

    while (!isEmpty(&s1)) {
        struct node* current = pop(&s1);
        push(&s2, current);

        if (current->left != NULL) {
            push(&s1, current->left);
        }
        if (current->right != NULL) {
            push(&s1, current->right);
        }
    }

    while (!isEmpty(&s2)) {
        printf("%d ", pop(&s2)->data);
    }
}

int countNodes(struct node* root) {
    struct stack s;
    initializeStack(&s);
    int count = 0;

    while (root != NULL || !isEmpty(&s)) {
        if (root != NULL) {
            count++;
            if (root->right != NULL) {
                push(&s, root->right);
            }
            root = root->left;
        } else {
            root = pop(&s);
        }
    }

    return count;
}

int findHeight(struct node* root) {
    struct stack s;
    initializeStack(&s);
    int height = 0;

    while (root != NULL || !isEmpty(&s)) 
    {
        if (root != NULL) 
        {
            if (root->right != NULL) 
            {
                push(&s, root->right);
            }
            push(&s, root);
            root = root->left;
        } 
        else 
        {
            root = pop(&s);
            if (root->right != NULL && !isEmpty(&s) && root->right == s.data[s.top]) {
                pop(&s);
                push(&s, root);
                root = root->right;
            } else {
                height++;
                root = NULL;
            }
        }
    }

    return height;
}

int main() {
    struct node* root = NULL;

    createBinaryTree(&root);

    printf("Preorder Traversal: ");
    preorderTraversal(root);
    printf("\n");

    printf("Inorder Traversal: ");
    inorderTraversal(root);
    printf("\n");

    printf("Postorder Traversal: ");
    postorderTraversal(root);
    printf("\n");

    printf("Total number of nodes: %d\n", countNodes(root));

    printf("Height of the tree: %d\n", findHeight(root));

    return 0;
}
