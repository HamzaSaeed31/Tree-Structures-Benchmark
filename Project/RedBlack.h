#pragma once
#ifndef header_H
#define header_H
#include<string>
#include<iostream>
#include<fstream>
using namespace std;
template <class X>
struct list_node
{
    list_node<X>* next;
    X data;
};
template <class X>
class linked_list
{
public:
    list_node<X>* head;
    linked_list()
    {
        head = NULL;
    }
    void insert(X key)
    {
        list_node<X>* new_node = new list_node<X>;
        new_node->data = key;
        new_node->next = NULL;
        if (head == NULL)
        {
            head = new_node;
        }
        else
        {
            list_node<X>* trav = head;
            while (trav->next != NULL)
            {
                trav = trav->next;
            }
            trav->next = new_node;
        }
        return;
    }
    bool is_present(X key)
    {
        if (head == NULL)
            return 0;
        list_node<X>* trav = head;
        while (trav != NULL)
        {
            if (trav->data == key)
                return 1;
            trav = trav->next;
        }
        return 0;
    }
    void print()
    {
        list_node<X>* trav = head;
        while (trav != NULL)
        {
            cout << trav->data << endl;
            trav = trav->next;
        }
    }
};
template <class X>
struct RedBlackNode
{
    X data;
    bool color;
    RedBlackNode<X>* pre;
    RedBlackNode<X>* left;
    RedBlackNode<X>* right;
};

template <class X>
class RedBlackTree
{
public:
    RedBlackNode<X>* root;
    RedBlackTree()
    {
        root = new RedBlackNode<X>;
        root->color = 0;
        root->left = NULL;
        root->right = NULL;
    }


    void left_rotation(RedBlackNode<X>* oper)
    {
        RedBlackNode<X>* temp = oper->right;
        oper->right = temp->left;
        if (temp->left != NULL)
            temp->left->pre = oper;
        temp->pre = oper->pre;
        if (oper->pre == NULL)
            root = temp;
        else if (oper == oper->pre->right)
            oper->pre->right = temp;
        else if (oper == oper->pre->left)
            oper->pre->left = temp;
        temp->left = oper;
        oper->pre = temp;
    }

    void right_rotation(RedBlackNode<X>* oper)
    {
        RedBlackNode<X>* temp = oper->left;
        oper->left = temp->right;
        if (temp->right != NULL)
            temp->right->pre = oper;
        temp->pre = oper->pre;
        if (oper->pre == NULL)
            root = temp;
        else if (oper == oper->pre->left)
            oper->pre->left = temp;
        else if (oper == oper->pre->right)
            oper->pre->right = temp;
        temp->right = oper;
        oper->pre = temp;
    }

    void Rotations(RedBlackNode<X>* oper)
    {
        RedBlackNode<X>* uncle = new RedBlackNode<X>;
        while (1)
        {
            if (oper->pre->color == 0)//base case, parent's color
                break;

            if (oper->pre == oper->pre->pre->left)//checking uncle
            {
                uncle = oper->pre->pre->right;//uncle = uncle

                if (uncle->color == 0)//if uncle is black
                {
                    if (oper == oper->pre->right)
                    {
                        oper = oper->pre;
                        left_rotation(oper);
                    }
                    oper->pre->color = 0;
                    oper->pre->pre->color = 1;
                    right_rotation(oper->pre->pre);
                }
                else if (uncle->color == 1)//if uncle is red
                {
                    uncle->color = 0;
                    oper->pre->color = 0;
                    oper->pre->pre->color = 1;
                    oper = oper->pre->pre;
                }
            }
            else if (oper->pre == oper->pre->pre->right)
            {
                uncle = oper->pre->pre->left;
                if (uncle->color == 0)
                {
                    if (oper == oper->pre->left)
                    {
                        oper = oper->pre;
                        right_rotation(oper);
                    }
                    oper->pre->color = 0;
                    oper->pre->pre->color = 1;
                    left_rotation(oper->pre->pre);
                }
                else if (uncle->color == 1)
                {

                    uncle->color = 0;
                    oper->pre->color = 0;
                    oper->pre->pre->color = 1;
                    oper = oper->pre->pre;
                }
            }
            if (oper->color == root->color && oper->pre == NULL && oper->left == root->left && oper->right == root->right)//base case
                break;
        }
        root->color = 0;//root is always black, if root changed while applying rotations
    }




    // Inserting a node
    void insert(X key) {
        RedBlackNode<X>* node = new RedBlackNode<X>;
        RedBlackNode<X>* null_ptr = new RedBlackNode<X>;
        null_ptr->color = 0;
        null_ptr->left = NULL;
        null_ptr->right = NULL;
        node->pre = NULL;
        node->data = key;
        node->left = null_ptr;//for comparison
        node->right = null_ptr;//for comparison
        node->color = 1;//every newly inserted node is red

        RedBlackNode<X>* temp = NULL;
        RedBlackNode<X>* oper = this->root;

        while (oper->left != NULL && oper->right != NULL) //doing traversals using BST principle
        {
            temp = oper;
            if (node->data > oper->data)
                oper = oper->right;
            else
                oper = oper->left;
        }
        node->pre = temp;
        if (temp == NULL)
        {
            root = node;
            return;
        }
        else if (node->data > temp->data) //adding node as per BST principle
            temp->right = node;
        else if (node->data < temp->data) //adding node as per BST principle
            temp->left = node;

        if (node->pre == NULL)//root node is always black
        {
            node->color = 0;
            return;
        }
        //if grandparent == NULL 
        if (node->pre->pre == NULL)
            return;

        Rotations(node);//apply balancing as per red black principles
    }
    void preorder(RedBlackNode<X>* root)
    {
        if (root->left != NULL && root->right != NULL)
        {
            cout << root->data << " " << root->color << ", ";
            preorder(root->left);
            preorder(root->right);
        }
    }

};


