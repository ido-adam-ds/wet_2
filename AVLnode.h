//
// Created by Iddo Petrank on 30/11/2021->
//

#ifndef WET1_AVLNODE_H
#define WET1_AVLNODE_H
#define MAX_SIZE 201

#include <ostream>
namespace DS{
    
    
    struct AVLnode {

        int key;
        AVLnode *left_son;
        AVLnode *right_son;
        AVLnode *father;
        int height;
        int scores[MAX_SIZE];
        int player_weight;
        int  weighted_sum;



        AVLnode( int key1):key(key1), left_son(nullptr), right_son(nullptr), father(nullptr), height(0), player_weight(0), weighted_sum(0)
        {
            for(int i = 0; i < MAX_SIZE; i++)
            {
                scores[i] = 0;
            }

        };

        ~AVLnode() = default;

        const int getBalanceFactor() const {
            return getHeight(left_son) - getHeight(right_son);
        }

        friend const int getHeight(const AVLnode* node){
            if(node == nullptr)
            {
                return -1;
            }
            return node->height;
        }


        friend void swapFathers(AVLnode* first, AVLnode* second){
            AVLnode* temp = first->father;
            if(second->father && second->father == first)
            {
                first->father = second;
                second->father = temp;
            }
            else if(first->father && first->father == second)
            {
                first->father = second->father;
                second->father = first;
            }else{
                first->father = second->father;
                second->father = temp;
            }
        }

        friend void swapLeftSon(AVLnode* first, AVLnode* second) {
            AVLnode* temp = first->left_son;

            if(second->left_son && second->left_son == first)
            {
                first->left_son = second;
                second->left_son = temp;
                if(second->left_son)
                {
                    second->left_son->father = second;
                }
            }
            else if(first->left_son && first->left_son == second)
            {
                first->left_son = second->left_son;
                if(first->left_son)
                {
                    first->left_son->father = first;
                }
                second->left_son = first;
            }else{
                first->left_son = second->left_son;
                if(first->left_son)
                {
                    first->left_son->father = first;
                }
                second->left_son = temp;
                if(second->left_son)
                {
                    second->left_son->father = second;
                }
            }
        }

        friend void swapRightSon(AVLnode* first, AVLnode* second) {
            AVLnode* temp = first->right_son;
            if(second->right_son && second->right_son == first)
            {
                first->right_son = second;
                second->right_son = temp;
                if(second->right_son)
                {
                    second->right_son->father = second;
                }
            }
            else if(first->right_son && first->right_son == second)
            {
                first->right_son = second->right_son;
                if(first->right_son)
                {
                    first->right_son->father = first;
                }
                second->right_son = first;
            }else{
                first->right_son = second->right_son;
                if(first->right_son)
                {
                    first->right_son->father = first;
                }
                second->right_son = temp;
                if(second->right_son)
                {
                    second->right_son->father = second;
                }
            }
        }


        friend AVLnode* swap(AVLnode* root, AVLnode* new_root)
        {
            /*
            AVLnode<KEY, VALUE, intMAX_SIZE> temp = *root;
            *root = *new_root;
            *new_root = temp;
    */
            swapFathers(root, new_root);
            swapLeftSon(root, new_root);
            swapRightSon(root, new_root);

            if(root->father && root->father != new_root){
                if(root->father->right_son == new_root )
                {
                    root->father->right_son = root;
                }
                else
                {
                    root->father->left_son = root;
                }
            }
            if(new_root->father && new_root->father != root){
                if(new_root->father->right_son == root)
                {
                    new_root->father->right_son = new_root;
                }
                else
                {
                    new_root->father->left_son = new_root;
                }
            }
            return new_root;


        }


    } ;
    
    int getAllPlayersWeight( const AVLnode *node)
    {
        if(node == nullptr)
        {
            return 0;
        }
        else return node->player_weight;
    }


    
    int getScorePlayersWeight( const AVLnode *node, int score)
    {
        if(node == nullptr)
        {
            return 0;
        }
        else return node->scores[score];
    }

    
    int getWeightedSum( const AVLnode *node)
    {
        if(node == nullptr)
        {
            return 0;
        }
        else return node->weighted_sum;
    }


    
    int getNumPlayers( const AVLnode *node)
    {
        if(node == nullptr)
        {
            return 0;
        }
        else return node->player_weight - node->left_son->player_weight-node->right_son->player_weight;
    }

    
    int getNumPlayersWithScore( const AVLnode *node, int score)
    {
        if(node == nullptr)
        {
            return 0;
        }
        else return node->scores[score] - node->left_son->scores[score]-node->right_son->scores[score];
    }


    
    void addScores(  AVLnode *dst, const AVLnode *node1, const AVLnode *node2)
    {
        if (dst == nullptr) return;
        if(node1 == nullptr && node2 == nullptr)
        {
            for(int i = 0; i <MAX_SIZE; i++)
            {
                dst->scores[i] = 0;
            }
            return;
        }
        else if (node1 == nullptr)
        {
            for(int i = 0; i <MAX_SIZE; i++)
            {
                dst->scores[i] = node2->scores[i];
            }
            return;
        }
        else if (node2 == nullptr)
        {
            for(int i = 0; i <MAX_SIZE; i++)
            {
                dst->scores[i] = node1->scores[i];
            }
            return;
        }
        else
        {
            for(int i = 0; i <MAX_SIZE; i++)
            {
                dst->scores[i] = node1->scores[i]+node2->scores[i];
            }
            return;
        }
    }

    
    void updateWeights(AVLnode *node)
    {
        if(node == nullptr) {
            return;
        }
        addScores(node, node->right_son, node->left_son);
        node->weighted_sum = node->right_son->weighted_sum+node->left_son->weighted_sum;
        node->player_weight = node->right_son->player_weight+node->left_son->player_weight;
    }
}

#endif //WET1_AVLNODE_H
