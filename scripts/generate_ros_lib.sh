#!/bin/zsh

echo "Don't forget to source setup.zsh or setup.bash first!"

BASEDIR=$(realpath $(dirname "$0"))

ROSLIB_DST_DIR=$BASEDIR/../Libraries/ROS-Generated
GIT_REPO="git@github.com:autonomousrobotshq/ros_packages.git"
GIT_REPO_NAME="ros_packages"

TMP_DIR=`mktemp -d`
cd $TMP_DIR && pwd || exit 1

git clone $GIT_REPO $GIT_REPO_NAME || exit 1
cd $GIT_REPO_NAME && git submodule update --init --recursive && cd $TMP_DIR || exit 1

mkdir src && cd src && catkin_init_workspace && cd .. || exit 1
mv $GIT_REPO_NAME ./src || exit 1

catkin_make && source ./devel/setup.zsh && rosrun rosserial_arduino make_libraries.py .  || exit 1

mv $ROSLIB_DST_DIR/library.properties ./ros_lib/ || exit 1
rm -rf $ROSLIB_DST_DIR && mkdir $ROSLIB_DST_DIR || exit 1
mv ./ros_lib/* $ROSLIB_DST_DIR && rm -rf $TMP_DIR

find $ROSLIB_DST_DIR \( -type d -name .git -prune \) -o -type f -print0 | xargs -0 sed -i 's/cstring/string\.h/g'
find $ROSLIB_DST_DIR \( -type d -name .git -prune \) -o -type f -print0 | xargs -0 sed -i 's/std::memcpy/memcpy/g'
