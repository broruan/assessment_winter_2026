#include <iostream>
#include <string>
#include <sstream>

#include "rm_a0/a0_08_raii_handle.hpp"

namespace rm_a0{
  FileHandle::FileHandle(const char *path, const char *mode) {
    this->fp_ = std::fopen(path,mode);
    if(!fp_) throw std::runtime_error("文件打开失败");
}
  FileHandle::~FileHandle(){
      if(this->fp_!=nullptr){
          std::fclose(this->fp_);//fclose不能传入空指针
          this->fp_ = nullptr;
      }
  }
  FileHandle::FileHandle(FileHandle &&other) noexcept {
      this->fp_ = other.fp_;
      other.fp_ = nullptr;
  }
  FileHandle &FileHandle::operator=(FileHandle &&other) noexcept {
      if(this!=&other){
          if(this->fp_) std::fclose(this->fp_);
          this->fp_ = other.fp_;
          other.fp_ = nullptr;
      }
      return *this;
  }//类内生成一个默认的operator=函数，强制用成员函数
  bool FileHandle::valid() const{
      if(this->fp_!=nullptr) return true;
      else{
          return false;
      }
  }
  FILE* FileHandle::get() const{
      return fp_;
  }//静态函数不用创建对象（直接调用），且没有this指针
  bool CopyFile(const std::string& in_path, const std::string& out_path) {
      try{FileHandle F_in(in_path.c_str(),"r"),F_out(out_path.c_str(),"w");
      char buffer[4096];
      size_t n;
      while ((n = std::fread(buffer, 1, sizeof(buffer), F_in.get())) > 0) {
          std::fwrite(buffer, 1, n, F_out.get());
      }
      F_out = std::move(F_in);
      return true;
      }
      catch(...){
          return false;
      }
}

std::string SolveRaiiCopy(const std::string& input, bool& ok) {
    std::istringstream in(input);
    std::string in_path;
    std::string out_path;
    if (!(in >> in_path >> out_path)) {
        ok = false;
        return "FAIL\n";
    }

    if (CopyFile(in_path, out_path)) {
        ok = true;
        return "OK\n";
    }

    ok = false;
    return "FAIL\n";
}
}

int main() {
  std::string in_path, out_path;
  if (!(std::cin >> in_path >> out_path))
    return 0;

  if (rm_a0::CopyFile(in_path, out_path)) {
    std::cout << "OK\n";
  } else {
    std::cout << "FAIL\n";
  }

  return 0;
}
