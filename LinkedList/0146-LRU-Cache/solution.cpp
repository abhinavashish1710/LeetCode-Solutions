class LRUCache {
    int cap;
    list<pair<int,int>> l;
    unordered_map<int,list<pair<int,int>>::iterator> mp;

public:
    LRUCache(int capacity) {
        cap=capacity;
    }
    
    int get(int key) {
        if(!mp.count(key)) return -1;
        auto it=mp[key];
        int val=it->second;
        l.erase(it);
        l.push_front({key,val});
        mp[key]=l.begin();
        return val;
    }
    
    void put(int key, int value) {
        if(mp.count(key))
            l.erase(mp[key]);
        else if(l.size()==cap){
            mp.erase(l.back().first);
            l.pop_back();
        }
        l.push_front({key,value});
        mp[key]=l.begin();
    }
};
