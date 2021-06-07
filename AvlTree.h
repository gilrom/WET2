#ifndef AVLTREE_H
#define AVLTREE_H

#include "exceptions.h"

namespace wet1
{
    //Generic tree node class
    template<typename T>
    class AvlTreeNode {
        T data;
        AvlTreeNode* parent;
        AvlTreeNode* left;
        AvlTreeNode* right;
        int height;
        int num_of_subtree;

    public:
        AvlTreeNode(const T& data) : data(data) , parent(nullptr),left(nullptr), right(nullptr), height(0), num_of_subtree(1) {}
        AvlTreeNode(const T& data , AvlTreeNode<T>* father ) : data(data) , parent(father), left(nullptr),
                                                                right(nullptr), height(0), num_of_subtree(1) {}

        // Building a Tree at O(max-min) using a sorted aaray
        AvlTreeNode* buildATree(T* arr, int max, int min) {
            if ((max-min) < 0 ) return nullptr;
            int mid = (max+min)/2;
            AvlTreeNode* node = new AvlTreeNode<T>(arr[mid]);

            node->left = buildATree(arr, mid-1,min);
            if (node->left) node->left->parent = node;
            int left_height = node->left ? node->left->height : -1 ;
            node->right = buildATree(arr, max,mid+1);
            if (node->right) node->right->parent = node;
            int right_height = node->right ? node->right->height : -1 ;
            node->height = right_height > left_height ? right_height : left_height;
            node->height++;
            node->num_of_subtree= 1 + max - min;
            return node;
        }
        ~AvlTreeNode() {}
        AvlTreeNode<T>* get_left() {
            return this->left ? this->left : nullptr ;
        }
        void set_left(AvlTreeNode<T>* node) {
            this->left = node;
        }
        AvlTreeNode<T>* get_right() {
            return this->right ? this->right : nullptr;
        }
        void set_right(AvlTreeNode<T>* node) {
            this->right = node;
        }
        AvlTreeNode<T>* get_parent() {
            return this->parent ? this->parent : nullptr ;
        }
        void set_parent(AvlTreeNode<T>* node) {
            this->parent = node;
        }
        int get_height(){
            return this->height ? this->height : -1;
        }
        int get_left_height(){
            return left ? left->height : -1;
        }
        int get_right_height(){
            return right ? right->height : -1;
        }
        void set_height(int new_height){
            this->height = new_height;
        }
        void set_num_of_subtree(int new_num_of_subtree){
            this->num_of_subtree = new_num_of_subtree;
        }
        int get_num_of_subtree(){
            return this->num_of_subtree ? this->num_of_subtree : 0;
        }
        int get_left_num_of_subtree(){
            return left ? left->num_of_subtree : 0;
        }
        int get_right_num_of_subtree(){
            return right ? right->num_of_subtree : 0;
        }
        T& get_data() {
            return this->data;
        }
        T& get_left_data() {
            return left->get_data();
        }
        T& get_right_data() {
            return right->get_data();
        }
        void set_data( T& new_data) {
            this->data = new_data;
        }
        void destroyTree(AvlTreeNode<T>* root) {
            if (root == nullptr ) return;
            destroyTree(root->left);
            destroyTree(root->right);
            delete root;
        }
    };

    template<typename T, typename Comp>
    class AvlTree {
        AvlTreeNode<T>* root;
        Comp compFunc;
        AvlTreeNode<T>* youngest;
        AvlTreeNode<T>* oldest;
        int max(int x, int y) {
            return ( x > y ) ? x : y;
        }

    public:
        AvlTree() : root(nullptr),compFunc(), youngest(nullptr), oldest(nullptr) {}
        AvlTree(T* arr, int max , int min) : root(nullptr),compFunc(), youngest(nullptr) {
            root = root->buildATree(arr,max,min);
            youngest = get_younget_child(root);
            oldest = get_oldest_child(root);
        }
        ~AvlTree() {
            root->destroyTree(root);
        };

