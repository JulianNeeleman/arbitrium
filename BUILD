# Core algorithms library.
cc_library(
    name = "arbitrium_lib",
    srcs = glob(["src/lib/**/*.cc"]),
    hdrs = glob(["include/lib/**/*.h"]),
)

# Tic Tac Toe implementation.
cc_library(
    name = "tic_tac_toe_lib",
    srcs = glob(["src/tic_tac_toe_*.cc"]),
    hdrs = glob(["include/tic_tac_toe_*.h"]),
    deps = ["arbitrium_lib"],
)