RedBlackNode<int>* id_wise_RBinsertion()
{
    RedBlackTree<int>* RBT = new RedBlackTree<int>;
    ifstream csv_file;
    csv_file.open("NCHS_-_Leading_Causes_of_Death__United_States_1.csv");
    ofstream write;
    int i = 1;
    string val;
    string dest = "";
    while (i <= 10)
    {
        getline(csv_file, val);
        string id = "";
        string year = "";
        string cause_113 = "";
        string cause = "";
        string state = "";
        string deaths = "";
        string death_rate = "";
        int comma = 0, j = 0;
        bool cont = 0;
        while (val[j] != '\0')
        {
            if (comma == 0)
            {
                if (val[j] == ',')
                {
                    comma++;
                    j++;
                    continue;
                }
                id += val[j];
            }
            else if (comma == 1)
            {
                if (val[j] == ',')
                {
                    comma++;
                    j++;
                    continue;
                }
                year += val[j];
            }
            else if (comma == 2 || comma == 3)
            {
                if (val[j] == ',')
                {
                    comma++;
                    j++;
                    continue;
                }
                cause_113 += val[j];
            }
            else if (comma == 4)
            {
                if (val[j] == ',')
                {
                    comma++;
                    j++;
                    continue;
                }
                cause += val[j];
            }
            else if (comma == 5)
            {
                if (val[j] == ',')
                {
                    comma++;
                    j++;
                    continue;
                }
                state += val[j];
            }
            else if (comma == 6)
            {
                if (val[j] == ',')
                {
                    comma++;
                    j++;
                    continue;
                }
                deaths += val[j];
            }
            else if (comma == 7)
            {
                if (val[j] == ',')
                {
                    comma++;
                    j++;
                    continue;
                }
                death_rate += val[j];
            }
            j++;
        }
        if (id == "ID")
            continue;
        dest = to_string(i) + ".txt";
        write.open(dest);
        write << id << endl;
        write << year << endl;
        write << cause_113 << endl;
        write << cause << endl;
        write << state << endl;
        write << deaths << endl;
        write << death_rate << endl;
        RBT->insert(stoi(id));
        write.close();
        i++;
    }
    return RBT->root;
}

RedBlackNode<int>* year_wise_insertion()
{
    RedBlackTree<int>* RBT = new RedBlackTree<int>;
    linked_list<int>* LL = new linked_list<int>;
    ifstream csv_file;
    csv_file.open("NCHS_-_Leading_Causes_of_Death__United_States_1.csv");
    ofstream write;
    int i = 1;
    string val;
    string dest = "";
    while (i <= 100)
    {
        getline(csv_file, val);
        string id = "";
        string year = "";
        string cause_113 = "";
        string cause = "";
        string state = "";
        string deaths = "";
        string death_rate = "";
        int comma = 0, j = 0;
        bool cont = 0;
        while (val[j] != '\0')
        {
            if (i <= 51)
            {
                if (comma == 0)
                {
                    if (val[j] == ',')
                    {
                        comma++;
                        j++;
                        continue;
                    }
                    id += val[j];
                }
                else if (comma == 1)
                {
                    if (val[j] == ',')
                    {
                        comma++;
                        j++;
                        continue;
                    }
                    year += val[j];
                }
                else if (comma == 2 || comma == 3)
                {
                    if (val[j] == ',')
                    {
                        comma++;
                        j++;
                        continue;
                    }
                    cause_113 += val[j];
                }
                else if (comma == 4)
                {
                    if (val[j] == ',')
                    {
                        comma++;
                        j++;
                        continue;
                    }
                    cause += val[j];
                }
                else if (comma == 5)
                {
                    if (val[j] == ',')
                    {
                        comma++;
                        j++;
                        continue;
                    }
                    state += val[j];
                }
                else if (comma == 6)
                {
                    if (val[j] == ',')
                    {
                        comma++;
                        j++;
                        continue;
                    }
                    deaths += val[j];
                }
                else if (comma == 7)
                {
                    if (val[j] == ',')
                    {
                        comma++;
                        j++;
                        continue;
                    }
                    death_rate += val[j];
                }
                j++;
            }
            else
            {
                if (comma == 0)
                {
                    if (val[j] == ',')
                    {
                        comma++;
                        j++;
                        continue;
                    }
                    id += val[j];
                }
                else if (comma == 1)
                {
                    if (val[j] == ',')
                    {
                        comma++;
                        j++;
                        continue;
                    }
                    year += val[j];
                }
                else if (comma == 2)
                {
                    if (val[j] == ',')
                    {
                        comma++;
                        j++;
                        continue;
                    }
                    cause_113 += val[j];
                }
                else if (comma == 3)
                {
                    if (val[j] == ',')
                    {
                        comma++;
                        j++;
                        continue;
                    }
                    cause += val[j];
                }
                else if (comma == 4)
                {
                    if (val[j] == ',')
                    {
                        comma++;
                        j++;
                        continue;
                    }
                    state += val[j];
                }
                else if (comma == 5)
                {
                    if (val[j] == ',')
                    {
                        comma++;
                        j++;
                        continue;
                    }
                    deaths += val[j];
                }
                else if (comma == 6)
                {
                    if (val[j] == ',')
                    {
                        comma++;
                        j++;
                        continue;
                    }
                    death_rate += val[j];
                }
                j++;
            }
        }
        if (id == "ID")
            continue;
        //checking for repetitiion
        if (LL->is_present(stoi(year)))
        {
            dest = year + ".txt";
            write.open(dest, ios::app);
            write << id << endl;
            write << year << endl;
            write << cause_113 << endl;
            write << cause << endl;
            write << state << endl;
            write << deaths << endl;
            write << death_rate << endl;
            //RBT->insert(stoi(year));
            write.close();
        }
        else if (!LL->is_present(stoi(year)))
        {
            LL->insert(stoi(year));
            dest = year + ".txt";
            write.open(dest);
            write << id << endl;
            write << year << endl;
            write << cause_113 << endl;
            write << cause << endl;
            write << state << endl;
            write << deaths << endl;
            write << death_rate << endl;
            RBT->insert(stoi(year));
            write.close();
        }
        i++;
    }
    //LL->print();
    return RBT->root;
}
RedBlackNode<string>* cause113_wise_insertion()
{
    RedBlackTree<string>* RBT = new RedBlackTree<string>;
    linked_list<string>* LL = new linked_list<string>;
    ifstream csv_file;
    csv_file.open("NCHS-_-Leading_Causes_of_Death_United_States_1.csv");
    ofstream write;
    int i = 1;
    string val;
    string dest = "";
    while (i <= 1015)
    {
        getline(csv_file, val);
        string id = "";
        string year = "";
        string cause_113 = "";
        string cause = "";
        string state = "";
        string deaths = "";
        string death_rate = "";
        int comma = 0, j = 0;
        bool cont = 0;
        while (val[j] != '\0')
        {
            if (i <= 51)
            {
                if (comma == 0)
                {
                    if (val[j] == ',')
                    {
                        comma++;
                        j++;
                        continue;
                    }
                    id += val[j];
                }
                else if (comma == 1)
                {
                    if (val[j] == ',')
                    {
                        comma++;
                        j++;
                        continue;
                    }
                    year += val[j];
                }
                else if (comma == 2 || comma == 3)
                {
                    if (val[j] == ',')
                    {
                        comma++;
                        j++;
                        continue;
                    }
                    if (val[j] == 34)
                    {
                        j++;
                        continue;
                    }
                    cause_113 += val[j];
                }
                else if (comma == 4)
                {
                    if (val[j] == ',')
                    {
                        comma++;
                        j++;
                        continue;
                    }
                    cause += val[j];
                }
                else if (comma == 5)
                {
                    if (val[j] == ',')
                    {
                        comma++;
                        j++;
                        continue;
                    }
                    state += val[j];
                }
                else if (comma == 6)
                {
                    if (val[j] == ',')
                    {
                        comma++;
                        j++;
                        continue;
                    }
                    deaths += val[j];
                }
                else if (comma == 7)
                {
                    if (val[j] == ',')
                    {
                        comma++;
                        j++;
                        continue;
                    }
                    death_rate += val[j];
                }
                j++;
            }
            else
            {
                if (comma == 0)
                {
                    if (val[j] == ',')
                    {
                        comma++;
                        j++;
                        continue;
                    }
                    id += val[j];
                }
                else if (comma == 1)
                {
                    if (val[j] == ',')
                    {
                        comma++;
                        j++;
                        continue;
                    }
                    year += val[j];
                }
                else if (comma == 2)
                {
                    if (val[j] == ',')
                    {
                        comma++;
                        j++;
                        continue;
                    }
                    cause_113 += val[j];
                }
                else if (comma == 3)
                {
                    if (val[j] == ',')
                    {
                        comma++;
                        j++;
                        continue;
                    }
                    cause += val[j];
                }
                else if (comma == 4)
                {
                    if (val[j] == ',')
                    {
                        comma++;
                        j++;
                        continue;
                    }
                    state += val[j];
                }
                else if (comma == 5)
                {
                    if (val[j] == ',')
                    {
                        comma++;
                        j++;
                        continue;
                    }
                    deaths += val[j];
                }
                else if (comma == 6)
                {
                    if (val[j] == ',')
                    {
                        comma++;
                        j++;
                        continue;
                    }
                    death_rate += val[j];
                }
                j++;
            }
        }
        if (id == "ID")
            continue;

        //checking for repetitiion
        if (LL->is_present(cause_113))
        {
            dest = cause_113 + ".txt";
            write.open(dest, ios::app);
            write << id << endl;
            write << year << endl;
            write << cause_113 << endl;
            write << cause << endl;
            write << state << endl;
            write << deaths << endl;
            write << death_rate << endl;
            //RBT->insert(stoi(year));
            write.close();
        }
        else if (!LL->is_present(cause_113))
        {
            LL->insert(cause_113);
            dest = cause_113 + ".txt";
            write.open(dest);
            write << id << endl;
            write << year << endl;
            write << cause_113 << endl;
            write << cause << endl;
            write << state << endl;
            write << deaths << endl;
            write << death_rate << endl;
            RBT->insert(cause_113);
            write.close();
        }
        i++;
    }
    //LL->print();
    return RBT->root;
}

