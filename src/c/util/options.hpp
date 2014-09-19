#ifndef _OPTIONS_H_
#define _OPTIONS_H_

class QFilterOptions {
private:
  // list of all the options
  bool stxxl;
  std::string fastqFilePath;
  
  void ParseCommandLineArguments(int argn, char** argv);
  void SetDefaultValues();
  
public:
  QFilterOptions(int argn, char** argv);
  ~QFilterOptions();
  friend std::istream& operator>>(std::istream& is, QFilterOptions& opts);
  friend std::ostream& operator<<(std::ostream& os, QFilterOptions& otps);

  bool isStxxlEnabled() const { return stxxl; }
};

#endif
