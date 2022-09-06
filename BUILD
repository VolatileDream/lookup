package(
  default_visibility = ["//visibility:public"],
)

filegroup(
  name = "path_bins",
  srcs = [":lookup"],
)

cc_library(
  name = "liblookup",
  srcs = ["lookup.c"],
  hdrs = ["lookup.h"],
)

cc_binary(
  name = "lookup",
  srcs = ["main.c"],
  deps = [":liblookup"],
)
