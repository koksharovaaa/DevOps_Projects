#!/bin/bash

set -e

DEPLOY_USER="root"
DEPLOY_HOST="192.168.100.11"
DEPLOY_PATH="/usr/local/bin"

scp src/Simple_Bash/cat/s21_cat ${DEPLOY_USER}@${DEPLOY_HOST}:${DEPLOY_PATH}
scp src/Simple_Bash/grep/s21_grep ${DEPLOY_USER}@${DEPLOY_HOST}:${DEPLOY_PATH}

ssh ${DEPLOY_USER}@${DEPLOY_HOST} ls -lah ${DEPLOY_PATH}