        AvlTreeNode<T>* getRoot() {
            return this->root;
        }
        void set_root(AvlTreeNode<T>* new_root) {
            root = new_root;
        }

    private:

        AvlTreeNode<T>* find_in_tree(AvlTreeNode<T>* node , const T& data_to_find ) const {
            if (!node)
                return nullptr;
            if (compFunc(data_to_find, node->get_data()))
                return find_in_tree(node->get_left(),data_to_find);
            else if (compFunc(node->get_data(), data_to_find))
                return find_in_tree(node->get_right(),data_to_find);
            else return node;
            return nullptr; //should never get here
        }

        AvlTreeNode<T>* find_rank_in_tree(AvlTreeNode<T>* node , const T& rank ) const
        {
            if (!node) return nullptr;
            int left_subtree = node->get_left_num_of_subtree();
            if ( left_subtree == (rank-1)) return node;
            else if ( left_subtree > (rank-1))
                return find_rank_in_tree(node->get_left(),rank);
            else return find_rank_in_tree(node->get_right(),(rank-left_subtree-1));
            return nullptr; //should never get here
        }


        AvlTreeNode<T>* rightRotate(AvlTreeNode<T>* y)
        {
            AvlTreeNode<T>* x = y->get_left();
            AvlTreeNode<T>* z = x ? x->get_right() : nullptr ;
            x->set_right(y);
            x->set_parent(y->get_parent());
            y->set_parent(x);
            y->set_left(z);
            if (z) z->set_parent(y);
            y->set_height(1 + max(y->get_left_height(),y->get_right_height()));
            y->set_num_of_subtree(1+y->get_left_num_of_subtree()+y->get_right_num_of_subtree());
            x->set_height(1 + max(x->get_left_height(),x->get_right_height()));
            x->set_num_of_subtree(1+x->get_left_num_of_subtree()+x->get_right_num_of_subtree());

            return x;
        }


        AvlTreeNode<T>* leftRotate(AvlTreeNode<T>* x)
        {
            AvlTreeNode<T>* y = x->get_right();
            AvlTreeNode<T>* z = y ? y->get_left() : nullptr;
            y->set_left(x);
            y->set_parent(x->get_parent());
            x->set_parent(y);
            x->set_right(z);
            if (z) z->set_parent(x);
            x->set_height(1 + max(x->get_left_height(),x->get_right_height()));
            x->set_num_of_subtree(1+x->get_left_num_of_subtree()+x->get_right_num_of_subtree());
            y->set_height(1 + max(y->get_left_height(),y->get_right_height()));
            y->set_num_of_subtree(1+y->get_left_num_of_subtree()+y->get_right_num_of_subtree());

            return y;
        }

        AvlTreeNode<T>* get_younget_child(AvlTreeNode<T>* node) {
            if(!node)
                return nullptr;
            if ( node->get_left() == nullptr )
                return node;
            else return get_younget_child(node->get_left());
        }

        AvlTreeNode<T>* get_oldest_child(AvlTreeNode<T>* node) {
            if(!node)
                return nullptr;
            if ( node->get_right() == nullptr )
                return node;
            else return get_oldest_child(node->get_right());
        }

        // Recursive insert function which find the right place to insert and then return the
        // corrected root all the way up
        AvlTreeNode<T>* insert( const T& data , AvlTreeNode<T>* node , AvlTreeNode<T>* parent_node ) {
            if (node == nullptr)
                return new AvlTreeNode<T>(data,parent_node);
            if ( compFunc(data,node->get_data()))
                node->set_left(insert(data,node->get_left(),node));
            else if (compFunc(node->get_data(),data))
                node->set_right(insert(data,node->get_right(),node));
            else return node;

            node->set_height(1 + max(node->get_left_height(),node->get_right_height()));
            node->set_num_of_subtree(1+node->get_left_num_of_subtree()+node->get_right_num_of_subtree());

            int balance = node->get_left_height() - node->get_right_height();

            // LL
            if (balance > 1 && compFunc(data,node->get_left_data()) )
                return rightRotate(node);
            // RR
            if (balance < -1 && compFunc(node->get_right_data(),data))
                return leftRotate(node);
            // LR
            if (balance > 1 && compFunc(node->get_left_data(),data))
            {
                node->set_left(leftRotate(node->get_left()));
                return rightRotate(node);
            }
            // RL
            if (balance < -1 && compFunc(data,node->get_right_data()))
            {
                node->set_right(rightRotate(node->get_right()));
                return leftRotate(node);
            }
            return node;

        }