RedBlackNode<string>* cause_wise_insertion()
{
    RedBlackTree<string>* RBT = new RedBlackTree<string>;
    linked_list<string>* LL = new linked_list<string>;
    ifstream csv_file;
    csv_file.open("NCHS_-_Leading_Causes_of_Death__United_States_1.csv");
    ofstream write;
    int i = 1;
    string val;
    string dest = "";
    while (i <= 1015)
    {
        getline(csv_file, val);
        string id = "";
        string year = "";
        string cause_113 = "";
        string cause = "";
        string state = "";
        string deaths = "";
        string death_rate = "";
        int comma = 0, j = 0;
        bool cont = 0;
        while (val[j] != '\0')
        {
            if (i <= 51)
            {
                if (comma == 0)
                {
                    if (val[j] == ',')
                    {
                        comma++;
                        j++;
                        continue;
                    }
                    id += val[j];
                }
                else if (comma == 1)
                {
                    if (val[j] == ',')
                    {
                        comma++;
                        j++;
                        continue;
                    }
                    year += val[j];
                }
                else if (comma == 2 || comma == 3)
                {
                    if (val[j] == ',')
                    {
                        comma++;
                        j++;
                        continue;
                    }
                    if (val[j] == 34)
                    {
                        j++;
                        continue;
                    }
                    cause_113 += val[j];
                }
                else if (comma == 4)
                {
                    if (val[j] == ',')
                    {
                        comma++;
                        j++;
                        continue;
                    }
                    cause += val[j];
                }
                else if (comma == 5)
                {
                    if (val[j] == ',')
                    {
                        comma++;
                        j++;
                        continue;
                    }
                    state += val[j];
                }
                else if (comma == 6)
                {
                    if (val[j] == ',')
                    {
                        comma++;
                        j++;
                        continue;
                    }
                    deaths += val[j];
                }
                else if (comma == 7)
                {
                    if (val[j] == ',')
                    {
                        comma++;
                        j++;
                        continue;
                    }
                    death_rate += val[j];
                }
                j++;
            }
            else
            {
                if (comma == 0)
                {
                    if (val[j] == ',')
                    {
                        comma++;
                        j++;
                        continue;
                    }
                    id += val[j];
                }
                else if (comma == 1)
                {
                    if (val[j] == ',')
                    {
                        comma++;
                        j++;
                        continue;
                    }
                    year += val[j];
                }
                else if (comma == 2)
                {
                    if (val[j] == ',')
                    {
                        comma++;
                        j++;
                        continue;
                    }
                    cause_113 += val[j];
                }
                else if (comma == 3)
                {
                    if (val[j] == ',')
                    {
                        comma++;
                        j++;
                        continue;
                    }
                    cause += val[j];
                }
                else if (comma == 4)
                {
                    if (val[j] == ',')
                    {
                        comma++;
                        j++;
                        continue;
                    }
                    state += val[j];
                }
                else if (comma == 5)
                {
                    if (val[j] == ',')
                    {
                        comma++;
                        j++;
                        continue;
                    }
                    deaths += val[j];
                }
                else if (comma == 6)
                {
                    if (val[j] == ',')
                    {
                        comma++;
                        j++;
                        continue;
                    }
                    death_rate += val[j];
                }
                j++;
            }
        }
        if (id == "ID")
            continue;

        //checking for repetitiion
        if (LL->is_present(cause))
        {
            dest = cause + ".txt";
            write.open(dest, ios::app);
            write << id << endl;
            write << year << endl;
            write << cause_113 << endl;
            write << cause << endl;
            write << state << endl;
            write << deaths << endl;
            write << death_rate << endl;
            //RBT->insert(stoi(year));
            write.close();
        }
        else if (!LL->is_present(cause))
        {
            LL->insert(cause);
            dest = cause + ".txt";
            write.open(dest);
            write << id << endl;
            write << year << endl;
            write << cause_113 << endl;
            write << cause << endl;
            write << state << endl;
            write << deaths << endl;
            write << death_rate << endl;
            RBT->insert(cause);
            write.close();
        }
        i++;
    }
    //LL->print();
    return RBT->root;
}
RedBlackNode<string>* state_wise_insertion()
{
    RedBlackTree<string>* RBT = new RedBlackTree<string>;
    linked_list<string>* LL = new linked_list<string>;
    ifstream csv_file;
    csv_file.open("NCHS_-_Leading_Causes_of_Death__United_States_1.csv");
    ofstream write;
    int i = 1;
    string val;
    string dest = "";
    while (i <= 1015)
    {
        getline(csv_file, val);
        string id = "";
        string year = "";
        string cause_113 = "";
        string cause = "";
        string state = "";
        string deaths = "";
        string death_rate = "";
        int comma = 0, j = 0;
        bool cont = 0;
        while (val[j] != '\0')
        {
            if (i <= 51)
            {
                if (comma == 0)
                {
                    if (val[j] == ',')
                    {
                        comma++;
                        j++;
                        continue;
                    }
                    id += val[j];
                }
                else if (comma == 1)
                {
                    if (val[j] == ',')
                    {
                        comma++;
                        j++;
                        continue;
                    }
                    year += val[j];
                }
                else if (comma == 2 || comma == 3)
                {
                    if (val[j] == ',')
                    {
                        comma++;
                        j++;
                        continue;
                    }
                    if (val[j] == 34)
                    {
                        j++;
                        continue;
                    }
                    cause_113 += val[j];
                }
                else if (comma == 4)
                {
                    if (val[j] == ',')
                    {
                        comma++;
                        j++;
                        continue;
                    }
                    cause += val[j];
                }
                else if (comma == 5)
                {
                    if (val[j] == ',')
                    {
                        comma++;
                        j++;
                        continue;
                    }
                    state += val[j];
                }
                else if (comma == 6)
                {
                    if (val[j] == ',')
                    {
                        comma++;
                        j++;
                        continue;
                    }
                    deaths += val[j];
                }
                else if (comma == 7)
                {
                    if (val[j] == ',')
                    {
                        comma++;
                        j++;
                        continue;
                    }
                    death_rate += val[j];
                }
                j++;
            }
            else
            {
                if (comma == 0)
                {
                    if (val[j] == ',')
                    {
                        comma++;
                        j++;
                        continue;
                    }
                    id += val[j];
                }
                else if (comma == 1)
                {
                    if (val[j] == ',')
                    {
                        comma++;
                        j++;
                        continue;
                    }
                    year += val[j];
                }
                else if (comma == 2)
                {
                    if (val[j] == ',')
                    {
                        comma++;
                        j++;
                        continue;
                    }
                    cause_113 += val[j];
                }
                else if (comma == 3)
                {
                    if (val[j] == ',')
                    {
                        comma++;
                        j++;
                        continue;
                    }
                    cause += val[j];
                }
                else if (comma == 4)
                {
                    if (val[j] == ',')
                    {
                        comma++;
                        j++;
                        continue;
                    }
                    state += val[j];
                }
                else if (comma == 5)
                {
                    if (val[j] == ',')
                    {
                        comma++;
                        j++;
                        continue;
                    }
                    deaths += val[j];
                }
                else if (comma == 6)
                {
                    if (val[j] == ',')
                    {
                        comma++;
                        j++;
                        continue;
                    }
                    death_rate += val[j];
                }
                j++;
            }
        }
        if (id == "ID")
            continue;

        //checking for repetitiion
        if (LL->is_present(state))
        {
            dest = state + ".txt";
            write.open(dest, ios::app);
            write << id << endl;
            write << year << endl;
            write << cause_113 << endl;
            write << cause << endl;
            write << state << endl;
            write << deaths << endl;
            write << death_rate << endl;
            //RBT->insert(stoi(year));
            write.close();
        }
        else if (!LL->is_present(state))
        {
            LL->insert(state);
            dest = state + ".txt";
            write.open(dest);
            write << id << endl;
            write << year << endl;
            write << cause_113 << endl;
            write << cause << endl;
            write << state << endl;
            write << deaths << endl;
            write << death_rate << endl;
            RBT->insert(state);
            write.close();
        }
        i++;
    }
    //LL->print();
    return RBT->root;
}
RedBlackNode<int>* death_wise_insertion()
{
    RedBlackTree<int>* RBT = new RedBlackTree<int>;
    linked_list<int>* LL = new linked_list<int>;
    ifstream csv_file;
    csv_file.open("NCHS_-_Leading_Causes_of_Death__United_States_1.csv");
    ofstream write;
    int i = 1;
    string val;
    string dest = "";
    while (i <= 1015)
    {
        getline(csv_file, val);
        string id = "";
        string year = "";
        string cause_113 = "";
        string cause = "";
        string state = "";
        string deaths = "";
        string death_rate = "";
        int comma = 0, j = 0;
        bool cont = 0;
        while (val[j] != '\0')
        {
            if (i <= 51)
            {
                if (comma == 0)
                {
                    if (val[j] == ',')
                    {
                        comma++;
                        j++;
                        continue;
                    }
                    id += val[j];
                }
                else if (comma == 1)
                {
                    if (val[j] == ',')
                    {
                        comma++;
                        j++;
                        continue;
                    }
                    year += val[j];
                }
                else if (comma == 2 || comma == 3)
                {
                    if (val[j] == ',')
                    {
                        comma++;
                        j++;
                        continue;
                    }
                    if (val[j] == 34)
                    {
                        j++;
                        continue;
                    }
                    cause_113 += val[j];
                }
                else if (comma == 4)
                {
                    if (val[j] == ',')
                    {
                        comma++;
                        j++;
                        continue;
                    }
                    cause += val[j];
                }
                else if (comma == 5)
                {
                    if (val[j] == ',')
                    {
                        comma++;
                        j++;
                        continue;
                    }
                    state += val[j];
                }
                else if (comma == 6)
                {
                    if (val[j] == ',')
                    {
                        comma++;
                        j++;
                        continue;
                    }
                    deaths += val[j];
                }
                else if (comma == 7)
                {
                    if (val[j] == ',')
                    {
                        comma++;
                        j++;
                        continue;
                    }
                    death_rate += val[j];
                }
                j++;
            }
            else
            {
                if (comma == 0)
                {
                    if (val[j] == ',')
                    {
                        comma++;
                        j++;
                        continue;
                    }
                    id += val[j];
                }
                else if (comma == 1)
                {
                    if (val[j] == ',')
                    {
                        comma++;
                        j++;
                        continue;
                    }
                    year += val[j];
                }
                else if (comma == 2)
                {
                    if (val[j] == ',')
                    {
                        comma++;
                        j++;
                        continue;
                    }
                    cause_113 += val[j];
                }
                else if (comma == 3)
                {
                    if (val[j] == ',')
                    {
                        comma++;
                        j++;
                        continue;
                    }
                    cause += val[j];
                }
                else if (comma == 4)
                {
                    if (val[j] == ',')
                    {
                        comma++;
                        j++;
                        continue;
                    }
                    state += val[j];
                }
                else if (comma == 5)
                {
                    if (val[j] == ',')
                    {
                        comma++;
                        j++;
                        continue;
                    }
                    deaths += val[j];
                }
                else if (comma == 6)
                {
                    if (val[j] == ',')
                    {
                        comma++;
                        j++;
                        continue;
                    }
                    death_rate += val[j];
                }
                j++;
            }
        }
        if (id == "ID")
            continue;

        //checking for repetitiion
        if (LL->is_present(stoi(deaths)))
        {
            dest = deaths + ".txt";
            write.open(dest, ios::app);
            write << id << endl;
            write << year << endl;
            write << cause_113 << endl;
            write << cause << endl;
            write << state << endl;
            write << deaths << endl;
            write << death_rate << endl;
            //RBT->insert(stoi(year));
            write.close();
        }
        else if (!LL->is_present(stoi(deaths)))
        {
            LL->insert(stoi(deaths));
            dest = deaths + ".txt";
            write.open(dest);
            write << id << endl;
            write << year << endl;
            write << cause_113 << endl;
            write << cause << endl;
            write << state << endl;
            write << deaths << endl;
            write << death_rate << endl;
            RBT->insert(stoi(deaths));
            write.close();
        }
        i++;
    }
    //LL->print();
    return RBT->root;
}

