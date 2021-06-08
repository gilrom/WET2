#include "UnionFind.h"
#include <iostream>

using wet2::UnionFind;
using wet2::Group;
using namespace std;

/*simply adding ints*/
class IntMerge{
    public:
    int operator()(int x, int y)
    {
        return x+y;
    }
};

int main()
{
    UnionFind<int, IntMerge> uf;
    uf.addOrgan(0);
    uf.addOrgan(1);
    uf.addOrgan(2);
    uf.addOrgan(3);
    uf.addOrgan(4);
    Group<int> g = uf.unionGroups(0,1);
    cout <<"new group num: " << g.getGroupNum() << "\n";
    cout <<"new group data: " << g.getData() << "\n";
    g = uf.find(0);
    cout << "group num of organ 0: " << g.getGroupNum() << "\n";
    g = uf.unionGroups(g.getGroupNum(), 3);
    g = uf.find(3);
    cout << "group num of organ 3: " << g.getGroupNum() << "\n";
    cout << "data of group 3: " << g.getData() << "\n";
}
