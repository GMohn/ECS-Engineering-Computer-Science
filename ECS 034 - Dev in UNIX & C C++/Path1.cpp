#include "Path.h" 	  			 	 
#include <cstdlib>
#include <unistd.h>
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
    // Your code goes here

}

CPath CPath::operator+(const CPath &path) const{
    std::string Result = DImplementation->input_path + "/" + path.DImplementation->input_path;
    return CPath(Result);
}

bool CPath::operator==(const CPath &path) const{
    // Your code goes here
    return true;
}

bool CPath::operator!=(const CPath &path) const{
    // Your code goes here
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
    if (DImplementation->input_path[0] == '/'){
        return CPath(DImplementation->input_path);
    }
    //path is absolute, must be relative, make absolute
    std::string Result = GetCWD() + DImplementation->input_path.substr(1);
    return CPath(Result);
}

CPath CPath::CommonPath(const CPath &path) const{
    // Your code goes here
    return CPath();
}

CPath CPath::NormalizePath() const{
    auto index = DImplementation->input_path.find_last_of("./");
    std::cout << "normalize: " << DImplementation->input_path << std::endl;
    if (index == std::string::npos){
        return CPath();
    }
    std::string Result = DImplementation->input_path;
    //fix this Result = Result.erase(index,10); //fix this
    std::cout << " result: " << DImplementation->input_path <<"index: "<< index<< std::endl;
    return CPath(Result);
}

CPath CPath::RelativePathTo(const CPath &path) const{
    std::string Result = DImplementation->input_path + "/" + path.DImplementation->input_path;
    return CPath();
}

// Helper function provided to get the current working directory
std::string CPath::GetCWD(){
    std::vector< char > CurrentPathName;

    CurrentPathName.resize(1024);
    while(NULL == getcwd(CurrentPathName.data(), CurrentPathName.size())){
        CurrentPathName.resize(CurrentPathName.size() * 2);
    }
    return CurrentPathName.data();
}

// Helper funciton provided to get the home directory
std::string CPath::GetHome(){
    return std::getenv("HOME");
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
    // Your code goes here
    return CPath();
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
    return CPath();
}