RedBlackNode<float>* deathrate_wise_insertion()
{
    RedBlackTree<float>* RBT = new RedBlackTree<float>;
    linked_list<float>* LL = new linked_list<float>;
    ifstream csv_file;
    csv_file.open("NCHS_-_Leading_Causes_of_Death__United_States_1.csv");
    ofstream write;
    int i = 1;
    string val;
    string dest = "";
    while (i <= 1015)
    {
        getline(csv_file, val);
        string id = "";
        string year = "";
        string cause_113 = "";
        string cause = "";
        string state = "";
        string deaths = "";
        string death_rate = "";
        int comma = 0, j = 0;
        bool cont = 0;
        while (val[j] != '\0')
        {
            if (i <= 51)
            {
                if (comma == 0)
                {
                    if (val[j] == ',')
                    {
                        comma++;
                        j++;
                        continue;
                    }
                    id += val[j];
                }
                else if (comma == 1)
                {
                    if (val[j] == ',')
                    {
                        comma++;
                        j++;
                        continue;
                    }
                    year += val[j];
                }
                else if (comma == 2 || comma == 3)
                {
                    if (val[j] == ',')
                    {
                        comma++;
                        j++;
                        continue;
                    }
                    if (val[j] == 34)
                    {
                        j++;
                        continue;
                    }
                    cause_113 += val[j];
                }
                else if (comma == 4)
                {
                    if (val[j] == ',')
                    {
                        comma++;
                        j++;
                        continue;
                    }
                    cause += val[j];
                }
                else if (comma == 5)
                {
                    if (val[j] == ',')
                    {
                        comma++;
                        j++;
                        continue;
                    }
                    state += val[j];
                }
                else if (comma == 6)
                {
                    if (val[j] == ',')
                    {
                        comma++;
                        j++;
                        continue;
                    }
                    deaths += val[j];
                }
                else if (comma == 7)
                {
                    if (val[j] == ',')
                    {
                        comma++;
                        j++;
                        continue;
                    }
                    death_rate += val[j];
                }
                j++;
            }
            else
            {
                if (comma == 0)
                {
                    if (val[j] == ',')
                    {
                        comma++;
                        j++;
                        continue;
                    }
                    id += val[j];
                }
                else if (comma == 1)
                {
                    if (val[j] == ',')
                    {
                        comma++;
                        j++;
                        continue;
                    }
                    year += val[j];
                }
                else if (comma == 2)
                {
                    if (val[j] == ',')
                    {
                        comma++;
                        j++;
                        continue;
                    }
                    cause_113 += val[j];
                }
                else if (comma == 3)
                {
                    if (val[j] == ',')
                    {
                        comma++;
                        j++;
                        continue;
                    }
                    cause += val[j];
                }
                else if (comma == 4)
                {
                    if (val[j] == ',')
                    {
                        comma++;
                        j++;
                        continue;
                    }
                    state += val[j];
                }
                else if (comma == 5)
                {
                    if (val[j] == ',')
                    {
                        comma++;
                        j++;
                        continue;
                    }
                    deaths += val[j];
                }
                else if (comma == 6)
                {
                    if (val[j] == ',')
                    {
                        comma++;
                        j++;
                        continue;
                    }
                    death_rate += val[j];
                }
                j++;
            }
        }
        if (id == "ID")
            continue;

        //checking for repetitiion
        if (LL->is_present(stof(deaths)))
        {
            dest = death_rate + ".txt";
            write.open(dest, ios::app);
            write << id << endl;            write << year << endl;
            write << cause_113 << endl;
            write << cause << endl;
            write << state << endl;
            write << deaths << endl;
            write << death_rate << endl;
            //RBT->insert(stoi(year));
            write.close();
        }
        else if (!LL->is_present(stof(death_rate)))

        {
            LL->insert(stof(death_rate));
            dest = death_rate + ".txt";
            write.open(dest);
            write << id << endl;
            write << year << endl;
            write << cause_113 << endl;
            write << cause << endl;
            write << state << endl;
            write << deaths << endl;
            write << death_rate << endl;
            RBT->insert(stof(death_rate));
            write.close();
        }
        i++;
    }
    //LL->print();
    return RBT->root;
}

