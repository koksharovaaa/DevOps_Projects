#!/bin/bash

TG_TOKEN=definitelyatoken
TG_ID=definitelyanid
URL="https://api.telegram.org/bot${TG_TOKEN}/sendMessage"
TEXT="Project: ${CI_PROJECT_NAME}%0A${1}: ${2}"

curl -s -d "chat_id=$TG_ID&disable_web_page_preview=1&text=$TEXT" $URL > /dev/null
