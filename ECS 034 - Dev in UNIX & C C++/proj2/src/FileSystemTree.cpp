#include "FileSystemTree.h"
#include "Path.h"
#include "StringUtils.h"
#include <iostream>                      
#include <map>
#include <string>

//#define DEBUG_ON
#ifdef DEBUG_ON
#define DEBUG_LINE() std::cout << "In " << __FILE__ << "@ LINE " << __LINE__ <<std::endl
#else
#define DEBUG_LINE()
#endif
struct CFileSystemTree::SImplementation {
	//Shared ptr points down root to node
	std::shared_ptr<CEntry::SImplementation> RootNode;
	CPath Path;
};

struct CFileSystemTree::CEntry::SImplementation : std::enable_shared_from_this<CFileSystemTree::CEntry::SImplementation> {
	std::string DName;
	CPath Path;
	std::weak_ptr<CEntry::SImplementation> DParent;
	std::map<std::string, std::shared_ptr<SImplementation>> DChildren;
	bool AddPath(const std::string& path);
	std::string ToStringHelper(std::vector<bool> moretocome, int Depth = 0) const;
	std::string FullPath() const;
};

struct CFileSystemTree::CEntryIterator::SImplementation {
	CEntry DEntry;
	std::weak_ptr<CEntry::SImplementation> DParent;
	int index = -1; // How many elements into our container are we
	std::map<std::string, std::shared_ptr<CEntry::SImplementation>> DChildren; // copy of the children from the target node
};

struct CFileSystemTree::CConstEntryIterator::SImplementation {
	CEntry DEntry;
	std::weak_ptr<CEntry::SImplementation> DParent;
	int index = -1; // How many elements into our container are we
	std::map<std::string, std::shared_ptr<CEntry::SImplementation>> DChildren; // copy of the children from the target node
};
std::string CFileSystemTree::CEntry::SImplementation::FullPath() const {
	if (auto Parent = DParent.lock()) {
		auto ParentFullPath = Parent->FullPath();
		//make sure to check /
		return ParentFullPath + std::string("/") + DName;
	}
	return "/";
}
std::string CFileSystemTree::CEntry::SImplementation::ToStringHelper(std::vector<bool> moretocome, int Depth)const {
	auto Str = DName;
	if (moretocome.empty()) {
		Str += "/";
	}
	else if (moretocome.back()) {
		std::string Line = "";
		if (Depth > 1) // if Depth is greater than 1, we'll add the starting | to our Line
			Line += "| ";
		for (auto i = 1; i < Depth; ++i) // now, we add 2 spaces for each Depth over 1
			Line += "  ";
		// if the Depth is greater than tree, and the parent has more than 1 child
		// we'll show a | marking the parent indentation by substringing
		if (Depth > 3 && DParent.lock()->DChildren.size() > 1) {
			Line = Line.substr(0, Line.length() - 2) + "|  ";
		}

		// build Line
		Str = Line + "|--" + Str;
	}
	else {
		// start Line padding with | for the root level
		std::string Line = "";
		if (Depth > 1)
			Line = "|";
		// add two spacers per Depth after 1
		for (auto i = 1; i < Depth; ++i)
			Line += "   ";
		// if Depth is greater than 3, we edit the end of the Line
		// to add the parent's indentation level.
		if (Depth > 3 && DParent.lock()->DChildren.size() > 1) {
			Line = Line.substr(0, Line.length() - 4) + "|  ";
		}
		else
			Line = Line.substr(0, Line.length() - 1);

		Str = Line + "`--" + Str;
	}

	size_t Index = 0;
	for (auto iter : DChildren) {
		Str += "\n";
		moretocome.push_back(Index + 1 < DChildren.size());
		Str += iter.second->ToStringHelper(moretocome, ++Depth);
		--Depth;
		moretocome.pop_back();
		Index++;
	}
	return Str;
}

CFileSystemTree::CEntry::CEntry() {
	// Your code here
}

CFileSystemTree::CEntry::~CEntry() {
	// Your code here
}

bool CFileSystemTree::CEntry::Valid() const {
	DEBUG_LINE();
	if (!DImplementation)
		return false;
	return true;

}

