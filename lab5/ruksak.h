#ifndef RUKSAK_H
#define RUKSAK_H
#include <algorithm>
#include <cstdlib>
//#include <ctime>
#include <iostream>
#include <set>
//#include <tuple>
#include <utility>
#include <QStringList>
#include <QString>
#include <sstream>

struct T_item
{
    int weight_;
    int cost_;
    QString name_;
    T_item(QString name,int weight,int cost):name_ (name),weight_ (weight),cost_ (cost){}
    bool operator<(T_item const &i)const
    {
        return std::make_pair(weight_,cost_)<std::make_pair(i.weight_,i.cost_);
    }
    friend std::stringstream & operator<<(std::stringstream &ostr, T_item const &i)
    {
        ostr<<"("<<i.name_.toStdString()<<","<<i.weight_<<","<<i.cost_<<")";
        return ostr;
    }
};

typedef std::multiset <T_item> T_items;

class T_rucksack
{
    int weight_total_max_;
    int weight_total_;
    int cost_total_;
    T_items items_;
public:
    T_rucksack(int weight_total_max) : weight_total_max_(weight_total_max), weight_total_ (), cost_total_ (){}
    void fill_with_max_cost(T_items const &items)
    {
        T_rucksack rucksack_cur(weight_total_max_);
        while(rucksack_cur.successfully_add_item_from(items) || rucksack_cur.successfully_inc_item_from(items))
            if(rucksack_cur.cost_total_>cost_total_)
                *this=rucksack_cur;
    }
    QStringList print()
    {
        //std::cout<<std::endl<<"rucksack:"<<std::endl<<"weight_total_max = "<<weight_total_max_<<std::endl;
        QStringList tmp = print_cont(items_);
        QStringList out;
        if(tmp.size()!=0)
            out.push_back(tmp.last());
        return out;
    }
    template <typename TT_cont>
    QStringList print_cont(TT_cont const &cont)
    {
        std::stringstream buffer;
        QStringList listelem;
        listelem.clear();
        if(successfully_print(cont))
        {
            for(auto const &elem:cont)
            {
                buffer<<elem<<" ";
                listelem.append(QString::fromStdString(buffer.str()));
            }
        }
        return listelem;
    }
private:
    bool successfully_add_item_from(T_items const &items)
    {
        bool bool_res{};
        if(items_.empty())
            bool_res=successfully_insert_item(*items.begin());
        else
        {
            auto it=std::find_if(items.find(*items_.rbegin()),items.end(),[=] (auto const &item)
            {
                return items_.count(item)<items.count(item) && item.weight_<=this->weight_free();}
            );
            bool_res=it!=items.end();
            if(bool_res)
                insert_item(*it);
        }
        return  bool_res;
    }
    bool successfully_inc_item_from(T_items const &items)
    {
        bool bool_res{};
        for(;;)
        {
            bool_res=!items_.empty();
            if(!bool_res)
                break;
            auto item_back=*items_.rbegin();
            remove_item(item_back);
            auto begin_it=items.upper_bound(item_back);
            auto it=std::find_if(begin_it,items.end(),[=](auto const &item){
                return item.weight_<=this->weight_free();
            }
            );
            bool_res=it!=items.end();
            if(bool_res)
            {
                insert_item(*it);
                break;
            }
        }
        return bool_res;
    }
    void remove_item(T_item const &item)
    {
        items_.erase(items_.lower_bound(item));
        weight_total_-=item.weight_;
        cost_total_-=item.cost_;
    }
    void insert_item(T_item const &item)
    {
        items_.emplace(item);
        weight_total_+=item.weight_;
        cost_total_+=item.cost_;
    }
    bool successfully_insert_item(T_item const &item)
    {
        bool bool_res=item.weight_<=weight_free();
        if(bool_res)
            insert_item(item);
        return bool_res;
    }
    int weight_free() const
    {
        return weight_total_max_-weight_total_;
    }
    bool successfully_print(T_items const &items)
    {
        bool bool_res{};
        bool_res=!items.empty();
        return bool_res;
    }
    int get_rand_val_in_segm(int min, int max)
    {
        return rand()%(max-min+1)+min;
    }
public:
    T_items get_rand_items(size_t items_size)
    {
        const int VAL_MIN{1};
        const int VAL_MAX{10};
        T_items res;
        while(res.size()<items_size)
            res.emplace(T_item("rand",get_rand_val_in_segm(VAL_MIN,VAL_MAX),get_rand_val_in_segm(VAL_MIN,VAL_MAX)));
        return  res;
    }
    T_items get_items(QStringList namelist,int* weigth_, int* cost_,size_t items_size)
    {
        T_items res;
        for(int i=0;i<(int)items_size;i++)
            if(res.size()<items_size)
            {
                //char *x = new char[namelist.length()];
                //strcpy(x, namelist.at(i).toStdString().c_str());
                res.emplace(T_item(namelist.at(i),weigth_[i],cost_[i]));
                //delete[] x;
            }
        //while(res.size()<items_size)
        //    res.emplace(T_item(get_rand_val_in_segm(VAL_MIN,VAL_MAX),get_rand_val_in_segm(VAL_MIN,VAL_MAX)));
        return  res;
    }
};

#endif // FULLBUST_H
