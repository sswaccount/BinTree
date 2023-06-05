#include "SolutionTry_1.h"
#include "util.h"

string SolutionTry_1::method_name = "Method_Try_1";


SolutionTry_1::SolutionTry_1(const string& filepath_)
	:SolutionBase(filepath_) {
	input();
	cost = vector<idx>(1 << TREEDEPTH, 0);
	common_node_status = Vpmin(TREEDEPTH);
	leaf_node_status = Vpmin(TREEDEPTH);
}


int SolutionTry_1::solve()
{
	// 构建status
	compute_status();

	// 计算整体树的权重
	compute_cost();
	cost_ans = 0;

	// 计算当前的count_now
	compute_new_count();

	// 计算当前的 node_status
	// compute_node_status();

	// 逐层计算问题
	compute_by_layer();
	
	// 输出数据
	//show();

	// 返回答案
	return cost_ans;
}


void SolutionTry_1::compute_status()
{
	int limit = (1 << TREEDEPTH);
	status = vector<NodeStatus>(limit);
	for (int j = 0; j < TREEDEPTH; ++j) {
		for (int i = (1 << j); i < (1 << (j + 1)); ++i) {
			if (!x[i])
				status[i] = NodeStatus::EMPTY;
			else if ((i << 1) < limit && x[i << 1])
				status[i] = NodeStatus::COMMON;
			else
				status[i] = NodeStatus::LEAF;
		}
	}
}


idx SolutionTry_1::compute_cost(idx id)
{
	if (w[id] != 0) {
		cost[id] = w[id];
		return cost[id];
	}
	cost[id] = compute_cost(id << 1) + compute_cost((id << 1) + 1) + w[id];
	return cost[id];
}

void SolutionTry_1::compute_new_count()
{
	count_new = vector<idx>(TREEDEPTH);
	for (int j = 0; j < TREEDEPTH; ++j) {
		for (int i = (1 << j); i < (1 << (j + 1)); ++i) {
			if (status[i] == NodeStatus::LEAF)
				count_new[j] ++;
		}
	}
}

void SolutionTry_1::compute_by_layer()
{
	for (int j = 0; j < TREEDEPTH; ++j)
	{
		// 计算当前层的node_status
		compute_node_status(j);
		// 当前层要求叶子大于当前叶子，需要上层下分裂
		if (count[j] > count_new[j]) {
			idx k = count[j] - count_new[j];
			for (idx i = 0; i < k; ++i) {
				if (common_node_status[j].empty())
				{
					cout << "false" << endl;
					exit(-1);
				}
				grow(common_node_status[j].top().id, j);
			}
		}
		// 当前层要求叶子小于当前叶子，需要向下分裂
		else if (count[j] < count_new[j]) {
			idx k = count_new[j] - count[j];
			for (idx i = 0; i < k; ++i) {
				if (leaf_node_status[j].empty())
				{
					cout << "false" << endl;
					exit(-1);
				}
				split(leaf_node_status[j].top().id, j);
			}
		}
	}
}

void SolutionTry_1::compute_node_status(idx j)
{
	for (idx i = (1 << j); i < (1 << (j + 1)); ++i) {
		if (status[i] == NodeStatus::COMMON)
			common_node_status[j].push(NodeKey(i, cost[i]));
		else if (status[i] == NodeStatus::LEAF)
			leaf_node_status[j].push(NodeKey(i, cost[i]));
	}
}

void SolutionTry_1::show()
{
	for (int j = 0; j < TREEDEPTH; ++j) {
		for (int i = (1 << j); i < (1 << (j + 1)); ++i) {
			cout << cost[i] << ' ';
		}
		cout << endl;
	}
	cout << endl;
	for (auto i : count)
		cout << i << ' ';
	cout << endl;
	cout << endl;
	for (auto i : count_new)
		cout << i << ' ';
	cout << endl;
	cout << endl;

	for (auto& i : leaf_node_status)
	{
		cout << i.size() << ' ';
		show_pq(i);
	}
	cout << endl << endl;

	for (auto& i : common_node_status)
	{
		cout << i.size() << ' ';
		show_pq(i);
	}
	cout << endl << endl;

}


void SolutionTry_1::split(idx id, idx depth_idx)
{
	// << id << ' ' << depth_idx << endl;
	// 检查是否可以分裂节点
	if (status[id] != NodeStatus::LEAF)
	{
		cout << "非法分割非叶子节点" << endl;
		exit(-1);
	}
	else if (depth_idx >= TREEDEPTH - 1)
	{
		cout << "超越树界限" << endl;
		exit(-1);
	}
	// 更新节点状态
	status[id] = NodeStatus::COMMON;
	status[id << 1] = status[(id << 1) + 1] = NodeStatus::LEAF;
	// 更新小根堆 出队，不更新儿子的，只更新自己的状态和值
	NodeKey nk = leaf_node_status[depth_idx].top();
	// 更新代价
	cost_ans += nk.key;
	leaf_node_status[depth_idx].pop();
	// 调整自身的代价函数
	w[id] = 0;
	//更新父亲小根堆
	common_node_status[depth_idx].push(NodeKey(nk.id, w[id]));
	// 更新count_new
	count_new[depth_idx] -= 1;
	count_new[depth_idx + 1] += 2;
}


void SolutionTry_1::grow(idx id, idx depth_idx)
{
	//cout << id << ' ' << depth_idx << endl;
	// 检查是否可以构造
	if (status[id] != NodeStatus::COMMON)
	{
		cout << "非法生长非父亲节点" << endl;
		exit(-1);
	}
	//cout << "?" << endl;

	// 更新节点状态(当前变儿子，子节点全变空)，
	// 只需要更新status、count_new、自身的node_status
	
	// 更新自身node_status即为：com中删顶部，leaf中加入0叶子
	NodeKey nk = common_node_status[depth_idx].top();
	cost_ans += nk.key;
	common_node_status[depth_idx].pop();
	w[id] = 0;
	leaf_node_status[depth_idx].push(NodeKey(nk.id, w[id]));
	//cout << "aaaaaaaaaaaaaaaaa" << endl;
	//递归的更新status（自己的状态变为叶子，儿子们全变成empty）
	//使得count_new当前层叶子+1，其他层叶子狠狠的减
	count_new[depth_idx] += 1;
	status[id] = NodeStatus::LEAF;
	recursive_update_status(id << 1, depth_idx + 1, NodeStatus::EMPTY);
	recursive_update_status((id << 1) + 1, depth_idx + 1, NodeStatus::EMPTY);

}

void SolutionTry_1::recursive_update_status(idx id, idx depth_idx, NodeStatus ns)
{

	//cout << id << ' ' << depth_idx << endl;
	if (depth_idx < TREEDEPTH && status[id] != ns)
	{
		if (status[id] == NodeStatus::LEAF)
			count_new[depth_idx] -= 1;
		status[id] = ns;
		recursive_update_status(id << 1, depth_idx + 1, ns);
		recursive_update_status((id << 1) + 1, depth_idx + 1, ns);
	}
}