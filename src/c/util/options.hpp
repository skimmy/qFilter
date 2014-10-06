#ifndef _OPTIONS_H_
#define _OPTIONS_H_

enum OutputFormat { Fasta, Fastq };

class QFilterOptions {
  
private:
  // list of all the options  
  std::string fastqFilePath; // <fasq_input>
  bool stxxl;                // -X: use stxxl
  double fraction;           // -f: total reads fraction
  OutputFormat outFormat;    // -O: output format [int]
 
  
  void SetDefaultValues();
  
public:
  QFilterOptions();
  QFilterOptions(int argn, char** argv);
  ~QFilterOptions();

  void ParseCommandLineArguments(int argn, char** argv);

  friend std::istream& operator>>(std::istream& is, QFilterOptions& opts);
  friend std::ostream& operator<<(std::ostream& os, QFilterOptions& otps);

  bool isStxxlEnabled() const { return stxxl; }
  std::string getFastqFilePath() const { return fastqFilePath; }
  double getFraction() const { return fraction; }
  OutputFormat getOutputFormat() const { return outFormat; }


};

extern QFilterOptions opts;

#endif
