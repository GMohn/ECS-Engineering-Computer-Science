#include "Path.h" 	  			 	 
#include <cstdlib>
#include <vector>
#include "StringUtils.h"
#include <iostream>

struct CPath::SImplementation{
    std::string input_path; 
};

CPath::CPath() : DImplementation(std::make_unique< SImplementation >()){
    DImplementation->input_path = ""; //default 

}

CPath::CPath(const CPath &path) : DImplementation(std::make_unique< SImplementation >()){
    DImplementation->input_path = path.DImplementation->input_path; //copy

}

CPath::CPath(const std::string &path): DImplementation(std::make_unique< SImplementation >()) {
    DImplementation->input_path = path; //explicit
}

CPath::~CPath(){
    // Your code goes here Desctructor
}

CPath &CPath::operator=(const CPath &path){
    DImplementation->input_path = path.DImplementation->input_path;
    return *this;

}

CPath CPath::operator+(const CPath &path) const{
    std::string Result = DImplementation->input_path + "/" + path.DImplementation->input_path;
    return CPath(Result);
}

bool CPath::operator==(const CPath &path) const{
    if(DImplementation->input_path == path.DImplementation->input_path){
        return true;
    }
    return false;
}

bool CPath::operator!=(const CPath &path) const{
    if(DImplementation->input_path != path.DImplementation->input_path){
        return false;
    }
    return true;
}

CPath CPath::Directory() const{
    auto index = DImplementation->input_path.find_last_of("/");
    std::string Result = DImplementation->input_path.substr(0,index);
    return CPath(Result);
}

std::string CPath::BaseName() const{
    if (DImplementation->input_path == ""){
        return "";
    }
    auto index = DImplementation->input_path.find_last_of("/");
    std::string Result = DImplementation->input_path.substr(index+1);
    return Result;
}

std::string CPath::Extension() const{
    auto index = DImplementation->input_path.find_last_of("."); 
    if (index == std::string::npos){
        return "";
    }
    std::string Result = DImplementation->input_path.substr(index);
    return Result;
}

bool CPath::IsAbsolute() const{
    if (DImplementation->input_path == ""){
        return false;
    }
    return DImplementation->input_path[0] == '/';
}

std::string CPath::ToString() const{
    // Your code goes here
    return "";
}

CPath::operator std::string() const{
    return DImplementation->input_path;
}

CPath CPath::AbsolutePath() const{
    // input_path "" then its empty 
    if (DImplementation->input_path == ""){
        return CPath();
    }
	//if first char is / then its abs
	if (DImplementation->input_path[0] == '/') {
		std::string temp = DImplementation->input_path;
		if (temp.length() > 2 && temp[0] == '/' && temp[1] == '/')
			temp = temp.substr(1);

		return CPath(temp);
	}
    //path is absolute, must be relative, make absolute
    std::string Result = GetCWD() + DImplementation->input_path.substr(1);
	if (Result.length() > 2 && Result[0] == '/' && Result[1] == '/')
		Result = Result.substr(1);
    return CPath(Result);
}

CPath CPath::CommonPath(const CPath &path) const{
    // Your code goes here
    return CPath();
}

CPath CPath::NormalizePath() const{
    auto index = DImplementation->input_path.find("./");
    //std::cout << "normalize: " << DImplementation->input_path << std::endl;
    if (index == std::string::npos){
        return CPath();
    }
    std::string ResultAbs = DImplementation->input_path;
    std::string ResultFile = ResultAbs;
    ResultAbs = ResultAbs.substr(0,index);
    ResultFile = ResultFile.substr(index+2);
    std::string Result = ResultAbs + ResultFile;
    //std::cout << "result: " << DImplementation->input_path <<"index: "<< index<< std::endl;
    return CPath(Result);
}

CPath CPath::RelativePathTo(const CPath &path) const{
    std::string Result = DImplementation->input_path + "/" + path.DImplementation->input_path;
    std::string path1 = DImplementation->input_path;
    std::string path2 = path.DImplementation->input_path;
    //std::cout << "path 1 : " << path1 << "\npath 2: "<< path2 << std::endl;
    //std::cout << "Result RelativePathTo: " << Result << std::endl;
    //interactive doesn't give path 1
    if (path1 == ""){
        path1 = GetCWD();
    }
    //find where the strings are different then substr the difference and add
    size_t Idx = 0;
    for (;Idx < path1.length();++Idx){
        if (path1[Idx] != path2[Idx]){
            path1 = path1.substr(Idx);
            path2 = path2.substr(Idx);
            break;
        }
    }
    //count # directories; # "'/' + 1" to go down
    size_t counter = 1;
    for(char c:path1){
        if (c == '/'){
            counter++;
        }
    }
    //result = n * ../ + path2; n is the number of directories
    Result = "";
    for(size_t i = 0; i < counter;++i){
        Result += "../"; 
    }
    Result += path2;

    //std::cout << "path 1 : " << path1 << "\npath 2: "<< path2 << std::endl;
    //std::cout << "Result RelativePathTo: " << Result << std::endl;
    return CPath(Result);
}

// Helper function provided to get the current working directory
std::string CPath::GetCWD(){
#ifndef _MSC_VER    
	std::vector< char > CurrentPathName;

    CurrentPathName.resize(1024);
    while(NULL == getcwd(CurrentPathName.data(), CurrentPathName.size())){
        CurrentPathName.resize(CurrentPathName.size() * 2);
    }
    return CurrentPathName.data();
#else
	return "";
#endif
}

// Helper funciton provided to get the home directory
std::string CPath::GetHome(){
#ifndef _MSC_VER    
	return std::getenv("HOME");
#else	
	return "";
#endif
}

CPath CPath::AbsolutePath(const CPath &path){
    // Your code goes here

    return path.AbsolutePath(); //building a new cpath that returns an absolute path but called different.
}

CPath CPath::CurrentPath(){
    // Your code goes here
    return CPath();
}

CPath CPath::CommonPath(const CPath &path1, const CPath &path2){
    // Your code goes here
    return CPath();
}

CPath CPath::ExpandUserPath(const CPath &path){
    //static method so it has no instance
    //std::cout << " ExpandUserPath: " << path.DImplementation->input_path << std::endl;
    auto index = path.DImplementation->input_path.find("~");
    if (index == std::string::npos){
        return CPath();
    }
    std::string RelPath = path.DImplementation->input_path;
    std::string Home = path.GetHome();
    RelPath = RelPath.substr(index+1);
    std::string Result = Home+RelPath;
    //std::cout << "result: " << Result <<" index: "<< index<< std::endl;
    return CPath(Result);
}

CPath CPath::HomePath(){
    return CPath (GetHome());
}

CPath CPath::NormalizePath(const CPath &path){
    // Your code goes here
    return path.NormalizePath();
}

CPath CPath::RelativePath(const CPath &path, const CPath &startpath){
    // Your code goes here

    return startpath.RelativePathTo(path);
}
