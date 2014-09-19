// Copyright (c) 2013, Cloudera, inc.
//
// Base test class, with various utility functions.
#ifndef KUDU_UTIL_TEST_UTIL_H
#define KUDU_UTIL_TEST_UTIL_H

#include <gtest/gtest.h>
#include <string>

#include "kudu/gutil/gscoped_ptr.h"
#include "kudu/util/env.h"
#include "kudu/util/test_macros.h"

namespace kudu {

class KuduTest : public ::testing::Test {
 public:
  KuduTest();

  // Env passed in from subclass, for tests that run in-memory.
  explicit KuduTest(Env *env);

  virtual ~KuduTest();

  virtual void SetUp() OVERRIDE;

 protected:
  std::string GetTestPath(const std::string& relative_path);

  gscoped_ptr<Env> env_;
  std::string test_dir_;
  google::FlagSaver flag_saver_;  // Reset flags on every test.
};

// Returns true if slow tests are runtime-enabled.
bool AllowSlowTests();

// Override the given gflag to the new value, only in the case that
// slow tests are enabled and the user hasn't otherwise overridden
// it on the command line.
void OverrideFlagForSlowTests(const std::string& flag_name,
                              const std::string& new_value);

// Call srand() with a random seed based on the current time, reporting
// that seed to the logs. The time-based seed may be overridden by passing
// --test_random_seed= from the CLI in order to reproduce a failed randomized
// test. Returns the seed.
int SeedRandom();

// Return a per-test directory in which to store test data. Guaranteed to
// return the same directory every time for a given unit test.
//
// May only be called from within a gtest unit test.
std::string GetTestDataDirectory();

} // namespace kudu
#endif