std::string CFileSystemTree::CEntry::Name() const {
	DEBUG_LINE();
	//loses Dimpl
	if (!DImplementation) {
		std::cout << "Empty" << std::endl;
		return "";
	}
	return DImplementation->DName;
}
bool CFileSystemTree::CEntry::SImplementation::AddPath(const std::string & path) {

	/*Split String into vec delim /
	Look at first Element of split string
	if the element exists add sub path to it
	if !exists add the child and add subpath to child
	this would be recursive
	*/
	auto Components = StringUtils::Split(path, "/");
	if (Components[0] == "" || Components[0] == ".") {
		Components.erase(Components.begin());
	}
	if (Components[0] == "..") { //move up 1 dir
		if (auto Parent = DParent.lock()) {
			Components.erase(Components.begin());
			return Parent->AddPath(StringUtils::Join("/", Components));
		}
		return false;
	}
	//->first and ->second
	// first being the element on the lhs & second being rhs within your declaration
	for (auto iter : DChildren) {
		if (iter.second->DName == Components[0]) {
			if (Components.size() == 1) {
				return false;
			}
			Components.erase(Components.begin());
			return iter.second->AddPath(StringUtils::Join("/", Components));
		}
	}
	CEntry Temp;
	Temp.DImplementation = shared_from_this();
	Temp.AddChild(Components[0]);
	if (Components.size() == 1) {
		return true;
	}
	auto NewChild = Temp.DImplementation->DChildren[Components[0]];
	Components.erase(Components.begin());
	//get the child we created to pass the rest of the path to it
	return NewChild->AddPath(StringUtils::Join("/", Components));

}
std::string CFileSystemTree::CEntry::FullPath() const {

	//expect '/' as root
	//expects a returned string type
	//iterate through the temp  node
	//std::cout<< "CFileSystemTree::CEntry::FullPath()" <<std::endl;
	//if (DImplementation->RootNode){
	//    return "/";
	//}
	return DImplementation->Path.AbsolutePath();
}

std::string CFileSystemTree::CEntry::ToString() const {
	DEBUG_LINE();
	return DImplementation->Path.AbsolutePath();
}

CFileSystemTree::CEntry::operator std::string() const {
	DEBUG_LINE();
	return DImplementation->Path.AbsolutePath();
}

bool CFileSystemTree::CEntry::Rename(const std::string & name) {
	DEBUG_LINE();
	//Check that we dont duplicate names
	DImplementation->Path = CPath(name);
	return true;
}

size_t CFileSystemTree::CEntry::ChildCount() const {
	DEBUG_LINE();
	return DImplementation->DChildren.size();
}

bool CFileSystemTree::CEntry::SetChild(const std::string & name, const CEntryIterator & iter) {
	DEBUG_LINE();
	return false;
}

bool CFileSystemTree::CEntry::AddChild(const std::string & name) {
	DEBUG_LINE();
	if (DImplementation->DChildren.find(name) != DImplementation->DChildren.end())
		return false;
	/*
	Create a sharedpointer, child
	populate it 
	store it under dchildren
	*/
	auto SharedPointer = std::shared_ptr<CEntry::SImplementation>(new CEntry::SImplementation());
	SharedPointer->DName = name;
	SharedPointer->DParent = DImplementation->shared_from_this();
	SharedPointer->Path = DImplementation->Path + CPath(name);
	DImplementation->DChildren[name] = SharedPointer;

	return true;
}

bool CFileSystemTree::CEntry::AddPath(const std::string & path) {
	DEBUG_LINE();
	//return DImplementation->AddPath(path);
	return DImplementation->AddPath(path);
}

bool CFileSystemTree::CEntry::RemoveChild(const std::string & name) {
	DEBUG_LINE();
	return false;
}

bool CFileSystemTree::CEntry::SetData(const std::vector< char > & data) {
	DEBUG_LINE();
	return false;
}

bool CFileSystemTree::CEntry::GetData(std::vector< char > & data) const {
	std::cout << "CFileSystemTree::CEntry::GetData" << std::endl;
	return false;
}

CFileSystemTree::CEntryIterator CFileSystemTree::CEntry::Parent() {
	DEBUG_LINE();
	//parent should do something to DEntry?
	if (!DImplementation->DParent.lock()) {
		return CEntryIterator();
	}
	CEntryIterator Parent;
	auto OldParent = DImplementation->DParent.lock();//parent is empty
	Parent.DImplementation->DParent = OldParent;
	Parent.DImplementation->DChildren = OldParent->DChildren;
	Parent.DImplementation->index = -1;
	Parent.DImplementation->DEntry.DImplementation = OldParent->shared_from_this();
	return Parent;
}

CFileSystemTree::CConstEntryIterator CFileSystemTree::CEntry::Parent() const {
	DEBUG_LINE();
	return CConstEntryIterator();
}

CFileSystemTree::CEntryIterator CFileSystemTree::CEntry::Find(const std::string & path) {
	DEBUG_LINE();
	return CEntryIterator();
}

