#pragma once
#include <iostream>
#include <conio.h>
#include <iomanip>
#include <string>
#include <vector>
#include <functional>
#include <algorithm>
#include <tuple>
#include <stdexcept>
#include <memory>
#include <locale.h>
#define COUNT 2
using namespace std;
struct Node
{
	int n;
	int count;
	Node* left, * right;
};

class Tree
{
public:
	Node* root;
	int lv = 0;
	Tree() {
		root = 0;
	};
	Tree(int t);
	~Tree() {
		DelTree(root);
	};

	void CopyTree(Node*& rootnew, Node* rootold);
	Tree(const Tree& ob);
	void DelTree(Node* wer);
	void Push(Node*& wer, int data);
	void Look(Node* wer);
	void PrintLeaves(Node* wer);
	void CountLeaves(Node* wer);
	//void dump0(Node const* node, std::string const& prefix = "", bool root = true, bool last = true);
	void printTree(Node* root, int space);
};

Tree::Tree(int t)
{
	root = 0;
	for (int i = 0; i < t; i++)
		Push(root, rand() % 11 - 5);
}

void Tree::CopyTree(Node*& rootnew, Node* rootold)
{
	if (rootold->left != 0) {
		Push(rootnew, (rootold->left)->n);
		CopyTree(rootnew, rootold->left);
	}
	if (rootold->right != 0) {
		Push(rootnew, (rootold->right)->n);
		CopyTree(rootnew, rootold->right);
	}
}

Tree::Tree(const Tree& ob)
{
	if (ob.root == 0)
		root = 0;
	else
	{
		root = new Node;
		root->n = ob.root->n;
		root->count = 1;
		root->left = 0;
		root->right = 0;
		CopyTree(root, ob.root);
	}
}

void Tree::DelTree(Node* wer)
{
	if (wer->left != 0)
		DelTree(wer->left);
	if (wer->right != 0)
		DelTree(wer->right);
	delete wer;
}

void Tree::Push(Node*& wer, int data)
{
	if (wer == 0) {
		wer = new Node;
		wer->n = data;
		wer->left = 0;
		wer->right = 0;
		wer->count = 1;
	}
	else
		if (data < wer->n)
			Push(wer->left, data);
		else
			if (data > wer->n)
				Push(wer->right, data);
			else
				wer->count++;
}

void Tree::Look(Node* wer)
{
	if (wer != 0) {
		Look(wer->left);
		cout << "Число: " << setw(2) << wer->n << " - " << wer->count << " шт." << endl;
		Look(wer->right);
	}
}

void Tree::PrintLeaves(Node* wer)
{
	if (wer == 0)
		return;
	else
		if ((wer->left == 0) && (wer->right == 0)) {
			cout << "Число: " << setw(2) << wer->n << " - " << wer->count << " шт.\n";
		}
		else {
			PrintLeaves(wer->left);
			PrintLeaves(wer->right);
		}
}

void Tree::CountLeaves(Node* wer)
{
	if (wer == 0)
		return;
	else
		if ((wer->left == 0) && (wer->right == 0)) {
			lv += wer->count;
		}
		else
		{
			CountLeaves(wer->left);
			CountLeaves(wer->right);
		}
}

int mmm(int kol, char menu[][100], int max, int k);

static std::string ch_hor = "-", ch_ver = "|", ch_ddia = "/", ch_rddia = "\\", ch_udia = "\\", ch_ver_hor = "|-", ch_udia_hor = "\\-", ch_ddia_hor = "/-", ch_ver_spa = "| ";
//static std::string ch_hor = "\u2500" /*─*/, ch_ver = "\u2502" /*│*/, ch_ddia = "\u250C" /*┌*/, ch_rddia = "\u2510" /*┐*/, ch_udia = "\u2514" /*└*/, ch_ver_hor = "\u251C\u2500" /*├─*/, ch_udia_hor = "\u2514\u2500" /*└─*/, ch_ddia_hor = "\u250C\u2500" /*┌─*/, ch_ver_spa = "\u2502 " /*│ */;
void dump0(Node const* node, std::string const& prefix = "", bool root = true, bool last = true) {

	std::cout << prefix << (root ? "" : (last ? ch_udia_hor : ch_ver_hor)) << (node ? std::to_string(node->n) : "") << std::endl;
	if (!node || (!node->left && !node->right))
		return;
	std::vector<Node*> v{ node->left, node->right };
	for (size_t i = 0; i < v.size(); ++i)
		dump0(v[i], prefix + (root ? "" : (last ? "  " : ch_ver_spa)), false, i + 1 >= v.size());
}