void add_address(RedBlackNode<int>* root)
{
    if (root->left != NULL && root->right != NULL)
    {
        ofstream write;
        string dest = to_string(root->data) + ".txt";
        write.open(dest, ios::app);
        ////cout << root->data << " ";
        if (root->left->data < 0 && root->right->data>0)
        {
            write << "NULL" << endl;
            write << to_string(root->right->data) + ".txt" << endl;
        }
        else if (root->right->data < 0 && root->left->data > 0)
        {
            write << to_string(root->left->data) + ".txt" << endl;
            write << "NULL" << endl;
        }
        else if (root->right->data < 0 && root->left->data < 0)
        {
            write << "NULL" << endl;
            write << "NULL" << endl;
        }
        else
        {
            write << to_string(root->left->data) + ".txt" << endl;
            write << to_string(root->right->data) + ".txt" << endl;
        }
        add_address(root->left);
        add_address(root->right);
    }
}
void add_address_string(RedBlackNode<string>* root)
{
    if (root->left != NULL && root->right != NULL)
    {
        ofstream write;
        string dest = root->data + ".txt";
        write.open(dest, ios::app);
        ////cout << root->data << " ";
        if (root->left->data == "" && root->right->data != "")
        {
            write << "NULL" << endl;
            write << root->right->data + ".txt" << endl;
        }
        else if (root->right->data == "" && root->left->data != "")
        {
            write << root->left->data + ".txt" << endl;
            write << "NULL" << endl;
        }
        else if (root->right->data == "" && root->left->data == "")
        {
            write << "NULL" << endl;
            write << "NULL" << endl;
        }
        else
        {
            write << root->left->data + ".txt" << endl;
            write << root->right->data + ".txt" << endl;
        }
        add_address_string(root->left);
        add_address_string(root->right);
    }
}