CFileSystemTree::CConstEntryIterator CFileSystemTree::CEntry::Find(const std::string & path) const {
	DEBUG_LINE();
	return CConstEntryIterator();
}

CFileSystemTree::CEntryIterator CFileSystemTree::CEntry::begin() {
	DEBUG_LINE();
	CEntryIterator iter;
	iter.DImplementation->DEntry.DImplementation = DImplementation->shared_from_this();
	iter.DImplementation->index = 0;
	iter.DImplementation->DChildren = DImplementation->DChildren;
	iter.DImplementation->DParent = DImplementation->DParent;
	return iter;
}

CFileSystemTree::CConstEntryIterator CFileSystemTree::CEntry::begin() const {
	DEBUG_LINE();
	return CConstEntryIterator();
}

CFileSystemTree::CConstEntryIterator CFileSystemTree::CEntry::cbegin() const {
	DEBUG_LINE();
	return CConstEntryIterator();
}

CFileSystemTree::CEntryIterator CFileSystemTree::CEntry::end() {
	DEBUG_LINE();
	CEntryIterator iter;
	iter.DImplementation->index = DImplementation->DChildren.size();
	iter.DImplementation->DChildren = DImplementation->DChildren;
	return iter;
}

CFileSystemTree::CConstEntryIterator CFileSystemTree::CEntry::end() const {
	DEBUG_LINE();
	return CConstEntryIterator();
}

CFileSystemTree::CConstEntryIterator CFileSystemTree::CEntry::cend() const {
	DEBUG_LINE();
	//
	return CConstEntryIterator();
}
/*

*START OF CEentry ITERATOR *
CEntryIterator creates a CEntry() object and stores
it in DImpl. This gets deleted in the destructor.
Whenever we need to use the CEntry, we changed the DImplementation
on the CEntry because it's a shared_ptr and auto managed.

*/
CFileSystemTree::CEntryIterator::CEntryIterator() : DImplementation(std::make_unique< SImplementation >()) {
	DEBUG_LINE();
}

CFileSystemTree::CEntryIterator::CEntryIterator(const CEntryIterator & iter) : DImplementation(std::make_unique< SImplementation >()) {
	DEBUG_LINE();
	DImplementation->DEntry.DImplementation = iter.DImplementation->DEntry.DImplementation;
	DImplementation->DParent = iter.DImplementation->DParent;
	DImplementation->DChildren = iter.DImplementation->DChildren;
	DImplementation->index = iter.DImplementation->index;
}

CFileSystemTree::CEntryIterator::~CEntryIterator() {
	//Destructor
	DEBUG_LINE();
}

CFileSystemTree::CEntryIterator& CFileSystemTree::CEntryIterator::operator=(const CEntryIterator & iter) {
	DEBUG_LINE();
	return *this;
}

bool CFileSystemTree::CEntryIterator::operator==(const CEntryIterator & iter) const {
	DEBUG_LINE();
	if (DImplementation->DChildren == iter.DImplementation->DChildren)
		if (DImplementation->index == iter.DImplementation->index)
			//if (DImplementation->DEntry.DImplementation == iter.DImplementation->DEntry.DImplementation) {
				return true;
	//}
	return false;
}

bool CFileSystemTree::CEntryIterator::operator!=(const CEntryIterator & iter) const {
	DEBUG_LINE();
	return false;
}

CFileSystemTree::CEntryIterator& CFileSystemTree::CEntryIterator::operator++() {
	// update the index of our current DImplmentation, then return reference to us
	DEBUG_LINE();
	DImplementation->index++;
	return *this;
}

CFileSystemTree::CEntryIterator CFileSystemTree::CEntryIterator::operator++(int) {
	// Update the index of our current DImpl index, then return copy of us
	DEBUG_LINE();
	DImplementation->index++;
	return *this;
}

CFileSystemTree::CEntryIterator& CFileSystemTree::CEntryIterator::operator--() {
	DEBUG_LINE();
	DImplementation->index--;
	return *this;
}

CFileSystemTree::CEntryIterator CFileSystemTree::CEntryIterator::operator--(int) {
	DEBUG_LINE();
	DImplementation->index--;
	return *this;
}

CFileSystemTree::CEntry* CFileSystemTree::CEntryIterator::operator->() const {
	DEBUG_LINE();
	// if we've got a container, then we're iterating over something
	// adjust iterator into the container by the amount we want.
	if (DImplementation->DChildren.size() > 0 && DImplementation->index >= 0) {
		auto iterator = DImplementation->DChildren.begin();
		iterator = std::next(iterator, DImplementation->index);
		DImplementation->DEntry.DImplementation = iterator->second;
	}

	return &DImplementation->DEntry;
}


