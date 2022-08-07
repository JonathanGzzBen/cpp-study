#ifndef JOB_BUILDER_H
#define JOB_BUILDER_H

#include "job.h"

class JobBuilder {
private:
  Job job;

public:
  JobBuilder() {}

  JobBuilder &place(std::string place) {
    job.place = place;
    return *this;
  }

  JobBuilder &role(std::string role) {
    job.role = role;
    return *this;
  }

  Job build() const { return std::move(job); }
  operator Job() const { return std::move(job); }
};

#endif // JOB_BUILDER_H