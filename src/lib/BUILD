load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "TrojanMap",
    srcs = ["trojanmap.cc"],
    hdrs = ["trojanmap.h"],
    deps = ["@opencv//:opencv"],
    data = ["map.csv", 
    "input.jpg", 
<<<<<<< HEAD
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
=======
    "output.avi"],
>>>>>>> 0cc44c22c0d46e7d7236be2c61b6537daad6869e
    visibility = ["//visibility:public"],
)