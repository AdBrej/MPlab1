#include <stdio.h>
#include <iostream>

struct Tree
{
    Tree * parent;
    Tree ** children;
    int count;
    int value;
};

Tree * PermutationTree_Create(int set[], int setCount, int value, Tree * parent)
{
    Tree * root = new Tree;
    root->value = value;
    root->count = setCount;
    root->parent = parent;
    if (setCount == 0){
        root->children = NULL;
        return root;
    }
    root->children = new Tree * [setCount];

    for (int i = 0; i < setCount; i++){
        int * newSet = new int[setCount-1];
        for (int j = 0; j < i; j++){
            newSet[j] = set[j];
        }
        for (int j = i+1; j < setCount; j++){
            newSet[j - 1] = set[j];
        }
        root->children[i] = PermutationTree_Create(newSet, setCount-1,set[i], root);
        delete[] newSet;
    }
    return root;
}

void PermutationTree_Print(Tree * root)
{
    if (root->children == NULL){
        while (root->parent != NULL){
            std::cout << root->value << " ";
            root = root->parent;
        }
        std::cout << "\n";
        return;
    }
    for (int i = 0; i < root->count; i++){
        if (root->children[i] != NULL){
            PermutationTree_Print(root->children[i]);
        }
    }
}

void Combinations_Print(int const set[], int start, int setCount, const int comLength, int result[], int count)
{
    if (count == comLength){
        for (int i = 0; i < comLength; i++){
            std::cout << result[i] << " ";

        }
        std::cout << "\n";
        return;
    }
    for (int i = start; i < setCount; i++){
        result[count] = set[i];
        Combinations_Print(set, i+1, setCount, comLength, result, count+1);
    }
}

int main()
{
    int const size = 5;
    int tab[size];
    int result[3];
    for (int i = 0; i < size; i++)tab[i] = i;
    Tree * root = PermutationTree_Create(tab, size, 0, NULL);
    PermutationTree_Print(root);
    Combinations_Print(tab, 0, size, 3, result,0);
    return 0;
}