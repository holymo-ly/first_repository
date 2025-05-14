#include <stdio.h>
#include <stdlib.h>

typedef struct treeNode {
    char key;
    struct treeNode* left;
    struct treeNode* right;
} treeNode;

treeNode* createNode(char key) {
    treeNode* newNode = (treeNode*)malloc(sizeof(treeNode));
    newNode->key = key;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

treeNode* insertBSTNode(treeNode* root, char key) {
    if (root == NULL) return createNode(key);

    if (key < root->key)
        root->left = insertBSTNode(root->left, key);
    else if (key > root->key)
        root->right = insertBSTNode(root->right, key);

    return root;
}

treeNode* searchBST(treeNode* root, char key) {
    if (root == NULL || root->key == key)
        return root;

    if (key < root->key)
        return searchBST(root->left, key);
    else
        return searchBST(root->right, key);
}

treeNode* deleteBSTNode(treeNode* root, char key) {
    if (root == NULL) return NULL;

    if (key < root->key)
        root->left = deleteBSTNode(root->left, key);
    else if (key > root->key)
        root->right = deleteBSTNode(root->right, key);
    else {
        if (root->left == NULL) {
            treeNode* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            treeNode* temp = root->left;
            free(root);
            return temp;
        }
        treeNode* succ = root->right;
        while (succ->left != NULL)
            succ = succ-> left;
        root->key = succ->key;
        root->right = deleteBSTNode(root->right, succ->key);
    }
    return root;
}

void displayInorder(treeNode* root) {
    if (root != NULL) {
        displayInorder(root->left);
        printf("%c ", root->key);
        displayInorder(root->right);
    }
}

int main() {
    treeNode* root = NULL;
    treeNode* found = NULL;
    int choice = 0;
    char key = 0;

    while (1) {
        printf("\n*-----------------------------*\n");
        printf("\t1 : 트리 출력\n");
        printf("\t2 : 문자 삽입\n");
        printf("\t3 : 문자 검색\n");
        printf("\t4 : 문자 삭제\n");
        printf("\t5 : 종료\n");
        printf("*-----------------------------*\n");
        printf("메뉴 입력 : ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("\t[이진트리 출력] ");
            displayInorder(root);
            printf("\n");
            break;

        case 2:
            printf("삽입할 문자 입력 : ");
            scanf(" %c", &key,1);
            root = insertBSTNode(root, key);
            break;

        case 3:
            printf("찾을 문자 입력 : ");
            scanf(" %c", &key,1);
            found = searchBST(root, key);
            if (found)
                printf("해당 문자를 찾았습니다.");
            else
                printf("해당 문자가 없습니다.");
            break;

        case 4:
            printf("삭제할 문자 입력 : ");
            scanf(" %c", &key,1);
            root = deleteBSTNode(root, key);
            break;

        case 5:
            printf("\n종료\n");
            return 0;

        default:
            printf("\n없는 메뉴\n");
            break;
        }
    }
}