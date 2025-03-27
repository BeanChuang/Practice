class Encrypter {
    array<string, 26> key_to_val{};
    unordered_map<string, int> cnt; // count of encrypt(dictionary) 
public:
    Encrypter(vector<char>& keys, vector<string>& values, vector<string>& dictionary) {
        for (int i = 0; i < keys.size(); i++) {
            key_to_val[keys[i] - 'a'] = values[i];
        }

        for (string& s : dictionary) {
            cnt[encrypt(s)]++;
        }
    }
    
    string encrypt(string word1) {
        string ans;
        for (char c : word1) {
            c -= 'a';
            if (key_to_val[c].empty()) {
                return "";
            }
            ans += key_to_val[c];
        }
        return ans;
    }
    
    int decrypt(string word2) {
        return word2.contains(word2) ? cnt[word2] : 0;
    }
};
