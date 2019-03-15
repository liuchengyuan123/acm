struct hashmap {
    long long a[4000005];
    int head[seed], next[4000005], size;
    void init () {
            memset (head, -1, sizeof head);
        size = 0;
    }
    int find (long long val) {
        int tmp = (val%seed + seed)%seed;
        for (int i = head[tmp]; i != -1; i = next[i]) {
            if (val == a[i]) return i;
        }
        return -1;
    }
    void add (long long val) {
        int tmp = (val%seed+seed)%seed;
        a[size] = val;
        next[size] = head[tmp];
        head[tmp] = size++;
    }
};
