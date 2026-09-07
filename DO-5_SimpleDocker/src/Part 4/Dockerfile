FROM nginx:latest

WORKDIR /server/

RUN apt-get update && apt-get install -y gcc libfcgi-dev spawn-fcgi

COPY ./file.c /server/
COPY ./nginx/nginx.conf /etc/nginx/

RUN gcc -o file.fcgi file.c -lfcgi

CMD spawn-fcgi -p 8080/server/file.fcgi && nginx -g 'daemon off;'