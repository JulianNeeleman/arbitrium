# Core algorithms library.
cc_library(
    name = "arbitrium_lib",
    srcs = glob(["src/lib/**/*.cc"]),
    hdrs = glob(["include/lib/**/*.h"]),
)

# Tic Tac Toe implementation.
cc_library(
    name = "tic_tac_toe_lib",
    srcs = glob(["src/tic_tac_toe/**/*.cc"]),
    hdrs = glob(["include/tic_tac_toe/**/*.h"]),
    deps = ["arbitrium_lib"],
)

cc_binary(
    name = "tic_tac_toe",
    srcs = ["games/tic_tac_toe.cc"],
    deps = ["tic_tac_toe_lib"],
)
