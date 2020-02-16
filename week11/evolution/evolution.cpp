//Implementation by marcobaga
//This solution achieves 0 points

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <stack>

int solve_query(long year, std::vector<std::pair<int, int>> &anc){

	//std::cout << "Input: " << year << '\n';
	for(int i=0; i<anc.size(); ++i){
		//std::cout << anc[i].first << ' ' << anc[i].second << ' ';
	}
	//std::cout << '\n';
	int l = 0;
	int r = anc.size()-1;
	while(l<r-1){
		int tmp = l+(r-l)/2;
		if(anc[tmp].second>year)
			l=tmp;
		else
			r=tmp;
	}
	if(anc[l].second < year){
		//std::cout << anc[l].first << '\n';
		return anc[l].first;
	}
	//std::cout << anc[r].first << '\n';
	return anc[r].first;
}

void testcase(){
	int n,q; std::cin >> n >> q;
	//std::cout << n << ' ' << q << '\n';
	std::map<std::string, int> name_to_int;
	std::vector<std::string> int_to_name(n);
	std::vector<int> age (n, -1);
	int oldest = 0;
	for(int i=0; i<n; ++i){
		std::string name;
		long year;
		std::cin >> name >> year;
		//std::cout << "Read input: " << name << ' ' << year << '\n';
		name_to_int.insert(std::pair<std::string, int>(name, i));
		int_to_name[i] = name;
		age[i] = year;
		//std::cout << "Saved with name " << int_to_name[i] << " and number " << name_to_int.find(name)->second << " and age " << age[i] << '\n';
		if(age[i] > age[oldest])
			oldest = i;
	}

	//std::cout << "Oldest organism: " << int_to_name[oldest] << '\n';

	std::vector<std::vector<int>> sons (n);
	std::vector<int> parent (n, -1);
	for(int i=0; i<n-1; ++i){
		std::string ss,ps;
		std::cin >> ss >> ps;
		int s = name_to_int.find(ss)->second;
		int p = name_to_int.find(ps)->second;
		sons[p].push_back(s);
		parent[s] = p;
	}
/*
	for(int i=0; i<n; ++i){
		std::cout << i << "'s parent is " << parent[i] << '\n';
		std::cout << i << "'s sons are: ";
		for(int j=0; j<sons[i].size(); ++j){
			std::cout << sons[i][j] << ' ';
		}
		std::cout << '\n';
	}
*/
	std::vector<std::vector<long>> query (n);
	std::vector<std::vector<int>> query_n (n);
	std::vector<std::string> answer(q, "nan");
	for(int i=0; i<q; ++i){
		std::string s;
		long b;
		std::cin >> s >> b;
		query[name_to_int.find(s)->second].push_back(b);
		query_n[name_to_int.find(s)->second].push_back(i);
	}
/*
	for(int i=0; i<n; ++i){
		std::cout << i << " has queries: ";
		for(int j=0; j<query[i].size(); ++j){
			std::cout << query[i][j] << "(" << query_n[i][j] << ") ";
		}
		std::cout << '\n';
	}
*/
	std::vector<std::pair<int, int>> ancestors;
	std::stack<int> Q;
	std::vector<int> visited (n, 0);
	Q.push(oldest);
	visited[oldest] = 1;
	while(!Q.empty()){
		int curr = Q.top();
		//std::cout << curr << '\n';
		Q.pop();
		while(!ancestors.empty() && ancestors.back().first!=parent[curr])
			ancestors.pop_back();
		/*
		std::cout << "ancestors ";
		for(int i=0; i<ancestors.size(); ++i)
			std::cout << ancestors[i].first << ' ';
		std::cout << '\n';
		*/
		for(int i=0; i<query[curr].size(); ++i){
			int ans = solve_query(query[curr][i], ancestors);
			if(age[ans]>query[curr][i])
				ans = curr;
			answer[query_n[curr][i]] = int_to_name[ans];
		}
		for(int son : sons[curr]){
			if(visited[son]==0){
				Q.push(son);
				visited[son]==1;
			}
		}
		ancestors.push_back(std::make_pair(curr, age[curr]));
	}

	for(int i=0; i<q; ++i)
		std::cout << answer[i] << ' ';
	std::cout << '\n';
	return;
}

int main(){
	std::ios_base::sync_with_stdio(false);
	int t; std::cin >> t;
	while(t-- > 0)
		testcase();
	return 0;
}