void add_address_float(RedBlackNode<float>* root)
{
    if (root->left != NULL && root->right != NULL)
    {
        ofstream write;
        string dest = to_string(root->data) + ".txt";
        write.open(dest, ios::app);
        ////cout << root->data << " ";
        if (root->left->data < 0 && root->right->data>0)
        {
            write << "NULL" << endl;
            write << to_string(root->right->data) + ".txt" << endl;
        }
        else if (root->right->data < 0 && root->left->data > 0)
        {
            write << to_string(root->left->data) + ".txt" << endl;
            write << "NULL" << endl;
        }
        else if (root->right->data < 0 && root->left->data < 0)
        {
            write << "NULL" << endl;
            write << "NULL" << endl;
        }
        else
        {
            write << to_string(root->left->data) + ".txt" << endl;
            write << to_string(root->right->data) + ".txt" << endl;
        }
        add_address_float(root->left);
        add_address_float(root->right);
    }
}


void red_black()
{
    int option, search_op, idin;
    cout << "Enter the column number on which base you want to execute indexing:\n1) ID\n2) Year\n3) Cause 113\n4) Cause\n5) State\n6) Deaths\n7) Age-adjusted Death Rate\nOption: ";
    cin >> option;
    cout << endl;
    if (option == 1)
    {
        RedBlackNode<int>* RBroot = id_wise_RBinsertion();
        add_address(RBroot);

        //add update and query functionality
        cout << "1) Search\n2) Updation\n3) Deletion\nOption: ";
        cin >> idin;
        cout << endl;
        if (idin == 1)
        {
            cout << "Enter the ID on which you want to perform Searching: \nOption: ";
            cin >> search_op;
            cout << endl;
            ifstream id_wise;
            string dest = to_string(search_op) + ".txt";
            id_wise.open(dest);
            if (id_wise.fail())
            {
                cout << "not found!!" << endl;
            }
            string id = "";
            string year = "";
            string cause_113 = "";
            string cause = "";
            string state = "";
            string deaths = "";
            string death_rate = "";
            string left_child = "";
            string right_child = "";
            while (!id_wise.eof() || !id_wise.fail())
            {
                getline(id_wise, id);
                getline(id_wise, year);
                getline(id_wise, cause_113);
                getline(id_wise, cause);
                getline(id_wise, state);
                getline(id_wise, deaths);
                getline(id_wise, death_rate);
                getline(id_wise, left_child);
                getline(id_wise, right_child);
            }
            cout << "------------------------------------------------------------------" << endl;
            cout << "ID         = " << search_op << endl;
            cout << "Year       = " << year << endl;
            cout << "Cause 113  = " << cause_113 << endl;
            cout << "Cause      = " << cause << endl;
            cout << "State      = " << state << endl;
            cout << "Deaths     = " << deaths << endl;
            cout << "Death Rate = " << death_rate << endl;
            cout << "Left Child = " << left_child << endl;
            cout << "Right Child= " << right_child << endl;
            cout << "------------------------------------------------------------------" << endl;
        }
        else if (idin == 2)
        {
            int op, col_op;
            cout << "Enter the ID you want to Update: ";   
            cin >> op;
            ifstream id_wise;
            string dest = to_string(op) + ".txt";
            id_wise.open(dest);
            if (id_wise.fail())
            {
                cout << "not found!!" << endl;
            }
            cout << "Enter the column number on which you want to perform Updation:\n1) Year\n2) 113 Cause\n3) Cause Name\n4) State\n5) Deaths\n6) Age-adjusted Death Rate\nOption: ";
            cin >> col_op;
            if (col_op == 1)
            {
                cout << "Enter the New Year: ";
                int yee;
                cin >> yee;
                string id = "";
                string year = "";
                string cause_113 = "";
                string cause = "";
                string state = "";
                string deaths = "";
                string death_rate = "";
                string left_child = "";
                string right_child = "";
                getline(id_wise, id);
                while (!id_wise.eof())
                {

                    getline(id_wise, year);
                    getline(id_wise, cause_113);
                    getline(id_wise, cause);
                    getline(id_wise, state);
                    getline(id_wise, deaths);
                    getline(id_wise, death_rate);
                    getline(id_wise, left_child);
                    getline(id_wise, right_child);

                }
                id_wise.close();
                ofstream write;
                write.open(dest);
                write << id << endl;
                write << to_string(yee) << endl;
                write << cause_113 << endl;
                write << cause << endl;
                write << state << endl;
                write << deaths << endl;
                write << death_rate << endl;
                write << left_child << endl;
                write << right_child << endl;
            }
            if (col_op == 2)
            {
                cout << "Enter the New Cause 113: ";
                string newCause;
                cin >> newCause;
                string id = "";
                string year = "";
                string cause_113 = "";
                string cause = "";
                string state = "";
                string deaths = "";
                string death_rate = "";
                string left_child = "";
                string right_child = "";
                getline(id_wise, id);
                while (!id_wise.eof())
                {

                    getline(id_wise, year);
                    getline(id_wise, cause_113);
                    getline(id_wise, cause);
                    getline(id_wise, state);
                    getline(id_wise, deaths);
                    getline(id_wise, death_rate);
                    getline(id_wise, left_child);
                    getline(id_wise, right_child);

                }
                id_wise.close();
                ofstream write;
                write.open(dest);
                write << id << endl;
                write << year << endl;
                write << newCause << endl;
                write << cause << endl;
                write << state << endl;
                write << deaths << endl;
                write << death_rate << endl;
                write << left_child << endl;
                write << right_child << endl;
            }
            if (col_op == 3)
            {
                cout << "Enter the New Cause: ";
                string newCause;
                cin >> newCause;
                string id = "";
                string year = "";
                string cause_113 = "";
                string cause = "";
                string state = "";
                string deaths = "";
                string death_rate = "";
                string left_child = "";
                string right_child = "";
                getline(id_wise, id);
                while (!id_wise.eof())
                {

                    getline(id_wise, year);
                    getline(id_wise, cause_113);
                    getline(id_wise, cause);
                    getline(id_wise, state);
                    getline(id_wise, deaths);
                    getline(id_wise, death_rate);
                    getline(id_wise, left_child);
                    getline(id_wise, right_child);

                }
                id_wise.close();
                ofstream write;
                write.open(dest);
                write << id << endl;
                write << year << endl;
                write << cause_113 << endl;
                write << newCause << endl;
                write << state << endl;
                write << deaths << endl;
                write << death_rate << endl;
                write << left_child << endl;
                write << right_child << endl;
            }
            if (col_op == 4)
            {
                cout << "Enter the New State: ";
                string newCause;
                cin >> newCause;
                string id = "";
                string year = "";
                string cause_113 = "";
                string cause = "";
                string state = "";
                string deaths = "";
                string death_rate = "";
                string left_child = "";
                string right_child = "";
                getline(id_wise, id);
                while (!id_wise.eof())
                {

                    getline(id_wise, year);
                    getline(id_wise, cause_113);
                    getline(id_wise, cause);
                    getline(id_wise, state);
                    getline(id_wise, deaths);
                    getline(id_wise, death_rate);
                    getline(id_wise, left_child);
                    getline(id_wise, right_child);

                }
                id_wise.close();
                ofstream write;
                write.open(dest);
                write << id << endl;
                write << year << endl;
                write << cause_113 << endl;
                write << cause << endl;
                write << newCause << endl;
                write << deaths << endl;
                write << death_rate << endl;
                write << left_child << endl;
                write << right_child << endl;
            }
            if (col_op == 5)
            {
                cout << "Enter the New Death: ";
                string newCause;
                cin >> newCause;
                string id = "";
                string year = "";
                string cause_113 = "";
                string cause = "";
                string state = "";
                string deaths = "";
                string death_rate = "";
                string left_child = "";
                string right_child = "";
                getline(id_wise, id);
                while (!id_wise.eof())
                {

                    getline(id_wise, year);
                    getline(id_wise, cause_113);
                    getline(id_wise, cause);
                    getline(id_wise, state);
                    getline(id_wise, deaths);
                    getline(id_wise, death_rate);
                    getline(id_wise, left_child);
                    getline(id_wise, right_child);

                }
                id_wise.close();
                ofstream write;
                write.open(dest);
                write << id << endl;
                write << year << endl;
                write << cause_113 << endl;
                write << cause << endl;
                write << state << endl;
                write << newCause << endl;
                write << death_rate << endl;
                write << left_child << endl;
                write << right_child << endl;
            }
            if (col_op == 6)
            {
                cout << "Enter the new Age-adjusted Death Rate: ";
                string newCause;
                cin >> newCause;
                string id = "";
                string year = "";
                string cause_113 = "";
                string cause = "";
                string state = "";
                string deaths = "";
                string death_rate = "";
                string left_child = "";
                string right_child = "";
                getline(id_wise, id);
                while (!id_wise.eof())
                {

                    getline(id_wise, year);
                    getline(id_wise, cause_113);
                    getline(id_wise, cause);
                    getline(id_wise, state);
                    getline(id_wise, deaths);
                    getline(id_wise, death_rate);
                    getline(id_wise, left_child);
                    getline(id_wise, right_child);

                }
                id_wise.close();
                ofstream write;
                write.open(dest);
                write << id << endl;
                write << year << endl;
                write << cause_113 << endl;
                write << cause << endl;
                write << state << endl;
                write << deaths << endl;
                write << newCause << endl;
                write << left_child << endl;
                write << right_child << endl;
            }
        }
        else
        {
        cout << " Error!!!" << endl;
        }
        

        //cout krwa de yahan sab kuch is se death rate tak usi format mien 
    }
    if (option == 2)
    {
        RedBlackNode<int>* RBroot = year_wise_insertion();
        add_address(RBroot);
        cout << "Enter the Year on which you want to perform searching: \nOption: ";
        cin >> search_op;
        cout << endl;
        ifstream id_wise;
        string dest = to_string(search_op) + ".txt";
        id_wise.open(dest);
        if (id_wise.fail())
        {
            cout << "not found!!" << endl;
        }
        string id = "";
        string year = "";
        string cause_113 = "";
        string cause = "";
        string state = "";
        string deaths = "";
        string death_rate = "";
        string left_child = "";
        string right_child = "";
        while (!id_wise.eof() || !id_wise.fail())
        {
            getline(id_wise, id);
            getline(id_wise, year);
            getline(id_wise, cause_113);
            getline(id_wise, cause);
            getline(id_wise, state);
            getline(id_wise, deaths);
            getline(id_wise, death_rate);
           // getline(id_wise, left_child);
            //getline(id_wise, right_child);
            cout << "------------------------------------------------------------------" << endl;
            cout << "ID         = " << id << endl;
            cout << "Year       = " << year << endl;
            cout << "Cause 113  = " << cause_113 << endl;
            cout << "Cause      = " << cause << endl;
            cout << "State      = " << state << endl;
            cout << "Deaths     = " << deaths << endl;
            cout << "Death Rate = " << death_rate << endl;
            //cout << "Left Child = " << left_child << endl;
            //cout << "Right Child= " << right_child << endl;
            cout << "------------------------------------------------------------------" << endl;
        }
        
    }
    if (option == 3)
    {
        RedBlackNode<string>* RBroot = cause113_wise_insertion();
        add_address_string(RBroot);
        cout << "Enter the Cause 113 on which you want to perform searching: \nOption: ";
        cin >> search_op;
        cout << endl;
        ifstream id_wise;
        string dest = to_string(search_op) + ".txt";
        id_wise.open(dest);
        if (id_wise.fail())
        {
            cout << "not found!!" << endl;
        }
        string id = "";
        string year = "";
        string cause_113 = "";
        string cause = "";
        string state = "";
        string deaths = "";
        string death_rate = "";
        string left_child = "";
        string right_child = "";
        while (!id_wise.eof() || !id_wise.fail())
        {
            getline(id_wise, id);
            getline(id_wise, year);
            getline(id_wise, cause_113);
            getline(id_wise, cause);
            getline(id_wise, state);
            getline(id_wise, deaths);
            getline(id_wise, death_rate);
            //getline(id_wise, left_child);
            //getline(id_wise, right_child);
            cout << "------------------------------------------------------------------" << endl;
            cout << "ID         = " << id << endl;
            cout << "Year       = " << year << endl;
            cout << "Cause 113  = " << cause_113 << endl;
            cout << "Cause      = " << cause << endl;
            cout << "State      = " << state << endl;
            cout << "Deaths     = " << deaths << endl;
            cout << "Death Rate = " << death_rate << endl;
            //cout << "Left Child = " << left_child << endl;
            //cout << "Right Child= " << right_child << endl;
            cout << "------------------------------------------------------------------" << endl;
        }
        
    }
    if (option == 4)
    {
        RedBlackNode<string>* RBroot = cause_wise_insertion();
        add_address_string(RBroot);
        cout << "Enter the Cause on which you want to perform searching: \nOption: ";
        cin >> search_op;
        cout << endl;
        ifstream id_wise;
        string dest = to_string(search_op) + ".txt";
        id_wise.open(dest);
        if (id_wise.fail())
        {
            cout << "not found!!" << endl;
        }
        string id = "";
        string year = "";
        string cause_113 = "";
        string cause = "";
        string state = "";
        string deaths = "";
        string death_rate = "";
        string left_child = "";
        string right_child = "";
        while (!id_wise.eof() || !id_wise.fail())
        {
            getline(id_wise, id);
            getline(id_wise, year);
            getline(id_wise, cause_113);
            getline(id_wise, cause);
            getline(id_wise, state);
            getline(id_wise, deaths);
            getline(id_wise, death_rate);
            //getline(id_wise, left_child);
            //getline(id_wise, right_child);
            cout << "------------------------------------------------------------------" << endl;
            cout << "ID         = " << id << endl;
            cout << "Year       = " << year << endl;
            cout << "Cause 113  = " << cause_113 << endl;
            cout << "Cause      = " << cause << endl;
            cout << "State      = " << state << endl;
            cout << "Deaths     = " << deaths << endl;
            cout << "Death Rate = " << death_rate << endl;
            //cout << "Left Child = " << left_child << endl;
            //cout << "Right Child= " << right_child << endl;
            cout << "------------------------------------------------------------------" << endl;
        }
    }
    if (option == 5)
    {
        RedBlackNode<string>* RBroot = state_wise_insertion();
        add_address_string(RBroot);
        cout << "Enter the State on which you want to perform searching: \nOption: ";
        cin >> search_op;
        cout << endl;
        ifstream id_wise;
        string dest = to_string(search_op) + ".txt";
        id_wise.open(dest);
        if (id_wise.fail())
        {
            cout << "not found!!" << endl;
        }
        string id = "";
        string year = "";
        string cause_113 = "";
        string cause = "";
        string state = "";
        string deaths = "";
        string death_rate = "";
        string left_child = "";
        string right_child = "";
        while (!id_wise.eof() || !id_wise.fail())
        {
            getline(id_wise, id);
            getline(id_wise, year);
            getline(id_wise, cause_113);
            getline(id_wise, cause);
            getline(id_wise, state);
            getline(id_wise, deaths);
            getline(id_wise, death_rate);
            //getline(id_wise, left_child);
            //getline(id_wise, right_child);
            cout << "------------------------------------------------------------------" << endl;
            cout << "ID         = " << id << endl;
            cout << "Year       = " << year << endl;
            cout << "Cause 113  = " << cause_113 << endl;
            cout << "Cause      = " << cause << endl;
            cout << "State      = " << state << endl;
            cout << "Deaths     = " << deaths << endl;
            cout << "Death Rate = " << death_rate << endl;
            //cout << "Left Child = " << left_child << endl;
            //cout << "Right Child= " << right_child << endl;
            cout << "------------------------------------------------------------------" << endl;
        }
    }
    if (option == 6)
    {
        RedBlackNode<int>* RBroot = death_wise_insertion();
        add_address(RBroot);
        cout << "Enter the Deaths on which you want to perform searching: \nOption: ";
        cin >> search_op;
        cout << endl;
        ifstream id_wise;
        string dest = to_string(search_op) + ".txt";
        id_wise.open(dest);
        if (id_wise.fail())
        {
            cout << "not found!!" << endl;
        }
        string id = "";
        string year = "";
        string cause_113 = "";
        string cause = "";
        string state = "";
        string deaths = "";
        string death_rate = "";
        string left_child = "";
        string right_child = "";
        while (!id_wise.eof() || !id_wise.fail())
        {
            getline(id_wise, id);
            getline(id_wise, year);
            getline(id_wise, cause_113);
            getline(id_wise, cause);
            getline(id_wise, state);
            getline(id_wise, deaths);
            getline(id_wise, death_rate);
            //getline(id_wise, left_child);
            //getline(id_wise, right_child);
        }
        cout << "------------------------------------------------------------------" << endl;
        cout << "ID         = " << search_op << endl;
        cout << "Year       = " << year << endl;
        cout << "Cause 113  = " << cause_113 << endl;
        cout << "Cause      = " << cause << endl;
        cout << "State      = " << state << endl;
        cout << "Deaths     = " << deaths << endl;
        cout << "Death Rate = " << death_rate << endl;
        //cout << "Left Child = " << left_child << endl;
        //cout << "Right Child= " << right_child << endl;
        cout << "------------------------------------------------------------------" << endl;
    }
    if (option == 7)
    {
        RedBlackNode<float>* RBroot = deathrate_wise_insertion();
        add_address_float(RBroot);
        cout << "Enter the Death Rate on which you want to perform searching: \nOption: ";
        cin >> search_op;
        cout << endl;
        ifstream id_wise;
        string dest = to_string(search_op) + ".txt";
        id_wise.open(dest);
        if (id_wise.fail())
        {
            cout << "not found!!" << endl;
        }
        string id = "";
        string year = "";
        string cause_113 = "";
        string cause = "";
        string state = "";
        string deaths = "";
        string death_rate = "";
        string left_child = "";
        string right_child = "";
        while (!id_wise.eof() || !id_wise.fail())
        {
            getline(id_wise, id);
            getline(id_wise, year);
            getline(id_wise, cause_113);
            getline(id_wise, cause);
            getline(id_wise, state);
            getline(id_wise, deaths);
            getline(id_wise, death_rate);
            //getline(id_wise, left_child);
            //getline(id_wise, right_child);
            cout << "------------------------------------------------------------------" << endl;
            cout << "ID         = " << id << endl;
            cout << "Year       = " << year << endl;
            cout << "Cause 113  = " << cause_113 << endl;
            cout << "Cause      = " << cause << endl;
            cout << "State      = " << state << endl;
            cout << "Deaths     = " << deaths << endl;
            cout << "Death Rate = " << death_rate << endl;
            //cout << "Left Child = " << left_child << endl;
            //cout << "Right Child= " << right_child << endl;
            cout << "------------------------------------------------------------------" << endl;
        }
    }
}
#endif