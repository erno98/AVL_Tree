//
// Created by Ernest Pokropek
//

/*
 * The presented below class is an AVL binary tree data structure, with two templates
 * as parameters. The tree balances itself after any change, using rotations.
 * Most of the public methods are implemented using the private recursive
 * ones with the same name.
 *
 * The data structure is similar to Python's dictionary, although once
 * setting up the template parameters, the DS can store only two types of
 * values.
 *
 */



#include <stdlib.h>
#include <iomanip>
#include <string>
#include <iostream>

#ifndef EADS3_DICTIONARY_H
#define EADS3_DICTIONARY_H




template<typename Key, typename Info>
class Dictionary {

    struct Node {
        Key key;
        Info info;
        Node* right;
        Node* left;
        Node* parent;
        int balance_factor;
        int height;


        //node constructors

        Node(Key nK, Info nI): key(nK),
                               info (nI),
                               right(nullptr),
                               left(nullptr),
                               balance_factor(0),
                               height(0) {};

        Node(Key nK, Info nI, int bf, int h): key(nK),
                                              info(nI),
                                              balance_factor(bf),
                                              height(h),
                                              right(nullptr),
                                              left(nullptr) {};
    };

    Node* root;



    //recursive insert used in public one
    Node* insert(const Key &newKey, const Info &newInfo, Node* root);

    //recursive remove used in public one
    Node* remove(const Key &key, Node* root);

    //methods returning maximal and minimal values of key
    Key get_max(Node *root);
    Key get_min(Node* root);

    //method returning height of the tree from initial node root
    //assumption: height of 1 element's tree is equal to 1
    unsigned int height(Node* root);

    //recursive print used in public one, post order print
    void print(Node* root);

    //recursive clear used in public one
    void clear(Node *root);

    //recursive method to copy the tree
    Node* copy(Node* root);

    //returns a pointer to node of given key from initial node root
    Node* search(const Key &aKey, Node* root);

    //updates the balance_factor parameter
    void update_node(Node *node);

    //balances the tree from initial node root
    Node* balance(Node *root);

    //rotations used in tree balancing
    Node* lRotate(Node* &destination);
    Node* rRotate(Node* &destination);
    Node* rlRotate(Node* &destination);
    Node* lrRotate(Node* &destination);
    Node* llRotate(Node* &destination);
    Node* rrRotate(Node* &destination);


public:

template<typename K, typename I>
    class Iterator {
        Node *iter;
    public:

        Iterator() { iter = nullptr; }

        Iterator(Node *element) {
            iter = element;
        }

        ~Iterator() {}

        Iterator(const Iterator &cc) { iter = cc.iter; }


        Iterator operator=(const Iterator &iterator) {
            if (this == &iterator) return *this;
            iter = iterator.iter;
            return *this;
        }

        Iterator operator+(int length) {
            if (length > 0)for (int i = 0; iter && iter->next && i < length; i++) iter = iter->next;
            return *this;
        }


        Iterator operator-(int length) {
            if (length > 0)for (int i = 0; iter && iter->next && i < length; i++) iter = iter->prev;
            return *this;
        }

        Iterator &operator++() {
            Node *p;

            if (iter == nullptr) {
                while (iter->left != nullptr) {
                    iter = iter->left;
                }
            } else if (iter->right != nullptr) {
                iter = iter->right;

                while (iter->left != nullptr) {
                    iter = iter->left;
                }
            } else {
                p = iter->parent;
                while (p != nullptr && iter == p->right) {
                    iter = p;
                    p = p->parent;
                }
                iter = p;
            }
            return *this;
        }


        const Iterator<K, I> operator++(int) {
            if (!iter) return *this;
            else {
                Node *p;
                auto *temporary = new Iterator(iter);
                if (iter == nullptr) {
                    while (iter->left != nullptr) {
                        iter = iter->left;
                    }
                } else if (iter->right != nullptr) {
                    iter = iter->right;

                    while (iter->left != nullptr) {
                        iter = iter->left;
                    }
                } else {
                    p = iter->parent;
                    while (p != nullptr && iter == p->right) {
                        iter = p;
                        p = p->parent;
                    }
                    iter = p;
                }
                return *temporary;
            }
        }


