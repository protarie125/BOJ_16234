#include <algorithm>
#include <bit>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

using ll = long long;
using vb = vector<bool>;
using vvb = vector<vb>;
using vi = vector<int>;
using vvi = vector<vi>;
using vl = vector<ll>;
using vvl = vector<vl>;
using pii = pair<int, int>;
using vii = vector<pii>;
using pll = pair<ll, ll>;
using vll = vector<pll>;
using vs = vector<string>;

int n, l, r;
vvi bd;
vvb visit;

const auto dx = vi{ -1,1,0,0 };
const auto dy = vi{ 0,0,-1,1 };

bool bfs(int i, int j) {
	auto q = queue<pii>{};
	q.push({ i, j });

	visit[i][j] = true;
	auto sum = bd[i][j];
	auto update = vii{ {i, j} };

	while (!q.empty())
	{
		auto [y, x] = q.front();
		q.pop();

		for (auto d = 0; d < 4; ++d) {
			const auto nx = x + dx[d];
			const auto ny = y + dy[d];

			if (nx < 0 || n <= nx ||
				ny < 0 || n <= ny) {
				continue;
			}

			if (visit[ny][nx]) {
				continue;
			}

			const auto dif = abs(bd[y][x] - bd[ny][nx]);
			if (dif < l || r < dif) {
				continue;
			}

			q.push({ ny, nx });

			visit[ny][nx] = true;
			sum += bd[ny][nx];
			update.push_back({ ny, nx });
		}
	}

	if (update.size() <= 1) {
		return false;
	}

	const auto newVal = sum / update.size();
	for (const auto& [y, x] : update) {
		bd[y][x] = newVal;
	}

	return true;
}

int main() {
	ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	cin >> n >> l >> r;

	bd = vvi(n, vi(n));
	for (auto&& v : bd) {
		for (auto&& x : v) {
			cin >> x;
		}
	}

	auto hasUpdate = bool{};
	auto ans = 0;
	while (true)
	{
		hasUpdate = false;
		visit = vvb(n, vb(n, false));
		for (auto i = 0; i < n; ++i) {
			for (auto j = 0; j < n; ++j) {
				if (visit[i][j]) {
					continue;
				}

				hasUpdate |= bfs(i, j);
			}
		}

		if (!hasUpdate) {
			break;
		}

		++ans;
	}

	cout << ans;

	return 0;
}