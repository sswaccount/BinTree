#include "SolutionStd.h"
#include "file_stream.h"
#include "param.h"
#include "tree.h"

string SolutionStd::method_name = "Method_Std";

SolutionStd::SolutionStd(const string& path_)
	:SolutionBase(path_), filename(path_)
{
	input((1 << (TREEDEPTH + 1)), (1 << (TREEDEPTH + 1)), TREEDEPTH);
}

int SolutionStd::solve()
{
	try {
		env = new GRBEnv(true);
		env->set(GRB_IntParam_OutputFlag, 0);
		env->set("LogFile", filename + ".log");
		env->start();
		
		GRBModel model = GRBModel(env);
		// 定义变量
		vector<GRBVar> vars(1 << (TREEDEPTH + 1));
		for (int i = 0; i < vars.size(); ++i) {
			vars[i] = model.addVar(0, 1, 0, GRB_BINARY);
		}
		// 添加二叉树结构约束
		for (int i = 1; i < (1 << TREEDEPTH); ++i) {
			model.addConstr(vars[i << 1] - vars[(i << 1) | 1] == 0);
			model.addConstr(vars[i] - vars[i << 1] >= 0);
		}
		// 层数限制
		for (int j = 0; j < TREEDEPTH; ++j) {
			GRBLinExpr le;
			for (int i = (1 << j); i < (1 << (j + 1)); ++i) {
				le += (vars[i] - vars[i << 1]);
			}
			model.addConstr(le == count[j]);
		}
		// 优化目标
		GRBLinExpr le;
		for (int i = 1; i < (1 << TREEDEPTH); ++i)
		{
			le += (x[i] - x[i << 1] - vars[i] + vars[i << 1]) * w[i];
		}
		model.setObjective(le, GRB_MINIMIZE);

		model.optimize();
		
		print(model, vars);
		generate();
		return model.get(GRB_DoubleAttr_ObjVal);
	}
	catch (GRBException e) {
		cout << "Error code = " << e.getErrorCode() << endl;
		cout << e.getMessage() << endl;
	}
	catch (...) {
		cout << "Exception during optimization" << endl;
	}
}


void SolutionStd::print(GRBModel& model, vector<GRBVar>& vgv)
{
	// 输出结果
	int ans = 0;
	for (auto& i : w)
		ans += i;
	WriteFileStream write(filename + ".out");
	write << model.get(GRB_DoubleAttr_ObjVal) << endl;
	write << ans << endl;
	// 构建结论树
	WriteFileStream wf(filename + "_out.dot");
	wf << "graph g {\ngraph[ordering=\"out\"];\n";
	
	for (int i = 1; i < (1 << TREEDEPTH); ++i)
		if (get(vgv[i]) == 1) {
			wf << i << "[label=\"\", shape=circle, width=0.5];\n";
			if (get(vgv[i << 1]) == 1) {
				wf << i << "--" << (i << 1) << ";\n";
				wf << i << "--" << (i << 1) + 1 << ";\n";
			}
		}	
	wf << "}\n";
}


int SolutionStd::get(GRBVar& var)
{
	return var.get(GRB_DoubleAttr_X);
}

void SolutionStd::generate()
{
	string param = dot_ + filename + "_out" + dot_dot +
		GRAPHVIZPARAM + filename + "_out" + dot_png;
	system(param.data());
}