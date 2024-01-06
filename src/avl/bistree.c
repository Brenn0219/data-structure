#include "bistree.h"

static void rotate_left(BiTreeNode **node) {
    BiTreeNode *left, *grandchild;

    left = bitree_left(*node);
    
    // rotacao EE
    if (((AvlNode *) bitree_data(left))->factor == AVL_LEFT_HEAVY) {
        bitree_left(*node) = bitree_right(left);
        bitree_right(left) = *node;

        ((AvlNode *) bitree_data(*node))->factor = AVL_BALANCED;
        ((AvlNode *) bitree_data(left))->factor = AVL_BALANCED;

        *node = left;
    } else { // rotacao ED
        grandchild = bitree_right(left);
        bitree_right(left) = bitree_left(grandchild);
        bitree_left(grandchild) = left;
        bitree_left(*node) = bitree_right(grandchild);
        bitree_right(grandchild) = *node;

        switch (((AvlNode *) bitree_data(grandchild))->factor) {
            case AVL_LEFT_HEAVY:
                ((AvlNode *) bitree_data(*node))->factor = AVL_RIGHT_HEAVY;
                ((AvlNode *) bitree_data(left))->factor = AVL_BALANCED;
                break;

            case AVL_BALANCED:
                ((AvlNode *) bitree_data(*node))->factor = AVL_BALANCED;
                ((AvlNode *) bitree_data(left))->factor = AVL_BALANCED;
                break;
            
            case AVL_RIGHT_HEAVY:
                ((AvlNode *) bitree_data(*node))->factor = AVL_BALANCED;
                ((AvlNode *) bitree_data(left))->factor = AVL_LEFT_HEAVY;
                break;
        }

        ((AvlNode *) bitree_data(grandchild))->factor = AVL_BALANCED;
        *node = grandchild;
    }
}

static void rotate_right(BiTreeNode **node) {
    BiTreeNode *right, *grandchild;

    right = bitree_right(*node);

    // rotacao DD
    if (((AvlNode *) bitree_data(right))->factor == AVL_RIGHT_HEAVY) {
        bitree_right(*node) = bitree_left(right);
        bitree_left(right) = *node;

        ((AvlNode *) bitree_data(*node))->factor = AVL_BALANCED;
        ((AvlNode *) bitree_data(right))->factor = AVL_BALANCED;

        *node = right;
    } else { // rotacao DE
        grandchild = bitree_left(right);
        bitree_left(right) = bitree_right(grandchild);
        bitree_right(grandchild) = right;
        bitree_right(*node) = bitree_left(grandchild);
        bitree_left(grandchild) = *node;
    }

    switch (((AvlNode *) bitree_data(grandchild))->factor) {
        case AVL_LEFT_HEAVY:
            ((AvlNode *) bitree_data(*node))->factor = AVL_BALANCED;
            ((AvlNode *) bitree_data(right))->factor = AVL_RIGHT_HEAVY;
            break;

        case AVL_BALANCED:
            ((AvlNode *) bitree_data(*node))->factor = AVL_BALANCED;
            ((AvlNode *) bitree_data(right))->factor = AVL_BALANCED;
            break;
        
        case AVL_RIGHT_HEAVY:
            ((AvlNode *) bitree_data(*node))->factor = AVL_LEFT_HEAVY;
            ((AvlNode *) bitree_data(right))->factor = AVL_BALANCED;
            break;
    }

    ((AvlNode *) bitree_data(grandchild))->factor = AVL_BALANCED;
    *node = grandchild;
}