package(default_visibility = ["//visibility:public"])

#cc_library(
#  name = "test_main",
#  srcs = ["main.cc"],
#  deps = ["@com_github_catch2//:catch2"],
#)

cc_binary(
  name = "test_main",
  srcs = ["main.cc"],
  defines = ["CATCH_CONFIG_MAIN"],
  deps = ["@catch2"],
)