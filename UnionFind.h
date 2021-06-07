#ifndef UNION_FIND
#define UNION_FIND


namespace wet2
{
    template<class T>
    class Organ
    {
        T data;
        Organ* father;
        /*only for root organs, otherwise groupNum is -1*/
        int groupNum;
        public:
            Organ(const T& supp_data, int num) : data(supp_data), father(nullptr), groupNum(num){}
            Organ* getFather(){
                return father;
            }
            void setFather(Organ* to_set){
                if (father != nullptr)
                    groupNum = -1;
                father = to_set;
            }
    };

    template<class T>
    class Group
    {
        T data;
        int numOfMembers;
        public:
            Group(const T& supp_data, int members) : data(supp_data), numOfMembers(members) {}
            
    }


}

#endif