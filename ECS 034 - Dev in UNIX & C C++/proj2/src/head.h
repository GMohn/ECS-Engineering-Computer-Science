template <typename T>
int Compare(const T &l, const T &r){
    if(l < r){
        return -1;
    }
    if(l > r){
        return 1;
    }
    return 0;
}