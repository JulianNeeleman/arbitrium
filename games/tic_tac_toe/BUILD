# Tic Tac Toe implementation.
cc_library(
    name="tic_tac_toe_lib",
    srcs=glob(["**/*.cc"]),
    hdrs=glob(["**/*.h"]),
    deps=[
        "//lib:arbitrium_lib",
        "//players:players_lib",
    ],
)

cc_binary(
    name="tic_tac_toe",
    srcs=["tic_tac_toe.cc"],
    deps=["tic_tac_toe_lib"],
)
