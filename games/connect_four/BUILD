# Connect Four implementation.
cc_library(
    name="connect_four_lib",
    srcs=glob(["**/*.cc"]),
    hdrs=glob(["**/*.h"]),
    deps=[
        "//lib:arbitrium_lib",
        "//players:players_lib",
    ],
)

cc_binary(
    name="connect_four",
    srcs=["connect_four.cc"],
    deps=["connect_four_lib"],
)
