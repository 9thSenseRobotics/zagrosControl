FILE(REMOVE_RECURSE
  "src/zagrosControl/msg"
  "src/zagrosControl/srv"
  "msg_gen"
  "srv_gen"
  "msg_gen"
  "srv_gen"
  "CMakeFiles/ROSBUILD_gensrv_lisp"
  "srv_gen/lisp/telo_state.lisp"
  "srv_gen/lisp/_package.lisp"
  "srv_gen/lisp/_package_telo_state.lisp"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/ROSBUILD_gensrv_lisp.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
