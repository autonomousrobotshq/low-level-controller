#!/bin/sh

BASEDIR=$(realpath $(dirname "$0"))

MSG_DST_DIR=$BASEDIR/../Libraries/External/Messages/
GIT_REPO="git@github.com:autonomousrobotshq/ros_packages.git"
GIT_TARGET_DIR="llc_messages"

TMP_DIR=`mktemp -d`
cd $TMP_DIR

# source: https://stackoverflow.com/questions/600079/how-do-i-clone-a-subdirectory-only-of-a-git-repository/52269934
git clone \
  --depth 1 \
  --filter=blob:none \
  --no-checkout \
  $GIT_REPO \
  $TMP_DIR \
;
cd $TMP_DIR
git checkout master -- $GIT_TARGET_DIR || { echo "Failed to checkout $GIT_TARGET_DIR" && exit 1; }
mkdir src && cd src && catkin_init_workspace && cd ..
mv $GIT_TARGET_DIR ./src

mkdir messages && catkin_make && rosrun rosserial_client make_libraries ./messages || { echo "Are you sure you sourced the rosserial setup.zsh in your catkin_ws?" && exit 1; }

pwd
mv ./messages/ros_lib/llc_messages/* $MSG_DST_DIR && rm -rf $TMP_DIR
