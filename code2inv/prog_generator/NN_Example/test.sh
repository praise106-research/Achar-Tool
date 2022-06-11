echo "\$LD_LIBRARY_PATH is"
echo $LD_LIBRARY_PATH

if [ -z $CUDA_PATH ]; then
  echo "\$CUDA_PATH is not set"
  ls /usr/local/cuda/lib64 | grep libnvrtc-builtins.so
else
  echo "\$CUDA_PATH is set."
  echo $CUDA_PATH
  ls $CUDA_PATH/lib64 | grep libnvrtc-builtins.so
fi
