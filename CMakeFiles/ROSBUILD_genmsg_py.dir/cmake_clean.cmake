FILE(REMOVE_RECURSE
  "src/zagrosControl/msg"
  "src/zagrosControl/srv"
  "msg_gen"
  "srv_gen"
  "msg_gen"
  "srv_gen"
  "CMakeFiles/ROSBUILD_genmsg_py"
  "src/zagrosControl/msg/__init__.py"
  "src/zagrosControl/msg/_telo_state.py"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/ROSBUILD_genmsg_py.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