        Iterator &operator--() {
            Node *p;

            if (iter == nullptr) {
                while (iter->right != nullptr) {
                    iter = iter->right;
                }
            } else if (iter->left != nullptr) {
                iter = iter->left;

                while (iter->right != nullptr) {
                    iter = iter->right;
                }
            } else {
                p = iter->parent;
                while (p != nullptr && iter == p->left) {
                    iter = p;
                    p = p->parent;
                }
                iter = p;
            }
            return *this;
        }


        const Iterator<K, I> operator--(int) {
            if (!iter) return *this;
            else {
                Node *p;
                auto *temporary = new Iterator(iter);
                if (iter == nullptr) {
                    while (iter->right != nullptr) {
                        iter = iter->right;
                    }
                } else if (iter->left != nullptr) {
                    iter = iter->left;

                    while (iter->right != nullptr) {
                        iter = iter->right;
                    }
                } else {
                    p = iter->parent;
                    while (p != nullptr && iter == p->left) {
                        iter = p;
                        p = p->parent;
                    }
                    iter = p;
                }
                return *temporary;
            }
        }


        bool operator==(Iterator iterator) const { return iter == iterator.iter; }


        bool operator!=(Iterator iterator) const { return iter != iterator.iter; }


        Node &operator*() const { return *iter; }


        Node *operator->() const { return iter; }


    };

    //inserts a new element to the tree, with given parameters
    void insert(const Key &newKey, const Info &newInfo);

    //removes an element from the tree by given key
    //if the element doesn't exist method passes
    void remove(const Key& key);

    //returns the height of the whole tree
    unsigned int height();

    //prints the contents of the tree
    void print();

    //clears the whole tree
    void clear();

    //returns true if the node of given key exists in the
    //tree, returns false otherwise
    bool exists(const Key &aKey);


    // default constructor
    Dictionary(){
        root = nullptr;
    }

    // default destructor
    ~Dictionary(){
        clear();
    }

    // copy constructor
    Dictionary(const Dictionary <Key, Info> &dict){
        this->root = nullptr;
        *this = dict;
    }

    // assignment operator
    Dictionary<Key, Info> &operator=(const Dictionary<Key, Info> &dict);


//********************************************************************************************

/*
 * pretty printing of the tree.
 * METHOD WAS TAKEN FROM:
 * https://stackoverflow.com/questions/801740/c-how-to-draw-a-binary-tree-to-the-console
 */

    int _print_t(Node *tree, int is_left, int offset, int depth, char s[20][255])
    {
        char b[20];
        int width = 5;

        if (!tree) return 0;

        sprintf(b, "(%03d)", tree->key);

        int left  = _print_t(tree->left,  1, offset,                depth + 1, s);
        int right = _print_t(tree->right, 0, offset + left + width, depth + 1, s);

#ifdef COMPACT
        for (int i = 0; i < width; i++)
        s[depth][offset + left + i] = b[i];

    if (depth && is_left) {

        for (int i = 0; i < width + right; i++)
            s[depth - 1][offset + left + width/2 + i] = '-';

        s[depth - 1][offset + left + width/2] = '.';

    } else if (depth && !is_left) {

        for (int i = 0; i < left + width; i++)
            s[depth - 1][offset - width/2 + i] = '-';

        s[depth - 1][offset + left + width/2] = '.';
    }
#else
        for (int i = 0; i < width; i++)
            s[2 * depth][offset + left + i] = b[i];

        if (depth && is_left) {

            for (int i = 0; i < width + right; i++)
                s[2 * depth - 1][offset + left + width/2 + i] = '-';

            s[2 * depth - 1][offset + left + width/2] = '+';
            s[2 * depth - 1][offset + left + width + right + width/2] = '+';

        } else if (depth && !is_left) {

            for (int i = 0; i < left + width; i++)
                s[2 * depth - 1][offset - width/2 + i] = '-';

            s[2 * depth - 1][offset + left + width/2] = '+';
            s[2 * depth - 1][offset - width/2 - 1] = '+';
        }
#endif

        return left + width + right;
    }

