FILE(REMOVE_RECURSE
  "src/zagrosControl/msg"
  "src/zagrosControl/srv"
  "msg_gen"
  "srv_gen"
  "msg_gen"
  "srv_gen"
  "CMakeFiles/ROSBUILD_genmsg_lisp"
  "msg_gen/lisp/telo_state.lisp"
  "msg_gen/lisp/_package.lisp"
  "msg_gen/lisp/_package_telo_state.lisp"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/ROSBUILD_genmsg_lisp.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
