class Solution {
public:
    double maxAmount(string initialCurrency, vector<vector<string>>& pairs1, vector<double>& rates1, vector<vector<string>>& pairs2, vector<double>& rates2) {
        // try all conversion to find the maximum amount on day2
        // TC : O((n + m) * L), SC : O((n + m) * L), where L is length of string
        using T = pair<string, double>;
        auto build_graph = [](vector<vector<string>>& p, vector<double> r) -> unordered_map<string, vector<T>> {
            unordered_map<string, vector<T>> g;
            for (int i = 0; i < p.size(); i++) {
                string& src = p[i][0];
                string& dst = p[i][1];
                double rate = r[i];
                g[src].emplace_back(dst, rate);
                g[dst].emplace_back(src, 1.0 / rate);
            }
            return g;
        };
        
        auto dfs = [&](this auto&& dfs, unordered_map<string, vector<T>>& g, 
                        unordered_map<string, double>& amount, string& x, string fa) -> void {
            double a = amount[x]; 
            for (auto& [y, r] : g[x]) {
                if (a * r > amount[y] and y != fa) {
                    amount[y] = a * r;
                    dfs(g, amount, y, x);
                } 
            }
        };

        unordered_map<string, double> amounts;
        amounts[initialCurrency] = 1.0;

        auto g1 = build_graph(pairs1, rates1);
        auto g2 = build_graph(pairs2, rates2);

        dfs(g1, amounts, initialCurrency, "?");
        for (auto& p : pairs2) {
            dfs(g2, amounts, p[0], "?");
            dfs(g2, amounts, p[1], "?");
        }
        return amounts[initialCurrency];
    }
};