    void print_t()
    {
        char s[20][255];
        for (int i = 0; i < 20; i++)
            sprintf(s[i], "%80s", " ");

        _print_t(this->root, 0, 0, 0, s);

        for (int i = 0; i < 20; i++)
            printf("%s\n", s[i]);
    }

//********************************************************************************************

};


/***********************************************************************
*   IMPLEMENTATION
************************************************************************/



//--------------------------------------------------------------------------

template<typename Key, typename Info>
typename Dictionary<Key, Info>::Node* Dictionary<Key, Info>::insert(const Key &newKey, const Info &newInfo, Node* root) {


    //element already exists
    if(this->exists(newKey))
        return nullptr;

    //insertion
    if(!root)
        return new Node(newKey, newInfo);

    if(newKey > root->key)
        root->right = insert(newKey, newInfo, root->right);
    else if(newKey < root->key)
        root->left = insert(newKey, newInfo, root->left);

    //updating balance factor and balancing the tree
    update_node(root);
    return balance(root);



}

//--------------------------------------------------------------------------



template<typename Key, typename Info>
void Dictionary<Key, Info>::insert(const Key &newKey, const Info &newInfo) {

    //element already exists
    if(this->exists(newKey))
        return;


    this->root = insert(newKey, newInfo, this->root);



}

//--------------------------------------------------------------------------

template<typename Key, typename Info>
void Dictionary<Key, Info>::remove(const Key &key) {

    if(!exists(key))
        return;

    this->root = remove(key, this->root);

}

//--------------------------------------------------------------------------

template<typename Key, typename Info>
typename Dictionary<Key, Info>::Node *Dictionary<Key, Info>::remove(const Key &key, Dictionary::Node *root) {

    if(!root)
        return nullptr;

    if(key < root->key)
        root->left = remove(key, root->left);
    else if(key > root->key)
        root->right = remove(key, root->right);
    else{
        if(!root->left)
            return root->right;
        else if(!root->right)
            return root->left;
        else{
            if(root->left->height > root->right->height){
                Node *replace = search(get_max(root->left), root->left);
                root->info = replace->info;
                root->key = replace->key;

                root->left = remove(replace->key, root->left);
                delete replace;
            }
            else{
                Node *replace = search(get_min(root->right), root->right);
                root->info = replace->info;
                root->key = replace->key;

                root->right = remove(replace->key, root->right);
                delete replace;
            }
        }
    }

    update_node(root);
    return balance(root);
}


//--------------------------------------------------------------------------


template<typename Key, typename Info>
Key Dictionary<Key, Info>::get_max(Dictionary::Node *root) {

    if(!root->right)
        return root->key;

    return get_max(root->right);

}

//--------------------------------------------------------------------------

template<typename Key, typename Info>
Key Dictionary<Key, Info>::get_min(Dictionary::Node *root) {
    if(!root->left)
        return root->key;

    return get_max(root->left);
}

//--------------------------------------------------------------------------

template<typename Key, typename Info>
unsigned int Dictionary<Key, Info>::height(Node* root) {

    if(root == nullptr)
        return 0;

    unsigned int rightHeight = height(root->right);
    unsigned int leftHeight = height(root->left);

    return 1 + (rightHeight > leftHeight ? rightHeight : leftHeight);

}


//--------------------------------------------------------------------------


template<typename Key, typename Info>
unsigned int Dictionary<Key, Info>::height(){

    return height(this->root);

}

//--------------------------------------------------------------------------

template<typename Key, typename Info>
void Dictionary<Key, Info>::print(Node* root) {

    if(!root)
        return;

    print(root->left);
    print(root->right);

    std::cout << "{" << root->key << ": " << root->info << "}  ";


}


//--------------------------------------------------------------------------



template<typename Key, typename Info>
void Dictionary<Key, Info>::print(){

    if(!root) {
        std::cout << "Dictionary is empty." << std::endl;
        return;
    }


    print(this->root);
    std::cout << std::endl;

}


//--------------------------------------------------------------------------


template<typename Key, typename Info>
void Dictionary<Key, Info>::clear(Dictionary::Node *root) {

    if(!root)
        return;

    clear(root->left);
    clear(root->right);

    delete root;

}


//--------------------------------------------------------------------------


template<typename Key, typename Info>
void Dictionary<Key, Info>::clear() {

    clear(this->root);
    this->root = nullptr;

}