void dump1(Node const* node) {
#define _MAX(x, y) ((x) > (y) ? (x) : (y))
#define _MIN(x, y) ((x) < (y) ? (x) : (y))

	auto RepStr = [](std::string const& s, size_t cnt) {
		if (ptrdiff_t(cnt) < 0)
			throw std::runtime_error("RepStr: Bad value " + std::to_string(ptrdiff_t(cnt)) + "!");
		std::string r;
		for (size_t i = 0; i < cnt; ++i)
			r += s;
		return r;
	};
	std::function<std::tuple<std::vector<std::string>, size_t, size_t>(Node const* node, bool)> Rec;
	Rec = [&RepStr, &Rec](Node const* node, bool left) {
		std::vector<std::string> lines;
		if (!node)
			return std::make_tuple(lines, size_t(0), size_t(0));
		auto sval = std::to_string(node->n);
		//if (sval.size() % 2 != 1) sval += " ";
		auto resl = Rec(node->left, true), resr = Rec(node->right, false);
		auto const& vl = std::get<0>(resl);
		auto const& vr = std::get<0>(resr);
		auto cl = std::get<1>(resl), cr = std::get<1>(resr), lss = std::get<2>(resl), rss = std::get<2>(resr);
		size_t lv = sval.size();
		size_t ls = vl.size() > 0 ? lss : size_t(0);
		size_t rs = vr.size() > 0 ? rss : size_t(0);
		size_t lis = ls == 0 ? lv / 2 : _MAX(int(lv / 2 + 1 - (ls - cl)), 0);
		size_t ris = rs == 0 ? (lv + 1) / 2 : _MAX(int((lv + 1) / 2 - cr), (lis > 0 ? 0 : 1));
		size_t dashls = (ls == 0 ? 0 : ls - cl - 1 + lis - lv / 2), dashrs = (rs == 0 ? 0 : cr + ris - (lv + 1) / 2);
		//DEB(node->value); DEB(lv); DEB(ls); DEB(rs); DEB(cl); DEB(cr); DEB(lis); DEB(ris); DEB(dashls); DEB(dashrs); std::cout << std::endl;
		lines.push_back(
			(ls == 0 ? "" : (RepStr(" ", cl) + ch_ddia + RepStr(ch_hor, dashls))) +
			sval + (rs == 0 ? "" : (RepStr(ch_hor, dashrs) + ch_rddia + RepStr(" ", rs - cr - 1)))
		);
		//if (lines.back().size() != ls + lis + ris + rs)
		//    throw std::runtime_error("Dump: First line wrong size, got " + std::to_string(lines.back().size()) + ", expected " + std::to_string(ls + lis + ris + rs));
		for (size_t i = 0; i < _MAX(vl.size(), vr.size()); ++i) {
			std::string sl = RepStr(" ", ls), sr = RepStr(" ", rs);
			if (i < vl.size()) sl = vl[i];
			if (i < vr.size()) sr = vr[i];
			sl = sl + RepStr(" ", lis);
			sr = RepStr(" ", ris) + sr;
			lines.push_back(sl + sr);
		}
		return std::make_tuple(lines, (left || ls + lis == 0 || lv % 2 == 1) ? ls + lis : ls + lis - 1, ls + lis + ris + rs);
	};
	auto v = std::get<0>(Rec(node, true));
	for (size_t i = 0; i < v.size(); ++i)
		std::cout << v[i] << std::endl;

#undef _MAX
#undef _MIN
}

void Tree::printTree(Node* root, int space) {
	if (root == NULL)
		return;
	space += COUNT;
	printTree(root->right, space);
	for (int i = COUNT; i < space; i++)
		cout << " ";
	cout << root->n << "\n";
	printTree(root->left, space);
}
