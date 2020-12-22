#!/bin/zsh

BASEDIR=$(realpath $(dirname "$0"))

MSG_DST_DIR=$BASEDIR/../Libraries/External/Roslib-Generated
GIT_REPO="git@github.com:autonomousrobotshq/ros_packages.git"
GIT_REPO_NAME="ros_packages"

ROS_SERIAL_VERSION=0.9.1
ROS_SERIAL="https://github.com/ros-drivers/rosserial/archive/$ROS_SERIAL_VERSION.zip"
ROS_SERIAL_NAME="rosserial-$ROS_SERIAL_VERSION"

TMP_DIR=`mktemp -d`
cd $TMP_DIR && pwd || exit 1

git clone $GIT_REPO $GIT_REPO_NAME || exit 1
cd $GIT_REPO_NAME && git submodule update --init --recursive && cd $TMP_DIR || exit 1
wget $ROS_SERIAL && unzip $ROS_SERIAL_VERSION.zip || exit 1

mkdir src && cd src && catkin_init_workspace && cd .. || exit 1
mv $GIT_REPO_NAME ./src && mv $ROS_SERIAL_NAME ./src || exit 1

catkin_make && source ./devel/setup.zsh &&  rosrun rosserial_arduino make_libraries.py .  || exit 1

rm -rf $MSG_DST_DIR && mkdir $MSG_DST_DIR || exit 1
mv ./ros_lib/* $MSG_DST_DIR && rm -rf $TMP_DIR

find $MSG_DST_DIR \( -type d -name .git -prune \) -o -type f -print0 | xargs -0 sed -i 's/cstring/string\.h/g'
find $MSG_DST_DIR \( -type d -name .git -prune \) -o -type f -print0 | xargs -0 sed -i 's/std::memcpy/memcpy/g'