//--------------------------------------------------------------------------


template<typename Key, typename Info>
bool Dictionary<Key, Info>::exists(const Key &aKey) {

    return search(aKey, this->root) != nullptr;
}


//--------------------------------------------------------------------------


template<typename Key, typename Info>
typename Dictionary<Key, Info>::Node* Dictionary<Key, Info>::lRotate(Dictionary::Node *&destination) {

    Node *newParent = destination->right;
    destination->right = newParent->left;
    newParent->left = destination;

    update_node(destination);
    update_node(newParent);

    return newParent;

}

//--------------------------------------------------------------------------

template<typename Key, typename Info>
typename Dictionary<Key, Info>::Node* Dictionary<Key, Info>::rRotate(Dictionary::Node *&destination) {

    Node *newParent = destination->left;
    destination->left = newParent->right;
    newParent->right = destination;

    update_node(destination);
    update_node(newParent);

    return newParent;


}

//--------------------------------------------------------------------------

template<typename Key, typename Info>
typename Dictionary<Key, Info>::Node* Dictionary<Key, Info>::rlRotate(Dictionary::Node *&destination) {

    destination->right = rRotate(destination->right);
    return lrRotate(destination);

}

//--------------------------------------------------------------------------

template<typename Key, typename Info>
typename Dictionary<Key, Info>::Node* Dictionary<Key, Info>::lrRotate(Dictionary::Node *&destination) {

    destination->left = lRotate(destination);
    return rRotate(destination);

}

//--------------------------------------------------------------------------

template<typename Key, typename Info>
typename Dictionary<Key, Info>::Node* Dictionary<Key, Info>::llRotate(Dictionary::Node *&destination) {

    return rrRotate(destination);

}

//--------------------------------------------------------------------------

template<typename Key, typename Info>
typename Dictionary<Key, Info>::Node* Dictionary<Key, Info>::rrRotate(Dictionary::Node *&destination) {

    return lRotate(destination);


}

//--------------------------------------------------------------------------

template<typename Key, typename Info>
typename Dictionary<Key, Info>::Node *Dictionary<Key, Info>::balance(Dictionary::Node *root) {


    if(root->balance_factor < -1){
        if(root->left->balance_factor <= 0)

            // LEFT-LEFT ROTATION
            return llRotate(root);
        else

            //LEFT-RIGHT ROTATION
            return lrRotate(root);
    }
    else if(root->balance_factor > 1){

        if(root->right->balance_factor >= 0)\

            //RIGHT-RIGHT ROTATION
            return rrRotate(root);
        else
            //RIGHT-LEFT ROTATION
            return rlRotate(root);
    }


    return root;
}



//--------------------------------------------------------------------------


template<typename Key, typename Info>
Dictionary<Key, Info> &Dictionary<Key, Info>::operator=(const Dictionary<Key, Info> &dict) {

    clear();
    root = copy(dict->root);
    return *this;
}


//--------------------------------------------------------------------------


template<typename Key, typename Info>
void Dictionary<Key, Info>::update_node(Dictionary::Node *node) {

    int left_height = node->left ? node->left->height : -1;
    int right_height = node->right ? node->right->height : -1;

    node->height = (left_height > right_height) ? (1 + left_height) : (1 + right_height);
    node->balance_factor = right_height - left_height;
}


//--------------------------------------------------------------------------

template<typename Key, typename Info>
typename Dictionary<Key, Info>::Node *Dictionary<Key, Info>::copy(Dictionary::Node *root) {

    Node *ret = nullptr;

    if(root){
        ret = new Node(root->key, root->info, root->balance_factor, root->height);
        ret->left = copy(root->left);
        ret->right = copy(root->right);
    }

    return ret;

}

template<typename Key, typename Info>
typename Dictionary<Key, Info>::Node *Dictionary<Key, Info>::search(const Key &aKey, Dictionary::Node *root) {

        if(!root)
            return nullptr;

        if (root->key == aKey)
            return root;

        // Key is greater than root's key
        if (root->key < aKey)
            return search(aKey, root->right);

        // Key is smaller than root's key
        return search(aKey, root->left);
}



//--------------------------------------------------------------------------



#endif //EADS3_DICTIONARY_H
