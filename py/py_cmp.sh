#! /bin/bash

# echo "参数1："$1
# echo "参数2："$2
# echo "参数个数："$#

echo "python -m compileall"$1
python -m compileall $1
