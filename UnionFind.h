#ifndef UNION_FIND
#define UNION_FIND

/*Union_find with data merging support*/

#include "dynamic_array.h"
#include "exceptions.h"

namespace wet2
{
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class Organ
    {
        Organ* father;
        /*relevant only for root organs*/
        int groupNum;
        public:
            /*ctor*/
            Organ(int num) : father(nullptr), groupNum(num) {}

            Organ* getFather() const{
                return father;
            }
            void setFather(Organ* to_set){
                if (father != nullptr)
                    groupNum = -1;
                father = to_set;
            }
            bool isRoot() const{
                return !father;
            }
            int getGroupNum() const{
                return groupNum;
            }
    };
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

    template<class T>
    class Group
    {
        T data;
        int numOfMembers, groupNum;
        Organ* root;
        public:
            /*ctor*/
            Group(const T& supp_data, int members, int group_num, Organ* root_organ) : data(supp_data),
             numOfMembers(members), groupNum(group_num), root(root_organ) {}

            T getData() const{
                return data;
            }
            int getNumOfMembers() const{
                return numOfMembers;
            }
            int getGroupNum() const{
                return groupNum;
            }
            void setRootOrg(Organ* to_set){
                root = to_set;
            }
            Organ* getRoot() const{
                return root;
            }
    };
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

    template <class T, class MergeFunc>
    class UnionFind{
    private:
        int organNum;
        DynamicArray<Organ*> organs;
        DynamicArray<Group<T>*> groups;
        /*An object func that merges data and return the merged data*/
        MergeFunc merge;

        /*aid func for shrinking organ find path*/
        void shrink(Organ* org, Organ* root){
            Organ* tmp = nullptr;
            while (org != root)
            {
                tmp = org;
                org = org->getFather();
                tmp->setFather(root);
            }
        }

    public:
        /*ctor*/
        UnionFind() : organNum(0), organs(), groups(), merge(){}

        /*dtor (o(n))*/
        ~UnionFind(){
            for(int i = 0; i < organs.get_current_size();i++){
                delete organs[i];
            }
            for(int i = 0; i < groups.get_current_size(); i++){
                delete groups[i];
            }
        }

        /**
         * Adds organ to the union
         * the organ will be in a group of his own.
         * @param data the data of the organ
         * @throw std::bad_alloc() in case of allocation error
        */
        void addOrgan(const T& data){
            Organ* new_organ = new Organ(organNum);
            Group<T>* new_group = new Group<T>(data, 1, organNum, new_organ);
            organs.push(new_organ);
            groups.push(new_group);
            organNum++;
        }

        /**
         * Unite group number p and group number q.
         * @param p first group number
         * @param q second group number
         * @return the new united group data
         * */
        Group<T>&  unionGroups(int p , int q){
            T merged_data = merge(groups[p]->getData(), groups[q]->getData());
            int p_members_num = groups[p]->getNumOfMembers();
            int q_members_num = groups[q]->getNumOfMembers();
            /*We will unite the smaller group with the larger group(for better complexity)*/
            if(p_members_num > q_members_num){
                Group<T>* united_group = new Group<T>(merged_data, p_members_num + q_members_num, 
                groups[p]->getGroupNum() , groups[p]->getRoot());
                Organ* q_root = groups[q]->getRoot();
                q_root->setFather(groups[p]->getRoot());
                delete groups[q];
                delete groups[p];
                groups[p] = united_group;
                groups[q] = nullptr;
                return *groups[p];
            }
            else{
                Group<T>* united_group = new Group<T>(merged_data, p_members_num + q_members_num, 
                groups[q]->getGroupNum(), groups[q]->getRoot());
                Organ* p_root = groups[p]->getRoot();
                p_root->setFather(groups[q]->getRoot());
                delete groups[q];
                delete groups[p];
                groups[q] = united_group;
                groups[p] = nullptr;
                return *groups[q];
            }
        }

        /**
         * find in the given organ and return it's group
         * @param i organ number
         * @return the organ's Group
        */
        Group<T>& find (int i){
            if(i >= organs.get_current_size())
                throw NotExist();
            Organ* org = organs[i];
            Organ* root = org;
            while (root->getFather() != nullptr){
                root = root->getFather();
            }
            shrink(org, root);
            int group_num = root->getGroupNum();
            return *groups[group_num];
        }
    };
}
#endif