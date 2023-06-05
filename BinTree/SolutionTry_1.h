#pragma once

#include "SolutionBase.h"



enum NodeStatus
{
	COMMON,
	LEAF,
	EMPTY
};

struct NodeKey
{
	idx id;
	idx key;
	NodeKey(idx id_, idx key_)
		:id(id_), key(key_) {}
	
	bool operator<(const NodeKey& nk) const {
		return this->key < nk.key;
	}
	bool operator>(const NodeKey& nk) const {
		return this->key > nk.key;
	}
	friend ostream& operator<<(ostream& os, const NodeKey& nk) {
		os << "(" << nk.id << " : " << nk.key << ") ";
		return os;
	}
};


typedef vector<priority_queue<NodeKey, vector<NodeKey>, std::greater<NodeKey>>> Vpmin;

class SolutionTry_1 : public SolutionBase 
{
public:
	SolutionTry_1(const string& filepath_);
	int solve();

	static string method_name;

private:
	void compute_status();
	idx compute_cost(idx id = 1);
	void compute_new_count();
	void compute_by_layer();
	void compute_node_status(idx j);
	void show();

	void split(idx id, idx depth_idx);

	void grow(idx id, idx depth_idx);
	void recursive_update_status(idx id, idx depth_idx, NodeStatus ns);

	// �ڵ��Ҷ�ӡ���ͨ��״̬
	vector<NodeStatus> status;
	// �ڵ�Ļ���Ȩֵ
	vector<idx> cost;
	// �ڵ�ĵ�ǰ����Ȩֵ
	vector<idx> count_new;
	// ÿһ�β��Ҷ�ӽڵ�С����
	Vpmin common_node_status, leaf_node_status;

	int cost_ans;
};

