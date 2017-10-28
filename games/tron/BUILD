# Tron implementation.
cc_library(
    name="tron_lib",
    srcs=glob(["**/*.cc"]),
    hdrs=glob(["**/*.h"]),
    deps=[
        "//lib:arbitrium_lib",
        "//players:players_lib",
    ],
)

cc_binary(
    name="tron",
    srcs=["tron.cc"],
    deps=["tron_lib"],
)
