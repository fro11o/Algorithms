#include <bits/stdc++.h>
using namespace std;

const int MAXC = 30;  // size of character set

struct TrieNode {
    char val;
    TrieNode* pa;
    TrieNode* ch[MAXC];
    TrieNode* fail;
    TrieNode* last;
    bool is_word;
    TrieNode(): is_word(false), pa(NULL), fail(NULL), last(NULL) {
        memset(ch, 0, sizeof(TrieNode*) * MAXC);
    }
};

const int MAXN = 1000;  // number of patterns
const int MAXL = 100;  // length of a pattern

struct AhoCorasickAutomata {
    TrieNode tn[MAXN * MAXL];
    int cnt = 1;
    void insert(char* p) {
        TrieNode* cur = &tn[0];
        int m = strlen(p);
        for (int i = 0; i < m; ++i) {
            if (cur->ch[p[i] - 'a'] == NULL) {
                cur->ch[p[i] - 'a'] = &tn[cnt++]; 
                cur->ch[p[i] - 'a']->val = p[i];
                cur->ch[p[i] - 'a']->pa = cur;
                //cout << "node_id " << cnt-1 << " char " << p[i] <<endl;
            }
            cur = cur->ch[p[i] - 'a'];
        }
        cur->is_word = true;
    }
    void getFail() {
        queue<TrieNode*> q;
        q.push(&tn[0]);
        tn[0].fail = tn[0].last = &tn[0];
        while (!q.empty()) {
            TrieNode* cur = q.front();
            q.pop();
            for (int i = 0; i < MAXC; ++i) {
                if (cur->ch[i] != NULL) {
                    q.push(cur->ch[i]);
                    
                    // calculate fail and last pointer
                    TrieNode* t1 = cur->ch[i];
                    TrieNode* t2 = cur->fail;
                    if (cur == &tn[0]) {
                        // the fail and last pointer of first character (pa is null node) should be zero
                        t1->fail = t1->last = &tn[0];
                    } else {
                        while (t2 != &tn[0] && t2->ch[i] == NULL)  t2 = t2->fail;
                        t1->fail = (t2->ch[i] != NULL) ? t2->ch[i] : t2;
                        t1->last = t1->fail->is_word ? t1->fail : t1->fail->last;
                    }
                    //cout << "char " << t1->val << " fail " << t1->fail->val << " last " << t1->last->val << endl;
                }
            }
        }
    }
    void find(char* t) {
        int n = strlen(t);
        TrieNode* j = &tn[0];
        for (int i = 0; i < n; ++i) {
            while (j != &tn[0] && j->ch[t[i] - 'a'] == NULL) j = j->fail;
            if (j->ch[t[i] - 'a'] != NULL)  j = j->ch[t[i] - 'a'];
            if (j->is_word)  print(i, j);
            else if (j->last != NULL)  print(i, j->last);
        }
    }
    void print(int idx, TrieNode* node) {
        // print all patterns that end at text[idx]
        while (node != &tn[0]) {
            TrieNode* tmp = node;
            string s;
            while (tmp != &tn[0]) {
                s += tmp->val;
                tmp = tmp->pa;
            }
            reverse(s.begin(), s.end());
            cout << idx << ' ' << s << endl;
            node = node->last;
        }
    }
};

const int MAXT = 1e6;

AhoCorasickAutomata ac;

int main() {
    char pattern[MAXN][MAXL], text[MAXT];
    int n;
    cout << "number of pattern: "; cin >> n;
    for (int i = 0; i < n; ++i) {
        cout << "#" << i+1 << " pattern: "; cin >> pattern[i];
    }
    cout << "text: "; cin >> text;

    // AC
    for (int i = 0; i < n; ++i) {
        ac.insert(pattern[i]);
    }
    ac.getFail();
    ac.find(text);

    return 0;
}