        int get_blance (AvlTreeNode<T>* node) {
            if (!node) return 0;
            int balance = node->get_left_height() - node->get_right_height();
            return balance;
        }

        // Recursive delete function which finds the requested element to delete and then returns
        // the corrected roots all the way up using rotations to fix the balance
        AvlTreeNode<T>* deleteNode(AvlTreeNode<T>* node, const T& data)
        {

            if (node == nullptr)
                return node;

            if ( compFunc(data,node->get_data()))
                node->set_left(deleteNode(node->get_left(),data));
            else if( compFunc(node->get_data(),data) )
                node->set_right(deleteNode(node->get_right(),data));
            else
            {
                // node with max one child
                if( (node->get_left() == nullptr ) || ( node->get_right() == nullptr) )
                {
                    AvlTreeNode<T>* temp = node->get_left() ? node->get_left() : node->get_right() ;

                    // No child case
                    if (temp == nullptr)
                    {
                        temp = node;
                        node = nullptr;
                    }
                    else // One child case
                    {
                        AvlTreeNode<T>* temp_parent = node->get_parent();
                        *node = *temp;
                        node->set_parent(temp_parent);
                    }

                    delete temp;
                }
                else
                {
                    // node with two children
                    AvlTreeNode<T>* temp = get_younget_child(node->get_right());
                    node->set_data(temp->get_data());
                    T temp_data = temp->get_data();
                    node->set_right(deleteNode(node->get_right(),temp_data));
                }
            }

            if (node == nullptr)
                return node;

            node->set_height(1+ max(node->get_left_height(),node->get_right_height()));
            node->set_num_of_subtree(1+node->get_left_num_of_subtree()+node->get_right_num_of_subtree());

            int balance = node->get_left_height() - node->get_right_height();

            // LL
            if (balance > 1 && get_blance(node->get_left()) >= 0 )
                return rightRotate(node);
            // RR
            if (balance < -1 && get_blance(node->get_right()) <= 0 )
                return leftRotate(node);
            // LR
            if (balance > 1 && get_blance(node->get_left()) < 0 )
            {
                node->set_left(leftRotate(node->get_left()));
                return rightRotate(node);
            }
            // RL
            if (balance < -1 && get_blance(node->get_right()) > 0 )
            {
                node->set_right(rightRotate(node->get_right()));
                return leftRotate(node);
            }
            return node;
        }

    public:

        // Wrap functions for the user in order to perform the common actions of a tree


        T find(const T& data) const
        {
            AvlTreeNode<T>* node = find_in_tree(root, data);
            if(!node)
                throw NotFound();
            return node->get_data();
        }
        T find_rank(const T& data) const
        {
            AvlTreeNode<T>* node = find_rank_in_tree(root, data);
            if(!node)
                throw NotFound();
            return node->get_data();
        }

        void deleteElement(const T& data) {
            root = deleteNode(root,data);
            youngest = get_younget_child(root);
            oldest = get_oldest_child(root);
        }

        void addElement(const T& data) {
            root = insert(data, this->root, this->root);
            youngest = get_younget_child(root);
            oldest = get_oldest_child(root);
        }

        T getOldestData() const
        {
            if(!oldest)
                throw EmptyTree();
            return oldest->get_data();
        }

        T getYoungestData() const
        {
            if(!youngest)
                throw EmptyTree();
            return youngest->get_data();
        }

        AvlTreeNode<T>* getYoungestNode()
        {
            return youngest;
        }
    };
}
#endif //AVLTREE_H
