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
	// ����status
	compute_status();

	// ������������Ȩ��
	compute_cost();
	cost_ans = 0;

	// ���㵱ǰ��count_now
	compute_new_count();

	// ���㵱ǰ�� node_status
	// compute_node_status();

	// ����������
	compute_by_layer();
	
	// �������
	//show();

	// ���ش�
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
		// ���㵱ǰ���node_status
		compute_node_status(j);
		// ��ǰ��Ҫ��Ҷ�Ӵ��ڵ�ǰҶ�ӣ���Ҫ�ϲ��·���
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
		// ��ǰ��Ҫ��Ҷ��С�ڵ�ǰҶ�ӣ���Ҫ���·���
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
	// ����Ƿ���Է��ѽڵ�
	if (status[id] != NodeStatus::LEAF)
	{
		cout << "�Ƿ��ָ��Ҷ�ӽڵ�" << endl;
		exit(-1);
	}
	else if (depth_idx >= TREEDEPTH - 1)
	{
		cout << "��Խ������" << endl;
		exit(-1);
	}
	// ���½ڵ�״̬
	status[id] = NodeStatus::COMMON;
	status[id << 1] = status[(id << 1) + 1] = NodeStatus::LEAF;
	// ����С���� ���ӣ������¶��ӵģ�ֻ�����Լ���״̬��ֵ
	NodeKey nk = leaf_node_status[depth_idx].top();
	// ���´���
	cost_ans += nk.key;
	leaf_node_status[depth_idx].pop();
	// ��������Ĵ��ۺ���
	w[id] = 0;
	//���¸���С����
	common_node_status[depth_idx].push(NodeKey(nk.id, w[id]));
	// ����count_new
	count_new[depth_idx] -= 1;
	count_new[depth_idx + 1] += 2;
}


void SolutionTry_1::grow(idx id, idx depth_idx)
{
	//cout << id << ' ' << depth_idx << endl;
	// ����Ƿ���Թ���
	if (status[id] != NodeStatus::COMMON)
	{
		cout << "�Ƿ������Ǹ��׽ڵ�" << endl;
		exit(-1);
	}
	//cout << "?" << endl;

	// ���½ڵ�״̬(��ǰ����ӣ��ӽڵ�ȫ���)��
	// ֻ��Ҫ����status��count_new�������node_status
	
	// ��������node_status��Ϊ��com��ɾ������leaf�м���0Ҷ��
	NodeKey nk = common_node_status[depth_idx].top();
	cost_ans += nk.key;
	common_node_status[depth_idx].pop();
	w[id] = 0;
	leaf_node_status[depth_idx].push(NodeKey(nk.id, w[id]));
	//cout << "aaaaaaaaaaaaaaaaa" << endl;
	//�ݹ�ĸ���status���Լ���״̬��ΪҶ�ӣ�������ȫ���empty��
	//ʹ��count_new��ǰ��Ҷ��+1��������Ҷ�Ӻݺݵļ�
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