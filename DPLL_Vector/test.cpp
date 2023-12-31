#include<iostream>
#include"input_class.cpp"
#include"formula.h"
#include"dpll.h"
#include"vtoc.h"
#include <chrono>
#include"AdvancedDPLL.h"
#include"AdvancedFormula.h"
using namespace std;
extern Vtoc variableId_to_Clauses;
//'C:\\Users\\l1768\\Desktop\\sat\\DPLL��ѵ\\DPLL��ѵ\\SAT���Ա�ѡ����\\��׼����\\���ܲ���\\unsat-5cnf-30.cnf'
//C:\\Users\\l1768\\Desktop\\sat\\DPLL��ѵ\\DPLL��ѵ\\SAT���Ա�ѡ����\\��׼����\\���ܲ���\\sat-20.cnf
//void test1() {
//	string filename = "C:\\Users\\l1768\\Desktop\\sat\\DPLL��ѵ\\DPLL��ѵ\\SAT���Ա�ѡ����\\Beijing\\enddr2-10-by-5-1.cnf";
//	cout << filename << endl;
//	Input input(filename);
//	Formula* f_ptr = new Formula();
//	f_ptr->setCurrentClausesCnt(input.getClauseCnt());
//	f_ptr->setVariablesCnt(input.getBoolVarCnt());
//	variableId_to_Clauses.setVtocSize(input.getBoolVarCnt());
//	input.readClauses(*f_ptr);
//	//f_ptr->printFormula();
//	auto start = chrono::high_resolution_clock::now();
//	int result = DPLL::solver(*f_ptr);
//	auto stop = chrono::high_resolution_clock::now();
//	DPLL::showResult(result);
//	auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
//	cout << "��ʱ��" << duration.count() / 1000.0 << "s" << endl;
//}
//void test2(string filename) {
//	cout << filename << endl;
//	Input input(filename);
//	Formula* f_ptr = new Formula();
//	f_ptr->setCurrentClausesCnt(input.getClauseCnt());
//	f_ptr->setVariablesCnt(input.getBoolVarCnt());
//	variableId_to_Clauses.setVtocSize(input.getBoolVarCnt());
//	input.readClauses(*f_ptr);
//	//f_ptr->printFormula();
//	auto start = chrono::high_resolution_clock::now();
//	int result = DPLL::solver(*f_ptr);
//	auto stop = chrono::high_resolution_clock::now();
//	DPLL::showResult(result);
//	auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
//	cout << duration.count() / 1000.0 << endl;
//}
void verify(AdvancedFormula& f) {
	for (int i = 1; i < f.variables_cnt + 1; i++) {
		bool value = (bool)AdvancedFormula::variables_assign_ptr[i];
		cout << i << " -> " << value << endl;
		if (value != -1) {
			int result = AdvancedDPLL::applyVariableAssign(f, i, value);
			if (result == 0 || result == 1) {
				cout << result << endl;
				return;
			}
		}
	}
	cout << "No" << endl;
}
void testAdvancedDPLL1() {
	string filename = "C:\\Users\\l1768\\Desktop\\sat\\DPLL��ѵ\\DPLL��ѵ\\SAT���Ա�ѡ����\\Beijing\\2bitcomp_5.cnf";
	cout << filename << endl;  
	Input input(filename);
	AdvancedFormula* f_ptr = new AdvancedFormula();
	f_ptr->setCurrentClausesCnt(input.getClauseCnt());
	f_ptr->setVariablesCnt(input.getBoolVarCnt());
	variableId_to_Clauses.setVtocSize(input.getBoolVarCnt());
	input.readClauses<AdvancedFormula>(*f_ptr);
	f_ptr->initVariablesAssignAndFlipFlag(input.getBoolVarCnt());
	AdvancedFormula* verify_f = new AdvancedFormula(*f_ptr);
	auto start = chrono::high_resolution_clock::now();
	int result = AdvancedDPLL::solverByIncrementalUpdate(*f_ptr);
	auto stop = chrono::high_resolution_clock::now();
	AdvancedDPLL::showResult(result);
	auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
	cout << "��ʱ��" << duration.count() / 1000.0 << "s" << endl;
	verify(*verify_f);
	delete verify_f; 
}

void testAdvancedDPLL2(string filename) {
	//string filename = "../instances/unsat-php-15-10.cnf";
	cout << filename << endl;
	Input input(filename);
	AdvancedFormula* f_ptr = new AdvancedFormula();
	f_ptr->setCurrentClausesCnt(input.getClauseCnt());
	f_ptr->setVariablesCnt(input.getBoolVarCnt());
	variableId_to_Clauses.setVtocSize(input.getBoolVarCnt());
	input.readClauses<AdvancedFormula>(*f_ptr);
	f_ptr->initVariablesAssignAndFlipFlag(input.getBoolVarCnt());
	AdvancedFormula* verify_f = new AdvancedFormula(*f_ptr);
	auto start = chrono::high_resolution_clock::now();
	int result = AdvancedDPLL::solverByIncrementalUpdate(*f_ptr);
	auto stop = chrono::high_resolution_clock::now();
	AdvancedDPLL::showResult(result);
	auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
	cout << duration.count() / 1000.0 << endl;
	verify(*verify_f);
	delete verify_f;
}
int main(int argc,char* argv[]) {
	//test2(argv[1]);
	testAdvancedDPLL2(argv[1]);
	return 0;
}