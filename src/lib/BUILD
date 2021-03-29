load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "TrojanMap",
    srcs = ["trojanmap.cc"],
    hdrs = ["trojanmap.h"],
    deps = ["@opencv//:opencv"],
    data = ["map.csv", 
    "input.jpg", 
    "output.avi", 
    "topologicalsort_locations.csv", 
    "topologicalsort_dependencies.csv"],
    visibility = ["//visibility:public"],
)
 
cc_library(
    name = "UI",
    srcs = glob(["UI.cc"]),
    hdrs = glob(["UI.h"]),
    deps = ["@ncurses//:main"],
    visibility = ["//visibility:public"],
)