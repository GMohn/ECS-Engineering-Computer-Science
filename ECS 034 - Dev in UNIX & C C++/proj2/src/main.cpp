#include <iostream>
#include <vector>
#include <thread>

#include "FileSystemTree.h"

using namespace std;

void RunTest01() {
	CFileSystemTree Tree;
	(std::string(Tree), "/");
	(Tree.Root()->FullPath(), "/");
	(Tree.Root()->Valid());
	(Tree.Root()->Parent()->Valid());
	(Tree.Root()->AddChild("bin"));
	(Tree.Root()->AddChild("etc"));
	(Tree.Root()->AddChild("home"));
	(Tree.Root()->AddChild("dev"));
	(Tree.Root()->AddChild("proc"));
	(Tree.Root()->AddChild("usr"));
	(Tree.Root()->AddChild("var"));
	(Tree.Root()->AddPath("/home/cjnitta/ecs34"));
	(Tree.Root()->AddPath("home/cjnitta/ecs34/proj1"));
	(Tree.Root()->AddPath("home/cjnitta/ecs34/proj2"));
	(Tree.Root()->AddPath("home/cjnitta/ecs36c"));
	CFileSystemTree::CEntryIterator Iter = Tree.Root()->begin();
	(Iter->Name(), "bin");
	Iter++;
	(Iter->Name(), "dev");
	Iter++;
	(Iter->Name(), "etc");
	Iter++;
	(Iter->Name(), "home");
	++Iter;
	(Iter->Name(), "proc");
	++Iter;
	(Iter->Name(), "usr");
	Iter++;
	(Iter->Name(), "var");
	Iter++;
	(Iter, Tree.Root()->end());
	Iter--;
	(Iter->Name(), "var");
	Iter--;
	--Iter;
	--Iter;
	(Iter->Name(), "home");
	std::cout << std::string(Tree) << std::endl;
	CFileSystemTree::CEntryIterator Iter2 = Iter->begin()->begin();
	(Iter2->Name(), "ecs34");
	CFileSystemTree::CEntryIterator Iter3 = Iter2->begin();
	(Iter3->Name(), "proj1");
	(Iter3->Parent()->Name(), "ecs34");
	Iter3++;
	(Iter3->Name(), "proj2");
	(Iter3->Parent()->Name(), "ecs34");
	(Iter3->Parent()->Parent()->Name(), "cjnitta");
	(Iter3->FullPath(), "/home/cjnitta/ecs34/proj2");
	Iter2++;
	(Iter2->Name(), "ecs36c");
	(Iter2->FullPath(), "/home/cjnitta/ecs36c");
	(Iter2->AddPath("../../bob"));
	(Tree.Root()->AddPath("/home/bob"));
	(Iter2->FullPath(), "/home/cjnitta/ecs36c");
	(Iter2->AddPath("../../../../bob"));
	
	
}
void FindNodeTest() {
	CFileSystemTree Tree;

	(Tree.Root()->AddChild("bin"));
	(Tree.Root()->AddChild("etc"));
	(Tree.Root()->AddChild("home"));
	(Tree.Root()->AddChild("dev"));
	(Tree.Root()->AddChild("proc"));
	(Tree.Root()->AddChild("usr"));
	(Tree.Root()->AddChild("var"));
	(Tree.Root()->AddPath("/home/cjnitta/ecs34"));
	(Tree.Root()->AddPath("home/cjnitta/ecs34/proj1"));
	(Tree.Root()->AddPath("home/cjnitta/ecs34/proj2"));
	(Tree.Root()->AddPath("home/cjnitta/ecs36c"));

	auto NodeIter = Tree.Find("home/cjnitta/ecs34");

	(NodeIter == Tree.NotFound());
	(NodeIter != Tree.NotFound());
	(NodeIter->FullPath(), "/home/cjnitta/ecs34");

	(Tree.Find("/a/path/to/nowhere"), Tree.NotFound());
}
int main() {

	RunTest01();
	FindNodeTest();


	return 0;
}
