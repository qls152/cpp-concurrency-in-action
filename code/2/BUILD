package(default_visibility = ["//visibility:public"])

# https://docs.bazel.build/versions/master/be/c-cpp.html#cc_library
cc_library(
	name = "func_object",
	srcs = ["func_object.h"],
)

# https://docs.bazel.build/versions/master/be/c-cpp.html#cc_binary
cc_binary(
	name = "basic_thread_manage",
	srcs = ["basic_thread_manage.cc"],
	copts = [],
	deps = [
		":func_object",
	]
)

cc_binary(
	name = "detach_obj_lifetime",
	srcs = [
		"detach_obj_lifetime.h",
		"detach_obj_lifetime.cc",
	]
)

cc_binary(
	name = "except_thread",
	srcs = [
		"except_thread.cc",
		"detach_obj_lifetime.h",
		"guard_thread.h",
	],
)