CFileSystemTree::CConstEntryIterator::CConstEntryIterator() : DImplementation(std::make_unique< SImplementation >()) {
	DEBUG_LINE();
}

CFileSystemTree::CConstEntryIterator::CConstEntryIterator(const CConstEntryIterator & iter) : DImplementation(std::make_unique< SImplementation >()) {
	DEBUG_LINE();
	//DImplementation = iter.DImplementation;
}

CFileSystemTree::CConstEntryIterator::CConstEntryIterator(const CEntryIterator & iter) : DImplementation(std::make_unique< SImplementation >()) {
	DEBUG_LINE();
	// DImplementation = iter.DImplementation;
}

CFileSystemTree::CConstEntryIterator::~CConstEntryIterator() {
	DEBUG_LINE();
	// Your code here
}

CFileSystemTree::CConstEntryIterator& CFileSystemTree::CConstEntryIterator::operator=(const CConstEntryIterator & iter) {
	DEBUG_LINE();
	return *this;
}

bool CFileSystemTree::CConstEntryIterator::operator==(const CConstEntryIterator & iter) const {
	DEBUG_LINE();
	return false;
}

bool CFileSystemTree::CConstEntryIterator::operator!=(const CConstEntryIterator & iter) const {
	DEBUG_LINE();
	return false;
}

CFileSystemTree::CConstEntryIterator& CFileSystemTree::CConstEntryIterator::operator++() {
	DEBUG_LINE();
	return *this;
}
CFileSystemTree::CConstEntryIterator CFileSystemTree::CConstEntryIterator::operator++(int) {
	DEBUG_LINE();
	return *this;
}


CFileSystemTree::CConstEntryIterator& CFileSystemTree::CConstEntryIterator::operator--() {
	DEBUG_LINE();
	return *this;
}

CFileSystemTree::CConstEntryIterator CFileSystemTree::CConstEntryIterator::operator--(int) {
	DEBUG_LINE();
	return *this;
}

const CFileSystemTree::CEntry* CFileSystemTree::CConstEntryIterator::operator->() const {
	DEBUG_LINE();
	return nullptr;

}

CFileSystemTree::CFileSystemTree() : DImplementation(std::make_shared< SImplementation >()) {
	DEBUG_LINE();
	auto SharedPointer = std::make_shared<CEntry::SImplementation>();
	SharedPointer->Path = CPath("/");
	DImplementation->RootNode = SharedPointer;

}

CFileSystemTree::~CFileSystemTree() {
	DEBUG_LINE();
	// Your code here
}

CFileSystemTree::CEntryIterator CFileSystemTree::Root() {
	DEBUG_LINE();
	CEntryIterator iter;
	iter.DImplementation->DEntry.DImplementation = DImplementation->RootNode;
	iter.DImplementation->DParent = DImplementation->RootNode->shared_from_this();
	iter.DImplementation->DChildren = DImplementation->RootNode->DChildren;
	return iter;
}

CFileSystemTree::CConstEntryIterator CFileSystemTree::Root() const {
	DEBUG_LINE();
	CEntryIterator iter;
	return iter;
}

std::string CFileSystemTree::ToString() const {
	DEBUG_LINE();
	//your code here
	return "";
}

//return current tree
CFileSystemTree::operator std::string() const {
	DEBUG_LINE();
	std::vector<bool> Temp;
	return DImplementation->RootNode->ToStringHelper(Temp);
}

CFileSystemTree::CEntryIterator CFileSystemTree::Find(const std::string & path) {
	DEBUG_LINE();
	//find a string where it returns NotFound method
	//break path into a vec
	auto PathVec = StringUtils::Split(path, "/");
	//check if each successive element exists in the tree	
	for (auto i : PathVec) {

	}
	return NotFound();
}

CFileSystemTree::CConstEntryIterator CFileSystemTree::Find(const std::string & path) const {
	DEBUG_LINE();
	//
	return CConstEntryIterator();
}

CFileSystemTree::CEntryIterator CFileSystemTree::NotFound() {
	DEBUG_LINE();
	CFileSystemTree::CEntryIterator Empty;
	return Empty;
}

CFileSystemTree::CConstEntryIterator CFileSystemTree::NotFound() const {
	DEBUG_LINE();
	CFileSystemTree::CConstEntryIterator Empty;
	return Empty;
}
